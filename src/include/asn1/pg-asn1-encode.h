/*-------------------------------------------------------------------------
 *
 * pg-asn1-encode.h
 *	  Structures related to ASN.1 encoding
 *
 *
 * IDENTIFICATION
 *	  src/asn1/pg-asn1-encode.h
 *
 *-------------------------------------------------------------------------
 */

#ifndef PGASN1ENCODE

typedef struct bufferInfo
{
	char	*buffer;
	int		 offset;
	int		 length;
} bufferInfo_t;

#endif
