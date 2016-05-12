ACLOCAL_AMFLAGS = -I m4

# pkg config system
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = tinyscheme.pc

AM_CPPFLAGS = -std=c99 -DSUN_DL=1

# meta library name used by libtool
lib_LTLIBRARIES=libtinyscheme.la
libtinyscheme_la_LDFLAGS = -release $(VERSION) -version-info 0:0:0
libtinyscheme_la_LIBADD = -ldl

# the rest of the sources goes into distribution (make dist)
libtinyscheme_la_SOURCES = \
	scheme.c \
	dynload.c

# startup file
startupdir = $(sysconfdir)
startup_DATA = init.scm

# installed header files
libtinyscheme_includedir=$(includedir)/tinyscheme
libtinyscheme_include_HEADERS=scheme.h dynload.h scheme-private.h opdefines.h
EXTRA_DIST=$(libtinyscheme_include_HEADERS) $(startup_DATA)
