/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "../SQLQuery.asn1"
 */

#include "ASNColumnRefList.h"

static asn_TYPE_member_t asn_MBR_ASNColumnRefList_1[] = {
	{ ATF_POINTER, 0, 0,
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_ASNColumnRefItem,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_ASNColumnRefList_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_ASNColumnRefList_specs_1 = {
	sizeof(struct ASNColumnRefList),
	offsetof(struct ASNColumnRefList, _asn_ctx),
	2,	/* XER encoding is XMLValueList */
};
asn_TYPE_descriptor_t asn_DEF_ASNColumnRefList = {
	"ASNColumnRefList",
	"ASNColumnRefList",
	SEQUENCE_OF_free,
	SEQUENCE_OF_print,
	SEQUENCE_OF_constraint,
	SEQUENCE_OF_decode_ber,
	SEQUENCE_OF_encode_der,
	SEQUENCE_OF_decode_xer,
	SEQUENCE_OF_encode_xer,
	SEQUENCE_OF_decode_uper,
	SEQUENCE_OF_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_ASNColumnRefList_tags_1,
	sizeof(asn_DEF_ASNColumnRefList_tags_1)
		/sizeof(asn_DEF_ASNColumnRefList_tags_1[0]), /* 1 */
	asn_DEF_ASNColumnRefList_tags_1,	/* Same as above */
	sizeof(asn_DEF_ASNColumnRefList_tags_1)
		/sizeof(asn_DEF_ASNColumnRefList_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ASNColumnRefList_1,
	1,	/* Single element */
	&asn_SPC_ASNColumnRefList_specs_1,	/* Additional specs */
	35, /* Top Expression: SEQUENCE OF */
	0,	/* Not an Anonymous Type */
	sizeof(ASNColumnRefList_t),
	1,	/* Generated */
	"asn_DEF_ASNColumnRefList" /* Symbol String */
};

