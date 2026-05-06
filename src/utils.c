#include "my_blockchain.h"
int READLINE_READ_SIZE = 512;

  /**
* @summary recreation of strlen.
* @param char* string: array of character.
* @return return the size.
*/
int my_strlen(char* string)
{
    if (string == NULL)
    {
        return 1;
    }

      int size = 0;
    while (string[size] != '\0')
    {
        size += 1;
    }
    return size;
}

  /**
* @summary malloc the buffer and verify the result of the malloc.
* @param size_t size: size for the malloc.
* @return return the buffer that has been malloc.
*/
void* secure_malloc(size_t size)
{
    char* buff = malloc(size);
    if (buff == NULL)
    {
        print_error_message(ERR_NO_MORE_RESSOURCES);
        return NULL;
    }
    memset(buff, 0, size);
    return buff;
}

  /**
* @summary copy a string into another.
* @param char* string: string that is copied.
*        char* result: where the string is copied.
*/
void my_strcpy(char* string, char* result)
{
    int index = 0;
    // printf("result: %s;\n", result);
    while (string[index] != '\0' && string[index] != '\n')
    {
        // printf("current char: %d\n", string[index]);
        result[index] = string[index];
        index += 1;
    }
    // printf("result: %s;\n", result);
}

  /**
* @summary print the element of a linked list.
* @param t_list* head: head of the linked list.
*/
void print_double_list(t_block* head)
{
    t_block* current = head;

      while (current->next != NULL)
    {
        printf("%s ", current->bid);
        current = current->next;
    }
    printf("%s", current->bid);
}

  /**
* @summary print the element of a linked list.
* @param t_list* head: head of the linked list.
*        int print_block: int telling if the block of the nodes needs to be printed, 1 if yes, 0 if not.
*/
t_list* print_ls(t_list* head, string_array* empty)
{
    (void) empty;
    t_list* current = head;
    while (current != NULL)
    {
        printf("%d", current->nid);
        printf("\n");
        current = current->next;
    }
    return head;
}

  /**
* @summary print the element of a linked list.
* @param t_list* head: head of the linked list.
*        int print_block: int telling if the block of the nodes needs to be printed, 1 if yes, 0 if not.
*/
t_list* print_linked_list(t_list* head, string_array* empty)
{
    (void) empty;
    t_list* current = head;
    while (current != NULL)
    {
        printf("%d", current->nid);
        if (current->head_block != NULL)
        {
            printf(": ");
            print_double_list(current->head_block);
        }
        printf("\n");
        current = current->next;
    }
    return head;
}

  /**
* @summary print the element of a linked list.
* @param t_list* head: head of the linked list.
* @return return 0 if the function failed, else return 1.
*/
int write_double_list(t_block* head, int fd)
{
    t_block* current = head;

      while (current->next != NULL)
    {
        if (secure_write(fd, current->bid, my_strlen(current->bid)) == -1)
        {
            return 0;
        }
        if (secure_write(fd, " ", 1) == -1)
        {
            return 0;
        }
        current = current->next;
    }
    if (secure_write(fd, current->bid, my_strlen(current->bid)) == -1)
    {
        return 0;
    }
    return 1;
}

  /**
* @summary print the element of a linked list.
* @param t_list* head: head of the linked list.
* @return return 0 if the function failed, else return 1.
*/
int write_linked_list(t_list* head, int fd)
{
    char* nid = NULL; //secure_malloc(sizeof(char) * 20);
    t_list* current = head;
    while (current != NULL)
    {
        nid = my_itoa(current->nid);
        if (secure_write(fd, nid, my_strlen(nid)) == -1)
        {
            free(nid);
            return 0;
        }
        if (current->head_block != NULL)
        {
            if (secure_write(fd, ": ", 2) == -1)
            {
                free(nid);
                return 0;
            }
            if (write_double_list(current->head_block, fd) == 0)
            {
                free(nid);
                return 0;
            }
        }
        current = current->next;
        if (secure_write(fd, "\n", 1) == -1)
        {
            free(nid);
            return 0;
        }
        free(nid);
    }
    return 1;
}

  /**
* @summary open the file and verify the result.
* @param char* pathname: name of the path of the file.
*        int flags: flags or option for the open.
* @return return an int corresponding to the error.
*/
int secure_open(char* pathname, int flags)
{
    int result = open(pathname, flags);
    if (result == -1)
    {
        write(2, pathname, my_strlen(pathname));
        write(2, "Open failed\n", my_strlen("Open failed\n"));
        return -1;
    }
    return result;
}

  /**
* @summary write something and verify the result.
* @param int fd: file descriptor.
*        const void* buff: array of character that will be writen.
*        size_t size: size of the array of character.
* @return return an int corresponding to the error.
*/
int secure_write(int fd, const void* buff, size_t size)
{
    int result = write(fd, buff, size);
    if (result == -1)
    {
        write(2, "Write failed\n", my_strlen("Write failed\n"));
        return -1;
    }
    return result;
}

  /**
* @summary read something and verify the result.
* @param int fd: file descriptor.
*        const void* buff: array of character that stocks the array.
*        size_t size: size of the array of character.
* @return return an int corresponding to the error.
*/
int secure_read(int fd, void* buff, size_t size)
{
    int result = read(fd, buff, size);
    if (result == -1)
    {
        write(2, "Read failed\n", my_strlen("Read failed\n"));
        return -1;
    }
    return result;
}

  /**
* @summary recreation of the function strcmp.
* @param char* string1 : first string that is compared.
*        char* string2 : second string that is compared:
* @return return 1 if the first one is superior, 0 if they are equals, -1 if the second one is superior.
*/
int my_strcmp(char* string1, char* string2)
{
    int index = 0;
    
    if (my_strlen(string1) < my_strlen(string2))
    {   
        return -1;
    }
    if (my_strlen(string1) > my_strlen(string2))
    {
        return 1;
    }
    while (string1[index] == string2[index] && string1[index] != '\0' && string2[index] != '\0')
    {
        index += 1;
    }
    if (string1[index] < string2[index])
    {
        return -1;
    }
    if (string1[index] > string2[index])
    {
        return 1;
    }
    return 0;
}

  /**
* @summary give the length of a linked list.
* @param t_list* head: head of list to get the length of.
* @return return the length of the list.
*/
int linked_list_length(t_block* head)
{
    t_block* current = head;
    int index = 0;
    
    while (current != NULL)
    {
        index += 1;
        current = current->next;
    }

      return index;
}

  void free_array(string_array* structure)
{
    int index = 0;
    while (index < structure->size)
    {
        free(structure->array[index]);
        index += 1;
    }
    free(structure->array);
    free(structure);
}

  void free_block_list(t_block* head_block)
{
    // printf("-------- ENTER FREE_BLOCK_LIST --------\n");
    t_block* tmp = head_block;
    // printf("-------- START STAT --------\n");
    // printf("head->nid = %s\n", head_block->bid);
    // printf("-------- FINISH STAT --------\n");
    while (head_block != NULL)
    {
        tmp = tmp->next;
        // printf("head->nid = %s\n", head_block->bid);
        // printf("temp->nid = %s\n", tmp->bid);
        free(head_block->bid);
        free(head_block);
        head_block = tmp;
    }
    // printf("-------- EXIT FREE_BLOCK_LIST --------\n");
}

 void free_linked_list(t_list* head)
{
    // printf("-------- ENTER FREE_LINKED_LIST --------\n");
    t_list* temp = head;
    // printf("-------- START STAT --------\n");
    // printf("head->nid = %d\n", head->nid);
    // printf("-------- FINISH STAT --------\n");
    while (head != NULL)
    {
        temp = temp->next; 
        // printf("head->nid = %d\n", head->nid);
        // printf("temp->nid = %d\n", temp->nid);
        free_block_list(head->head_block);
        free(head);
        head = temp;
    }
    // printf("-------- EXIT FREE_LINKED_LIST --------\n");
}

 /**
* @summary check if 2 linked list are equals.
* @param t_list* head: head of the first linked list.
         t_list* next_head: head of the second linked list.
* @return return 1 if the list are equals, 0 if not.
*/
int compare_linked_list(t_block* head, t_block* next_head)
{
    t_block* current_head = head;
    t_block* current_next_head = next_head;
    int result = 1;

      if (linked_list_length(head) != linked_list_length(next_head))
    {
        return 0;
    }

      while (current_head != NULL)
    {
        if (my_strcmp(current_head->bid, current_next_head->bid) != 0)
        {
            return 0;
        }
        current_head = current_head->next;
        current_next_head = current_next_head->next;
    }

      return result;
}

  char* my_itoa(int nbr)
{
    int save_nbr = nbr;
    char zero_in_char = 48;
    int size = 0;

      if (nbr == 0) {
        return "0";
    }
    
    while (nbr > 0) {
        nbr /= 10;
        size += 1;
    }

      if (nbr < 0) 
    {
        nbr = -1 * nbr;
        save_nbr = nbr;

          while (nbr > 0) {
            nbr /= 10;
            size += 1;
        }

          nbr = save_nbr;
        size += 1;
        char* nbr_in_to_char = secure_malloc(sizeof(char) * (size));

          while (nbr > 0) {
            zero_in_char += (nbr % 10);
            nbr_in_to_char[size -1] = zero_in_char;
            nbr /= 10;
            size -= 1;
            zero_in_char = 48;
        }
        
        nbr_in_to_char[0] = '-';

          return nbr_in_to_char;
    }

     char* nbr_in_to_char = secure_malloc(sizeof(char) * (size + 1));
    nbr = save_nbr;

     while (nbr > 0) {
        zero_in_char += (nbr % 10);
        nbr_in_to_char[size - 1] = zero_in_char;
        nbr /= 10;
        size -= 1;
        zero_in_char = 48;
    }

     return nbr_in_to_char;
}

 void* init_my_readline()
{
    void* buff = secure_malloc(sizeof(char) * READLINE_READ_SIZE);
    return buff;
}

 char* my_readline(int fd)
{
    if (fd == -1)
    {
        return NULL;
    }
    char buff = 0;
    char* result = init_my_readline();
    int index = 0;
    if (result == NULL)
    {
        return NULL;
    }
    while (read(fd, &buff, 1) != 0)
    {
        if (buff == '\n')
        {
            return result;
        }
        result[index] = buff;
        index += 1;
    }
    free(result);
    return NULL;
}

  int count_char (char* string, char character)
{
    int nb_char = 0;
    int index = 0;
    while (string[index] != '\0')
    {
        if (string[index] == character)
        {
            nb_char += 1;
        }
        index += 1;
    }
    return nb_char;
}

 string_array* my_split(char* string, char* separator)
{
    int size = 1;
    int index = 0;
    int temp_index = 0;
    int result_index = 0;
    int nb_occurence = (count_char(string, separator[0]) + 1);
    
    char* temp = secure_malloc(sizeof(char) * my_strlen(string));
    string_array* result = secure_malloc(sizeof(string_array));
    result->array = secure_malloc(sizeof(char *) * nb_occurence);
    result->size = 1;

     while (result_index < nb_occurence)  // initialisation of the array
    {
        while (string[temp_index] != separator[0] && string[temp_index] != '\0' && string[temp_index] != '\n')
        {
            size += 1;
            temp_index += 1;
        }

         result->array[result_index] = secure_malloc(sizeof(char) * size);// Probleme ICI j'alloue de la memoir 
        temp_index += 1;
        result_index += 1;
        size = 1;
    }

      if (my_strcmp(string, "\0") == 0)
    {
        result->array[0] = "\0";
        return result;
    }

      if (nb_occurence == 1)
    {
        my_strcpy(string, result->array[0]);
        return result;
    }

     result_index = 0;
    temp_index = 0;
    while (string[index] != '\0' && string[index] != '\n')
    {
        if (string[index] != separator[0])
        {
            temp[temp_index] = string[index];
            temp_index += 1;
        }
        else {
            my_strcpy(temp, result->array[result_index]); // <-- ET Probleme ICI et je re allou de la memoir par dessus
            result->size += 1;
            result_index += 1;
            temp_index = 0; 
            memset(temp, 0, sizeof(char) * my_strlen(temp));
        }
        index += 1;
    }
    my_strcpy(temp, result->array[result_index]);
    // free(string);    
    free(temp);
    return result;
}

  /**
* @summary convert a string into an int.
* @param char* str: string to convert.
* @return return the converted int.
*/
int my_atoi(char *str)
{
    int index = 0;
    int result = 0;

      if (str[index] == '*')
    {
        return -1;
    }

      if (str[index] == '-')
    {
        exit(1);
    }

      while (str[index] != '\0' && str[index] != ' ')
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            result = result * 10 + (str[index] - '0');
        }
        index++;
    }

      return result;
}