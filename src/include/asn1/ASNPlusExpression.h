/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "../SQLQuery.asn1"
 */

#ifndef	_ASNPlusExpression_H_
#define	_ASNPlusExpression_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ASNExpression.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ASNPlusExpression */
typedef struct ASNPlusExpression {
	ASNExpression_t	 lhs;
	ASNExpression_t	 rhs;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ASNPlusExpression_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ASNPlusExpression;

#ifdef __cplusplus
}
#endif

#endif	/* _ASNPlusExpression_H_ */
#include <asn_internal.h>
