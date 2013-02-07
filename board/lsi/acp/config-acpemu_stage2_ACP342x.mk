################################################################################
# (C) Copyright 2009
# LSI <www.lsi.com>
# John Jacques <john.jacques@lsi.com>
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
################################################################################

TEXT_BASE = 0xf0a00020

PLATFORM_CPPFLAGS += -DLSI -DACP -DACP2 -DACP_EMU -DACP_X2V1

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif

ifeq ($(dbcr),1)
PLATFORM_CPPFLAGS += -DCFG_INIT_DBCR=0x8cff0000
endif

LDSCRIPT := $(SRCTREE)/board/lsi/acp/u-boot-acp2.lds
