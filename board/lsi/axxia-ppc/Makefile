################################################################################
#
# Copyright (C) 2013 LSI Corporation (john.jacques@lsi.com)
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
################################################################################

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).o

ifndef CONFIG_SPL_BUILD

################################################################################
## Normal Build

COBJS = splash.o dt.o spintable.o os_access.o ipi.o
COBJS += ose.o nvram.o osg.o locks.o i2c.o pcie.o ncp_task_lite.o
COBJS += ncp_task_lite_uboot.o

ifdef CONFIG_AXXIA_EIOA
COBJS  += eioa.o
endif

SOBJS = util.o ipi.o acp_static.o

else

################################################################################
## SPL Build

COBJS = acp_init.o boot_spl.o

SOBJS = brs.o

endif

################################################################################
## All Builds

COBJS += dcr.o ncr.o ssp.o sbb.o reset.o clocks.o acp_failure.o mdio.o nand.o
COBJS += pciesrio.o version.o

SOBJS += acp_start.o

COBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(COBJS) $(SOBJS)
	$(call cmd_link_o_target, $(COBJS) $(SOBJS))

clean:
	rm -f $(SOBJS) $(COBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

# defines $(obj).depend target
include $(SRCTREE)/rules.mk
sinclude $(obj).depend
