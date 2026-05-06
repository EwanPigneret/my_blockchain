#include "my_blockchain.h"

int main()
{
    t_list* head = NULL;    
    head = my_blockchain(head);    
    if (head == NULL)    
    {    
        return 1;    
    }    
    free_linked_list(head);
    return 0;
}