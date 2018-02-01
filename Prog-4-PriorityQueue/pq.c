#include "pq.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node{
  double val;
  struct node * next;
  int currentIndex;
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
int percolateDown(PQ * pq,int id);
int percolateUp(PQ * pq, int parentIndex, int childIndex);




int pq_insert(PQ * pq, int id, double priority){
  if(id > pq->capacity - 1)
  	return 0;
  if(pq->arrID[id].next != NULL)
    return 0;
  int parentIndex = findParentIndex(pq, pq->size);
  int childIndex  = pq->size;
  
  pq->heap[childIndex].val = priority;
  
pq->heap[childIndex].next = &pq->arrID[id];
pq->heap[childIndex].next->next = &pq->heap[childIndex];

  if(pq->size == 0){
 
  pq->arrID[id].next = &pq->heap[0];
  pq->heap[0].currentIndex = 0;
  pq->heap[0].next = &pq->arrID[id];
  
  pq->size++;
  return 1;
}

if(parentIndex == -1){return 0;}

pq->heap[childIndex].currentIndex = pq->size;
pq->size++;

return percolateUp(pq, parentIndex, childIndex);
 
}




int percolateUp(PQ * pq, int parentIndex, int childIndex){
int parentVal = pq->heap[parentIndex].val;
int childVal  = pq->heap[childIndex].val;
if(isMin(pq) == 1){
   
    for(;;){
     
    if(pq->heap[parentIndex].val >= pq->heap[childIndex].val && (parentIndex != -1)){
      
      parentVal = pq->heap[parentIndex].val;
      childVal  = pq->heap[childIndex].val;       

      pq->heap[parentIndex].val = childVal;
      pq->heap[childIndex].val  = parentVal;
    
      NODE * temp = pq->heap[parentIndex].next;
      pq->heap[parentIndex].next = pq->heap[childIndex].next;
      pq->heap[childIndex].next = temp;

      pq->heap[parentIndex].next->next = &pq->heap[parentIndex];
      pq->heap[childIndex].next->next = &pq->heap[childIndex]; 

      childIndex  = parentIndex;
      parentIndex = findParentIndex(pq,parentIndex);

    }
    else{
      return 1;
    }
   }
  }else{
   
    for(;;){
     
    if(pq->heap[parentIndex].val <= pq->heap[childIndex].val && (parentIndex != -1)){
      
      parentVal = pq->heap[parentIndex].val;
      childVal  = pq->heap[childIndex].val;       

      pq->heap[parentIndex].val = childVal;
      pq->heap[childIndex].val  = parentVal;
    
      NODE * temp = pq->heap[parentIndex].next;
      pq->heap[parentIndex].next = pq->heap[childIndex].next;
      pq->heap[childIndex].next = temp;

      pq->heap[parentIndex].next->next = &pq->heap[parentIndex];
      pq->heap[childIndex].next->next = &pq->heap[childIndex]; 

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
for(int i = 0; i < pq->size; i++)
{
printf("[%lf] ",pq->heap[i].val);
printf("%s [%lf] ","// id is ", pq->heap[i].next->val);
printf("%s %d ","// index is", pq->heap[i].currentIndex);
printf("\n");
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
  
    for(int i = 0; i < capacity; i++)
    {
    	
    	myPq->arrID[i].val = (double)i;

    }
    myPq->heapFlag = min_heap;
    myPq->size = 0;
    myPq->capacity = capacity;
	}




void pq_free(PQ * pq){
	int capacity = pq->capacity;
	free(pq->heap);
	free(pq->arrID);
    pq->size = 0;
  }




int isLeftBigger(int left, int right){
	if(left < right){
		return 0;
	}
	else if(left > right)
	{
		return 1;
	}
	else{
		return -1;
	}
}




int percolateDown(PQ * pq,int id){
	int parentIndex;         
	int leftChildIndex;      
	int rightChildIndex;
    int someIndex;

	int parentVal; 
	int leftChildVal; 
	int rightChildVal; 
    
	if(isMin(pq) == 1){
	
    for(;;){
	
	parentIndex         = pq->arrID[id].next->currentIndex;
	leftChildIndex      = findLeftChildindex(pq, parentIndex);
	rightChildIndex     = findRightChildIndex(pq, parentIndex);
	
	parentVal     = pq->heap[parentIndex].val;
	leftChildVal  = pq->heap[leftChildIndex].val;
	rightChildVal = pq->heap[rightChildIndex].val;
    if(leftChildIndex > pq->size || rightChildIndex > pq->size){
    	return -1;
    }
	else if(pq->heap[leftChildIndex].next == NULL && pq->heap[rightChildIndex].next == NULL){
    	return -1;
    }
    else if(pq->heap[leftChildIndex].next == NULL && (rightChildVal <= parentVal)){
    	pq->heap[parentIndex].val = rightChildVal;
    	pq->heap[rightChildIndex].val = parentVal;
    	someIndex = rightChildIndex;
    	
    }
    else if(pq->heap[rightChildIndex].next == NULL && (leftChildVal <= parentVal)){
    	pq->heap[parentIndex].val = leftChildVal;
    	pq->heap[leftChildIndex].val = parentVal;
    	someIndex = leftChildIndex;
    }
    else if((isLeftBigger(leftChildVal, rightChildVal) == 1) && (leftChildVal <= parentVal))
    {
    	pq->heap[parentIndex].val = rightChildVal;
    	pq->heap[rightChildIndex].val = parentVal;
    	someIndex = rightChildIndex;
    }
    else if((isLeftBigger(leftChildVal,rightChildVal) == 0) && (rightChildVal <= parentVal))
    {
    	pq->heap[parentIndex].val = leftChildVal;
    	pq->heap[leftChildIndex].val = parentVal;
    	someIndex = leftChildIndex;

    }
    else if((isLeftBigger(leftChildVal, rightChildVal) == -1) && (leftChildVal <= parentVal))
    {
    	pq->heap[parentIndex].val = leftChildVal;
    	pq->heap[leftChildIndex].val = parentVal;
    	someIndex = leftChildIndex;
    }
    else{
    	return -1;
    }
      NODE * temp = pq->heap[parentIndex].next;
      pq->heap[parentIndex].next = pq->heap[someIndex].next;
      pq->heap[someIndex].next = temp;
       
      pq->heap[parentIndex].next->next = &pq->heap[parentIndex];
      pq->heap[someIndex].next->next = &pq->heap[someIndex]; 
     
      
      id = pq->heap[someIndex].next->val;
	}
}
else{
	for(;;){
	
	parentIndex         = pq->arrID[id].next->currentIndex;
	leftChildIndex      = findLeftChildindex(pq, parentIndex);
	rightChildIndex     = findRightChildIndex(pq, parentIndex);
	
	parentVal     = pq->heap[parentIndex].val;
	leftChildVal  = pq->heap[leftChildIndex].val;
	rightChildVal = pq->heap[rightChildIndex].val;


    if(leftChildIndex > pq->size || rightChildIndex > pq->size){
    	return -1;
    }
	else if(pq->heap[leftChildIndex].next == NULL && pq->heap[rightChildIndex].next == NULL){
    	return -1;
    }
    else if(pq->heap[leftChildIndex].next == NULL && (rightChildVal >= parentVal)){
    	pq->heap[parentIndex].val = rightChildVal;
    	pq->heap[rightChildIndex].val = parentVal;
    	someIndex = rightChildIndex;
    	
    }
    else if(pq->heap[rightChildIndex].next == NULL && (leftChildVal >= parentVal)){
    	pq->heap[parentIndex].val = leftChildVal;
    	pq->heap[leftChildIndex].val = parentVal;
    	someIndex = leftChildIndex;
    }
    else if((isLeftBigger(leftChildVal, rightChildVal) == 0) && (leftChildVal >= parentVal))
    {
    	pq->heap[parentIndex].val = rightChildVal;
    	pq->heap[rightChildIndex].val = parentVal;
    	someIndex = rightChildIndex;
    }
    else if((isLeftBigger(leftChildVal,rightChildVal) == 1) && (rightChildVal >= parentVal))
    {
    	pq->heap[parentIndex].val = leftChildVal;
    	pq->heap[leftChildIndex].val = parentVal;
    	someIndex = leftChildIndex;

    }
    else if((isLeftBigger(leftChildVal, rightChildVal) == -1) && (leftChildVal >= parentVal))
    {
    	pq->heap[parentIndex].val = leftChildVal;
    	pq->heap[leftChildIndex].val = parentVal;
    	someIndex = leftChildIndex;
    }
    else{
    	return -1;
    }

     

      NODE * temp = pq->heap[parentIndex].next;
      pq->heap[parentIndex].next = pq->heap[someIndex].next;
      pq->heap[someIndex].next = temp;
       
      pq->heap[parentIndex].next->next = &pq->heap[parentIndex];
      pq->heap[someIndex].next->next = &pq->heap[someIndex]; 
     
      
      id = pq->heap[someIndex].next->val;
}
}
}



int pq_change_priority(PQ * pq, int id, double new_priority){
   

    if(pq->arrID[id].next == NULL)
    	return 0;
 
    if(pq->arrID[id].next != NULL){
	pq->arrID[id].next->val = new_priority;
	percolateDown(pq, id);
	int childIndex = pq->arrID[id].next->currentIndex;
	int parentIndex = findParentIndex(pq, childIndex);
    percolateUp(pq, parentIndex,childIndex);
    return 1;
}
else{ return 0;}

}




int pq_remove_by_id(PQ * pq, int id){
	if(pq->arrID[id].next == NULL)
    	return 0;
	  
	if(pq->arrID[id].next->currentIndex == pq->size - 1){
		pq->arrID[id].next->val = 0;
		pq->arrID[id].next->next = NULL;
		pq->arrID[id].next = NULL;
		pq->size--;
		return 1;
	}
	  int new_priority = pq->heap[pq->size-1].val;
	  pq->heap[pq->size-1].val =  pq->arrID[id].next->val;

	  pq->arrID[id].next->val = new_priority;

	  pq->heap[pq->size - 1].next->next = pq->arrID[id].next;
	  pq->heap[pq->size - 1].next->next->next = pq->heap[pq->size - 1].next;
       
      pq->heap[pq->size - 1].next = &pq->arrID[id];
      pq->arrID[id] = pq->heap[pq->size - 1];

 	   

	  pq->heap[pq->size-1].next->next = NULL;
	  pq->heap[pq->size-1].next = NULL;

      pq_change_priority(pq,id, new_priority);
      pq->size--;
      return 1;
}




int pq_get_priority(PQ * pq, int id, double *priority){
   if(pq->arrID[id].next == NULL)
   	return 0;
   *priority = pq->arrID[id].next->val;
   return 1;
}




int pq_delete_top(PQ * pq, int *id, double *priority){
	if(pq->heap[0].next = NULL)
		return 0;

	*priority = pq->heap[0].val;
	*id       = (int)pq->heap[0].next->val;
	pq_remove_by_id(pq, pq->heap[0].next->val);

	return 1;
}




int pq_peek_top(PQ * pq, int *id, double *priority){
	if(pq->heap[0].next == NULL)
		return 0;
	*id = (int)pq->heap[0].next->val;
	*priority = pq->heap[0].val;
	
    return 1;
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
