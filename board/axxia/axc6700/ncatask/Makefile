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

ccflags-y += -D_GNU_SOURCE -DNCP_USE_NVM -DNCP_MULTI_THREAD -DNCP_LINUX -DUSE_NCAV3 
ccflags-y += -I$(srctree)/board/axxia/axc6700/ncatask/include -I$(srctree)/board/axxia/axc6700/ncatask/include/uboot/

obj-y += mdio.o eioa.o
obj-y += ncp.o mp_free.o mp_malloc.o mp_mstats.o mp_realloc.o ncp_vpm.o 
obj-y += ncp_sal.o ncp_task.o ncp_config_uboot.o ncp_task_pvt.o ncp_task_pvt_user.o
obj-y += ncp_sal_linux.o ncp_dev_linux_user.o
endif

