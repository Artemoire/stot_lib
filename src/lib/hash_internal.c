#include "hash_internal.h"

const char plt2n_diff_table[] = {
  0, // 1 - 0   = 1	
  1, // 2 - 1   = 1
  1, // 4 - 1   = 3
  1, // 8 - 1   = 7
  3, // 16 - 3  = 13
  1, // 32 - 1  = 31
  3, // 64 - 3  = 61
  1, // 128 - 1 = 127 
  5, // 256 - 5 = 251
  3, // 512 - 3 = 509
  3,
  9,
  3,
  1,
  3,
  19,
  15,
  1,
  5,
  1,
  3,
  9,
  3,
  15,
  3,
  39,
  5,
  39,
  57,
  3,
  35,
  1,
  5,
  9,
  41,
  31,
  5,
  25,
  45,
  7,
  87,
  21,
  11,
  57,
  17,
  55,
  21,
  115,
  59,
  81
};