/**********************************
 *  RED BLACK SEARCH TREE H file  *
 **********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 50
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

enum _bool {false, true};
typedef enum _bool bool; 

enum _color {black, red}; 
typedef enum _color Color;  

typedef struct _node {
   char *pstr; 
   int max_str; 
   Color color; 
   struct _node* left;
   struct _node* right; 
   struct _node* parent; 
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

/* Clears all space used, and sets pointer to NULL */
void dic_free(dic** s);
