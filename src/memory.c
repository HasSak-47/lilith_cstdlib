#include <stdlib.h>
#include <stdio.h>
#include <Lmemory.h>

dyn_mem std_mem = {
    malloc,
    realloc,
    free
};

dyn_mem pgc_mem = {
    new,
    nes,
    del
};

mem_vec std_gc = make_vector();

int add_memory(mem_vec* vec, void* ptr){
    for(size_t i = 0; i < vec->size; ++i){
        if(vec->data[i] == NULL){
            vec->data[i] = ptr;
            return 0;
        }
    }

    void** buffer = vec->data;
    buffer = realloc(buffer, sizeof(void*) * (vec->size + 1));
    if(buffer == NULL)
        return -1;

    vec->data = buffer;
    vec->data[vec->size++] = ptr;

    return 0;
}

int trim_memory(mem_vec* vec){
    void** buffer = vec->data;
    while(buffer[vec->size - 1] == NULL){
        buffer = realloc(buffer, sizeof(void*) * (vec->size - 1));
        if(buffer == NULL)
            return 1;
        
        vec->data = buffer;
        vec->size--;
    }

    return 0;
}

int del_memory (mem_vec* vec, void* ptr){
    for(size_t i = 0; i < vec->size; ++i){
        if(vec->data[i] == ptr){
            vec->data[i] = NULL;
            return 0;
        }
    }

    trim_memory(vec);
    return 1;
}

void* std_new(size_t size, mem_vec* vec){
    void* ptr = malloc(size);
    if(ptr == NULL)
        return NULL;

    int error = add_memory(vec, ptr);
    if(error)
        exit(-1);

    return ptr;
}

int std_del(void* ptr, mem_vec* vec){
    if(del_memory(vec, ptr))
        return -1;

    free(ptr);
    return 0;
}

void clean_memory(){
    for(size_t i = 0; i < std_gc.size; ++i){
        if(std_gc.data[i] != NULL)
            free(std_gc.data[i]);
    }

    free(std_gc.data);
}

void* new(size_t size){
    return std_new(size, &std_gc);
}

void* nes(void* ptr, size_t size){
    return NULL;
}

void del(void* ptr){
    std_del(ptr, &std_gc);
}