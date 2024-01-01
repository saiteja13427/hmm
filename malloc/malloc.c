#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<memory.h>

void * xmalloc(int size){
    void *p;
    p = sbrk(0);
    if(sbrk(size) == NULL) return NULL;
    return p;
}

void xfree(int nbytes){
    assert(nbytes>0);
    sbrk(nbytes*-1);
}

int main(int argc, char **argv){
    char *p = xmalloc(20);
    printf("Pointer: %p\n", p);
    // p = "Hello";
    // printf("Pointer: %s\n", p);
    strcpy(p, "Hello");
    printf("Content: %s\n", p);
    xfree(20);
    return 0;
}