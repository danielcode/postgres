/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "SQLQuery.asn1"
 * 	`asn1c -fskeletons-copy -fnative-types`
 */

#include <asn_internal.h>

#include "ASNSelectStmt.h"

static asn_TYPE_member_t asn_MBR_targets_2[] = {
	{ ATF_POINTER, 0, 0,
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_ASNResTarget,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_targets_tags_2[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_targets_specs_2 = {
	sizeof(struct targets),
	offsetof(struct targets, _asn_ctx),
	2,	/* XER encoding is XMLValueList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_targets_2 = {
	"targets",
	"targets",
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
	asn_DEF_targets_tags_2,
	sizeof(asn_DEF_targets_tags_2)
		/sizeof(asn_DEF_targets_tags_2[0]), /* 1 */
	asn_DEF_targets_tags_2,	/* Same as above */
	sizeof(asn_DEF_targets_tags_2)
		/sizeof(asn_DEF_targets_tags_2[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_targets_2,
	1,	/* Single element */
	&asn_SPC_targets_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_fromClause_4[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_ASNFromClause,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_fromClause_tags_4[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_fromClause_specs_4 = {
	sizeof(struct fromClause),
	offsetof(struct fromClause, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_fromClause_4 = {
	"fromClause",
	"fromClause",
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
	asn_DEF_fromClause_tags_4,
	sizeof(asn_DEF_fromClause_tags_4)
		/sizeof(asn_DEF_fromClause_tags_4[0]), /* 1 */
	asn_DEF_fromClause_tags_4,	/* Same as above */
	sizeof(asn_DEF_fromClause_tags_4)
		/sizeof(asn_DEF_fromClause_tags_4[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_fromClause_4,
	1,	/* Single element */
	&asn_SPC_fromClause_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ASNSelectStmt_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ASNSelectStmt, targets),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_targets_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"targets"
		},
	{ ATF_POINTER, 1, offsetof(struct ASNSelectStmt, fromClause),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_fromClause_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"fromClause"
		},
};
static int asn_MAP_ASNSelectStmt_oms_1[] = { 1 };
static ber_tlv_tag_t asn_DEF_ASNSelectStmt_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_ASNSelectStmt_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 0, 0, 1 }, /* targets at 6 */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 1, -1, 0 } /* fromClause at 8 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ASNSelectStmt_specs_1 = {
	sizeof(struct ASNSelectStmt),
	offsetof(struct ASNSelectStmt, _asn_ctx),
	asn_MAP_ASNSelectStmt_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_ASNSelectStmt_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ASNSelectStmt = {
	"ASNSelectStmt",
	"ASNSelectStmt",
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
	asn_DEF_ASNSelectStmt_tags_1,
	sizeof(asn_DEF_ASNSelectStmt_tags_1)
		/sizeof(asn_DEF_ASNSelectStmt_tags_1[0]), /* 1 */
	asn_DEF_ASNSelectStmt_tags_1,	/* Same as above */
	sizeof(asn_DEF_ASNSelectStmt_tags_1)
		/sizeof(asn_DEF_ASNSelectStmt_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ASNSelectStmt_1,
	2,	/* Elements count */
	&asn_SPC_ASNSelectStmt_specs_1	/* Additional specs */
};

