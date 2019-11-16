/**********************************
 *     Simple BST Header file     *
 *________________________________*
 *  redblack.c and redlback.h also*
 * uploaded for a Red Black Tree  *
 **********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 50
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

enum _bool {false, true};
typedef enum _bool bool; 

typedef struct _node {
   char *pstr; 
   struct _node* left;
   struct _node* right; 
   int max_str; 
} Node;

struct _dic {
   Node* root;
   int max_str;   
   int num_nodes;
};
typedef struct _dic dic; 


/*Create empty dic*/
dic* dic_init(int size); 

/* Add one element into the dic */
void dic_insert(dic* s, char* v);

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void dic_free(dic** s);
