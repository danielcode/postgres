#-------------------------------------------------------------------------
#
# Makefile for src/interfaces
#
# Copyright (c) 1994, Regents of the University of California
#
# src/interfaces/Makefile
#
#-------------------------------------------------------------------------

subdir = src/interfaces
top_builddir = ../..
include $(top_builddir)/src/Makefile.global

SUBDIRS = libpq ecpg libpqasn1

$(recurse)

all-ecpg-recurse: all-libpq-recurse
install-ecpg-recurse: install-libpq-recurse
