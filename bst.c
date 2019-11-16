/***************************************
 *        RED BLACK SEARCH TREE        *
 *_____________________________________*
 * rebalances after node insertion     * 
 * based on Red-Black properties       *
 * - slower initial set-up but faster  *
 *   searching afterwards              *
 *_____________________________________*
 ***************************************/

#include <assert.h>

#define RED_AUNT a != NULL && a->color == red
#define IS_ROOT n->parent == NULL
#define TREE_BALANCED parent(n)->color == black
#define DOUBLE_LEFT p == gl && n == p->left
#define RIGHT_LEFT p == gr && n == p->left
#define DOUBLE_RIGHT p == gr && n == p->right
#define LEFT_RIGHT p == gl && n == p->right

/*primary*/
void insert_node( Node* r, Node* n);
Node* create_node( dic* s);
void set_node_value( Node* n, char* v);
void isin_tree( Node* n, char* v, bool* isin);
void free_tree( Node* n); 

/*helper*/
void set_new_root(dic* s, Node* n); 
void go_left(Node* r, Node* n);
void go_right(Node* r, Node* n);
void check_left(Node* n, char* v, bool* isin);
void check_right(Node* n, char* v, bool* isin);
void print_tree( Node* n);

/*Create empty dic*/
dic* dic_init(int size) 
{
   dic* dl = (dic*) calloc(1,sizeof(dic));
   if(dl == NULL){
      ON_ERROR("Creation of Dictionary Failed\n");
   }

   if(size < 1) {
      ON_ERROR("Size must be 1 or greater\n");
   }

   dl->max_str = size;
   dl->num_nodes = 0; 

   return dl; 
}

/* Add one element into the dic */
void dic_insert(dic* s, char* v)
{ 
   Node* n;

   if ( v == NULL || s == NULL ){
      ON_ERROR("\nDic_insert() passed a NULL value"); 
   }

   if ( strlen(v) < 1){
      return;
   }

   n = create_node(s); 

   set_node_value(n, v); 

   if ( s->root == NULL ){
      set_new_root(s, n); 
      return;  
   }

   insert_node(s->root, n);
}

void set_new_root(dic* s, Node* n)
{
   s->root = n;
}

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v)
{
   bool isin = false;

   if ( v == NULL || s == NULL ){
      return false; 
   }

   if ( strlen(v) < 1 ){
      return false; 
   }

   isin_tree(s->root, v, &isin);

   if ( isin ){
      return true; 
   }
   return false; 
}

/* Clears all space used, and sets pointer to NULL */
void dic_free(dic** s)
{
   dic* p_d;

   if ( s == NULL ){
      return; 
   }

   p_d = *s;
   if ( p_d == NULL ){
      return; 
   }

   free_tree(p_d->root); 

   free(p_d);    
   p_d = NULL;
}

void free_tree(Node* n)
{
   if (n == NULL){
      return; 
   }

   /*free string on n*/
   if (n->pstr != NULL){
      free(n->pstr);
   }

   /*go left and right*/
   if (n->left != NULL){
      free_tree(n->left);
   } 
   if (n->right != NULL){
      free_tree(n->right);
   }

   free(n);
}

void isin_tree(Node* n, char* v, bool* isin)
{
   /*recursively search tree*/
   int compare; 

   if ( n == NULL || v == NULL ) {
      *isin = false;
      return;
   }

   compare = strcmp(v, n->pstr);

   if ( compare == 0 ) {
      *isin = true;
      return; 
   }

   if ( compare < 0 ){  
 
      check_left(n, v, isin); 

   } else {              

      check_right(n, v, isin); 

   }
   return; 
}

void check_left(Node* n, char* v, bool* isin)
{
   if (n->left == NULL){
      *isin = false;
      return; 
   } else {
      isin_tree(n->left, v, isin);
   }
}

void check_right(Node* n, char* v, bool* isin)
{
   if (n->right == NULL){
      *isin = false;
      return; 
   } else {
      isin_tree(n->right, v, isin); 
   }
}

Node* create_node(dic* s)
{
   Node* n = (Node*) calloc(1, sizeof(Node));

   if ( n == NULL ){
      ON_ERROR("\nFailed to make node"); 
   }

   n->left  = NULL;
   n->right = NULL; 
   n->max_str = s->max_str;

   return n; 
}

void set_node_value(Node* n, char* v)
{
   /*get space for word and point pstr to space*/
   n->pstr = (char*) calloc(n->max_str, sizeof(char));

   if (n->pstr == NULL){
      ON_ERROR("String allocation memory failure\n");
   }  

   strncpy(n->pstr, v, strlen(v));
}

void insert_node(Node* r, Node* n)
{
   /* recursively find correct location and add node there */
   int compare; 

   if ( r == NULL ) {return;}

   compare = strcmp(n->pstr, r->pstr);
   if ( compare == 0 ){    /*don't add duplicates*/
      if (n != NULL) {
         free(n->pstr);
         free(n); 
      }
      return; 
   }

   if ( compare < 0 ){

      go_left(r, n); 

   } else { 

     go_right(r, n);              

   }
} 

void go_left(Node* r, Node* n)
{
   if (r->left == NULL){
      /*add node to r left*/
      r->left = n;
   } else {
      insert_node(r->left, n);
   }
}

void go_right(Node* r, Node* n)
{
   if (r->right == NULL){
      /*add node to r right*/
      r->right = n;
   } else {
      insert_node(r->right, n); 
   }
}

void print_tree(Node* n) 
{
   if ( n == NULL ) {
      return; 
   } else {
      printf("\n%s", n->pstr);
      print_tree(n->left);
      print_tree(n->right); 
   }
   printf("\n");
}
