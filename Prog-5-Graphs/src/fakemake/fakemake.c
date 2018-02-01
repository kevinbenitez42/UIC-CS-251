#include <stdio.h>
#include <stdlib.h>
#include "hmap.h"
#include <string.h>
#define INT_MAXIMUM 200000
#define WHITE 0
#define GREY 1
#define BLACK 2
#define BASIC 1
#define TARGET 2


typedef struct lst_node{
	int node_id;
	char * char_id;
	struct lst_node * next;
} LST_NODE;

typedef struct{
	int out_degree;
	int timestamp;
	int type;
	int id;
	char * char_id;
	LST_NODE * neighbors;
} VERTEX;

typedef struct graph{
	int n; // number of vertices
	VERTEX * vertices;// array of vertices
    int time;
    int updateFiles;
} GRAPH;




GRAPH * graph_build(int n){
	GRAPH * g = malloc(sizeof(struct graph));
	g->n = n;
	g->vertices = malloc(n * sizeof(VERTEX));
	int i = 0;
	for(i = 0; i < n; i++){
		g->vertices[i].out_degree = 0;
		g->vertices[i].timestamp = 0;
		g->updateFiles = 0;
		g->vertices[i].neighbors  = NULL;
	}
	return g;
}




void graph_add_edge(GRAPH * g, int u, int v, char * uID){
	LST_NODE * new = malloc(sizeof(LST_NODE));
	new->node_id = v;
	new->char_id = uID;
	new->next = g->vertices[u].neighbors;
	g->vertices[u].neighbors = new;
	g->vertices[u].out_degree++;
}




void graph_free(GRAPH * g){
	int i = 0;
	for(i = 0; i <g->n; i++){
		LST_NODE * cur = g->vertices[i].neighbors;
		while(cur != NULL){
			LST_NODE * temp = cur->next;
			free(cur);
			cur = temp;
		}
	}
	free(g->vertices);
	free(g);
}




void makeBasicOrTarget(GRAPH * g){
        int i;
	for(i = 0; i < g->n; i++){
		if(g->vertices[i].neighbors == NULL){
		   g->vertices[i].type = BASIC;
		}
		else{
		   g->vertices[i].type = TARGET;
		}
	}
}




void dfs_r(GRAPH * g, int src, int * labels){
	LST_NODE * p;
	int v;
	labels[src] = GREY;
	p = g->vertices[src].neighbors;
	while(p!=NULL){
		v = p->node_id;
		if(labels[v] == WHITE){
			dfs_r(g,v,labels);
		}
		else if(labels[v] == GREY){
			printf("%s\n","CYCLE HAS BEEN DETECTED!!!, program aborted" );
			abort();
			
		}
		p = p->next;
	}
	labels[src] = BLACK;
	if(g->updateFiles == 1){
	g->vertices[src].timestamp = g->time;
	g->time++;
	printf("%d %s\n", src , "is up to date" );
}
}




void dfs(GRAPH * g, int src){
	int * labels = malloc(g->n * sizeof(int));
   	int v;
	for(v = 0; v < g->n; v++){
		labels[v] = WHITE;
	}

	dfs_r(g,src,labels);
	free(labels);
}




void printTable(HMAP * dict){
	KV_PAIR * table = hmap_extract_kv_pairs(dict);
	int i;
	for(i = 0; i < hmap_size(dict); i++){
		printf("key: %s ", table[i].key );
		printf("val: %d\n",table[i].val );
	}
}



void hashStrings(HMAP * dict, char * saveString){
int f = 0;
char buf[20000];

char * keys;

strcat(buf, saveString);
keys = strtok (buf," :\n");

while(keys != NULL){

	if(!hmap_contains(dict, keys)){
		hmap_set(dict, keys, f);
			f += 1;
			
		}
     keys = strtok(NULL, " :\n");

  
 }
 
}

char * readFile(char ** argv){
	
	int size = 250;
	char * saveString = (char*)malloc(sizeof(char) * 2000);
    int MAXCHAR = 20000;
FILE *fp;

char str[MAXCHAR];
char * filename = argv[1];
fp = fopen(filename, "r");
    int i = 0;
    while (fgets(str, sizeof(str), fp) != NULL){

       strcat(saveString, str);
   	if(feof(fp)){
    		return saveString;
    	}
    }

fclose(fp);

}


void printList(VERTEX  v){
	LST_NODE * curr = v.neighbors;
	while(curr != NULL){
		printf("->[%d]", curr->node_id );
		curr = curr->next;
	}
	printf("\n");
}




void printAdjHashMap(GRAPH * g, HMAP * dict){
	printTable(dict);
	int type = 0;
	int i;
	for(i = 0; i < g->n; i++){
		
		type = g->vertices[i].type;
		if(type == BASIC){printf("%s ","BASIC" );}
		else if(type == TARGET){printf("%s ","TARGET" );}

		printf("[%d]->",i );
		printList(g->vertices[i]);
		//printf("\n");
	}
	KV_PAIR * pairs = hmap_extract_kv_pairs(dict);

}



