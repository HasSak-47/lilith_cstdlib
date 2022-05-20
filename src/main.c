#include <stdlib.h>
#include <stdio.h>
#include <Lmemory.h>

#include <vector.h>

int main(int argc, char* argv[]){
    atexit(clean_memory);
    return 0;
}