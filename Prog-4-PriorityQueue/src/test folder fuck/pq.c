#include "pq.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node{
  double val;
  struct node * next;
}NODE;

struct pq_struct {

	NODE * heap;
  NODE * arrID;
    
    int heapFlag;
    int size;
    int capacity;
};



int isMin(PQ * pq);
int printQueue(PQ *pq);
int findLeftChildID(PQ * pq);
int findRightChildID(PQ * pq);
int findParentID(PQ * pq);
void insertAtID(PQ * pq, int id, int priority);
int findLeftChildindex(PQ * pq, int i);
int findRightChildIndex(PQ * pq, int i);
int findParentIndex(PQ * pq,int i);


int main(){
PQ * myPq = pq_create(10, 1);
pq_insert(myPq, 1, 22);
pq_insert(myPq, 2, 4);
pq_insert(myPq, 6, 5);
pq_insert(myPq, 3, 7);
printQueue(myPq);
}
int pq_insert(PQ * pq, int id, double priority){
  if(pq->arrID[id].next != NULL)
    return 0;
  int parentIndex = findParentIndex(pq, pq->size);
  int childIndex  = pq->size;
  
  pq->heap[childIndex].val = priority;
  
pq->heap[childIndex].next = &pq->arrID[id];
pq->arrID[id].val = id;

  if(pq->size == 0){
 
  pq->arrID[id].next = &pq->heap[0];
  pq->heap[0].next = &pq->arrID[id];
  pq->arrID[id].val = id;
  pq->size++;
  return 1;
}



if(parentIndex == -1){return 0;}

int parentVal = pq->heap[parentIndex].val;
int childVal  = pq->heap[childIndex].val;
pq->size++;

 if(isMin(pq) == 1){
   
    for(;;){
     
    if(pq->heap[parentIndex].val >= pq->heap[childIndex].val){
      
      parentVal = pq->heap[parentIndex].val;
      childVal  = pq->heap[childIndex].val;       

      pq->heap[parentIndex].val = childVal;
      pq->heap[childIndex].val  = parentVal;
    
      NODE * temp = pq->heap[parentIndex].next;
      pq->heap[parentIndex].next = pq->heap[childIndex].next;
      pq->heap[childIndex].next = temp;

      pq->heap[parentIndex].next->next = &pq->heap[childIndex];
      pq->heap[childIndex].next->next = &pq->heap[parentIndex]; 
        
    
      

      childIndex  = parentIndex;
      parentIndex = findParentIndex(pq,parentIndex);

    }
    else{
      return 1;
    }
   }
  }

}


int printQueue(PQ * pq){
printf("%s %d\n","size is", pq->size);
printf("%s %d\n","capacity is", pq->capacity);
printf("%s\n","======" );
int i;
for(i = 0; i < pq->size; i++)
{
printf("[%lf] ",pq->heap[i].val);
printf("%s [%lf] \n","(its id is )", pq->heap[i].next->val);
}
printf("%s\n","======" );
}




int isMin(PQ * pq){
	int bool = pq->heapFlag;
	if(bool != 0){
		return 1;
	}
	else{
		return 0;
	}
}




PQ * pq_create(int capacity, int min_heap){
	PQ * myPq  = (PQ*)malloc(sizeof(PQ));
  myPq->heap = (NODE*)malloc(sizeof(NODE) * capacity);
	myPq->arrID   = (NODE*)malloc(sizeof(NODE) * capacity);
  
    myPq->heapFlag = min_heap;
    myPq->size = 0;
    myPq->capacity = 10;
	}




void pq_free(PQ * pq){
	int capacity = pq->capacity;
	free(pq->heap);
	free(pq->arrID);
    pq->size = 0;
  }

void percolateDown(PQ * pq, int id){

}
int pq_remove_by_id(PQ * pq, int id){}
int pq_change_priority(PQ * pq, int id, double new_priority){}
int pq_get_priority(PQ * pq, int id, double *priority){}
int pq_delete_top(PQ * pq, int *id, double *priority){}




int pq_peek_top(PQ * pq, int *id, double *priority){
	

}




int pq_capacity(PQ * pq){
	return pq->capacity;
}




int pq_size(PQ * pq){
	return pq->size;
}




int findLeftChildindex(PQ * pq, int i){
int capacity = pq->capacity;

if( ((2*i + 1) > capacity) || (i < 0) )
	{ return -1; printf("%s\n","index out of bounds" );}

return (2*i) + 1;


}




int findRightChildIndex(PQ * pq, int i){
int capacity = pq->capacity;

if( ((2*i + 2) > capacity) || (i < 0) )
	{ return -1; printf("%s\n","index out of bounds" );}

return (2*i) + 2;

}




int findParentIndex(PQ * pq,int i){

int capacity = pq->capacity;
if(i > capacity || i == 0)
	{return -1; printf("%s\n","index out of bounds");}

return (i - 1) / 2;
}
