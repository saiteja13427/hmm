#include<stdio.h>
#include"uapi_mm.h"

struct student_{
    char name[64];
} student_st;

struct employee_{
    char name[63];
} employee_st;

int main(){
    mm_init();
    MM_REG_STRUCT(student_st);
    MM_REG_STRUCT(employee_st);
    mm_print_registered_page_families();
    vm_page_family_t* find_st = LOOKUP_STRUCT(student_st);
    printf("Name: %s, size: %d\n", find_st->struct_name, find_st->struct_size);
}