#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    int count ;
    NODE *front;
    NODE *back;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  return l;
}

void lst_free(LIST *l) {
NODE *p = l->front;
NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST
  free(l);
}

void lst_print(LIST *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}


/**
* TODO:
*   function:  lst_are_equal
*   description:  returns true(1) if lst1 and lst2
*      contain exactly the same sequenc of values.
*      Returns 0 otherwise.
**/
int lst_are_equal(LIST *lst1, LIST *lst2) {
  NODE *node1 = lst1->front;
  NODE *node2= lst2->front;

  while((node1 != NULL) && (node2 != NULL)){

    if(node1->val == node2->val){
      node1 = node1->next;
      node2 = node2->next;
    }
    else{
      return 0;
    }
  }
  if((node1 == NULL) && (node2== NULL))
  {
    return 1;
  }
  else{
    return 0;
  }
}

/**
* TODO:  print in reverse order
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/

void print_node(NODE* node)
{
  if(node->next != NULL){
  print_node(node->next);
}
  printf("%d ",node->val);
}
void lst_print_rev(LIST *l) {
    if(l->front == NULL)
    {
      printf("%s\n","[ ]" );
    }
    else{
    printf("%s","[ " );
    print_node(l->front);
    printf("%s\n"," ]");
  }
}

void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));
l->count++;
  p->val = val;
  p->next = l->front;

  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;

}

void lst_push_back(LIST *l, ElemType val) {
NODE *p;
l->count++;
  if(l->back == NULL)   // list empty - same as push_front
	lst_push_front(l, val);
  else {  // at least one element before push
	p = malloc(sizeof(NODE));
	p->val = val;
	p->next = NULL;
	l->back->next = p;

	l->back = p;

  }
}

/** TODO
*   modifications to enable this operation
*   to execute in O(1) time.  (You will almost
*   certainly modify other functions and the
*   data structure itself -- see header).
**/
int lst_length(LIST *l) {
return l->count;
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
}


/** TODO
 *    function:  lst_count
*     description:  Counts number of occurrences
*     		of x in the list and returns
*     		that value.
*/
int lst_count(LIST *l, ElemType x) {
  int count;
  NODE *p = l->front;
  while(p != NULL)
  {
    if(p->val == x)
    count++;
    p = p->next;
  }
  return count;
}


/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/
int lst_sanity1(LIST *l) {
  if(l->front == NULL && l->back != NULL){
	fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
	return 0;
  }
  if(l->back == NULL && l->front != NULL){
	fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
	return 0;
  }
  return 1;
}

int lst_sanity2(LIST *l) {
  if(l->back != NULL && l->back->next != NULL) {
	fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
	return 0;
  }
  return 1;
}

/*
* function:  find_back()
* description:  returns a pointer to the last
*               node of the given list.
*		Note that we are operating at
*		the "node level".
*
*		if p is NULL, NULL is returned.
*
* purpose:  mostly for debugging -- enables sanity3
*/
static NODE * find_back(NODE *p) {

  if(p ==  NULL)
	return NULL;

  while(p->next != NULL) {
	p = p->next;
  }
  return p;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l) {
NODE *real_back;

  real_back = find_back(l->front);

  return (real_back == l->back);
}



ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
l->count--;

  if(lst_is_empty(l))
	return DEFAULT;   // no-op

  ret = l->front->val;

  if(l->front == l->back) {  // one element
	free(l->front);
	l->front = NULL;
	l->back = NULL;
  }
  else {
	p = l->front;  // don't lose node being deleted
	l->front = l->front->next;  // hop over
	free(p);
  }

  return ret;
}





/* TODO
*
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l){

  l->count--;
  NODE* p = l->front;
  NODE* temp;
  int save;
  if(l->front == l->back && l->front != NULL)
  {
    save = p->val;
    free(l->front);
    l->front == NULL;
    l->back == NULL;
   return save;
  }
  while(p != NULL)
  {

    if(p->next->next == NULL)
  {
    temp = p->next;
    save = temp->val;
    p->next = NULL;
    free(temp);
    l->back = p;
    return save;
  }
  p = p->next;
  }
  return 1;
}
/* TODO
*  For full credit, you cannot allocate any new memory!
*
*  description:  self-evident
*/
void lst_reverse(LIST *l) {
if(l->front == NULL);
  return;
  NODE* p = l->front;
  NODE* temp;

  temp = l->back;
  while(p != NULL){
    if(p->next == NULL){
      l->back = l->front;
      l->front = temp; break;
    }
    else if (p->next->next == NULL)
    {
      p->next->next = p;
      p->next = NULL;
      p = l->front;
    }
    else{
      p = p->next;
    }
  }

}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/

int lst_remove_first(LIST *l, ElemType x) {
NODE *p;
NODE *tmp;

  if(l->front == NULL) return 0;
  if(l->front->val == x) {
	lst_pop_front(l);
	return 1;
  }
  // lst non-empty; no match on 1st elem
  p = l->front;

  while(p->next != NULL) {
     if(x == p->next->val) {
	tmp = p->next;
	p->next = tmp->next;
	if(tmp == l->back)
	    l->back = p;
	free(tmp);
  l->count--;
	return 1;
     }
     p = p->next;
  }
  return 0;
}


/**
* function: lst_remove_all_slow
* description:  removes all occurrences of x
*   from given list (if any).
*   Returns number of occurrences (i.e., deletions).
*
* notes:  it is called "slow" because in the worst
*   case, it takes quadratic time.
*   (Discussion of why and when this happens is a
*   lecture topic).
*/
int lst_remove_all_slow(LIST *l, ElemType x) {
int n=0;
  while(lst_remove_first(l, x))
	n++;
  return n;
}

