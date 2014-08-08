#
# (C) Copyright 2006
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

.PHONY: version

ifneq ($(OBJTREE),$(SRCTREE))
$(shell mkdir -p $(obj)board/$(VENDOR)/common)
endif

LIB	= $(obj)lib$(VENDOR).a

ifdef CONFIG_LSI_NET
COBJS   := phy.o version.o femac.o
else
COBJS   := version.o
endif

SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak $(obj).depend

version.c: version

$(obj)version.o: version.c
	$(CC) $(CFLAGS) -c -o $@ $<

version: version.c.in
	@git --version >/dev/null 2>&1 ; \
	if [ 0 -ne $$? ] ; then \
		echo "ERROR: git is not available, version UNKNOWN" ; \
		VERSION_STRING="UNKNOWN" ; \
	else \
		VERSION_STRING=`git describe --dirty 2>/dev/null` ; \
		if [ 0 -ne $$? ] ; then \
			echo "ERROR: not in a repository, version UNKNOWN" ; \
			VERSION_STRING="UNKNOWN" ; \
		fi ; \
	fi ; \
	sed -e s/GIT_VERSION_STRING/$$VERSION_STRING/ version.c.in >version.c

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
