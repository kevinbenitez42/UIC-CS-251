#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int MAX = INT_MAX;
struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;
    int numNodes;
    int numLeft;
    int numRight;
   
};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
    int total_work;
};


BST * bst_create(){
  BST * t = malloc(sizeof(struct bst));
  int workdone = 0;
  t->total_work = workdone;
  t->root = NULL;
  
  return t;
}

int bst_sb_work(BST *t){
  return t->total_work;
}

static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST * t){
    free_r(t->root);
    free(t);
}

void toArray(NODE * r, int * bstA, int *count){
  
  if(r==NULL) return;
  toArray(r->left, bstA, count);
  
  bstA[*count] = r->val;
  *count = *count + 1;
  toArray(r->right,bstA, count);

}

int * bst_to_array(BST * t){
  printf("%d", bst_size(t));
  int * bstA = (int*)malloc(sizeof(int) * (bst_size(t) + 1));
  int count = 0;
  toArray(t->root, bstA, &count);
  return bstA;
}
int maxNodes(NODE * r){
  if(r->numLeft > r->numRight){
    return r->numLeft;
  }
  else if(r->numRight > r->numLeft){
    return r->numRight;
  }
}

int minNodes(NODE * r){
  if(r->numLeft > r->numRight){
    return r->numRight;
  }
  else if(r->numRight > r->numLeft){
    return r->numLeft;
  }
}
int isSizeBalanced(NODE * n){
  int max;
  int min;
  if(n->left == NULL && n->right == NULL){
    return 1;
  }
  else if(n->left == NULL && n->right != NULL){
    max = n->numRight;
    min = n->numLeft;
  }
  else if(n->left != NULL && n->right == NULL){
    max = n->numLeft;
    min = n->numRight;
  }
  else{
  min = minNodes(n);
  max = maxNodes(n);
  }


  if(max <= ((2*min) + 1)){
    return 1;
  }
  else{
    return 0;
  }

}
static NODE * insert(NODE *r, int x, int * work){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      leaf->numRight = 0;
      leaf->numLeft  = 0;
      leaf->numNodes = 1;
     
      return leaf;
    }

    if(r->val == x)
        return r;
    if(x < r->val){
        r->left = insert(r->left, x, work);
        r->numNodes++;
    	  r->numLeft++;
        //return r;
    }
    else {
    	  
        r->right = insert(r->right, x, work);
        r->numNodes++;
    	r->numRight++;
        //return r;
    }

if(!isSizeBalanced(r) ){
  int * arr = (int*)malloc(sizeof(int) * r->numNodes);
  int count = 0;
  toArray(r, arr, &count); 
  struct bst * bsdf = bst_from_sorted_arr(arr, r->numNodes);
  *work = bsdf->root->numNodes;
  return bsdf->root;
}
else{

  return r;
}

}


// how about an iterative version?
static NODE *insert_i(NODE *r, int x){

  return NULL;

}


void bst_insert(BST * t, int x){
    int work = 0;
    t->root = insert(t->root, x, &work);
    t->total_work += work;
}

int bst_contains(BST * t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;  
}

static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success, int * work){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;
    return NULL;
  }
  if(r->val == x){
  	
  	r->numNodes--;
    *success = 1;
    

    if(r->left == NULL){
    	
        tmp = r->right;
        free(r);

        return tmp;
    }

    if(r->right == NULL){

        tmp = r->left;
        free(r);
        return tmp;
    }
    // if we get here, r has two children

    r->val = min_h(r->right);
 
    r->right = remove_r(r->right, r->val, &sanity,work);
    if(!sanity)
        printf("ERROR:  remove() failed to delete promoted value?\n");
    return r;

  }
  


  if(x < r->val){
  
    r->left = remove_r(r->left, x, success,work);
    
    if(*success == 1){r->numLeft--; r->numNodes--;}
    
  }
  else {
  	
    r->right = remove_r(r->right, x, success,work);
    
    if(*success == 1){r->numRight--;r->numNodes--;}
  
  }
  
   if(!isSizeBalanced(r)){
          int * arr = (int*)malloc(sizeof(int) * r->numNodes);
          int count = 0;
          toArray(r, arr, &count); 
          struct bst * bsdf = bst_from_sorted_arr(arr, r->numNodes);
           *work = bsdf->root->numNodes;
           return bsdf->root;
        }

  return r;

}


