#include"ht_interface.h"
/*#include<stdint.h>*/
unsigned int MurmurHash2 (const char * key, unsigned int len)
{
  const unsigned int m = 0x5bd1e995;
  const unsigned int seed = 0;
  const int r = 24;

  unsigned int h = seed ^ len;

  const unsigned char * data = (const unsigned char *)key;
  unsigned int k = 0;

  while (len >= 4)
  {
      k  = data[0];
      k |= data[1] << 8;
      k |= data[2] << 16;
      k |= data[3] << 24;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      data += 4;
      len -= 4;
  }

  switch (len)
  {
    case 3:
      h = h ^ (data[2] << 16);
      break;
    case 2:
      h = h ^ (data[1] << 8);
      break;
    case 1:
      h = h ^ data[0];
      h *= m;
      break;
  };

  h = h ^ (h >> 13);
  h *= m;
  h = h ^ (h >> 15);

  return h % 100;
};


unsigned int simple_sum_hash(const char* key, unsigned int len){
  unsigned int index = 0;
  for(unsigned int i = 0; i < len; ++i){
    index += key[i];
  }
  return index % MAX_CAPACITY;
};



