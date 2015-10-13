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

ifndef CONFIG_SPL_BUILD

################################################################################
## Normal Build

#obj-y += axxia.o mdio.o phy.o usb_phy.o non_secure.o timer_init.o
obj-y += axxia.o mdio.o phy.o non_secure.o timer_init.o

ifdef CONFIG_AXXIA_EIOA
obj-y += eioa.o ncp_task_config_axm55xx.o ncp_task_axm55xx.o
obj-y += ncp_task_api_entry.o ncp_task_uboot_config_axm55xx.o
endif

obj-y += smp.o

else

################################################################################
## SPL Build

ifdef CONFIG_AXXIA_55XX
ifndef CONFIG_AXXIA_EMU
#obj-y += voltage.o pciesrio.o
endif
endif

obj-y   += mbist_range.o spl.o axxia_initialize.o

endif

################################################################################
## All Builds

#obj-y   += failure.o version.o axxia_clocks.o cache.o spi.o sbb.o vat.o
obj-y   += failure.o version.o axxia_clocks.o cache.o outer_cache.o spi.o vat.o
#obj-y   += lowlevel.o monitor.o tables.o
obj-y   += sbb.o lowlevel.o

ifdef CONFIG_HW_WATCHDOG
obj-y += watchdog.o
endif
