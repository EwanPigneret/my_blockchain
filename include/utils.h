#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
 
 /*
** structs
*/
typedef struct s_string_array
{
    int size;
    char** array;
} string_array;

 typedef struct s_block {
    char* bid;              // block id
    struct s_block* next;   // next block
} t_block;

 typedef struct s_list {
    int nid;                // node id
    struct s_block* head_block;   // block head
    struct s_list* next;    // next node
} t_list;

 typedef struct s_sync {
    int nbr_block;
    int nbr_block_ref;      //nbr of block reference
    int nbr_block_in_check;  //nbr of block in check
    char** array_block;     //array of my block to check if existe              | ["B3", "B1", "B10", "B4"]
    int* array_check_block; //array to my block exist 1 if exist 0 is not exist | [0 , 0 , 0. , 0 ] 
}t_sync;

 typedef struct s_param {
    char* str;
    t_list*(*func)(t_list*, string_array*);
    t_list*(*test)(t_list*, char*);
}t_param;

 /*
** utils.h
*/
int my_strlen(char*);
void* secure_malloc(size_t);
void* secure_malloc_1(size_t);
void print_double_list(t_block*);
t_list* print_ls(t_list*, string_array*);
t_list* print_linked_list(t_list*, string_array*);
int write_linked_list(t_list*, int);
int secure_open(char*, int);
int secure_write(int, const void*, size_t);
int secure_read(int, void*, size_t);
int my_strcmp(char*, char*);
void my_strcpy(char*, char*);
string_array* my_split(char*, char*);
int linked_list_length(t_block*);
void free_linked_list(t_list*);
int compare_linked_list(t_block*, t_block*);
char* my_itoa(int);
string_array* my_split(char*, char*);
int my_atoi(char*);
char* my_readline(int);