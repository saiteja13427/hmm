#include<stdio.h>

#define PARSE_LINKED_LIST_START(list_ptr, node_ptr)   \
{                                                      \
    struct Node* _node_ptr = NULL;                      \
    node_ptr = list_ptr;                                 \
    for(;node_ptr != NULL ;node_ptr = _node_ptr){      \
        _node_ptr = node_ptr->next;            


#define PARSE_LINKED_LIST_END }}


struct Node{
    struct Node* next;
    int key;
};

int main(){
    struct Node* head;
    head->key = 0;
    struct Node second;
    second.key = 1;
    head->next = &second;
    struct Node* node_ptr = NULL;
    PARSE_LINKED_LIST_START(head, node_ptr){
        printf("%d \n", node_ptr->key);
    } PARSE_LINKED_LIST_END
}