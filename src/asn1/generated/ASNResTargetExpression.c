/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "../SQLQuery.asn1"
 */

#include "ASNResTargetExpression.h"

static asn_TYPE_member_t asn_MBR_ASNResTargetExpression_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ASNResTargetExpression, expr),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_ASNExpression,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"expr"
		},
	{ ATF_POINTER, 1, offsetof(struct ASNResTargetExpression, colLabel),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_ASNString,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"colLabel"
		},
};
static int asn_MAP_ASNResTargetExpression_oms_1[] = { 1 };
static ber_tlv_tag_t asn_DEF_ASNResTargetExpression_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_ASNResTargetExpression_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 1 }, /* intConst */
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 1, -1, 0 }, /* utf8String */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 1 }, /* floatConst */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, -1, 0 }, /* asciiString */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 0, 0, 0 }, /* stringConst */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 0, 0, 0 } /* binaryExpr */
};
static asn_SEQUENCE_specifics_t asn_SPC_ASNResTargetExpression_specs_1 = {
	sizeof(struct ASNResTargetExpression),
	offsetof(struct ASNResTargetExpression, _asn_ctx),
	asn_MAP_ASNResTargetExpression_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_ASNResTargetExpression_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ASNResTargetExpression = {
	"ASNResTargetExpression",
	"ASNResTargetExpression",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_ASNResTargetExpression_tags_1,
	sizeof(asn_DEF_ASNResTargetExpression_tags_1)
		/sizeof(asn_DEF_ASNResTargetExpression_tags_1[0]), /* 1 */
	asn_DEF_ASNResTargetExpression_tags_1,	/* Same as above */
	sizeof(asn_DEF_ASNResTargetExpression_tags_1)
		/sizeof(asn_DEF_ASNResTargetExpression_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ASNResTargetExpression_1,
	2,	/* Elements count */
	&asn_SPC_ASNResTargetExpression_specs_1,	/* Additional specs */
	32, /* Top Expression: SEQUENCE */
	0,	/* Not an Anonymous Type */
	sizeof(ASNResTargetExpression_t),
	1,	/* Generated */
	"asn_DEF_ASNResTargetExpression", /* Symbol String */
	(void (*)(struct asn_TYPE_descriptor_s *))NULL
};

