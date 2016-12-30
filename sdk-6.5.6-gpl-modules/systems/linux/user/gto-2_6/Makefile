#
#  Unless you and Broadcom execute a separate written software license
#  agreement governing use of this software, this software is licensed to
#  you under the terms of the GNU General Public License version 2 (the
#  "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
#  with the following added to such license:
#  
#  As a special exception, the copyright holders of this software give
#  you permission to link this software with independent modules, and to
#  copy and distribute the resulting executable under terms of your
#  choice, provided that you also meet, for each linked independent
#  module, the terms and conditions of the license of that module.  An
#  independent module is a module which is not derived from this
#  software.  The special exception does not apply to any modifications
#  of the software.
#
# -*- Makefile -*-
# $Id: Makefile,v 1.9 Broadcom SDK $
# $Copyright: (c) 2007 Broadcom Corp.
# All Rights Reserved.$

#
# This make job requires the following environment variables to be set:
#
# SDK                - path to StrataXGS SDK root directory
#
# Optionally the following environment variables can be set to
# override the default build server configuration:
#
# PPC_TOOLS_DIR      - path to build tools (if not in PATH already)
# PPC_CROSS_COMPILE  - cross compile tools prefix
# LINUX_INCLUDE      - path to Linux kernel include directory
#

SDK :=$(shell if [ -n "$$SDK" ] ; then\
	echo $$SDK;\
	else\
	cd $(dir $(lastword $(MAKEFILE_LIST))); while /usr/bin/test ! -e RELEASE ; do \
	dir=`cd ../;pwd`;			\
	if [ "$$dir" = "/" ] ; then		\
	   echo Cannot find SDK in $(lastword $(MAKEFILE_LIST)) 1>&2;		\
	   exit 1;				\
	fi ;					\
	cd $$dir;				\
	done ;					\
	pwd;					\
	fi)

ifeq ($(SDK),)					
$(error Please run this in a tree)		
endif 				

export SDK

override kernel_version=2_6
platform=gto-$(kernel_version)
LINUX_MAKE_USER=1
export LINKER_RELAX=1

# Select the build environment
#BUILD_PLATFORM=ELDK
#BUILD_PLATFORM=WR_LINUX

#Select the LINUX KERNEL VERSION
#KERN_VER = 2.6.21.7
#KERN_VER = 2.6.24.4
#KERN_VER = 2.6.25


# Select the ELDK version
#ELDK_VERSION=4.1
#ELDK_VERSION=4.0

#Select WRS Linux version
#WRS_LINUX_VERSION=2.0
#WRS_LINUX_VERSION=3.0


export KERN_VER
export ELDK_VERSION
export BUILD_PLATFORM
export WRS_LINUX_VERSION

include ${SDK}/make/Make.linux

