
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

/**
* Toy program experimentally evaluating the runtime
*    of the lst_remove_all_slow function.
*
* NOTE:  uses the library function clock() reports number
*    of micro-seconds elapsed since the program started.
*/

int main(int argc, char *argv[])
{
  LIST *lst;
  unsigned int n = 10000;
  time_t start, end;
  double time_sec;
  int i;

  if (argc == 2)
    sscanf(argv[1], "%u", &n);

  lst = lst_sra_bad_case(n);

  printf("\n  --- RUNTIME TESTS (n=%u) ---\n", n);
  printf("\n    TEST 1:  timing lst_length()\n");
  start = clock();
  if (lst_length(lst) != n)
    printf("       BUG ALERT\n");
  end = clock();
  time_sec = (end - start) / 1000000.0;
  printf("         ELAPSED TIME:                  %.7lf sec.\n", time_sec);

  printf("\n    TEST 2:  lst_remove_all_slow (BAD CASE)\n");

  start = clock();
  lst_remove_all_slow(lst, 0);
  end = clock();

  time_sec = (end - start) / 1000000.0;
  printf("         ELAPSED TIME:                  %.7lf sec.\n", time_sec);

  lst_free(lst);

  lst = lst_create();
  for (i = 0; i < n; i++)
  {
    lst_push_front(lst, 0);
  }
  printf("\n    TEST 3:  lst_remove_all_slow (ALL ZEROES)\n");

  start = clock();
  lst_remove_all_slow(lst, 0);
  end = clock();

  time_sec = (end - start) / 1000000.0;
  printf("         ELAPSED TIME:                  %.7lf sec.\n\n", time_sec);

  lst_free(lst);

  return 0;
}
