#include "my_blockchain.h"
/**
* @brief recover the linked list when the program starts, print info about the linked list and read the input of the user.
* @param t_list* head: head of the linked list.
* @return return the linked list once the program is done.
*/

t_list* my_blockchain(t_list* head)
{
    char* nbr = NULL;
    int loop = 1;
    t_list* tmp = NULL;
    char* buff = NULL;

    head = recover_savefile("savefile.txt");
    if (head == NULL)
    {
        printf("No Backup Found: Starting New Blockchain\n");
    }
    else
    {
        printf("Restoring From Backup\n");
    }

    while (loop)
    {
        nbr = my_itoa(nbr_node(head));
        if (is_synced(head) == 1) 
        {
            write(1, "[s", 2);
            write(1, nbr, my_strlen(nbr));
            write(1, "]>", 2);
        }
        else
        {
            write(1, "[-", 2);
            write(1, nbr, my_strlen(nbr));
            write(1, "]>", 2);
        }

        buff = secure_malloc(sizeof(char) * 100);

        if (secure_read(0, buff, 100) == -1)
        {
            return NULL;
        }
        
        tmp = compare_input(buff, head);

        if (tmp != NULL)
        {
            if (tmp->nid == -1)
            {
                loop = 0;
            }
        } 
        
        head = tmp;
        free(buff);
    }
    // free(nbr);
    return head;
}