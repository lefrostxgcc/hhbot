bin_PROGRAMS = hhbot hhbot_wpf hh_prof
hhbot_SOURCES = main.c
hhbot_CPPFLAGS = -I$(top_srcdir)/lib @PKGGTK_CFLAGS@ $(AM_CPPFLAGS)
hhbot_CFLAGS = $(AM_CFLAGS)
hhbot_LDFLAGS= $(PKGGTK_LDFLAGS) $(AM_LDFLAGS)			 
hhbot_LDADD = ../lib/libhhapi.la @PKGGTK_LIBS@

hhbot_wpf_SOURCES = main_wpf.c resources_wpf.c
hhbot_wpf_CPPFLAGS = -I$(top_srcdir)/lib @PKGGTK_CFLAGS@ $(AM_CPPFLAGS)
hhbot_wpf_CFLAGS = $(AM_CFLAGS)
hhbot_wpf_LDFLAGS= $(PKGGTK_LDFLAGS) $(AM_LDFLAGS)			 
hhbot_wpf_LDADD = ../lib/libhhapi.la @PKGGTK_LIBS@

hh_prof_SOURCES = main_prof.c resources_prof.c
hh_prof_CPPFLAGS = -I$(top_srcdir)/lib @PKGGTK_CFLAGS@ $(AM_CPPFLAGS)
hh_prof_CFLAGS = $(AM_CFLAGS)
hh_prof_LDFLAGS= $(PKGGTK_LDFLAGS) $(AM_LDFLAGS)			 
hh_prof_LDADD = ../lib/libhhapi.la @PKGGTK_LIBS@ 

EXTRA_DIST = resources_wpf.xml wpf.css resources_prof.xml hh_prof.css 

resources_wpf.c: resources_wpf.xml wpf.css
	glib-compile-resources --generate-source --sourcedir=$(srcdir) \
$(srcdir)/resources_wpf.xml

resources_prof.c: resources_prof.xml hh_prof.css
	glib-compile-resources --generate-source --sourcedir=$(srcdir) \
$(srcdir)/resources_prof.xml
