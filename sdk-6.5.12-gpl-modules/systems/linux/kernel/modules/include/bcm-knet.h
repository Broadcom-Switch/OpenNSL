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

typedef struct {
    uint32 netif_user_data;
    uint32 filter_user_data;
    uint16 dcb_type;
} knet_skb_cb_t;

#define KNET_SKB_CB(__skb) ((knet_skb_cb_t *)&((__skb)->cb[0]))

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
