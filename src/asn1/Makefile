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
#-------------------------------------------------------------------------

subdir = src/port
top_builddir = ../..
include $(top_builddir)/src/Makefile.global

override CPPFLAGS := -I$(top_builddir)/src/asn1 $(CPPFLAGS)

OBJS 	= ASNBinaryExpression.o ASNBinaryOperator.o ASNColumnRef.o ASNColumnRefItem.o ASNColumnRefList.o \
			ASNExpression.o ASNFromClause.o ASNPlusExpression.o ASNQuery.o ASNRangeVar.o ASNResTarget.o \
			ASNSelectStmt.o ASNString.o BIT_STRING.o BOOLEAN.o IA5String.o INTEGER.o NULL.o NativeEnumerated.o \
			NativeInteger.o NativeReal.o OCTET_STRING.o REAL.o UTF8String.o asn_SEQUENCE_OF.o asn_SET_OF.o \
			asn_codecs_prim.o ber_decoder.o ber_tlv_length.o ber_tlv_tag.o constr_CHOICE.o constr_SEQUENCE.o \
			constr_SEQUENCE_OF.o constr_SET_OF.o constr_TYPE.o constraints.o der_encoder.o per_decoder.o \
			per_encoder.o per_support.o xer_decoder.o xer_encoder.o xer_support.o

HEADERS = ASNBinaryExpression.h ASNBinaryOperator.h ASNColumnRef.h ASNColumnRefItem.h ASNColumnRefList.h \
			ASNExpression.h ASNFromClause.h ASNPlusExpression.h ASNQuery.h ASNRangeVar.h ASNResTarget.h \
			ASNSelectStmt.h ASNString.h BIT_STRING.h BOOLEAN.h IA5String.h INTEGER.h NULL.h NativeEnumerated.h \
			NativeInteger.h NativeReal.h OCTET_STRING.h REAL.h UTF8String.h asn_SEQUENCE_OF.h asn_SET_OF.h \
			asn_application.h asn_codecs.h asn_codecs_prim.h asn_internal.h asn_system.h ber_decoder.h \
			ber_tlv_length.h ber_tlv_tag.h constr_CHOICE.h constr_SEQUENCE.h constr_SEQUENCE_OF.h constr_SET_OF.h \
			constr_TYPE.h constraints.h der_encoder.h per_decoder.h per_encoder.h per_support.h xer_decoder.h \
			xer_encoder.h xer_support.h

GENC =	ASNBinaryExpression.c ASNBinaryOperator.c ASNColumnRef.c ASNColumnRefItem.c ASNColumnRefList.c ASNExpression.c \
		ASNFromClause.c ASNPlusExpression.c ASNQuery.c ASNRangeVar.c ASNResTarget.c ASNSelectStmt.c ASNString.c \
		BIT_STRING.c BOOLEAN.c IA5String.c INTEGER.c NULL.c NativeEnumerated.c NativeInteger.c NativeReal.c \
		OCTET_STRING.c REAL.c UTF8String.c asn_SEQUENCE_OF.c asn_SET_OF.c asn_codecs_prim.c ber_decoder.c \
		ber_tlv_length.c ber_tlv_tag.c constr_CHOICE.c constr_SEQUENCE.c constr_SEQUENCE_OF.c constr_SET_OF.c \
		constr_TYPE.c constraints.c der_encoder.c per_decoder.c per_encoder.c per_support.c xer_decoder.c \
		xer_encoder.c xer_support.c


all: $(top_builddir)/src/include/asn1/ASNQuery.h pgasn1_s.so libpgasn1.a

$(top_builddir)/src/include/asn1/ASNQuery.h: ASNQuery.h
	-mkdir $(top_builddir)/src/include/asn1
	for header in $(HEADERS); do \
	  $(INSTALL_DATA) $(srcdir)/$$header '$(top_builddir)/src/include/asn1' || exit; \
	done

ASNQuery.h: SQLQuery.asn1
ifdef ASN1C
	$(ASN1C) -fskeletons-copy -fnative-types -gen-PER SQLQuery.asn1 && touch ASNQuery.h
	-rm converter-sample.c Makefile.am.sample
else
	@$(missing) asn1c $< $@
endif

libpgasn1.a: ASNQuery.h
	$(CC) -g -I. -c *.c
	ar cr libpgasn1.a *.o
	ranlib libpgasn1.a

pgasn1_s.so: ASNQuery.h
	$(CC) -g -fPIC -I. -shared -o pgasn1_s.so *.c

installdirs:
	$(MKDIR_P) '$(DESTDIR)$(libdir)'

install: all installdirs
	$(INSTALL_STLIB) libpgasn1.a '$(DESTDIR)$(libdir)/libpgasn1.a'
	$(INSTALL_STLIB)  pgasn1_s.so '$(DESTDIR)$(libdir)/pgasn1_s.so'
	-$(LN_S) '$(DESTDIR)$(libdir)/pgasn1_s.so' '$(DESTDIR)$(libdir)/libpgasn1_s.so'

clean:
	-rm libpgasn1.a pgasn1_s.so $(OBJS)

maintainer-clean: clean
	-rm $(GENC) $(HEADERS)
