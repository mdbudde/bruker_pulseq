#ifndef MD5_H
#define MD5_H

//#ifdef __alpha
//typedef unsigned int uint32;
//#else
//typedef unsigned long uint32;
//#endif

#if defined(_MSC_VER) && _MSC_VER<=1600
typedef unsigned __int32 uint32;
#else
#ifdef VXWORKS
#include "types/vxTypes.h" 
#else
#include <stdint.h>
#endif
typedef uint32_t uint32;
#endif //_MSC_VER

struct MD5Context
{
    uint32        buf[4];
    uint32        bits[2];
    unsigned char in[64];
};

void MD5Init(struct MD5Context* context);
void MD5Update(struct MD5Context* context, unsigned char const* buf, unsigned len);
void MD5Final(unsigned char digest[16], struct MD5Context* context);
void MD5Transform(uint32 buf[4], uint32 const in[16]);

/*
    * This is needed to make RSAREF happy on some MS-DOS compilers.
    */
typedef struct MD5Context MD5_CTX;


#endif /* !MD5_H */
