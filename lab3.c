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
	while((p < end) && ((*(p+1) & 1) || (*(p+1) & -2 <= (newSize+1)))){
		printf("allocated while: %d, size while: %d  \n",(*(p+1) & 1), (*(p+1) & -2));
		p = p + 2 + (*(p+1) & -2);
	}
	if(p >= head+126){
		printf("Heap is Full...\n");
		return;
	}
	int newBlockSize = ((newSize +1) >> 1) << 1;
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
	while(p < end){
		printf("size: %d, allocated: %d, start add: %d, end add: %d \n", 
					(*(p+1) & -2), (*(p+1) & 1), p, (p + (*(p+1) & -2) + 1));
		p = p + ((*(p+1) & -2) + 2);
	}
}

void writeHeap(int targetBlock, char payload, int mult){
	char *p = head;
	char *end = (p+127);
	int i;
	printf("payload: %c, mult: %d", (char)payload, mult);
	while((p < end) && (*p != targetBlock)){
		printf("block id: %d \n", *p);
		p = p + 2 + (*(p+1) & -2);
	}
	for(i = 0; i < mult; ++i){
		*(p+2+i) = payload;
	}							
}

void printHeap(int targetBlock, int mult){
	char *p = head;						
	char *end = (p+127);
	int i;
	printf("targetblock: %d, mult: %d", targetBlock, mult);
	while((p < end) && (*p != targetBlock)){
		printf("block id: %d \n", *p);
		p = p + 2 + (*(p+1) & -2);
	}
	for(i = 0; i < mult; ++i){
		printf("%c", *(p+2+i));
	}
	printf("\n");						
}

void printHeader(int targetBlock){
	char *p = head;						
	char *end = (p+127);
	int i;
	printf("targetblock: %d", targetBlock);
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

/*void parseResponse(char response[MAXINPUTSIZE]){
	char delim[] = " ";
	char *token;

	for (token = strtok(response, delim); token; token = (NULL, delim)){
		
	}
}*/

void processResponse(char response[MAXINPUTSIZE]){
	int count, i, j;
	int args[4];
	char commandTitle[16];
	count = sscanf(response, "%s %d %c %d %d", commandTitle, &args[0], &args[1], &args[2], &args[3]);
	printf("count %d\n", count);
	if(!strcmp(commandTitle, "allocate")){
		if(count == 2){
			printf("value of arg0: %d", args[0]);
			allocate(args[0]);
		}
		else{
			printf("Improper use of %s...\n", commandTitle);
			return;
		}
	}					
	else if(!strcmp(commandTitle, "free")){
		if(count == 2){
			
		}
		else{
			printf("Improper use of %s...\n", commandTitle);
			return;
		}
	}				
	else if(!strcmp(commandTitle, "blocklist")){
		if(count == 1){
        		blockList();	
        	}
        	else{
        		printf("Improper use of %s...\n", commandTitle);
        	}
        }
	else if(!strcmp(commandTitle, "writeheap")){
		if(count == 4){
       			writeHeap(args[0], (char)args[1], args[2]);
       		}
       		else{
       			printf("Improper use of %s ... \n", commandTitle);
			return;
       		}
       	}			
	else if(!strcmp(commandTitle, "printheap")){
		if(count == 3){
        		printHeap(args[0], args[1]);
        	}
        	else{
        		printf("Improper use of %s...\n", commandTitle);
			return;
        	}
        }
	else if(!strcmp(commandTitle, "printheader")){
		if(count == 2){
        		printHeader(args[0]);	
        	}
        	else{
        		printf("Improper use of %s...\n", commandTitle);
			return;
        	}
        }			
	else if(!strcmp(commandTitle, "quit")){
		if(count == 1){
       			printf("Goodbye ");
			quit();	
       		}
       		else{
        		printf("Improper use of %s...\n", commandTitle);
			return;
        	}			
	}
	else{

		printf("Command Not Recognized\n");
		return;
	}
}

int main(int argc, char* argv[]){
	blockId = 0;
	char response[MAXINPUTSIZE];
	head = malloc(128);
	*head = blockId;
	*(head+1) = 126;
	
	
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
