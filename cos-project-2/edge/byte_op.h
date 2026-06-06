#ifndef __BYTE_OP_H__
#define __BYTE_OP_H__

#include <cstdio>
#include <cstring>

#define VAR_TO_MEM_1BYTE_BIG_ENDIAN(v, p) \
  *(p++) = v & 0xff;

#define VAR_TO_MEM_2BYTES_BIG_ENDIAN(v, p) \
  *(p++) = (v >> 8) & 0xff; *(p++) = v & 0xff;

#define VAR_TO_MEM_4BYTES_BIG_ENDIAN(v, p) \
  *(p++) = (v >> 24) & 0xff; *(p++) = (v >> 16) & 0xff; *(p++) = (v >> 8) & 0xff; *(p++) = v & 0xff;

#define MEM_TO_VAR_1BYTE_BIG_ENDIAN(p, v) \
  v = (p[0] & 0xff); p += 1;

#define MEM_TO_VAR_2BYTES_BIG_ENDIAN(p, v) \
  v = ((p[0] & 0xff) << 8) | (p[1] & 0xff); p += 2;

#define MEM_TO_VAR_4BYTES_BIG_ENDIAN(p, v) \
  v = ((p[0] & 0xff) << 24) | ((p[1] & 0xff) << 16) | ((p[2] & 0xff) << 8) | (p[3] & 0xff); p += 4;

#define PRINT_MEM(p, len) \
  printf("Print buffer:\n  >> "); \
  for (int i=0; i<len; i++) { \
    printf("%02x ", p[i]); \
    if (i % 16 == 15) printf("\n  >> "); \
  } \
  printf("\n");

#endif /* __BYTE_OP_H__ */
