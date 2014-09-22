##
## (C) Copyright 2000-2003
## Wolfgang Denk, DENX Software Engineering, wd@denx.de.
##
## See file CREDITS for list of people who contributed to this
## project.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation; either version 2 of
## the License, or (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston,
## MA 02111-1307 USA
##

obj-y := reset.o
obj-y += timer.o

#
#include $(TOPDIR)/config.mk
#
#LIB	= $(obj)libaxxia-common.o
#
#obj-y	:= reset.o
#obj-y	+= utils.o
#
#ifneq ($(CONFIG_OMAP44XX)$(CONFIG_OMAP54XX)$(CONFIG_AXXIA_ARM),)
#obj-y	+= hwinit-common.o
#obj-y	+= clocks-common.o
#obj-y	+= emif-common.o
#obj-y	+= vc.o
#endif
#
##ifndef CONFIG_AXXIA_ARM
##obj-y	+= timer.o
##endif
#
#ifneq ($(CONFIG_AM33XX)$(CONFIG_OMAP44XX)$(CONFIG_OMAP54XX),)
#obj-y	+= boot-common.o
#obj-y	+= lowlevel_init.o
#endif
#
#ifndef CONFIG_SPL_BUILD
#ifneq ($(CONFIG_OMAP44XX)$(CONFIG_OMAP54XX),)
#obj-y	+= mem-common.o
#endif
#endif
#
#SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
#OBJS	:= $(addprefix $(obj),$(SOBJS) $(COBJS))
#
#all:	$(obj).depend $(LIB)
#
#$(LIB):	$(OBJS)
#	$(call cmd_link_o_target, $(OBJS))
#
##########################################################################
#
## defines $(obj).depend target
##include $(SRCTREE)/rules.mk
#
##sinclude $(obj).depend
#
##########################################################################
