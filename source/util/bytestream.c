#include "definitions.h"
// A bytestream is essentialy a dynamically reallocted string
// Each time it is filled up, the capacity is doubled

bytestream initbytestream(uint32 len) // allocates bytestream, free when done
{
    bytestream b = (bytestream) malloc(sizeof(struct bytestream_struct));
    b->data = (char*) malloc(len);
    b->head = b->data;
    b->len = 0; // filled bytes
    b->streamlen = len; // total allocated bytes
    return b;
} // initbytestream

void freebytestream(bytestream b)
{
    free(b->data);
    free(b);
    b = NULL;
} // freebytestream

void bytestreamfit(bytestream b, int32 len)
{
    // dynamically allocate more memory if needed
    if(b->len + len > b->streamlen) {
        int32 newlen = len + b->streamlen * 2;
        b->data = (char*) realloc(b->data, newlen);
        b->head = b->data + b->len;
        b->streamlen = newlen;
    }
} // bytestreamfit

void bytestreaminsert(bytestream b, void *data, int32 len)
{
    bytestreamfit(b, len);
    memcpy(b->head, data, len);
    b->len += len;
    b->head += len;
} // bytestreaminsert

void bytestreaminsertchar(bytestream b, char c)
{
    bytestreamfit(b, 1);
    *b->head = c;
    b->len += 1;
    b->head += 1;
} // bytestreaminsertchar
