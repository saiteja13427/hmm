#include<stdint.h>

#define MM_MAX_STRUCT_NAME 64

#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr) \
{                                                                   \
    uint32_t c = 0;                                             \
    for(curr = (vm_page_family_t *) &vm_page_for_families_ptr->vm_page_family[0]; \
    curr->struct_size && c < MAX_FAMILIES_PER_VM_PAGE;          \
    curr++, c++){                                               \

#define ITERATE_PAGE_FAMILIES_END   }}

typedef struct vm_page_family_ {
    char struct_name[MM_MAX_STRUCT_NAME];
    uint32_t struct_size;
} vm_page_family_t;

typedef struct vm_page_for_families_ {
    struct vm_page_for_families *next;
    vm_page_family_t vm_page_family[0];
} vm_page_for_families_t;

#define MAX_FAMILIES_PER_VM_PAGE \
    (SYSTEM_PAGE_SIZE - sizeof(vm_page_for_families_t *)/ \
    sizeof(vm_page_family_t))