int bst_remove(BST * t, int x){
    int success;
    int work = 0;
    t->root = remove_r(t->root, x, &success,&work);
    t->total_work += work;
    return success;
}
static int size(NODE *r){

    if(r==NULL) return 0;
    return size(r->left) + size(r->right) + 1;
}
int bst_size(BST * t){

    return size(t->root);
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST * t){
    return height(t->root);

}

int bst_min(BST * t){
    return min_h(t->root);
}

int bst_max(BST * t){
    return max_h(t->root);
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("%d ---",isSizeBalanced(r) );
  printf("[%d]  ", r->val);
  printf("%s %d %s %d %s %d\n","nR: ", r->numRight, "nL: ", r->numLeft, "nn: ", r->numNodes);
  inorder(r->right);
   
}
void bst_inorder(BST * t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d\n", r->val);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST * t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

/* 
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
    /* FILL IN FUNCTION */
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST * t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

/* 
 * Write the (recursive) helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */

static NODE * from_arr(int *a, int n){
int m;
NODE *root;

    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->numNodes = n;
    int x = (n-1) - m;
    root->val = a[m];
    
    root->left = from_arr(a, m);
    if(root->left != NULL)
    root->numLeft = m;
    
    root->right = from_arr(&(a[m+1]), n-(m+1));
    if(root->right != NULL)
    root->numRight = x;
    return root;

}

BST * bst_from_sorted_arr(int *a, int n){

  BST * t = bst_create();

  t->root = from_arr(a, n);

  return t;
}


int get_ith(NODE *r, int i){
	for(;;){
	if( i == r->numLeft + 1){
		return r->val;
	}
	else if( i > r->numLeft + 1){
		i = i-(r->numLeft + 1);
		r = r->right;
	}
	else{
		r = r->left;
	}
}
}

int bst_get_ith(BST * t, int i){
       if( (i > t->root->numNodes) || (i <= 0)){
         printf("%s \n", "out of range");
return -1;
}
	return get_ith(t->root, i);
 }

 
int num_geq(NODE* r,int x, int n){
	


		if(r == NULL){
			return n;
		}
		else if(x == r->val){
			return n + r->numRight + 1;
		}
	
		if(x < r->val){
			return num_geq(r->left, x, n + r->numRight + 1);
		
			
		}
		else if(x > r->val){
			num_geq(r->right, x, n);
		}


}


int bst_num_geq(BST * t, int x){
     
	int n = 0;
	n = num_geq(t->root, x, n);
        return n ;
}


int num_leq(NODE* r,int x){
	int n = 0;
	return r->numNodes - num_geq(r,x, n);


}


int bst_num_leq(BST * t, int x){
if(t->root->numNodes < x)
    return t->root->numNodes;
	if( x == 0){
	return num_leq(t->root, x);
}

	return num_leq(t->root, x) +1;
}



void get_near(NODE * r, int x, int * close, int * myVal){
	if(r == NULL){
		return;
	}
	if(abs(x - r->val) < *close){
		*close = abs(x - r->val);
		*myVal = r->val;
	}
	if(x < r->val){
		get_near(r->left, x, close, myVal);
	}
	else{
		get_near(r->right, x, close, myVal);
	}
	
}


int bst_get_nearest(BST * t, int x){
	int myVal = -1;
	int close = MAX;
	get_near(t->root, x, &close, &myVal);
	return myVal;
}

int bst_num_range(BST * t, int min, int max){
	int mymin = bst_num_leq(t, min);
	int mymax = bst_num_leq(t, max);
 
	return mymax - mymin + 1;
}
/*
int max_sb_height(int n) {
                unsigned int big;

                if(n<=0) return -1;
                if(n==1) return 0;
                big = (n-1) - (n/3);  // makes as imbalanced as possible within rules
                                        //    of being size-balanced

                return 1 + max_sb_height(big);
        }
*/
