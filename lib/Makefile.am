lib_LTLIBRARIES = libhhapi.la
libhhapi_la_SOURCES = hhapi.c hhapi.h
libhhapi_la_CPPFLAGS = -I$(top_srcdir)/lib/ @LIBSOUP_CFLAGS@ @LIBJSON_CFLAGS@ \
$(AM_CPPFLAGS)
libhhapi_la_LIBADD = @LIBSOUP_LIBS@ @LIBJSON_LIBS@ 
include_HEADERS = hhapi.h
