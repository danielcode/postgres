/*-------------------------------------------------------------------------
 *
 * pg-asn1-encode
 *	  functions relating to ASN.1 encoding
 *
 *
 * IDENTIFICATION
 *	  src/asn1/pg-asn1-encode
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

/*
 * ASN.1 related
 */
#include "nodes/parsenodes.h"
#include "ASNQuery.h"
#include "pg-asn1-encode.h"
static asn_app_consume_bytes_f consumeBytes;

extern ASNQuery_t *tree_to_asn1(List *);
void pg_asn1_buffer_free(transferBuffer_t *transferBuffer);

/*
 * consumeBytes
 */
static int
consumeBytes(const void *buffer, size_t size, void *application_specific_key)
{
	bufferInfo_t *bufferInfo = (bufferInfo_t *)application_specific_key;

	memcpy((void *)(bufferInfo->buffer + bufferInfo->offset), buffer, size);

	bufferInfo->offset += size;

	return 0;
}

/*
 * pg_asn1_encode
 *	 XXXXX - check returns from palloc
 *
 * Returns: XXXXX
 *			XXXXX
 */
transferBuffer_t *
pg_asn1_encode(List *l, int encoding)
{
	transferBuffer_t *transferBuffer = palloc((Size)sizeof(transferBuffer_t));
	asn_enc_rval_t ec;

	transferBuffer->queryStmt		 = tree_to_asn1(l);
	transferBuffer->bufferInfo.buffer = palloc((Size)32768);
	transferBuffer->bufferInfo.offset = 0;
	transferBuffer->bufferInfo.length = 32768;

	if (encoding == 0)
	{
		ec = xer_encode(&asn_DEF_ASNQuery, (void *)transferBuffer->queryStmt, XER_F_CANONICAL,
		(asn_app_consume_bytes_f *)consumeBytes, (void *)&transferBuffer->bufferInfo);
		if (ec.encoded == -1)
		{
			pg_asn1_buffer_free(transferBuffer);
			return NULL;
		}
	}
	else if (encoding == 1)
	{
		ec = der_encode(&asn_DEF_ASNQuery, (void *)transferBuffer->queryStmt,
		(asn_app_consume_bytes_f *)consumeBytes, (void *)&transferBuffer->bufferInfo);
		if (ec.encoded == -1)
		{
			pg_asn1_buffer_free(transferBuffer);
			return NULL;
		}
	}
	else if (encoding == 2)
	{
		ec = uper_encode(&asn_DEF_ASNQuery, (void *)transferBuffer->queryStmt,
		(asn_app_consume_bytes_f *)consumeBytes, (void *)&transferBuffer->bufferInfo);
		if (ec.encoded == -1)
		{
			pg_asn1_buffer_free(transferBuffer);
			return NULL;
		}
	}

	/* No need to keep the encoded data around anymore */

	return transferBuffer;
}

void
pg_asn1_buffer_free(transferBuffer_t *transferBuffer)
{
	asn_DEF_ASNQuery.free_struct(&asn_DEF_ASNQuery, transferBuffer->queryStmt, 0);
	pfree(transferBuffer->bufferInfo.buffer);
	pfree(transferBuffer);
}

