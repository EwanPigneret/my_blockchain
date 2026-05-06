#include "my_blockchain.h"
/**
* @summary create a node.
* @param int id: id of the created node.
* @return return the new node created.
*/
t_list* create_node(int id)
{
    t_list* new_node = secure_malloc(sizeof(t_list));
    
    if (new_node == NULL)
    {
        print_error_message(ERR_NO_MORE_RESSOURCES);
        free(new_node);
        return 0;
    }

     new_node->nid = id;
    new_node->next = NULL;

     return new_node;
}

  int same_nid (t_list* head, int id)
{
    int same_nid = 0;

      t_list* current = head;

      while (current != NULL && same_nid == 0) {
                        
        if (current->nid == id) 
        {
            same_nid = 1;
        }
        else {
            same_nid = 0;
        }

          current = current->next;
    }

      return same_nid;
}

  /**
* @summary add a node in a linked list.
* @param s_list* head: first elem of the linked list.
         int id: id of the node.
* @return return the head of the linked list.
*/
t_list* add_node(t_list* head, string_array* array)
{
    t_list* current = head;

     // string_array* array = my_split(str, " ");
    int id = my_atoi(array->array[2]);
    // free_array(array);
     if (current == NULL)
    {
        current = create_node(id); // <------ to the future add elem at elem
        print_error_message(OK);
        return current;
    }

      while (current->next != NULL) 
    {
        current = current->next;
    }
    
    if (same_nid(head, id) == 0) {
    
        current->next = create_node(id);
        print_error_message(OK);
    }
    else {
        print_error_message(ERR_NODE_ALREADY_EXIST);
    }
    return head;
}

  /**
* @summary add a node in a linked list without printing OK.
* @param s_list* head: first elem of the linked list.
         int id: id of the node.
* @return return the head of the linked list.
*/
t_list* add_node_duplicate(t_list* head, int id)
{
    t_list* current = head;
    
    if (current == NULL)
    {
        current = create_node(id); // <------ to the future add elem at elem
        return current;
    }

      while (current->next != NULL) 
    {
        current = current->next;
    }
    
    if (same_nid(head, id) == 0) {
    
        current->next = create_node(id);
    }
    else {
        print_error_message(ERR_NODE_ALREADY_EXIST);
    }
    return head;
}

  /**
* @summary remove a node with a given id.
* @param t_list* head: head a the linked list.
*        int nid: id of the node to find.
* @return return the modified head.
*/
t_list* rm_node(t_list* head, string_array* array)
{
    t_list* current = head;
    t_list* temp = NULL;

     // string_array* array = my_split(str, " ");
    int nid = my_atoi(array->array[2]);
    // free_array(array);
      if (nid == -1)
    {
        head = NULL;
        print_error_message(OK);
        return head;
    }

      if (current == NULL)  // if the head is NULL
    {
        print_error_message(ERR_NODE_NOT_FOUND);
        return head;
    }

      if (current->nid == nid)
    {
        head = head->next;
        print_error_message(OK);
        return head; 
    }

      while (current->next != NULL && current->next->nid != nid)  // searches for the node
    {
        current = current->next;
    }

      if (current->next == NULL)
    {
        print_error_message(ERR_NODE_NOT_FOUND);
        return head;
    }

      temp = current->next;
    current->next = temp->next;

      print_error_message(OK);
    
    free(temp);
    return head;
} 

  /**
* @summary compare 2 block list and see if they have the same bid in them. 
* @param t_block* current_block: the 1st list to compare.
*        t_block* temp_block: the 2nd list to compare.
* @return return an int, 1 if the block id of the lists are equals, 0 if not.
*/
int same_bid (t_block* current_block, t_block* temp_block)
{
    int same_bid = 0;

      while (current_block != NULL && same_bid == 0) {
                        
        if (my_strcmp(current_block->bid, temp_block->bid) == 0) 
        {
            same_bid = 1;
        }
        else {
            same_bid = 0;
        }

          current_block = current_block->next;
    }

      return same_bid;
}

  /**
* @summary create a new block.
* @param int bid: id of the block to create. 
* @return return the new node.
*/
t_block* new_block(t_block* head_block, char* bid, int nid)
{
    t_block* current = head_block;
    t_block* new_block = secure_malloc(sizeof(t_block));

     if (new_block == NULL)
    {
        print_error_message(ERR_NO_MORE_RESSOURCES);
        free(new_block);
        return head_block;
    }

     new_block->bid = bid;
    new_block->next = NULL;

     if (head_block == NULL)  // if no block has been initialised yet
    {
        return new_block;
    }

     if (same_bid(current, new_block) == 1)
    {   
        if (nid != -1)
        {
            print_error_message(ERR_BLOCK_ALREADY_EXIST);
        }
        free(new_block);
        return head_block;
    }

     while (current->next != NULL)
    {
        if (same_bid(current, new_block) == 1)
        {
            if (nid != -1)
            {
                print_error_message(ERR_BLOCK_ALREADY_EXIST);
            }
            free(new_block);
            return head_block;
        }
        current = current->next;
    }
    current->next = new_block;
    new_block->next = NULL;
    return head_block;
}

  /**
* @summary add a new block to a given node.  
* @param t_list* head: head of the linked list.
*        int nid: id of the node in the linked list.
*        char* bid: id to give to the new block.
* @return return the modified head with the new block.
*/
t_list* add_block(t_list* head, string_array* array)
{
    t_list* current = head;
    
    char* bid = secure_malloc(sizeof(char) * my_strlen(array->array[2])); //secure_malloc(sizeof(char) * my_strlen(array->array[2]));
    //my_strcpy(array->array[2], bid);
    my_strcpy(array->array[2], bid);
    // printf("bid = %s : %p\n", bid, bid);
    int nid = my_atoi(array->array[3]);


    if (nid == -1)  // if the nid is *
    {
        while (current != NULL)
        {
            current->head_block = new_block(current->head_block, bid, nid);
            current = current->next;
        }

        print_error_message(OK);
        // free(bid);
        return head;
    }

      while (current != NULL && current->nid != nid)  // seach for the node
    {
        current = current->next;
    }

      if (current == NULL)  // check if the node exist
    {
        print_error_message(ERR_NODE_NOT_FOUND); 
        // free(bid);
        return head;
    }

      current->head_block = new_block(current->head_block, bid, nid);

      if (current->head_block == NULL)  // check if new_block was succefull
    {
        return 0;
    }

    print_error_message(OK);
    // free(bid);
    return head;
}

  /**
* @summary add a new block to a given node without printing OK.  
* @param t_list* head: head of the linked list.
*        int nid: id of the node in the linked list.
*        char* bid: id to give to the new block.
* @return return the modified head with the new block.
*/
t_list* add_block_duplicate(t_list* head, char* bid, int nid)
{
    t_list* current = head;

      if (nid == -1)  // if the nid is *
    {
        while (current != NULL)
        {
            current->head_block = new_block(current->head_block, bid, nid);
            current = current->next;
        }
        return head;
    }

      while (current != NULL && current->nid != nid)  // seach for the node
    {
        current = current->next;
    }

      if (current == NULL)  // check if the node exist
    {
        print_error_message(ERR_NODE_NOT_FOUND);
        return head;
    }

      current->head_block = new_block(current->head_block, bid, nid);

      if (current->head_block == NULL)  // check if new_block was succefull
    {
        return 0;
    }
    return head;
}

  /**
* @summary removes a block inside a linked list.
* @param t_block*: head: head of the linked list.
*        char* bid: id of the block to remove.
* @return return the head once the block has been removed.
*/
t_block* remove_block(t_block* head, char* bid, int nid)
{
    t_block* current = head;

      t_block* temp = NULL;

      if (head == NULL)  // check if the linked list isn't NULL
    {
        print_error_message(ERR_BLOCK_NOT_FOUND);
        return head;
    }

      if (current->next == NULL)  // exception if the linked list only has one element
    {
        if (strcmp(current->bid, bid) != 0)  // if it's not the block that need to be removed
        {   
            if (nid != 0)
            {
                print_error_message(ERR_BLOCK_NOT_FOUND);
            }
            return head;            
        }
        free(head->next);
        head = NULL;
        return head;  // exactly like removing the only block
    }

      while (current->next != NULL && my_strcmp(current->next->bid, bid) != 0)  // search for the block to remove
    {
        current = current->next;
    }

      if (current->next == NULL)  // check if the block has been found
    {
        if (nid != -1)
        {
            print_error_message(ERR_BLOCK_NOT_FOUND);
        }
        return head;
    }

      temp = current->next;
    current->next = temp->next;
    free(temp);
    
    return head;
}

  /**
* @summary removes a given block from the linked list
* @param t_list* head: head of the linked list
*        char* bid: id of the block to remove
*        int nid: id of the node containing the block
* @return return the modified head
*/
t_list* rm_block(t_list* head, string_array* array)
{
    t_list* current = head;
    // string_array* array = secure_malloc(sizeof(string_array));
    // array = my_split(str, " ");
    char* bid = array->array[2];
    int nid = my_atoi(array->array[3]);

      if (nid == -1)  // if the nid is *
    {
        while (current != NULL)
        {
            current->head_block = remove_block(current->head_block, bid, nid);
            current = current->next;
        }

          print_error_message(OK);
        // free_array(array);
        return head;
    }

      while (current != NULL && current->nid != nid)  // search for the node
    {
        current = current->next;
    }

      if (current == NULL)  // check if the node exist
    {
        print_error_message(ERR_NODE_NOT_FOUND); 
        // free_array(array);
        return head;
    }
    current->head_block = remove_block(current->head_block, bid, nid);

      print_error_message(OK);
    // free_array(array);
    return head;
}

  /**
* @summary count number of node in the list.
* @param t_list* head_block: head of the list.
* @return return the number of node.
*/
int nbr_node(t_list* head)
{
    if (head == NULL) {
        return 0;
    }

      int index = 0;
    t_list* current = head;

      while (current != NULL) {
        index += 1;    
        current = current->next;
    }
    return index;
}

  /**
* @summary count number of block in one node.
* @param t_list* head_block: head of block.
* @return return the number of block.
*/
int nbr_elem_in_node(t_block* head_block)
{
    int nbr = 0;
    t_block* current = head_block;

      while (current != NULL) {
        current = current->next;
        nbr += 1;
    }

      return nbr;
}

  /**
* @summary identify the block id once a space is encountered and stop when another one has been encountered.
* @param char* string: string were the block id needs to be found .
* @return return the block id.
*/
char* find_block(char* string)
{
    char* result = secure_malloc(sizeof(char) * 100);
    int index = 0;
    int jndex = 0;
    int cpt = 0;
    while (string[index] != '\0')
    {
        if (cpt == 1)
        {
            while (string[index] != ' ' && string[index] != '\0')
            {
                result[jndex] = string[index];
                index += 1;
                jndex += 1;
            }
        }
        if (string[index] == ' ')
        {
            cpt += 1;
        }
        index += 1;
    }
    return result;
}

  /**
* @summary search for the block id.
* @param char* string: string were the block id needs to be found.
* @return return the block id.
*/
char* find_node(char* string)
{
    char* result = secure_malloc(sizeof(char) * 100);
    int index = 0;
    int jndex = 0;
    int cpt = 0;
    while (string[index] != '\0')
    {
        if (cpt == 0)
        {
            result[jndex] = string[index];
            jndex += 1;
        }
        index += 1;
        if (string[index] == ' ' || string[index] == ':')
        {
            cpt += 1;
        }
    }
    return result;
}

  /**
* @summary to initialise a sync struct.
* @param t_list* head: head of the linked list.
*        t_sync* my_sync_struct: struct sync to initiliase.
* @return return a sync struct.
*/
t_sync* init_sync_struct(t_list* head, t_sync* my_sync_struct)
{
    int index = 0;
    t_list* current = head;
    t_block* current_block = current->head_block;

     my_sync_struct = secure_malloc(sizeof(t_sync));
    my_sync_struct->nbr_block_ref = nbr_elem_in_node(head->head_block);
    my_sync_struct->array_block = secure_malloc(sizeof(char *) * nbr_elem_in_node(head->head_block));
    my_sync_struct->nbr_block_in_check = 0;
    my_sync_struct->nbr_block = 0;

      while (current_block != NULL) 
    {    
        my_sync_struct->array_block[index] = secure_malloc(sizeof(char) * strlen(current_block->bid));
        my_sync_struct->array_block[index] = current_block->bid;
        my_sync_struct->nbr_block += 1;
        
        index += 1;
        current_block = current_block->next;
    }
    
    my_sync_struct->array_check_block = secure_malloc(sizeof(int) * nbr_elem_in_node(head->head_block));

      return my_sync_struct;
}

  /**
* @summary check is the blocks are same.
* @param t_list* head: head of the block list.
*        t_sync* my_sync_struct: is my struct sync init.
* @return return a sync struct.
*/
t_sync* check_same_block(t_block* head, t_sync* my_sync_struct)
{
    t_block* current_block = head;
    int index = 0;
    int save_my_sync_struct_nbr_block_ref = my_sync_struct->nbr_block_ref;
    int compt = 0;
    
    while (current_block != NULL) 
    {   
        while (index < my_sync_struct->nbr_block_ref) 
        {
            if (my_strcmp(my_sync_struct->array_block[index], current_block->bid) == 0) 
            {
                my_sync_struct->array_check_block[index] += 1;
            }
            
            index += 1;
            compt += 1;
        }
        index = 0;
            
        current_block = current_block->next;
        my_sync_struct->nbr_block_in_check += 1;
    }
    my_sync_struct->nbr_block_ref = save_my_sync_struct_nbr_block_ref;
    return my_sync_struct;
}

  /**
* @summary count the number of element in an array.
* @param t_sync* my_sync_struct: struct countaning the array.
* @return return the size of the array.
*/
int total_in_array(t_sync* my_sync_struct){

      int index = 0;
    int compt = 0;

      while (compt < my_sync_struct->nbr_block_ref) {
        index += my_sync_struct->array_check_block[compt];
        compt += 1;
    }

      return index;
}

 void free_sync(t_sync* structure)
{
    free(structure->array_block);
    free(structure->array_check_block);
    free(structure);
}

  /**
* @summary check if the linked list is synced.
* @param t_list* head: head of the linked list.
* @return return 1 if the list is synced, 0 if not.
*/
int is_synced(t_list* head)
{
    if (head == NULL || nbr_node(head) == 1)
    {
        return 1;
    }

      t_list* current = head;
    int synced = 1;
    int index = 0;

     t_sync* my_sync_struct = NULL;
    my_sync_struct = init_sync_struct(current, my_sync_struct);

     current = current->next;
    t_block* current_block = current->head_block;

      while (current != NULL && synced == 1 ) {
        
        my_sync_struct = check_same_block(current_block, my_sync_struct);

          if (my_sync_struct->nbr_block_ref != my_sync_struct->nbr_block_in_check ) {
            synced = 0;
        }

          if (my_sync_struct->nbr_block_ref != total_in_array(my_sync_struct)) {
            synced = 0;
        }
        else {
            while (index < my_sync_struct->nbr_block_ref) {
                my_sync_struct->array_check_block[index] = 0;
                index += 1;
            }
            my_sync_struct->nbr_block_in_check = 0;
            index = 0;
        }

          current = current->next;
        if (current != NULL) {
            current_block = current->head_block;
        }

      }

     free_sync(my_sync_struct);
    return synced;
}

  /**
* @summary to add all block in all node.
* @param t_list* head: it's just my linked list.
* @return return my linked list.
*/
t_list* my_sync(t_list* head, char* empty){
    
    if (head == NULL)
    {
        print_error_message(OK);
        return head;
    }

      (void)empty;
    t_list* current = head;
    t_list* temp = head;
    t_block* temp_block = head->head_block;
    t_block* current_block = temp_block;

      while (temp != NULL) {

          if (is_synced(head) == 1) 
        {
            print_error_message(OK);
            return head;
        }

          if (temp_block == NULL)
        {
            current = head;
            temp = temp->next;
            temp_block = temp->head_block;
            current_block = current->head_block;
        }

          if (current == NULL)
        {
            if (temp_block != NULL) {
            
                temp_block = temp_block->next;

                  if (temp_block != NULL) {
                    current = head;
                    current_block = current->head_block;
                }
         
                if (temp->next == NULL && temp_block == NULL) {
                    print_error_message(OK);
                    return head;
                }

              }
        }
        else {
            if (temp_block != NULL) 
            {
                if (same_bid(current_block, temp_block) != 1) 
                {    
                    if (current_block != NULL) {
                        while (current_block->next != NULL) {
                            current_block = current_block->next;
                        }
                    }
                    add_block_duplicate(head, temp_block->bid, current->nid);  // segfault quand temp_block est NULL
                }               
            }
            
            current = current->next;

              if (current != NULL) {
                current_block = current->head_block;
            }
        }
    }
    print_error_message(OK);
    return head;
}

 /**
* @brief save the current linked list in a file and quit the program.
* @param t_list* head: head of the linked list to save.
*        char* str: string to know if the command quit was called or if the EOF was reached.
* @return return a modified head to tell the program to quit.
*/
t_list* quit(t_list* head, char* string)
{
    t_list* quit = secure_malloc(sizeof(t_list));
    quit->nid = -1;

     if (strcmp(string, "\0") == 0){
        return quit;
    }

     char* filename = "savefile.txt";
    remove(filename);
    int fd = secure_open(filename, O_WRONLY | O_CREAT);
    if (fd == -1)
    {
        return 0;
    }

     chmod(filename, 0777);
    if (write_linked_list(head, fd) == 0)
    {
        close(fd);
        return 0;
    }

     close(fd);
    free_linked_list(head);
    printf("Backing up blockchain...\n");
    return quit;
}

  /**
* @summary read the line given and add the node and the eventual blocks.
* @param t_list* head: head of the linked list were the element are added.
*        char* str: line of character to read.
* @return return the modified head.
*/
t_list* recover_linked_list(t_list* head, char* str)
{
    t_list* current = head;
    char* tmp_id = NULL; //secure_malloc(sizeof(char) * 100);
      if (*str != '\0' && *str != '\n')  // identify the first character which coresponds to the node id 
    {
        tmp_id = find_node(str);
        head = add_node_duplicate(head, my_atoi(tmp_id));  // convert the char as an int
        current = head;
        str += my_strlen(tmp_id);  // go to the end of the node id
        memset(tmp_id, 0, 100);
        free(tmp_id);
    }

      if (head != NULL)
    {
        while (current->next != NULL)   // go to the node that has been added
        {
            current = current->next;
        }
    }

      if (*str != '\0' && *str != '\n')  // skip the character ':'
    {
        str += 1;
    }

      while (*str != '\0' && *str != '\n')  // go trough the rest of the string
    {
        tmp_id = find_block(str);
        head = add_block_duplicate(head, find_block(str), current->nid);  // add the block at the end of the block list
        str += my_strlen(tmp_id) + 1;  // go to the next block id 
        memset(tmp_id, 0, 100);
        free(tmp_id);
    }

     return head;
}

 /**
* @summary read the savefile and convert it back to a linked list.
* @param const char*: filename.
* @return return the head of the linked list.
*/
t_list* recover_savefile(char* filename)
{
    char* str_readline = NULL;
    t_list* head = NULL;
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        return NULL;
    }
    
    while ((str_readline = my_readline(fd)) != NULL)
    {
        head = recover_linked_list(head, str_readline);
        free(str_readline);
    }
    
    close(fd);
    free(str_readline);
    return head;
}

  char* concataine(char* str_1, char* str_2)
{
    int index = 0;
    char* result = secure_malloc(sizeof(char) * (strlen(str_1) + strlen(str_2) + 2));

      strcpy(result, str_1);

      while (str_1[index] != '\0') {
        index += 1;
    }

      result[index] = ' ';
    
    index += 1;

      int index_2 = 0;

      while (str_2[index_2] != '\0') 
    {    
        result[index] = str_2[index_2];
        index += 1;
        index_2 += 1;
    }

     return result;
}

 t_list* select_add(t_list* head, char* input)
{
    string_array* array = my_split(input, " ");

     t_param comutator[] =
    {
        {"node", add_node, 0},
        {"block", add_block, 0},
        {0,0,0}
    };

     t_param* tmp = comutator;

     while (tmp->str != 0) 
    {
        if (my_strcmp(tmp->str, array->array[1]) == 0) 
        {
            head = tmp->func(head, array);
            free_array(array);
            return head;
        }
        
        tmp += 1;
    }
    
    free_array(array);
    print_error_message(ERR_COMMAND_NOT_FOUND);
    return head;
}

 t_list* select_rm(t_list* head, char* input)
{
    string_array* array = my_split(input, " ");

     t_param comutator[] =
    {
        {"node", rm_node, 0},
        {"block", rm_block, 0},
        {0,0,0}
    };

     t_param* tmp = comutator;

     while (tmp->str != 0) 
    {
        if (my_strcmp(tmp->str, array->array[1]) == 0) 
        {
            head = tmp->func(head, array);
            free_array(array);
            return head;
        }
        
        tmp += 1;
    }
    
    free_array(array);
    print_error_message(ERR_COMMAND_NOT_FOUND);
    return head;
}

 t_list* select_ls(t_list* head, char* input)
{
    string_array* array = NULL;
    if (my_strcmp("ls\n", input) == 0) {
        array = my_split("empty ls", " ");
    }else {
        array = my_split(input, " ");
    }

     t_param comutator[] =
    {
        {"-l", print_linked_list, 0},
        {"ls", print_ls, 0},
        {0,0,0}
    };

     t_param* tmp = comutator;

     while (tmp->str != 0) 
    {
        if (my_strcmp(tmp->str, array->array[1]) == 0) 
        {
            head = tmp->func(head, array);
            free_array(array);
            return head;
        }
        
        tmp += 1;
    }
    
    print_error_message(ERR_COMMAND_NOT_FOUND);
    free_array(array);
    return head;
}

 void* compare_input(char* input, t_list* head)
{
    string_array* array = my_split(input, " ");
    
    t_param comutator[] =
    {
        {"add", 0, select_add},
        {"rm", 0, select_rm},
        {"sync", 0, my_sync},
        {"ls", 0, select_ls},
        {"quit", 0, quit},
        {"\0", 0, quit},
        {0,0,0}
    };

     t_param* tmp = comutator;

     while (tmp->str != 0) 
    {
        if (my_strcmp(tmp->str, array->array[0]) == 0) 
        {
            head = tmp->test(head, input);
            free_array(array);
            return head;
        }
        
        tmp += 1;
    }

     print_error_message(ERR_COMMAND_NOT_FOUND);  
    free_array(array);
    return head;
}

 void print_error_message(int err) {
    if (err == OK) {  
        write(1, "OK\n", my_strlen("OK\n"));
    }
    if (err == ERR_NO_MORE_RESSOURCES) {  
        write(1, "1: no more resources available on the computer\n", my_strlen("1: no more resources available on the computer\n"));
    }
    if (err == ERR_NODE_ALREADY_EXIST) {  
        write(1, "2: this node already exists\n", my_strlen("2: this node already exists\n"));
    }
    if (err == ERR_BLOCK_ALREADY_EXIST) {  
        write(1, "3: this block already exists\n", my_strlen("3: this block already exists\n"));
    }
    if (err == ERR_NODE_NOT_FOUND) {  
        write(1, "4: node doesn't exist\n", my_strlen("4: node doesn't exist\n"));
    }
    if (err == ERR_BLOCK_NOT_FOUND) {  
        write(1, "5: block doesn't exist\n", my_strlen("5: block doesn't exist\n"));
    }
    if (err == ERR_COMMAND_NOT_FOUND) {  
        write(1, "6: command not found\n", my_strlen("6: command not found\n"));
    }
}