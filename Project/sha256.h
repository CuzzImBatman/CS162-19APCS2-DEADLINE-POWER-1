#ifndef _SHA256_H_
#define _SHA256_H_
#include <string>
using namespace std;

#define SHA256_BLOCK_SIZE 32          


typedef unsigned char BYTE;
typedef unsigned int  WORD;

typedef struct {
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA256_CTX;


void sha256_init(SHA256_CTX* ctx);
void sha256_update(SHA256_CTX* ctx, string data, size_t len);


#endif
