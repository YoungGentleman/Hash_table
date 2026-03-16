#ifndef _HASH_FUNCTIONS_H
#define _HASH_FUNCTIONS_H

unsigned int MurmurHash2(const char *key, unsigned int len);
unsigned int simple_sum_hash(const char* key, unsigned int len);

#endif