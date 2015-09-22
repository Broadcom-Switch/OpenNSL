/*
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to
 * you under the terms of the GNU General Public License version 2 (the
 * "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
 * with the following added to such license:
 * 
 * As a special exception, the copyright holders of this software give
 * you permission to link this software with independent modules, and to
 * copy and distribute the resulting executable under terms of your
 * choice, provided that you also meet, for each linked independent
 * module, the terms and conditions of the license of that module.  An
 * independent module is a module which is not derived from this
 * software.  The special exception does not apply to any modifications
 * of the software.
 */
/*
 * $Id: bcm-knet.h,v 1.4 Broadcom SDK $
 * $Copyright: (c) 2005 Broadcom Corp.
 * All Rights Reserved.$
 */
#ifndef __LINUX_BCM_KNET_H__
#define __LINUX_BCM_KNET_H__

#ifndef __KERNEL__
#include <stdint.h>
#endif

typedef struct  {
    int rc;
    int len;
    int bufsz;
    int reserved;
    uint64_t buf;
} bkn_ioctl_t;

#ifdef __KERNEL__

/*
 * Call-back interfaces for other Linux kernel drivers.
 */
#include <linux/skbuff.h>

typedef struct sk_buff *
(*knet_skb_cb_f)(struct sk_buff *skb, int dev_no, void *meta);

typedef int
(*knet_filter_cb_f)(uint8_t *pkt, int size, int dev_no, void *meta,
                    int chan, kcom_filter_t *filter);

extern int
bkn_rx_skb_cb_register(knet_skb_cb_f rx_cb);

extern int
bkn_rx_skb_cb_unregister(knet_skb_cb_f rx_cb);

extern int
bkn_tx_skb_cb_register(knet_skb_cb_f tx_cb);

extern int
bkn_tx_skb_cb_unregister(knet_skb_cb_f tx_cb);

extern int
bkn_filter_cb_register(knet_filter_cb_f filter_cb);

extern int
bkn_filter_cb_unregister(knet_filter_cb_f filter_cb);

#endif

#endif /* __LINUX_BCM_KNET_H__ */
