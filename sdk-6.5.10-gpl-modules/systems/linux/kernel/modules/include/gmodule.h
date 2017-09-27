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
