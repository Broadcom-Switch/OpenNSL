/*
 * Copyright 2017 Broadcom
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 (GPLv2) for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 (GPLv2) along with this source code.
 */
/*
 * $Id:
 * $Copyright: (c) 2017 Broadcom Corp.
 * All Rights Reserved.$
 */

/*
 * Driver for call-back functions for Linux KNET driver.
 *
 * This is sample code that demonstrates how to selectively strip VLAN tags
 * from an incoming packet based on tag information in the DMA control block
 * (DCB). The switch will automatically add a VLAN tag to packets that ingress
 * without an outer VLAN tag. Outer tagged and double tagged packets are
 * not modified. The call back defined here determines which packets have
 * had tags added by those and strips only those tags from the packet.
 *
 * This is sample code, the customer is responsible for maintaining and
 * modifying this code as necessary.
 *
 * The module can be built from the standard Linux user mode target
 * directories using the following command (assuming bash), e.g.
 *
 *   cd $SDK/systems/linux/user/<target>
 *   make BUILD_KNET_CB=1
 *
 */

#include <gmodule.h> /* Must be included first */
#include <kcom.h>
#include <bcm-knet.h>
#include <linux/if_vlan.h>

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom Linux KNET Call-Back Driver");
MODULE_LICENSE("GPL");

/* Module Information */
#define MODULE_MAJOR 121
#define MODULE_NAME "linux-knet-cb"

/* set KNET_CB_DEBUG for debug info */
#define KNET_CB_DEBUG

/* Maintain tag strip statistics */
struct strip_stats_s {
    unsigned long stripped;     /* Number of packets that have been stripped */
    unsigned long checked;
    unsigned long skipped;
};

static struct strip_stats_s strip_stats;

/* Local function prototypes */
static void strip_vlan_tag(struct sk_buff *skb);
static int  get_tag_status(int dcb_type, void *meta);
static struct sk_buff *strip_tag_rx_cb(struct sk_buff *skb, int dev_no, void *meta);
static struct sk_buff *strip_tag_tx_cb(struct sk_buff *skb, int dev_no, void *meta);
static int  strip_tag_filter_cb(uint8_t * pkt, int size, int dev_no, void *meta,
                                int chan, kcom_filter_t * kf);
static int  _pprint(void);
static int  _cleanup(void);
static int  _init(void);

/* Remove VLAN tag for select TPIDs */
static void
strip_vlan_tag(struct sk_buff *skb)
{
    uint16_t    vlan_proto = (uint16_t) ((skb->data[12] << 8) | skb->data[13]);
    if ((vlan_proto == 0x8100) || (vlan_proto == 0x88a8) || (vlan_proto == 0x9100)) {
        /* Move first 12 bytes of packet back by 4 */
        ((u32 *) skb->data)[3] = ((u32 *) skb->data)[2];
        ((u32 *) skb->data)[2] = ((u32 *) skb->data)[1];
        ((u32 *) skb->data)[1] = ((u32 *) skb->data)[0];
        skb_pull(skb, 4);       /* Remove 4 bytes from start of buffer */
    }
}

/*
 * Location of tagging status in select DCB types found below:
 *
 * DCB type 14: word 12, bits 10.11
 * DCB type 19, 20, 21, 22, 30: word 12, bits 10..11
 * DCB type 23, 29: word 13, bits 0..1 
 * DCB type 31, 34, 37: word 13, bits 0..1
 * DCB type 26, 32, 33, 35: word 13, bits 0..1
 *
 * The function get_tag_status() returns the tag status for known DCB types.
 * 0 = Untagged
 * 1 = Single inner-tag
 * 2 = Single outer-tag
 * 3 = Double tagged.
 * -1 = Unsupported DCB type
 */
static int
get_tag_status(int dcb_type, void *meta)
{
    uint32     *dcb = (uint32 *) meta;
    int         tag_status;
    switch (dcb_type) {
      case 14:
      case 19:
      case 20:
      case 21:
      case 22:
      case 30:
          tag_status = (dcb[12] > 10) & 0x3;
          break;
      case 23:
      case 29:
      case 31:
      case 34:
      case 37:
      case 26:
      case 32:
      case 33:
      case 35:
          tag_status = dcb[13] & 0x3;
          break;
      default:
          tag_status = -1;
          break;
    }
    return tag_status;
}

