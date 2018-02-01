#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

int main(){
    //int arr [] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
     int arr []  = {2,3,6,7,8,9,11};
    BST * t = bst_from_sorted_arr(arr , 7);
    bst_insert(t, 12);
    bst_insert(t, 13);
    bst_insert(t, 14);
    bst_insert(t, 15);
    bst_insert(t, 16);
    printf("%d\n", bst_num_geq(t,1) );
    //bst_num_range(t,1, 13) ;
    bst_inorder(t);
}


/**
    Test code for bst.c

    NOTE:
        1) This assumes the tester function below is IN bst.c:

        int max_sb_height(int n) {
                unsigned int big;

                if(n<=0) return -1;
                if(n==1) return 0;
                big = (n-1) - (n/3);  // makes as imbalanced as possible within rules
                                        //    of being size-balanced

                return 1 + max_sb_height(big);
        }

        2) For functions that have NOT FOUND as a valid return, it assumes -1 is returned.

        3) Some code is used to provoke errors in the code and won't print out
            a specific error message. It will either crash or print out what
            you have.

        4) The variable "temp" is how many inserts/deletes are done throughout tests.
            This is currently set to 10000. Note that the screen will flood with this
            many FAIL messages in many spots, so maybe set temp to 10-20 at first.

**/
/*
int main(){
    int i;

    printf("DONT FORGET TO DO YOUR WRITEUP\n");

    printf("Starting tests...\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrSize = 10;
    int temp = 0;

    temp = 10;

    BST * t = bst_create();


    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Add a bunch, remove a bunch
    //////////////////////////////////////////////////////////////////////////////////////////////////

    printf("Adding %d and then removing all %d (list should be empty at end):\n", temp, temp);
    printf("");

    for(i = 1; i < temp; i++)
        bst_insert(t, i);

    if(bst_size(t) != temp - 1)
        printf("FAIL (sizes don't match)\n");

    for(i = 1; i < temp; i++)
        bst_remove(t, i);

    printf("Testing remove on invalid values..\n");
    printf("No error message provide. Passes if list is empty at end\n");

    for(i = 1; i < temp; i++)
        bst_insert(t, i);

    for(i = 1; i < (temp * 2); i++)
    {
        bst_remove(t, i);
    }

    if(bst_size(t) == 0)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
    printf("Add/Remove test over.\n\n");


    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Size balance tests:
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Size balance test: start (%d inserts)\nIf becomes unbalanced, will show error message..\n", temp);
    for(i=1; i<temp; i++)
    {
        bst_insert(t, i);
        if(max_sb_height(bst_size(t)) < bst_height(t))
        {
            printf("UH OH: %d  %d  SIZE: %d\n", max_sb_height(bst_size(t)), bst_height(t), bst_size(t));
        }
    }

    printf("Inserts over.\n");
    printf("Size balance test: start (%d removes)\n", temp);

    for(i=1; i<temp; i++)
    {
        bst_remove(t, i);
        if(max_sb_height(bst_size(t)) < bst_height(t))
        {
           printf("UH OH: %d  %d  SIZE: %d\n", max_sb_height(bst_size(t)), bst_height(t), bst_size(t));
        }
    }
    if(bst_size(t) == 0)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");

    printf("Removes over.\n");
    printf("Test over..\n\n");

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Height test
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing height (tests size balancing)\n");
    printf("Will print FAIL if height of BST is over max_height.\n");
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        if(bst_height(t) > max_sb_height(bst_size(t)))
            printf("FAIL\n");

    }
     for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
        if(bst_height(t) > max_sb_height(bst_size(t)))
            printf("FAIL\n");

    }
    if(bst_size(t) == 0)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
    printf("Height test over.\n");

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing get_ith()
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing get_ith()\n");
    printf("Will show FAIL if wrong\n");

    int ith = 0;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        ith = bst_get_ith(t, i);
        if(ith != i)
            printf("FAIL\n");
    }

    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }

    //////////////////////////

    printf("Test over.\n");
    printf("Inserting in reverse order to test get_ith() again..\n");

    for(i = temp; i > 0; i--)
        bst_insert(t, i);

    for(i = 1; i < temp; i++)
    {
        ith = bst_get_ith(t, i);
        if(ith != i)
            printf("FAIL\n");
    }

    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    printf("Test over.\n");

    //////////////////////////////////////////
    printf("Testing get_ith on invalid values (assumes not found returns -1\n");

    for(i = 1; i < temp; i++)
    {

        bst_insert(t, i);
        ith = bst_get_ith(t, temp + 1);
        if(ith != -1)
            printf("FAIL\n");
    }

    for(i = 1; i < temp; i++)
    {
       // bst_inorder(t);
        bst_remove(t, i);
    }
    //printf("%d\n",bst_size(t));

    printf("Test over.\n\n");

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing greater than or equal
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing geq()\nWill print FAIL if wrong\n");

    int val = 1;
    int geq = 0;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        geq = bst_num_geq(t, val);
       // printf("%d\n",geq );
        //printf("%d\n",bst_size(t));
        if(geq != bst_size(t))
            printf("FAIL\n");
    }

    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_geq(t, i);
        if(geq != (temp - i + 1))
            printf("FAIL\n");
    }
    printf("Test over.\n");
    printf("Another test..\n");

    for(i = 1; i < temp; i++)
    {
        geq = bst_num_geq(t, temp + 1);
        if(geq != 0)
            printf("FAIL\n");
    }

    printf("Test over.\n");

    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }

    printf("Test over.\n\n");

    /////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing less than or equal
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing leq()\nWill print FAIL if wrong\n");

    val = 1;
    geq = 0;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        geq = bst_num_leq(t, val);
        if(geq != 1)
            printf("FAIL\n");
    }

    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_leq(t, i);
        if(geq != i)
            printf("FAIL\n");
    }
    printf("Test over.\n");

    ////////////////////////////

    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_leq(t, 0);
        if(geq != 0)
            printf("FAIL\n");
    }
    printf("Test over.\n");

    /////////////////////////////

    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }

    printf("Test over.\n\n");

    /////////////////////
   
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing range
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Test num_range()\nWill print FAIL if wrong\n");

    val = 1;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
    }

    for(i = 1; i < temp; i++)
    {
        val = bst_num_range(t, 1, temp);
        if(val != temp)
            printf("FAIL");
    }

    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        val = bst_num_range(t, -100, temp);
        if(val != temp)
            printf("FAIL");
    }

    for(i = 1; i < temp; i++)
        bst_remove(t, i);

    printf("Test over\n\n");


    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing nearest
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing get_nearest() will print FAIL if wrong\n");

    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        val = bst_get_nearest(t, i);
        if(val != i)
            printf("FAIL\n");
    }

    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }

    printf("Test over.\nAnother test..\n");

    for(i = 1; i < temp; i = i + 10)
    {
        bst_insert(t, i);
    }

    for(i = 1; i < temp; i = i + 10)
    {
        val = bst_get_nearest(t, i - 1);
        if(val != i)
            printf("FAIL\n");
        val = bst_get_nearest(t, i + 1);
        if(val != i)
            printf("FAIL\n");
    }

    printf("Test over (removing in strange way to provoke errors..\n");
    for(i = -100; i < temp; i++)
        bst_remove(t, i);


    printf("Test over.\n\n");

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing bst_from_array and bst_to_array
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Test bst_from_array and bst_to_array\n");

    t = bst_from_sorted_arr(arr, arrSize);
    if(bst_height(t) > max_sb_height(bst_size(t)))
            printf("FAIL\n");

    if(bst_size(t) != arrSize)
        printf("FAIL (sizes don't match)\n");

    val = bst_get_ith(t, 1);
    if(val != arr[0])
        printf("FAILs\n");
    
    val = bst_num_geq(t, arr[arrSize - 1]);
    //printf("%d", val);
    //printf("%d", arrSize);
    //printf("%d", arr[arrSize-1]);
   //printf("%d",  arr[arrSize - 1]);
    if(val != 1)
        printf("FAIL\n");

    val = bst_num_leq(t, arr[0]);
    //printf("%d", val);
    //printf("%d",  arr[arrSize - 1]);
    if(val != 1)
        printf("FAIL\n");

    for(i = -100; i < (arrSize + 200); i++)
        bst_remove(t, i);

    printf("Another test..\n");

    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
    }

    ///////////////////////////

    ///Test bst_to_array, sorted
    int* newArr;

    newArr = bst_to_array(t);

    for(i = 0; i < temp - 2; i++)
    {
        if(newArr[i] > newArr[i+1])
            printf("FAIL\n");
    }

    free(newArr);
     for(i = -100; i < (temp + 200); i++)
        bst_remove(t, i);

    printf("Test over.\n\n");


    printf("Freeing BST\n");
    bst_free(t);
    printf("All tests over.\n");



    return 0;
}
*/