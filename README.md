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
- **quit** save the linked list and quit the program. When permorming this command, a message is printed to inform the user the linked list is saved.

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
TODO - How have you solved the problem?

## Installation
TODO - How to install your project? npm install? make? make re?

## Usage
TODO - How does it work?
```
./my_project argument1 argument2
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