GRAPH * createAdjHashMap(HMAP * dict, char * saveString){

GRAPH * g = graph_build(hmap_size(dict));

char * prev = "";
char * newIndex = "em";
char * readin =  strtok (saveString,"\n");

while(readin != NULL){

while(strcmp(readin, ":") == 0 ){	
    
	newIndex = prev;
	readin = strtok(NULL, " \n");
	prev = readin;
	readin = strtok(NULL, " \n");
    
	while(strcmp(readin, ":") != 0 ){
	
	graph_add_edge(g, hmap_get(dict,newIndex), hmap_get(dict, prev), prev);
	
	
	prev = readin;
	readin = strtok(NULL, " \n");

    if(readin == NULL){
    	
    	graph_add_edge(g, hmap_get(dict,newIndex), hmap_get(dict, prev), prev);
    	break;
    }

}
if(readin == NULL){
	break;}
}
if(prev == NULL){
	return g;
}
if(readin == NULL)
	return g;


prev = readin;
readin = strtok(NULL, " \n");


}

return g;
}




void printTime(GRAPH * g){
	printf("%s", "\n");
	printf("%s %d\n","The current time is: ", g->time );
	printf("%s\n","------------------------ " );
	printf("%s", "\n");
}




void updateFile(GRAPH * g, HMAP * dict, char * readin){
	int id = hmap_get(dict,readin);
if(!hmap_contains(dict,readin)){
	printf("%s\n","nothing modified: not a valid" );
}
else if(g->vertices[id].type == BASIC){
	g->vertices[id].timestamp = g->time;
	g->time++;
	printf("%s", "\n");
	printf("%s%s%s\n","file ",readin, " has been modified"  );
	printf("%s", "\n");
}
else{
	printf("%s", "\n");
	printf("%s%s%s\n","file ",readin, " has not been modified"  );
	printf("%s", "\n");
}
    
}


void printTimeStamp(GRAPH * g, HMAP * dict, char * readin){
	int id = hmap_get(dict,readin);
	printf("%s", "\n");
	printf("%s%s%s","time stamp for file ", readin , " is " );
	printf("%d\n",g->vertices[id].timestamp);
	printf("%s", "\n");
}




void printTimeStamps(GRAPH * g, HMAP * dict){
	KV_PAIR * pairs = hmap_extract_kv_pairs(dict);
	for(int i = 0; i < hmap_size(dict); i++){
		printf("%s", "\n");
		printf("%s%s%s\n", "timestamp for key ", pairs[i].key," is ");
		printf("%d", g->vertices[pairs[i].val].timestamp);
		printf("%s", "\n");
	}
}




char * readArg(char * readin, char * arg){
	readin = strtok(NULL, " \n");
	if(readin == NULL){
		printf("%s\n","invalid input" );
		return NULL;
	}
	return readin;
}




void runProgram(GRAPH * g, HMAP * dict){
int bool;
char fstring[1000];
printf("%s","> ");
char * readin;

while(fgets(fstring,1000,stdin)){
 	readin =  strtok (fstring," \n");
 	
if(readin == NULL){

	printf("%s\n","no input, try again" );

}
else if(strcmp(readin, "touch") == 0){

	readin = readArg(readin, "touch");
	if(readin != NULL){
		updateFile(g, dict, readin);
		
	}
	

}
else if(strcmp(readin, "time") == 0){
	printTime(g);
}
else if(strcmp(readin, "timestamp") == 0){

	readin = readArg(readin, "timestamp");
	if(readin != NULL){
		printTimeStamp(g, dict, readin);
	}

}
else if(strcmp(readin, "timestamps") == 0){
	printTimeStamps(g, dict);
}
else if(strcmp(readin, "make") == 0){

	readin = readArg(readin, "make");
	if(readin != NULL){
		dfs( g, hmap_get(dict, readin));
	}

}
else if(strcmp(readin, "quit") == 0){

	printf("%s\n","quitting...." );
	abort();


}
else{
	printf("%s\n","invalid command" );
}
	
	printf("%s","> ");

}
}




void checkCycles(GRAPH * g){
for(int src = 0; src < g->n; src++){dfs( g, src);}
}








int main(int argc, char **argv)
{



	// Here we create a hash map of the files
	// and return the text from the given fakemake



char * saveString = readFile(argv);
HMAP * dict = hmap_create(0,1.0);
hashStrings(dict, saveString);




   // Here we create an adjacency Hash map
   // using the hash map and we check if its
   // acyclic. If the map is acyclic, program is aborted



GRAPH * g = createAdjHashMap(dict, saveString);
makeBasicOrTarget(g);
printAdjHashMap(g,dict);
checkCycles( g);
g->updateFiles = 1;


	// Here we run our program

runProgram(g, dict);



}
