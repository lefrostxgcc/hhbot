bin_PROGRAMS = hhbot
hhbot_SOURCES = main.c
hhbot_CPPFLAGS = -I$(top_srcdir)/lib @PKGGTK_CFLAGS@ $(AM_CPPFLAGS)
hhbot_CFLAGS = $(AM_CFLAGS)
hhbot_LDFLAGS= $(PKGGTK_LDFLAGS) $(AM_LDFLAGS)			 
hhbot_LDADD = ../lib/libhhapi.la @PKGGTK_LIBS@ 
