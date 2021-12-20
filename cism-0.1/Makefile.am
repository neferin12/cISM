AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = ism
ism_SOURCES = src/main.c src/fileInterface.c src/organization.c src/errorHandling.c
# SUBDIRS = src
if DEBUG
AM_CFLAGS = -g3 -O0
AM_CXXFLAGS = -g3 -O0
else
AM_CFLAGS = -O2
AM_CXXFLAGS = -O2
endif