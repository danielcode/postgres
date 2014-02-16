#-------------------------------------------------------------------------
#
# Makefile
#    Makefile for wire protocol library
#
# This makefile generates the following outputs:
#
#       libpgasn1.a.a - 
#
#       pgasn1_s.so - 
#
# IDENTIFICATION
#    src/asn1/Makefile
#
# NOTES
#    Doesn't use standard CFLAGS / LDFLAGS - fix
#
#-------------------------------------------------------------------------

subdir = src/port
top_builddir = ../..
include $(top_builddir)/src/Makefile.global

override CPPFLAGS := -I$(top_builddir)/src/asn1 $(CPPFLAGS)

OBJS 	= ASNBinaryExpression.o ASNBinaryOperator.o ASNColumnRef.o ASNColumnRefItem.o ASNColumnRefList.o \
		  ASNExpression.o ASNFromClause.o ASNPlusExpression.o ASNQuery.o ASNRangeVar.o ASNResTarget.o \
		  ASNResTargetExpression.o ASNSelectStmt.o ASNString.o BIT_STRING.o BOOLEAN.o IA5String.o INTEGER.o NULL.o \
		  NativeEnumerated.o NativeInteger.o NativeReal.o OCTET_STRING.o REAL.o UTF8String.o asn_SEQUENCE_OF.o \
		  asn_SET_OF.o asn_codecs_prim.o ber_decoder.o ber_tlv_length.o ber_tlv_tag.o constr_CHOICE.o \
		  constr_SEQUENCE.o constr_SEQUENCE_OF.o constr_SET_OF.o constr_TYPE.o constraints.o der_encoder.o \
		  per_decoder.o per_encoder.o per_support.o per_opentype.o xer_decoder.o xer_encoder.o xer_support.o \
		  pg-asn1-encode.o tree_to_asn1.o

GENH= generated/ASNBinaryExpression.h generated/ASNBinaryOperator.h generated/ASNColumnRef.h \
	generated/ASNColumnRefItem.h generated/ASNColumnRefList.h generated/ASNExpression.h generated/ASNFromClause.h \
	generated/ASNPlusExpression.h generated/ASNQuery.h generated/ASNRangeVar.h generated/ASNResTarget.h \
	generated/ASNResTargetExpression.h generated/ASNSelectStmt.h generated/ASNString.h generated/BIT_STRING.h \
	generated/BOOLEAN.h generated/IA5String.h generated/INTEGER.h generated/NULL.h generated/NativeEnumerated.h \
	generated/NativeInteger.h generated/NativeReal.h generated/OCTET_STRING.h generated/REAL.h generated/UTF8String.h \
	generated/asn_SEQUENCE_OF.h generated/asn_SET_OF.h generated/asn_application.h generated/asn_codecs.h \
	generated/asn_codecs_prim.h generated/asn_internal.h generated/asn_system.h generated/ber_decoder.h \
	generated/ber_tlv_length.h generated/ber_tlv_tag.h generated/constr_CHOICE.h generated/constr_SEQUENCE.h \
	generated/constr_SEQUENCE_OF.h generated/constr_SET_OF.h generated/constr_TYPE.h generated/constraints.h \
	generated/der_encoder.h generated/per_decoder.h generated/per_encoder.h generated/per_support.h \
	generated/per_opentype.h generated/xer_decoder.h generated/xer_encoder.h generated/xer_support.h \
	generated/expr_types.h

HEADERS= pg-asn1-encode.h

GENC =	generated/ASNBinaryExpression.c generated/ASNBinaryOperator.c generated/ASNColumnRef.c \
		generated/ASNColumnRefItem.c generated/ASNColumnRefList.c generated/ASNExpression.c generated/ASNFromClause.c \
		generated/ASNPlusExpression.c generated/ASNQuery.c generated/ASNRangeVar.c generated/ASNResTarget.c \
		generated/ASNResTargetExpression.c generated/ASNSelectStmt.c generated/ASNString.c generated/BIT_STRING.c \
		generated/BOOLEAN.c generated/IA5String.c generated/INTEGER.c generated/NULL.c generated/NativeEnumerated.c \
		generated/NativeInteger.c generated/NativeReal.c generated/OCTET_STRING.c generated/REAL.c \
		generated/UTF8String.c generated/asn_SEQUENCE_OF.c generated/asn_SET_OF.c generated/asn_codecs_prim.c \
		generated/ber_decoder.c generated/ber_tlv_length.c generated/ber_tlv_tag.c generated/constr_CHOICE.c \
		generated/constr_SEQUENCE.c generated/constr_SEQUENCE_OF.c generated/constr_SET_OF.c generated/constr_TYPE.c \
		generated/constraints.c generated/der_encoder.c generated/per_decoder.c generated/per_encoder.c \
		generated/per_support.c generated/per_opentype.c generated/xer_decoder.c generated/xer_encoder.c \
		generated/xer_support.c generated/expr_types.h

SOURCES= pg-asn1-encode.c tree_to_asn1.c


all: $(top_builddir)/src/include/asn1/ASNQuery.h pgasn1_s.so libpgasn1.a

$(top_builddir)/src/include/asn1/ASNQuery.h: generated/ASNQuery.h
	-mkdir $(top_builddir)/src/include/asn1
	for header in $(GENH); do \
	  $(INSTALL_DATA) $(srcdir)/$$header '$(top_builddir)/src/include/asn1' || exit; \
	done
	for header in $(HEADERS); do \
	  $(INSTALL_DATA) $(srcdir)/$$header '$(top_builddir)/src/include/asn1' || exit; \
	done

generated/ASNQuery.h: SQLQuery.asn1
ifdef ASN1C
	-mkdir generated
	(cd generated; $(ASN1C) -gen-PER ../SQLQuery.asn1 && touch ASNQuery.h)
	-rm generated/converter-sample.c generated/Makefile.am.sample
else
	@$(missing) asn1c $< $@
endif

libpgasn1.a: generated/ASNQuery.h
	# $(CC) -g -I../../src/include -I. -Igenerated -c generated/*.c *.c
	$(CC) -g -c -I../../src/include -I../../src/backend -I. -Igenerated generated/*.c
	$(CC) -g -c -I../include -I../backend -I. -Igenerated *.c
	ar cr libpgasn1.a *.o
	ranlib libpgasn1.a

pgasn1_s.so: generated/ASNQuery.h
	$(CC) -g -c -fPIC -I../../src/include -I../../src/backend -I. -Igenerated generated/*.c
	$(CC) -g -c -fPIC -I../include -I../backend -I. -Igenerated *.c
	$(CC) -g -fPIC -shared -o pgasn1_s.so $(OBJS)

installdirs:
	$(MKDIR_P) '$(DESTDIR)$(libdir)'

install: all installdirs
	$(INSTALL_STLIB) libpgasn1.a '$(DESTDIR)$(libdir)/libpgasn1.a'
	$(INSTALL_STLIB)  pgasn1_s.so '$(DESTDIR)$(libdir)/pgasn1_s.so'
	-$(LN_S) '$(DESTDIR)$(libdir)/pgasn1_s.so' '$(DESTDIR)$(libdir)/libpgasn1_s.so'

clean:
	-rm libpgasn1.a pgasn1_s.so $(OBJS)

maintainer-clean: clean
	-rm $(GENC) $(GENH)
	rmdir generated
