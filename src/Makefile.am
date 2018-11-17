bin_PROGRAMS = hhbot hhbot_wpf
hhbot_SOURCES = main.c
hhbot_CPPFLAGS = -I$(top_srcdir)/lib @PKGGTK_CFLAGS@ $(AM_CPPFLAGS)
hhbot_CFLAGS = $(AM_CFLAGS)
hhbot_LDFLAGS= $(PKGGTK_LDFLAGS) $(AM_LDFLAGS)			 
hhbot_LDADD = ../lib/libhhapi.la @PKGGTK_LIBS@

hhbot_wpf_SOURCES = main_wpf.c resources.c
hhbot_wpf_CPPFLAGS = -I$(top_srcdir)/lib @PKGGTK_CFLAGS@ $(AM_CPPFLAGS)
hhbot_wpf_CFLAGS = $(AM_CFLAGS)
hhbot_wpf_LDFLAGS= $(PKGGTK_LDFLAGS) $(AM_LDFLAGS)			 
hhbot_wpf_LDADD = ../lib/libhhapi.la @PKGGTK_LIBS@ 

EXTRA_DIST = resources.xml wpf.css

resources.c: resources.xml wpf.css
	glib-compile-resources --generate-source --sourcedir=$(srcdir) $(srcdir)/resources.xml