/*
 * SDK-134189 added the ability to pass two 4 byte unsigned values to the
 * KNET callback function, one from the matching filter and one from the
 * network interface. The usage of this data is completely defined by the
 * user. In this case, if bit 0 of the interface value is set, tag stripping
 * is enabled for that interface. When creating the interface and filter,
 * something like the following is necessary: "netif.cb_user_data = uflags".
 */
#define NETIF_UNTAGGED_STRIP  (1 << 0)

/* Rx packet callback function */
static struct sk_buff *
strip_tag_rx_cb(struct sk_buff *skb, int dev_no, void *meta)
{
    unsigned    netif_flags = KNET_SKB_CB(skb)->netif_user_data;
    unsigned    dcb_type;
    int         tag_status;
    /* Currently not using filter flags:
     * unsigned    filter_flags = KNET_SKB_CB(skb)->filter_user_data;
     */

#ifdef KNET_CB_DEBUG
    gprintk("%s Enter; Flags: %08X\n", __func__, netif_flags);
#endif

    if ((netif_flags & NETIF_UNTAGGED_STRIP) == 0) {
        /* Untagged stripping not enabled on this netif */
        strip_stats.skipped++;
        return skb;
    }

    /* Get DCB type for this packet, passed by KNET driver */
    dcb_type = KNET_SKB_CB(skb)->dcb_type;

    /* Get tag status from DCB */
    tag_status = get_tag_status(dcb_type, meta);

#ifdef KNET_CB_DEBUG
    gprintk("%s; DCB Type: %d; tag status: %d\n", __func__, dcb_type, tag_status);
#endif

    if (tag_status < 0) {
        /* Unsupported DCB type */
        return skb;
    }

    strip_stats.checked++;
    /*
     * Untagged and inner tagged packet will get a new tag from the switch
     * device, we need to strip this off.
     */
    if (tag_status < 2) {
#ifdef KNET_CB_DEBUG
        gprintk("%s; Stripping VLAN\n", __func__);
#endif
        strip_stats.stripped++;
        strip_vlan_tag(skb);
    }
#ifdef KNET_CB_DEBUG
    else {
        gprintk("%s; Preserve VLAN\n", __func__);
    }
#endif
    return skb;
}

/* Tx callback not used */
static struct sk_buff *
strip_tag_tx_cb(struct sk_buff *skb, int dev_no, void *meta)
{
    /* Pass through for now */
    return skb;
}

/* Filter callback not used */
static int
strip_tag_filter_cb(uint8_t * pkt, int size, int dev_no, void *meta,
               int chan, kcom_filter_t *kf)
{
    /* Pass through for now */
    return 0;
}

/*
 * Get statistics.
 * % cat /proc/linux-knet-cb
 */
static int
_pprint(void)
{   
    pprintf("Broadcom Linux KNET Call-Back: Untagged VLAN Stripper\n");
    pprintf("    %lu stripped packets\n", strip_stats.stripped);
    pprintf("    %lu packets checked\n", strip_stats.checked);
    pprintf("    %lu packets skipped\n", strip_stats.skipped);

    return 0;
}

static int
_cleanup(void)
{
    bkn_rx_skb_cb_unregister(strip_tag_rx_cb);
    bkn_tx_skb_cb_unregister(strip_tag_tx_cb);
    bkn_filter_cb_unregister(strip_tag_filter_cb);

    return 0;
}   

static int
_init(void)
{
    bkn_rx_skb_cb_register(strip_tag_rx_cb);
    bkn_tx_skb_cb_register(strip_tag_tx_cb);
    bkn_filter_cb_register(strip_tag_filter_cb);

    return 0;
}

static gmodule_t _gmodule = {
    name: MODULE_NAME, 
    major: MODULE_MAJOR, 
    init: _init,
    cleanup: _cleanup, 
    pprint: _pprint, 
    ioctl: NULL,
    open: NULL, 
    close: NULL, 
}; 

gmodule_t*
gmodule_get(void)
{
    EXPORT_NO_SYMBOLS;
    return &_gmodule;
}
