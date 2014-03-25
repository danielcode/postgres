/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "../SQLQuery.asn1"
 */

#include "ASNResTarget.h"

static asn_per_constraints_t asn_PER_type_ASNResTarget_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_ASNResTarget_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ASNResTarget, choice.star),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"star"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ASNResTarget, choice.columnRef),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ASNColumnRef,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"columnRef"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ASNResTarget, choice.resTargetExpression),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ASNResTargetExpression,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"resTargetExpression"
		},
};
static asn_TYPE_tag2member_t asn_MAP_ASNResTarget_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* star */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* columnRef */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* resTargetExpression */
};
static asn_CHOICE_specifics_t asn_SPC_ASNResTarget_specs_1 = {
	sizeof(struct ASNResTarget),
	offsetof(struct ASNResTarget, _asn_ctx),
	offsetof(struct ASNResTarget, present),
	sizeof(((struct ASNResTarget *)0)->present),
	asn_MAP_ASNResTarget_tag2el_1,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ASNResTarget = {
	"ASNResTarget",
	"ASNResTarget",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_ASNResTarget_constr_1,
	asn_MBR_ASNResTarget_1,
	3,	/* Elements count */
	&asn_SPC_ASNResTarget_specs_1,	/* Additional specs */
	33, /* Top Expression: CHOICE */
	0,	/* Not an Anonymous Type */
	sizeof(ASNResTarget_t),
	1,	/* Generated */
	"asn_DEF_ASNResTarget", /* Symbol String */
	(void (*)(struct asn_TYPE_descriptor_s *))NULL
};