/**
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that
 * the above function takes quadratic time to remove
 * all occurrences of a specified value.
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {
LIST *l = lst_create();
int i;
int k=n/2;

  for(i=0; i<k; i++) {
	lst_push_front(l, 0);
  }
  for(i=0; i<n-k; i++) {
	lst_push_front(l, 1);
  }
  return l;
}

/** TODO
*   function:  lst_remove_all_fast
*   description:  same behavior/semantics as
*      lst_remove_all_slow.  However, this function
*      must guarantee linear time worst case
*      runtime (hence, "fast").
*
*   REQUIREMENT:  linear worst-case runtime.
*
*   Note:  your solution may be either recursive or
*   iteratieve.
**/
int lst_remove_all_fast(LIST *l, ElemType x){

NODE* temp;
while(l->front->val == x){lst_pop_front(l);}
while(l->back->val == x){lst_pop_back(l);}
NODE* p = l->front;
  while((p != NULL) && (p->next != NULL)){
    if((p->next->val == x) && (p->next != NULL))
    {
      temp = p->next;
      p->next = temp->next;
      l->count--;
      free(temp);
    }
  p = p->next;
  }

  return 1;
}

int lst_is_sorted(LIST *l){
NODE *p = l->front;

  while(p!=NULL && p->next != NULL) {
	if(p->val > p->next->val)
	  return 0;
	p = p->next;
  }
  return 1;
}



/** TODO
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {
  if(l->front == NULL){
    l->front = (NODE*)malloc(sizeof(NODE));
    l->front->next = NULL;
    l->front->val = x;
    l->count++;
  }
  else{
NODE *p = l->front;
l->count++;
NODE *newNode = (NODE*)malloc(sizeof(NODE));
newNode->val = x;
newNode->next = NULL;

while(p != NULL)
{
  if(p->val > x){break;}
  if(p->next == NULL){
    p->next = newNode;
    l->count++;
    break;
  }
  if(x <= p->val)
  {
   newNode->next = p->next;
   p->next = newNode;
  }
  p = p->next;
}
}
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted,
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 *      Condition in which both parameters are the same
 *      list (not merely "equal"), the function simply
 *      does nothing and returns.  This can be tested
 *      with simple pointer comparison.
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 *
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
 static NODE * merge_rec(NODE* a, NODE *b){
   if(a == NULL)
   return b;
   if(b == NULL)
   return a;
   if(a->val <= b->val){
     a->next = merge_reg(a->next,b);
     return a;
   }
   else{
     b->next = merge_rec(a,b->next);
     return b;
   }
 }
 void lst_merge_sorted(LIST *a, LIST *b){
   NODE *m;
   m = merge_rec(a->front, b->front);
   a->front = m;
   if(b->back != NULL && b->back->next == NULL)
   a->back = b->back;
   a->n += b->n;
   b->n = 0;
   b->front = NULL;
   b->back = NULL;
   
 }




/**
* TODO
* function:  lst_filter_leq
*
* description:  removes all elements of the given list (lst) which
*		are less than or equal to a given value (cutoff)
*
*		A list containing the removed elements is returned.
*
* examples:
*
*	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
*		cutoff:  4
*
*		after call:
*			lst:  [9, 8, 12, 7]
*			returned list:  [4, 2, 4, 3]
*
*       -----------------------------------------
*	EX2: 	lst:  [6, 5, 2, 1]
*		cutoff:  6
*
*		after call:
*			lst:  []
*	 		returned list:  [6, 5, 2, 1]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) where n is the length of the given list
*
*       ORDERING:  the ordering of the returned list should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*
*/

NODE* removeNode(NODE* node1)
{
  NODE* temp;
  temp = node1->next;
  node1->next = node1->next->next;
  return temp;
}

static void pback_node(LIST *lst, NODE* p){

  p->next = NULL;
  if(lst->front == NULL)
  lst->front= lst->back = p;
  else{
    lst->back->next = p;
    lst->back = p;
  }
  lst->n++;
}

LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
  LIST *leq;
  int nleq=0;
  NODE *p;

  leq = lst_create();
  p = lst->front;
  lst->front = NULL;
  lst->back = NULL;
  lst->n = 0;

  while(p != NULL){
    if(p->val <= cutoff){
      pback_node(leq,p);
    }
    else{
      pback_node(lst, p)
    }
    p=p->next;
  }
  return leq;
}
/**
* TODO
* function:  lst_concat
*
* description:  concatenates lists a and b; resulting
*    concatenation is reflected in list a; list b becomes
*    empty.
*
*    example:
*
*	EX1:  a: [2, 9, 1]
*	      b: [5, 1, 2]
*
*	after call:
*
*		a: [2, 9, 1, 5, 1, 2]
*		b: []
*
* REQUIREMENTS:
*
*     runtime:  O(1)
*
*     sanity:  this operation makes sense when a and b
*		are distinct lists.  For example, we don't
*		want/allow the caller to do something like
*		this:
*
*			LIST *my_list;
*
*			lst_push_front(my_lst, 4);
*			lst_push_front(my_lst, 2);
*
*			lst_concat(my_lst, my_lst);
*
*		your implementation must detect if it is being
*		called this way.  If so the function does nothing
*		and (optionally) prints an error message to
*		stderr.
*
*/

void lst_concat(LIST *a, LIST *b) {
  if(a->front == b->front)
  {
    printf("%s\n","error" );
    return;
  }
  NODE * p = a->front;
  NODE * p2 = b->front;
  if( p == NULL){
    a->front = b->front;
    a->back = b->back;
    b->front = NULL;
    return;
  }
a->back->next = b->front;
b->front = NULL;
while(p2 != NULL)
{
  a->back = p2;
  p2 = p2->next;
}
}
