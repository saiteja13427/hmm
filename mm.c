#include<stdio.h>
#include<memory.h>
#include<unistd.h> //To get pagesize of virtual memory
#include<sys/mman.h> //To use mmap/munmap calls
#include <assert.h>
#include "mm.h"
 
static vm_page_for_families_t *first_vm_page_for_families = NULL;

static size_t SYSTEM_PAGE_SIZE = 0;

void
mm_init ()
{
    SYSTEM_PAGE_SIZE = getpagesize(); //Defined in unistd.h
}

/* API to request VM page from kernel */
static void*
mm_get_new_vm_page_from_kernel(int units)
{
    char* vm_page = mmap(
                        0, 
                        units*SYSTEM_PAGE_SIZE,
                        PROT_READ|PROT_WRITE|PROT_EXEC,
                        MAP_ANON|MAP_PRIVATE,
                        0,0);
    if(vm_page == MAP_FAILED){
        printf("ERROR: VM Page Allocation failed");
        return NULL;
    }
    memset(vm_page, 0, units * SYSTEM_PAGE_SIZE);
    return vm_page;
}

/* API to release VM page to the kernel*/
static void
mm_return_vm_page_to_kernel(void *vm_page, int units)
{
    if(munmap(vm_page, units*SYSTEM_PAGE_SIZE)){
        printf("ERROR: VM Page deallocation failed");
    }
}

void
mm_instantiate_new_page_family(
    char* struct_name, 
    uint32_t struct_size
){
    vm_page_family_t vm_page_family;
    vm_page_family_t *vm_page_family_curr = NULL;
    if(struct_size > SYSTEM_PAGE_SIZE){
        printf("ERROR: Unsupported size");
        return;
    }

    if(first_vm_page_for_families == NULL){
        first_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
        first_vm_page_for_families->next = NULL;
        strncpy(first_vm_page_for_families->vm_page_family[0].struct_name, struct_name, MM_MAX_STRUCT_NAME);
        first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
        return;
    }

    __uint32_t count = 0;

    ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr){
        if(strcmp(vm_page_family_curr->struct_name, struct_name) !=0){
            count++;
            continue;
        }
        assert(0);

    } ITERATE_PAGE_FAMILIES_END

    if(count == MAX_FAMILIES_PER_VM_PAGE){
        vm_page_for_families_t *new_vm_page_for_family = (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
        new_vm_page_for_family->next = first_vm_page_for_families;
        first_vm_page_for_families = new_vm_page_for_family;
        vm_page_family_curr = &first_vm_page_for_families->vm_page_family[0];
    }

    strncpy(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME+1);
    vm_page_family_curr->struct_size = struct_size;

}

void
mm_print_registered_page_families (){
    vm_page_family_t *vm_page_family_curr = NULL;
    vm_page_for_families_t* itr =NULL;
    for(itr = first_vm_page_for_families; itr->next; itr = itr->next){

        ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr){
            printf("Struct: %s, struct_size: %d\n", vm_page_family_curr->struct_name, vm_page_family_curr->struct_size);
        } ITERATE_PAGE_FAMILIES_END

    }
}

vm_page_family_t *
lookup_page_family_by_name (char *struct_name){
    vm_page_family_t *vm_page_family_curr = NULL;
     vm_page_for_families_t* itr =NULL;
    for(itr = first_vm_page_for_families; itr->next; itr = itr->next){
        ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr){
            if(strncmp(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME+1)==0){
                return vm_page_family_curr;
            }
        } ITERATE_PAGE_FAMILIES_END
    }

    return NULL;
}




