#
# (C) Copyright 2000, 2001, 2002
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).o
COBJS   =
SOBJS   =

ifndef CONFIG_SPL_BUILD

################################################################################
## Normal Build

COBJS += axxia.o mdio.o phy.o usb_phy.o non_secure.o timer_init.o

ifdef CONFIG_AXXIA_PCI
COBJS += pcie.o
endif

ifdef CONFIG_AXXIA_EIOA
COBJS += eioa.o ncp_task_config_axm55xx.o ncp_task_axm55xx.o 
COBJS += ncp_task_api_entry.o ncp_task_uboot_config_axm55xx.o
endif

SOBJS += smp.o

else

################################################################################
## SPL Build

ifdef CONFIG_AXXIA_55XX
ifndef CONFIG_AXXIA_EMU
COBJS += voltage.o pciesrio.o
endif
endif

COBJS   += mbist_range.o spl.o axxia_initialize.o

endif

################################################################################
## All Builds

COBJS   += failure.o axxia_clocks.o outer_cache.o spi.o debug.o sbb.o vat.o
SOBJS   += lowlevel.o monitor.o

ifdef CONFIG_HW_WATCHDOG
COBJS += watchdog.o
endif

################################################################################

COBJS	:= $(addprefix $(obj),$(COBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(COBJS) $(SOBJS)
	$(call cmd_link_o_target, $(COBJS) $(SOBJS))

clean:
	rm -f $(COBJS) $(SOBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

# defines $(obj).depend target
include $(SRCTREE)/rules.mk
sinclude $(obj).depend
