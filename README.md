# Welcome to My Blockchain
***

## Task
The task is recreate a functioning blockchain that is saved between each use of the function. A blockchain is made of linked list, were each node is identified by a node ID, named nid, which is an integer.
Each node also contain another linked list made of block, that we will call block list. Each block has a block ID, named bid, which is a string. 

The linked list has 2 states, synced and not synced. The linked list is synced when each node has the same block head. The user can input a command named 'sync' that will syncronise the linked list.
The order of the previously added blocks is not changed when this command is entered.

When the program starts, it checks if a previous linked list exists and recover it if it is the case. In order to inform the user, a message is printed to tell if a linked list existed or not.

The command that the user can perform are the following :
- **add node *nid*** add a node to the linked list with the id *nid*.
- **rm node *nid*** remove a node to the linked list with the id *nid*. If *nid* is '*', then all the nodes are removed.
- **add block *bid* *nid*** add a block with the id *bid*. If *nid* is '*', then all the block is added to all the nodes.
- **rm block *bid* *nid*** remove a block with the id *bid*. If *nid* is '*', then all the block is removed to all the nodes.
- **ls** list all the nodes by their ID.
- **ls -l** list all the node and each block they have by their ID.
- **sync** syncronise the linked list.
- **quit** save the linked list and quit the program. When performing this command, a message is printed to inform the user the linked list is saved.

If a command is succesfull, the program print OK and a newline.
If not the corresponding error is printed :
- 1: no more resources available on the computer
- 2: this node already exists
- 3: this block already exists
- 4: node doesn't exist
- 5: block doesn't exist
- 6: command not found

Each prompt display the following :
- a [ character
- a letter that indicates is the linked list is syncronised or not. "s" if it is syncronised, "-" if not
- the number of nodes in the linked list
- the string "]>"

Exemple for a linked list with 3 nodes that are syncronised : **[s3]>**

## Description
This program is starts an infinite loop that stops whenever the input is "quit" or the command CTRL + C that hard stops the program.
Each input entered by the user is split and calls each function accordingly, then returns the modified linked list. If the input detected is wrong, it calls the corresponding error.
Each loop, the number of nodes and the state of the linked list is calculated to print it. When the sync function is called, a "ghost" linked list is created when each block is added one by one
When quiting the program using the command, a savefile is created where the linked list is written and "Backing up blockchain..." is written in the terminal.
Each line corresponds to a node and it the contains the blocks attached to it.
When launching the program, it checks for the file. If it doesn't exist, it prints "No Backup Found: Starting New Blockchain". If it does, it prints "Restoring From Backup" and recreates the blockchain.

## Installation
There is no installation required for this programm

## Usage
To compile the programm use the command :
```
make
```

To execute it use the command :
```
./my_blockchain
```
