/**
 * @file  eso_lzma.h
 * @brief ES lzma zip api.
 */

#ifndef __ESO_LZMA_H__
#define __ESO_LZMA_H__

#include "es_types.h"
#include "es_comm.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//==============================================================================
// lzmz
//==============================================================================

#define ES_SZ_OK 0
#define ES_SZ_ERROR_DATA 1
#define ES_SZ_ERROR_MEM 2
#define ES_SZ_ERROR_CRC 3
#define ES_SZ_ERROR_UNSUPPORTED 4
#define ES_SZ_ERROR_PARAM 5
#define ES_SZ_ERROR_INPUT_EOF 6
#define ES_SZ_ERROR_OUTPUT_EOF 7
#define ES_SZ_ERROR_READ 8
#define ES_SZ_ERROR_WRITE 9
#define ES_SZ_ERROR_PROGRESS 10
#define ES_SZ_ERROR_FAIL 11
#define ES_SZ_ERROR_THREAD 12
#define ES_SZ_ERROR_ARCHIVE 16
#define ES_SZ_ERROR_NO_ARCHIVE 17

/*
 * LZMA
 */
typedef struct
{
	es_size_t (*write)(void *p, const void *buf, es_size_t size);
    /* Returns: result - the number of actually written bytes.
       (result < size) means error */
} es_lzma_ostream_t;

typedef struct
{
	es_int32_t (*read)(void *p, void *buf, es_size_t *size);
    /* if (input(*size) != 0 && output(*size) == 0) means end_of_stream.
       (output(*size) < input(*size)) is allowed. 
       Returns: 0-suceess, other-failure*/
} es_lzma_istream_t;

//==============================================================================

//LZMA ziped
es_int32_t eso_lzma_zip(es_lzma_ostream_t *outStream, 
                        es_lzma_istream_t *inStream, 
                        es_size_t dataSize);

//LZMA unzipd
es_int32_t eso_lzma_unzip(es_lzma_ostream_t *outStream, 
                          es_lzma_istream_t *inStream);

//LZMA with directory decompression, Note: opath must be last with '/'.
es_int32_t eso_lzma_unzip_arfile(const char *ifname, 
                                 es_size_t offset, 
                                 const char *opath, 
                                 es_bool_t overwrite);

es_int32_t eso_lzma_unzip_arbuff(const char *ibuff, 
                                 es_size_t size, 
                                 const char *opath, 
                                 es_bool_t overwrite);

#ifdef __cplusplus
}
#endif

#endif /* __ESO_LZMA_H__ */
