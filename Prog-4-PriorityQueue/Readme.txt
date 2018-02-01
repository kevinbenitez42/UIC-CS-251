


Name:

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.
-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class ans in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.  

Well pretty much I created a node struct that held a value and 
a pointer to another array. in this case, inisde of my priority queue
implementation, i create an array of nodes that held values and where each value in
the array held a pointer to an id. In the array of ids i held the value
of the id and a pointer to the heap value that points to it





-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?

well i had to keep in mind how the pointers work and that made working 
with it really difficult. I had to keep in mind where the pointers where pointing
to at all times so that it could be consistent.





-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?

delete top was not hard in itself. what i really did was call
pq_remove_id on the first element in the heap which references an id i could use
to delete the top. but again it was the memory managment that was difficult. 



-----------------------------------------------
Explain how your implementation of bst_change_priority worked,
why it is correct and why it achieves the runtime requirement.

the way i used change_priority  is by changing the value of a value in the heap. then calling percolate down and up on that element to see if it was posisitoned right in the heap.
this achieves an O(logn) runtime because in the worst case, we traverse all the way up a tree from the deepest node or traverse all the way down to the deepest node from the root.








-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?

well. to get a priority we need an id, the id enabled me to index an array of ids in O(1) and dircetly
direct me to the value of the priority asscoiated with this id.







