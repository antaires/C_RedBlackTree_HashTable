/***********************************
 *      (DOUBLE) HASHING           *
 *_________________________________*
 *  QUADRATIC PROBING              *
 *   - Avoids clustering           *
 *   - resizes                     *
 ***********************************/
#include <string.h>
#include <assert.h>

#define HASH_SEED 5381
#define L_START 970031
#define START 31
#define ARR_INCREASE 5
#define LOAD_FACTOR 0.45
#define ELEMENT_RATIO (float) s->num_elem / (float) s->arr_len
#define PRIME 7

/*primary*/
dic* my_dic_init(int size, int len);
unsigned long hash(dic* s, char* str, unsigned long count);
unsigned long hash1(char* str, int seed);
unsigned long hash2(char* str);
void insert_word(dic* s, char* v);
void resize(dic* s);
void rehash(dic* s);

/*helper*/
void add_word(dic* s, char* v, unsigned long index);
void arr_add_word(char** temp_arr, dic* s, int i, int* arr_ind);
char* init_str(dic* s, unsigned long index);
void arr_init_str(char** arr, unsigned long index, int max_string);
bool is_empty(dic* s, unsigned long index);
bool is_same(dic* s, char* v, unsigned long index);
bool isprime(int num);
int prime_gen(int start_num);
int max (int x, int y); 
void insert_null_check(dic* s, char* v);
char** init_arr(char** arr, int len);
void print_dic(dic* s);

/*Create empty dic*/
dic* dic_init(int size)
{
   if (size < 1){
      ON_ERROR("\nSize must be greater than 1");
   }

   /*len must be prime*/
   if ( !isprime(L_START) ){
      ON_ERROR("\nDictionary length must be prime");
   }

   return my_dic_init(size, L_START); 
}

/*Create empty dic with array length len*/
dic* my_dic_init(int size, int len)
{
   int i = 0;
   dic* dl = NULL;

   /*get enough space dic struct*/
   dl = (dic*) calloc(1,sizeof(dic));
   if(dl == NULL){
      ON_ERROR("Creation of Dictionary Failed\n");
   }

   /*calloc space for char** arr in dic*/
   dl->arr = (char**) calloc(len,sizeof(char*));
   if (dl->arr == NULL){
      ON_ERROR("Creation of Array Failed\n");
   }

   /* set all char* pointers in arr to NULL
      calloc space when insert each word    */
   for (i = 0; i < len; i++){
      dl->arr[i] = NULL;
   }

   dl->max_str = size;
   dl->num_elem = 0;
   dl->arr_len = len; 

   return dl;
}

/* Add one element into the dic */
void dic_insert(dic* s, char* v)
{
   if ( v == NULL || s == NULL){
      return; 
   }

   if ( strlen(v) < 1) {
      return; 
   }

   /*resize arr if too full*/
   if ( ELEMENT_RATIO > LOAD_FACTOR ){
      resize(s);
      rehash(s); 
   } 

   insert_word(s, v); 
}

void rehash(dic* s)
{
   int i = 0, j = 0; 
   int old_size = s->arr_len;
   char** temp_arr = NULL; 

   temp_arr = init_arr(temp_arr, s->arr_len); 

   /*fill temp array*/
   for ( i = 0; i < old_size; i++){
      arr_add_word(temp_arr, s, i, &j); 
   }

   /*set s to empty*/
   for (i = 0; i < s->arr_len; i++){

      if (s->arr[i] != NULL){
         free(s->arr[i]); 
      }
   }

   /*re-hash to s*/
   for( i = 0; i < s->arr_len; i++){
      insert_word(s, temp_arr[i]); 
      free(temp_arr[i]); 
   }

   free(temp_arr); 
}

void arr_add_word(char** temp_arr, dic* s, int i, int* arr_ind)
{
   int j = *arr_ind;

   if (temp_arr == NULL || s == NULL){
      ON_ERROR("\nArr_add_word() passed a null value");
   }

   if ( !is_empty(s, (unsigned long) i) ){

      /*calloc space for word and copy it to array*/
      arr_init_str(temp_arr, j, s->max_str); 
      strncpy(temp_arr[j++], s->arr[i], strlen(s->arr[i])); 

      /*empty dictionary array*/ 
      if (s->arr[i] != NULL){
         s->arr[i] = NULL;
      }
   }

   *arr_ind = j; 
}

void arr_init_str(char** arr, unsigned long index, int max_string)
{
   /*get space for word*/
   arr[index] = (char*) calloc(max_string,sizeof(char));
   if (arr[index] == NULL){  
      ON_ERROR("Insert_word() Failed to calloc space for word");
   }
}

char** init_arr(char** arr, int len)
{
   arr = (char**) calloc(len,sizeof(char*));
   if (arr == NULL){
      ON_ERROR("Creation of Array Failed\n");
   }
   return arr; 
}

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v)
{
   unsigned long key = 0;
   unsigned long count = 0;   

   if ( s == NULL || v == NULL){
      ON_ERROR("\nDic_isin() passed NULL value"); 
   }

   if ( strlen(v) < 1){
      return false; 
   }

   key = hash(s, v, count); 

   while ( !is_empty(s, key) ){

         if ( is_same(s, v, key) ){
         return true; 
      }
      /*is there a collision?*/
      ++count;
      key = hash(s, v, count); 
   }
   return false; 
}

