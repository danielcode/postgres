#-------------------------------------------------------------------------
#
# Makefile for src/interfaces/libpq library
#
# Portions Copyright (c) 1996-2012, PostgreSQL Global Development Group
# Portions Copyright (c) 1994, Regents of the University of California
#
# src/interfaces/libpqparser/Makefile
#
#-------------------------------------------------------------------------

subdir = src/libpqparser
top_builddir = ../..
include $(top_builddir)/src/Makefile.global

SUBDIRS = $(top_builddir)/src/timezone $(top_builddir)/src/backend

# shared library parameters
NAME= pqparser
SO_MAJOR_VERSION= 5
SO_MINOR_VERSION= 6

OBJS=	$(shell cat ../backend/access/objfiles.txt ../backend/bootstrap/objfiles.txt ../backend/catalog/objfiles.txt ../backend/parser/objfiles.txt ../backend/commands/objfiles.txt ../backend/executor/objfiles.txt ../backend/foreign/objfiles.txt ../backend/lib/objfiles.txt ../backend/libpq/objfiles.txt ../backend/nodes/objfiles.txt ../backend/optimizer/objfiles.txt ../backend/port/objfiles.txt ../backend/postmaster/objfiles.txt ../backend/regex/objfiles.txt ../backend/replication/objfiles.txt ../backend/rewrite/objfiles.txt ../backend/storage/objfiles.txt ../backend/tcop/objfiles.txt ../backend/tsearch/objfiles.txt ../backend/utils/objfiles.txt ../timezone/objfiles.txt | sed -e 's/src/\.\./g')

libpqparserrc.o: libpqparser.rc
	$(WINDRES) -i $< -o $@

SHLIB_EXPORTS = exports.txt

all: all-lib

# Shared library stuff
include $(top_srcdir)/src/Makefile.shlib
backend_src = $(top_srcdir)/src/backend


# We use several backend modules verbatim, but since we need to
# compile with appropriate options to build a shared lib, we can't
# necessarily use the same object files as the backend uses. Instead,
# symlink the source files in here and build our own object file.
# For some libpgport modules, this only happens if configure decides
# the module is needed (see filter hack in OBJS, above).

distprep: libpqparser-dist.rc

libpqparser.rc libpqparser-dist.rc: libpqparser.rc.in
	sed -e 's/\(VERSION.*\),0 *$$/\1,'`date '+%y%j' | sed 's/^0*//'`'/' $< >$@

# Depend on Makefile.global to force rebuild on re-run of configure.
# (But libpq-dist.rc is shipped in the distribution for shell-less
# installations and is only updated by distprep.)
libpqparser.rc: $(top_builddir)/src/Makefile.global

install: all installdirs install-lib

installcheck:
	# $(MAKE) -C test $@

installdirs: installdirs-lib
	$(MKDIR_P) '$(DESTDIR)$(includedir)' '$(DESTDIR)$(includedir_internal)'

uninstall: uninstall-lib

clean distclean: clean-lib
	# $(MAKE) -C test $@

maintainer-clean: distclean maintainer-clean-lib
	# $(MAKE) -C test $@
	rm -f libpqparser-dist.rc
