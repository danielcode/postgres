/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "SQLQuery"
 * 	found in "SQLQuery.asn1"
 * 	`asn1c -fskeletons-copy -fnative-types`
 */

#ifndef	_ASNColumnRef_H_
#define	_ASNColumnRef_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ASNColumnRefList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ASNColumnRef */
typedef struct ASNColumnRef {
	ASNColumnRefList_t	 fields;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ASNColumnRef_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ASNColumnRef;

#ifdef __cplusplus
}
#endif

#endif	/* _ASNColumnRef_H_ */
