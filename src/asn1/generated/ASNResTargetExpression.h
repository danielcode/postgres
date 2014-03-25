/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "../SQLQuery.asn1"
 */

#ifndef	_ASNResTargetExpression_H_
#define	_ASNResTargetExpression_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ASNExpression.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ASNString;

/* ASNResTargetExpression */
typedef struct ASNResTargetExpression {
	ASNExpression_t	 expr;
	struct ASNString	*colLabel	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ASNResTargetExpression_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ASNResTargetExpression;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ASNString.h"

#endif	/* _ASNResTargetExpression_H_ */
#include <asn_internal.h>