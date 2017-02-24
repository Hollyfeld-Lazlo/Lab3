#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUTSIZE 64
#define NUMCOMMANDS 4

unsigned char * head;
int blockId;


void allocate(int newSize){
	char *p = head;
	char *end = (p+127);
			printf("newsize: %d \n", newSize);
			printf("address of p : %d , address of end: %d , %d \n", p, end, *p);
	if(newSize > 126){
		printf("Block Size Too Large..\n");
		return;
	}
	while( (p < end) && ((*(p+1) & 1) || (*(p+1) & -2 <= (newSize+1))) ){
			printf("Allocate: while: %d, size while: %d  \n",(*(p+1) & 1), (*(p+1) & -2));
		p = p + 2 + (*(p+1) & -2);
	}
	printf("end: %d, p: %d, end-p: %d, newSize+1: %d\n", end, p, end-p, newSize+1);
	if( (end-p-1) < newSize ){
		printf("Not Enough Room...\n");
	}
	if(p >= head+126){
		printf("Heap is Full...\n");
		return;
	}
	int newBlockSize = newSize +1;
	int oldSize = *(p+1) & -2;
	*(p+1) = newBlockSize | 1;
	if (newBlockSize < oldSize){
		*(p+newBlockSize+2) = ++blockId;
		*(p+newBlockSize+3) = oldSize - newBlockSize - 2;
	}

	printf("newBlockId: %d, newBlockSize: %d, oldSize: %d, : %d  \n", *(p+newBlockSize+2), newBlockSize, oldSize, *(p+newBlockSize+1));
}


void freeBlock(int blockNum){
	
}


void blockList(){
	char *p = head;
	char *end = (p+127);
	char *booleanString[2];
	booleanString[0] = "no";
	booleanString[1] = "yes";
	printf("Size\tAllocated\tStart\t\t\tEnd\n");
	while(p < end){
		printf("%d\t%s\t\t0x%08x\t\t0x%08x \n", 
	 	(*(p+1) & -2), booleanString[(*(p+1) & 1)], p, (p + (*(p+1) & -2) + 1));
		p = p + ((*(p+1) & -2) + 2);
	}
}


void writeHeap(int targetBlock, char payload, int mult){
	char *p = head;
	char *end = (p+127);
	int i;
	printf("writeheap :: payload: %c, mult: %d \n", payload, mult);
	while((p < end) && (*p != targetBlock)){
		printf("block id: %d \n", *p);
		p = p + 2 + (*(p+1) & -2);
	}
	p+=2;
	for(i = 0; i < mult; ++i){
		*(p+i) = payload;
	}							
}


void printHeap(int targetBlock, int mult){
	char *p = head;						
	char *end = (p+127);
	int i;
	printf("printheap :: targetblock: %d, mult: %d \n", targetBlock, mult);
	while((p < end) && (*p != targetBlock)){
		printf(" block id: %d \n", *p);
		p = p + 2 + (*(p+1) & -2);
	}
	p+=2;
	for(i = 0; i < mult; ++i){
		printf("i: %d %c ", i, *(p+i));
	}
	printf("\nend printheap\n");						
}


void printHeader(int targetBlock){
	char *p = head;						
	char *end = (p+127);
	int i;
	printf("targetblock: %d \n", targetBlock);
	while((p < end) && (*p != targetBlock)){
		printf("block id: %d \n", *p);
		p = p + 2 + (*(p+1) & -2);
	}
	printf("%02x%02x\n", *p, *(p+1));
	printf("\n");						
}

void quit(){
	exit(0);
}


///////////////////////////////////////////////////

void processResponse(char response[MAXINPUTSIZE]){
	int count=0, i=0, j=0;
	int args[4];
	char commandTitle[16];
	char payload;

	sscanf(response, "%s", commandTitle);
	printf("response: %s \n", response);
	//count = sscanf(response, "%s %d %d %d %d", commandTitle, &args[0], &args[1], &args[2], &args[3]);
	//printf("count %d\n", count);
	if(!strcmp(commandTitle, "allocate")){
	count = sscanf(response, "%s %d %^d %^d %^d", commandTitle, &args[0]);
		if(count == 2){
			printf("value of arg0: %d", args[0]);
			allocate(args[0]);
		}
		else{
        		printf("Improper use of %s. %d arguments given, 1 expected...\n", commandTitle, count);
			return;
		}
	}					
	else if(!strcmp(commandTitle, "free")){
	count = sscanf(response, "%s %d %^d %^d %^d", commandTitle, &args[0]);
		if(count == 2){
			
		}
		else{
        		printf("Improper use of %s. %d arguments given, 1 expected...\n", commandTitle, count);
			return;
		}
	}				
	else if(!strcmp(commandTitle, "blocklist")){
	count = sscanf(response, "%s %^d %^d %^d %^d", commandTitle);
		if(count == 1){
        		blockList();	
        	}
        	else{
        		printf("Improper use of %s. %d arguments given, 0 expected...\n", commandTitle, count);
        	}
        }
	else if(!strcmp(commandTitle, "writeheap")){
	printf("response in writeheap: %s ...\n", response);
	count = sscanf(response, "%s %d %c %d", commandTitle, &args[0], &payload, &args[2]);
	printf("%d \n", count); 
		if(count == 4){
       			writeHeap(args[0], payload, args[2]);
       		}
       		else{
       			printf("Improper use of %s .%d arguments given, 3 expected... \n", commandTitle, count);
			return;
       		}
       	}			
	else if(!strcmp(commandTitle, "printheap")){
	count = sscanf(response, "%s %d %d %^d %^d", commandTitle, &args[0], &args[1]);
		if(count == 3){
        		printHeap(args[0], args[1]);
        	}
        	else{
       			printf("Improper use of %s .%d arguments given, 2 expected... \n", commandTitle, count);
			return;
        	}
        }
	else if(!strcmp(commandTitle, "printheader")){
	count = sscanf(response, "%s %d", commandTitle, &args[0]);
		if(count == 2){
        		printHeader(args[0]);	
        	}
        	else{
       			printf("Improper use of %s .%d arguments given, 1 expected... \n", commandTitle, count);
			return;
        	}
        }			
	else if(!strcmp(commandTitle, "quit")){	
	count = sscanf(response, "%s", commandTitle);
		if(count == 1){
       			printf("Goodbye ");
			quit();	
       		}
       		else{
       			printf("Improper use of %s .%d arguments given, 0 expected... \n", commandTitle, count);
			return;
        	}			
	}
	else{

		printf("Command Not Recognized\n");
		return;
	}
}
/////////////////////////////////

/////////////////////////////////
int main(int argc, char* argv[]){
	blockId = 1;
	char response[MAXINPUTSIZE];
	head = malloc(128);	
	*head = blockId;		//first byte in head's header is its block number; we start at 1
	*(head+1) = 126;		//second byte in head's heaer is its size in bytes
	
	
	while(1){
		printf("> ");
		if(fgets(response, MAXINPUTSIZE, stdin)!=NULL){
			printf("Your response: %s", response);
			processResponse(response);
		}
		else{
			exit(0);
		}
	}
	return 0;
}
