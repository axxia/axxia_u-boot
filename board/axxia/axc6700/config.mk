PLATFORM_RELFLAGS += -fno-strict-aliasing -Werror

# Only available in gcc 5 and the latest (as yet unreleased) binutils.
#PLATFORM_LDFLAGS += --fix-cortex-a53-843419 --fix-cortex-a53-835769
#KBUILD_CFLAGS += -mfix-cortex-a53-843419 -mfix-cortex-a53-835769

ifdef CROSS_LIBS
PLATFORM_LDFLAGS += -L $(CROSS_LIBS)
endif

ifdef AXXIA_VERSION
KBUILD_CFLAGS += -DAXXIA_VERSION='"$(AXXIA_VERSION)"'
endif

ifdef AXXIA_ATF_VERSION
KBUILD_CFLAGS += -DAXXIA_ATF_VERSION='"$(AXXIA_ATF_VERSION)"'
endif