/* Clears all space used, and sets pointer to NULL */
void dic_free(dic** s)
{
   int i = 0; 
   dic* p_d = NULL;

   if ( s == NULL ){
      ON_ERROR("\ndic_free() passed a NULL value"); 
   }

   p_d = *s;
   if ( p_d == NULL ){
      return; 
   }

   for (i = 0; i < p_d->arr_len; i++){
      if ( p_d->arr[i] != NULL ){
         free(p_d->arr[i]); 
      }
   }

   free(p_d->arr); 
   free(p_d);    
   p_d = NULL;
}

void insert_word(dic* s, char* v)
{
   unsigned long key = 0;
   unsigned long count = 0;  

   if ( s == NULL || v == NULL ){
      ON_ERROR("Insert_word() passed null value");
   }

   key = hash(s, v, count); 

   while ( !is_empty(s, key) ){

      if ( is_same(s, v, key) ){
         return; 
      }   
      /*is there a collision?*/
      count++;
      key = hash(s, v, count);
   }

   add_word(s, v, key); 
}

void add_word(dic* s, char* v, unsigned long index)
{
   /*set pointer to space, copy word*/
   if (s->arr[index] == NULL){
      s->arr[index] = init_str(s, index); 
   }   
   strncpy(s->arr[index], v, s->max_str); 
   s->num_elem++;
}

char* init_str(dic* s, unsigned long index)
{
   /*get space for word*/
   s->arr[index] = (char*) calloc(s->max_str,sizeof(char));
   if (s->arr[index] == NULL){  
      ON_ERROR("Insert_word() Failed to calloc space for word");
   }
   return s->arr[index]; 
}

void resize(dic* s)
{
   /*increase array size and increment until next nearest prime num*/
   int new_size;
   char** temp;
   int i; 

   if (s == NULL){
      ON_ERROR("\nResize() passed a NULL value");
   }
 
   new_size = prime_gen(s->arr_len * ARR_INCREASE);

   /*realloc space*/
   temp = (char**) realloc(s->arr,sizeof(char*) * new_size);

   if (temp == NULL){
      dic_free(&s); 
      ON_ERROR("\nRealloc failed");
   }
 
   s->arr = temp; 

   /*initialize all new realloced values*/
   for (i = s->arr_len; i < new_size; i++){
      s->arr[i] = NULL; 
   }

   s->arr_len = new_size;

   if (s->arr == NULL){
      dic_free(&s); 
      ON_ERROR("\nResized array...dictionary arr points to NULL");
   }
}

unsigned long hash(dic* s, char* str, unsigned long count)
{
   /*If no collision:     key = h1 
     For every collision, collision count incremented
     and multiplied by h2 thus: 
                          key = h1 + (h2 * collision count) 
     to avoid clustering                                  */
   unsigned long h1 = hash1(str, HASH_SEED);
   unsigned long h2 = hash2(str);
   unsigned long k = h1 + count*h2;
   return (unsigned long) k % s->arr_len;  
}

unsigned long hash1(char* str, int seed)
{
   /*djb2 hash*/
   unsigned long hash = seed;
   int c; 

   while ( (c = *str++) ){
      hash = ((hash << 5) + hash) + c;
   }

   return hash; 
}

unsigned long hash2(char* str){
   /*for probing after collision */
   unsigned long h = 0; 
   unsigned int i; 

   for (i = 0; i < strlen(str); i++){
      h += (unsigned long) str[i]; 
   }
   /*never returns 0*/
   return PRIME - (h % PRIME);
}

bool is_same(dic* s, char* v, unsigned long key)
{
   /*returns true if word v matches word at given key*/
   if ( v == NULL ){
      ON_ERROR("\nIs_same() passed a Null string"); 
   }

   if ( is_empty(s, key) ){
      return false; 
   }

   if ( strncmp(s->arr[key], v, s->max_str) == 0 ){ 
      return true; 
   } 
   return false; 
}

bool is_empty(dic* s, unsigned long key)
{
   if ((int) key >= s->arr_len || (int) key < 0){
      ON_ERROR("Is_empty() encountered index out of bounds");
   }

  if (s->arr[key] == NULL){
     return true; 
  }

   return false;  
}

int max(int x, int y)
{
   if (x > y) {
      return x; 
   } 
   return y; 
}

int prime_gen(int start_num)
{
   /*returns closest prime larger than start_num*/
   while ( !isprime(start_num) ){
      start_num++; 
   }
   return start_num; 
}

bool isprime(int num)
{
   int i = 0; 
      if (num <= 1){
         return false; 
      }
   for (i=2; i<num; i++) {
      if (num % i == 0) {
         return false; 
      }
   }
   return true;
}

void print_dic(dic* s)
{
   int i = 0; 
   
   if (s == NULL){
      return; 
   }

   for (i = 0; i < s->arr_len; i++){
      if ( !is_empty(s, i) ){
         printf("\n[%d] %s", i, s->arr[i]);
      }
   }
}

