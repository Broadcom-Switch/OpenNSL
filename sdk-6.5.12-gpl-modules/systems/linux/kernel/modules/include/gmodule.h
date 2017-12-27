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
 * $Id: gmodule.h,v 1.9 Broadcom SDK $
 * $Copyright: (c) 2005 Broadcom Corp.
 * All Rights Reserved.$
 */

#ifndef __COMMON_LINUX_KRN_GMODULE_H__
#define __COMMON_LINUX_KRN_GMODULE_H__

#include <lkm.h>

typedef struct gmodule_s {
  
    const char* name;
    int         major;
    int		minor; 

    int (*init)(void);
    int (*cleanup)(void);
  
    int (*pprint)(void);
  
    int (*open)(void);
    int (*ioctl)(unsigned int cmd, unsigned long arg);
    int (*close)(void);
    int (*mmap) (struct file *filp, struct vm_area_struct *vma);

} gmodule_t;
  

/* The framework will ask for your module definition */
extern gmodule_t* gmodule_get(void);


/* Proc Filesystem information */
extern int pprintf(const char* fmt, ...)
    __attribute__ ((format (printf, 1, 2)));
extern int gmodule_vpprintf(char** page, const char* fmt, va_list args)
    __attribute__ ((format (printf, 2, 0)));
extern int gmodule_pprintf(char** page, const char* fmt, ...)
    __attribute__ ((format (printf, 2, 3)));

extern int gprintk(const char* fmt, ...)
    __attribute__ ((format (printf, 1, 2)));

extern int gdbg(const char* fmt, ...)
    __attribute__ ((format (printf, 1, 2)));
#define GDBG gdbg

#endif /* __COMMON_LINUX_KRN_GMODULE_H__ */
