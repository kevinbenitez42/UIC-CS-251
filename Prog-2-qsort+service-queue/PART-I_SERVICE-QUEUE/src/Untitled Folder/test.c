#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
  LIST* myList = lst_create();
  lst_push_back(myList , 1);
  lst_push_back(myList , 2);
  lst_push_back(myList , 3);
//  printf("%d\n", lst_pop_front(myList));
//  printf("%d\n", lst_pop_front(myList));
//  printf("%d\n", lst_pop_front(myList));
  lst_print(myList);
}
