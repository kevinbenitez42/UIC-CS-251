#include <stdio.h>
#include "io.h"
#include "list.h"

LIST * my_qsort(LIST* l);

int main(){
  LIST *data;


  data = read_ints();
  data = my_qsort(data);
  print_and_destroy(data);
}

LIST *my_qsort(LIST* l){

if(lst_length(l) <= 1){return l;}
if(lst_length(l) == 2){
  if(!lst_is_sorted(l))
  {
    int popped = lst_pop_front(l);
    lst_push_back(l,popped);
    return l;
  }
  return l;
}
LIST* left;
LIST* right;
int pivot = lst_pop_front(l);
left = lst_filter_leq(l, pivot);
right = l;
lst_push_back(left, pivot);
left = my_qsort(left);
right = my_qsort(right);
lst_concat(left, right);
return left;

}



