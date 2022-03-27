#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

namespace rtiow{
    void* memalloc(size_t size, char* varname){
        printf("Allocated %d memory to var %s", size, varname);

        return malloc(size);
    }
    void cmemalloc(void* variable, size_t size, char* varname){
        printf("Allocated %d memory to var %s", size, varname);

        free(variable);
    }
}

#endif