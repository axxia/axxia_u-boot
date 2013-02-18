#
# (C) Copyright 2002-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).o

COBJS += acp_failure.o dcr.o nand.o ssp.o mdio.o splash.o
COBJS += ncr.o version.o reset.o clocks.o pciesrio.o sbb.o
SOBJS = acp_start.o util.o ipi.o

ifdef CONFIG_ACP3
COBJS  += dt.o spintable.o os_access.o ose.o nvram.o osg.o locks.o i2c.o pcie.o
COBJS  += ncp_task_lite.o ncp_task_lite_uboot.o
SOBJS  += acp_static.o
endif

ifdef CONFIG_AXXIA_EIOA
COBJS  += eioa.o
endif

ifdef CONFIG_ACP3
COBJS += ipi.o
endif

ifdef CONFIG_SPL_BUILD
COBJS = acp_init.o ncr.o acp_failure.o
SOBJS = brs.o
endif

COBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(COBJS) $(SOBJS)
	$(call cmd_link_o_target, $(COBJS) $(SOBJS))

clean:
	rm -f $(SOBJS) $(COBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
