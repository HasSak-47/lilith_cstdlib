/**
 * 
 * this shit is so fucking badly made that it should break the whole fucking project in the future
 * but i'm too lazy to fix it
 * 
 */

#ifndef __LILITH_MEMORY__
#define __LILITH_MEMORY__

#ifdef __cplusplus
#error "Just use the c++ memory header"
#endif

#include <stddef.h>
#include "vector.h"

typedef void* pointer;

define_vector(pointer);
typedef vector_pointer mem_vec;

int  add_memory(mem_vec* vec, void* ptr);
int  del_memory(mem_vec* vec, void* ptr);
int trim_memory(mem_vec* vec);

void clean_memory();

void* std_new(size_t size, mem_vec* vec);
int   std_del(void* ptr, mem_vec* vec);

void* new(size_t);
void* nes(void*, size_t);
void  del(void*);

#define _new(type) new(sizeof(type))

#endif // __LILITH_MEMORY__