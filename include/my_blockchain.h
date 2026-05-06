#include "utils.h"
 /*
** define error
*/
#define OK 0
#define ERR_NO_MORE_RESSOURCES 1
#define ERR_NODE_ALREADY_EXIST 2
#define ERR_BLOCK_ALREADY_EXIST 3
#define ERR_NODE_NOT_FOUND 4
#define ERR_BLOCK_NOT_FOUND 5
#define ERR_COMMAND_NOT_FOUND 6
/*
** main.c
*/
int main();
/*
** option.c
*/
t_list* add_node(t_list*, string_array*);
t_list* add_block(t_list*, string_array*);
t_list* create_node(int);
void free_array(string_array*);
int nbr_node(t_list*);
char* find_block(char*);
int is_synced(t_list*);
t_list* my_sync(t_list*, char*);
t_list* recover_savefile(char*);
char* concataine(char*, char*);
void* compare_input(char*, t_list*);
void print_error_message(int);
/*
** blockchain.c
*/
t_list* my_blockchain(t_list*);