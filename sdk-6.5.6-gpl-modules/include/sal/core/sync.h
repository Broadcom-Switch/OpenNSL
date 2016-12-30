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
 * $Id: sync.h,v 1.1 Broadcom SDK $
 * $Copyright: (c) 2005 Broadcom Corp.
 * All Rights Reserved.$
 */

#ifndef _SAL_SYNC_H
#define _SAL_SYNC_H

typedef struct sal_sem_s{
    char sal_opaque_type;
} *sal_sem_t;

#define sal_sem_FOREVER		(-1)
#define sal_sem_BINARY		1
#define sal_sem_COUNTING	0

sal_sem_t	sal_sem_create(char *desc, int binary, int initial_count);
void		sal_sem_destroy(sal_sem_t b);
int		sal_sem_take(sal_sem_t b, int usec);
int		sal_sem_give(sal_sem_t b);

#endif	/* !_SAL_SYNC_H */
