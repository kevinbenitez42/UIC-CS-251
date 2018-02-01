
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// very incomplete small test program...

int main() {
LIST *lst1;
LIST *lst2;

int i;

  lst1 = lst_create();
  lst2 = lst_create();

  for(i=0; i<5; i++) {
     lst_push_front(lst1, i);
  }
  for(i=0; i<5; i++) {
     lst_push_back(lst1, i);
  }

  for(i=0; i<5; i++) {
     lst_push_front(lst2, i);
  }
  for(i=0; i<5; i++) {
     lst_push_back(lst2, i);
  }
  lst_print(lst1);
  lst_print(lst2);

}
