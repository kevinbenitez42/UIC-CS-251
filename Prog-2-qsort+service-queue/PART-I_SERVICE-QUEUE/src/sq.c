#include <stdio.h>
#include <stdlib.h>
#include "sq.h"

typedef int ElemType;
#define FORMAT " %i "
#define DEFAULT 0
typedef struct list_struct LIST;

typedef struct node {
    ElemType val;
    struct node *next;
    struct node *prev;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
    int n;
};


struct service_queue {
    LIST * the_queue;
    LIST * buzzer_bucket;
    NODE ** b2n;
    int b2n_max_index;
    int number_of_buzzers;
    int qLen;
};
LIST *lst_create();
NODE* lst_push_front(LIST *l, ElemType val);
NODE* lst_push_back(LIST *l, ElemType val);
int lst_length(LIST *l);
int lst_is_empty(LIST *l);
ElemType lst_pop_front(LIST *l);
ElemType lst_pop_back(LIST *l);
void lst_print(LIST *l);
void lst_free(LIST *l);
int lst_remove_first(LIST *l, ElemType x);

int number_of_buzzers(SQ *q){
return (lst_length(q->the_queue) + lst_length(q->buzzer_bucket));
}

SQ * sq_create() {
  SQ *q;
  q = malloc(sizeof(SQ));
  q->b2n = (NODE**)malloc(sizeof(NODE*) * 10);
  for(int i = 0; i < 10; i++){q->b2n[i] = (NODE*)malloc(sizeof(NODE));}
  q->qLen = 1;
  q->b2n_max_index = 10;
  q->the_queue = lst_create();
  q->buzzer_bucket = lst_create();
  return q;
}


void sq_free(SQ *q) {
  lst_free(q->the_queue);
  lst_free(q->buzzer_bucket);
  for(int i = 0; i < q->b2n_max_index; i++){q->b2n[i] = NULL;}
  free(q->b2n);
  free(q);
}


void sq_display(SQ *q) {

  printf("current-queue contents:\n    ");
  lst_print(q->the_queue);
  printf("\n");
}

int  sq_length(SQ *q) {
  return lst_length(q->the_queue);
}

void doubleArray(SQ *q){
  NODE ** newArr = (NODE**)malloc(q->b2n_max_index * sizeof(NODE*) * 2);
  for(int i = 0; i < q->b2n_max_index; i++ ){newArr[i] = q->b2n[i];}
  //for(int i = 0; i < q->b2n_max_index; i++ ){free(q->b2n[i]);}
  q->b2n_max_index *= 2;
  //free(q->b2n);
  q->b2n = newArr;
}

int sq_give_buzzer(SQ *q) {
if(number_of_buzzers(q) >= q->b2n_max_index){ doubleArray(q); }
int buzzer;
  if(!lst_is_empty(q->buzzer_bucket)) {
	buzzer = lst_pop_front(q->buzzer_bucket);
  q->b2n[buzzer] = lst_push_back(q->the_queue, buzzer);
	return buzzer;
  }
  else {
	buzzer = sq_length(q);
	q->b2n[buzzer] = lst_push_back(q->the_queue, buzzer);
  if(number_of_buzzers(q) >= q->b2n_max_index){ doubleArray(q); }
	return buzzer;
  }
}

int sq_seat(SQ *q) {
int buzzer;
	if(lst_is_empty(q->the_queue))
	  return -1;
	else{
	  buzzer = lst_pop_front(q->the_queue);
    q->b2n[buzzer] = NULL;
	  lst_push_front(q->buzzer_bucket, buzzer);
	  return buzzer;
	}
}


void removeNode(NODE* node, SQ* q){

  int qval;
  if(node == NULL)
  return;

  if(node->val == q->the_queue->front->val){
    qval = q->the_queue->front->val;
    lst_pop_front(q->the_queue);
    //lst_push_front(q->buzzer_bucket, qval);
  }
  else {
  if(node->prev != NULL)
  node->prev->next = node->next;
  if(node->next != NULL)
  node->next->prev = node->prev;
  free(node);
}

};

int sq_kick_out(SQ *q, int buzzer) {
 if((buzzer >= (number_of_buzzers(q))) ||
           buzzer < 0){
  printf("%s","cant kick this buzzer, no" );
  }
  else if( q->b2n[buzzer] == NULL){
    printf("%s","no existing buzzer in line, no" );
  }else{
  removeNode(q->b2n[buzzer], q);
  q->b2n[buzzer] = NULL;
  lst_push_front(q->buzzer_bucket, buzzer);
}
}


int sq_take_bribe(SQ *q, int buzzer) {
  if(buzzer == q->the_queue->front->val){
  printf("%s","cant bribe someones this buzzer, no" );
}
  else if((buzzer >= (number_of_buzzers(q))) ||
           buzzer < 0){
  printf("%s","cant bribe someones this buzzer, no" );
  }
  else if( q->b2n[buzzer] == NULL){
    printf("%s","no existing buzzer in line, no" );
  }
  else{
  removeNode(q->b2n[buzzer], q);
	lst_push_front(q->the_queue, buzzer);
}
}
/*
if(q->the_queue->front->val == buzzer)
{
  lst_pop_front(q->the_queue);
  lst_push_front(q->buzzer_bucket,buzzer);
}
else if(q->the_queue->back->val == buzzer){
  lst_pop_back(q->the_queue);
  lst_push_front(q->buzzer_bucket,buzzer);
}
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
	return 1;
     }
     p = p->next;
  }
  return 0;
}
NODE * lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  p->prev = NULL;

  if(l->front != NULL)   // was empty, now one elem
  l->front->prev = p;

  l->front= p;
  if(lst_length(l) == 1)
  l->back = l->front;
  (l->n)++;
  return l->front;
}

NODE* lst_push_back(LIST *l, ElemType val) {
NODE *p;
NODE* returnNode;
  if(l->back == NULL){   // list empty - same as push_front
	returnNode = lst_push_front(l, val);
  
  return returnNode;
}
  else {  // at least one element before push
	p = malloc(sizeof(NODE));
	p->val = val;
	p->prev = l->back;
	l->back->next = p;
  p->next = NULL;

	l->back = p;
  (l->n)++;
  return p;
  }

}

ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
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

ElemType lst_pop_back(LIST *l) {
  NODE *p;
  ElemType ret;

    if(l->front == NULL)
      return DEFAULT;

    p = l->front;
    (l->n)--;
    if(p->next == NULL) {
  	// one element: front=back
  	ret = p->val;
  	free(p);
  	l->front = NULL;
  	l->back = NULL;
  	return ret;
    }
    // two or more nodes
    //   find 2nd to last node
    while(p->next != l->back) {
  	p = p->next;
    }
    ret = l->back->val;
    free(l->back);
    l->back = p;
    p->next = NULL;
    return ret;
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
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

ElemType lst_length(LIST *l) {
NODE *p = l->front;
int n=0;

  while(p != NULL) {
    n++;
    p = p->next;
  }
  return n;
}
