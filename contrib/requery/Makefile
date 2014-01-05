# contrib/requery/Makefile

MODULE_big = requery
OBJS = requery.o

EXTENSION = requery
DATA = requery--0.1.sql # test_parser--unpackaged--1.0.sql

REGRESS = requery

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/requery
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
