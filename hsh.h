/*******************************
 *  Double Hashing Header File *
 *******************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXWORD 50
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

typedef enum _bool {false, true} bool;

struct _dic {
   char** arr; 
   int max_str;
   int num_elem;
   int arr_len; 
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
