#ifndef __LILITH_VECTOR_H__
#define __LILITH_VECTOR_H__

#include <stddef.h>

#define make_name(suffix, name) suffix##_##name
#define cat_(suffix, name) suffix##_##name
#define define_vector(type) \
typedef struct make_name(Svector, type) { \
	type* data; \
	size_t size; \
} make_name(vector, type);

#define make_vector() {NULL, 0}

typedef unsigned char byte; 
define_vector(byte);

typedef void* (*alloc)(size_t);
typedef void* (*rlloc)(void*, size_t);
typedef void  (*dellc)(void*);

typedef struct Sdyn_mem{
	alloc all;
	rlloc rll;
	dellc dll;
} dyn_mem;

extern dyn_mem std_mem; //c std memory functions
extern dyn_mem pgc_mem; //primitive gargabe collector

int __push(vector_byte* vector, byte* data, size_t d_size, dyn_mem* mem);
int  __pop(vector_byte* vector, size_t d_size, dyn_mem* mem);

int __insert(vector_byte* vector, byte* data, size_t d_size, size_t index, dyn_mem* mem);
int __pop_in(vector_byte* vector, size_t index, dyn_mem* mem);

//push templates
#define declare_push(type) \
	int push_##type(vector_##type* vector, type data)

#define define_push(type)   \
	declare_push(type) { \
		return __push((vector_byte*)vector, (byte*)&data, sizeof(type), &std_mem); \
	}

//pop templates
#define declare_pop(type)    \
	int make_name(pop, type)(make_name(vector, type)* vector)

#define define_pop(type)    \
	declare_pop(type) { \
		return __pop((vector_byte*)vector, sizeof(type), &std_mem); \
	}

//insert templates
#define declare_insert(type) \
	int make_name(insert, type)(make_name(vector, type)* vector, type data, size_t index)

#define define_insert(type) \
	declare_insert(type) { \
		return __insert((vector_byte*)vector, (byte*)&data, sizeof(type), index, &std_mem); \
	}

//pop_in templates
#define declare_pop_in(type) \
	int make_name(pop_in, type)(make_name(vector, type)* vector, size_t index)

#define define_pop_in(type) \
	declare_pop_in(type) { \
		return __pop_in((vector_byte*)vector, index, &std_mem); \
	}

#define declare_all_vector(type) \
	define_vector(type); \
	declare_push(type); \
	declare_pop(type); \
	declare_insert(type); \
	declare_pop_in(type);

#define define_all_vector(type) \
	define_push(type) \
	define_pop(type) \
	define_insert(type) \
	define_pop_in(type)

#define declare_essentials(type)\
	declare_push(type); \
	declare_insert(type);

#define define_essentials(type) \
	define_push(type) \
	define_insert(type)

//macros for generic vector
/**
 * @brief kinda sketchy, but it works
 * should only be used when data is a variable
 */
#define push(vector, data)\
	__push((vector_byte*)&vector, &data, sizeof(data), &std_mem)

/**
 * @brief this shouldn't be used
 * use push_type instead, you will have to give the type
 * and it will end up calling push_type anyway
 */
#define pushv(type, vector, data)\
	make_name(push, type)(&vector, data)

/**
 * @brief this is a really hacky way to do this, but it works
 *  you should better use pop_T instead just in case
 */
#define pop(vector)\
	 __pop((vector_byte*)&vector, sizeof(*vector.data), &std_mem)

#endif