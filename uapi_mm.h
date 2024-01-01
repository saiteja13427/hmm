//User and LMM interface!!
#include<stdint.h>
#include "mm.h"

void mm_init();

void mm_instantiate_new_page_family(
    char* struct_name, 
    uint32_t struct_size
);

void
mm_print_registered_page_families ();

vm_page_family_t *
lookup_page_family_by_name (char *struct_name);

#define MM_REG_STRUCT(struct_name) mm_instantiate_new_page_family(#struct_name, sizeof(struct_name));

#define LOOKUP_STRUCT(struct_name) lookup_page_family_by_name(#struct_name);