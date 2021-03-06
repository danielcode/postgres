/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "../SQLQuery.asn1"
 */

#ifndef	_ASNBinaryExpression_H_
#define	_ASNBinaryExpression_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ASNBinaryOperator.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ASNExpression;

/* ASNBinaryExpression */
typedef struct ASNBinaryExpression {
	struct ASNExpression	*lhs;
	ASNBinaryOperator_t	 operator;
	struct ASNExpression	*rhs;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ASNBinaryExpression_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ASNBinaryExpression;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ASNExpression.h"

#endif	/* _ASNBinaryExpression_H_ */
#include <asn_internal.h>
