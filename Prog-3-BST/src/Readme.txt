


Name: KEVIN BENITEZ UIN: 654044015

-----------------------------------------------

Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what typedefs did you change and why?

I did a couple of changes to the typedefs. In my bst_node struct, I added 3 new fields:
numNodes that keeps track of the number of nodes in the subtree which includes the root, numLeft
and NumRight, that keeps track of the number of nodes in the left and right subtree respectively.

In my bst struct I added a total work field that keeps track of the total amount of work down,
every time a subtree is imbalanced.

-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

I had to modify bst_insert, bst_remove_ and from_arr.

every time I inserted or removed a new value, i had to maintain numNodes,numLeft,and numRight
for each individual node.

the same case is when i had to rebalance so when I rebalanced i had to maintain numNOdes,numLeft, and numRight in my from_arr function to maintain consistenecy.

everytime there was rebalancing i also had to update the trees total size balancing work

-----------------------------------------------

For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?

every time i updated number of nodes for each respective field, i would do so only when im heading 
down the tree. For example, insert recursively heads down a tree until it finds the right spot to insert. I only ever update each nodes numNode, numLeft, numRight as I traverse a node that would be affected by the insert. Same thing for remove. 

Also for from_arr would automatically reconfigure the nodes in a subtree to be balanced whenever i convert a subtree to an array and back into a subtree. Each node updates heading back up the tree



-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


bst_to_array level of completion: 5  


-----------------------------------------------
bst_get_ith level of completion:  4
    How did you ensure O(h) runtime?

    ANSWER:
	I insured that it is O(h) because the book keeping
	helped out. I did not do a recursive solution but instead I just
	traversed down the tree insuring the numbers on the left of the value 
	of ith was always less greater or equal to ith. at most the node would traverse 
	all the way down to the deepest root

-----------------------------------------------
bst_get_nearest level of completion:  5  

    How did you ensure O(h) runtime?

    ANSWER:
  	my node always recursively travels down the tree and 
	measures how far my value is from each of the nodes.
	it always travels as far as the farthest node in the tree so O(h) 
-----------------------------------------------
bst_num_geq level of completion:  5 

    How did you ensure O(h) runtime?

    ANSWER:
        if value for comparison is less than the node value
	i add number of nodes to the right and collapse into the left node
	if the value for comparisoin is greater i collapse into the right node
 	if its equal i return numbers added up. I only go as far in the worst case
	as the lowest node in the tree

-----------------------------------------------
bst_num_leq level of completion: 5
    How did you ensure O(h) runtime?

    ANSWER:
I use num_geq from my previous function and subtract it from the total number of nodes
in the tree. That way num_geq is O(h) and subtracting it from total number of nodes really
doesnt add anything. I also add special cases for accurate numbers but it does affect the runtime because they are indidiviaul constant time

-----------------------------------------------
bst_num_range level of completion:  5

    How did you ensure O(h) runtime?

    ANSWER:
num range depends on leq and geq in my code which are both O(h), also i do some calculations
to get the right numbers which are constant time so the total is O(h)

-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: 4


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

I ran michaels test cases in which all of my functions are tested with small numbers and really big numbers and they work fine and run as expected and with wierd cases as well. theres also this function max_sb_height that is used to test the size balancing and it works on small numbers and big numbers. Im not completely sure if my size balancing works within the time constraint but runtime works in some cases






