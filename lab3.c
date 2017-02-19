#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUTSIZE 64
#define NUMCOMMANDS 4

char *commandList[NUMCOMMANDS];
int commandArgNums[NUMCOMMANDS];

void allocate(int newSize){
	
}

void freeBlock(int blockNum){
	
}

void blockList(){
	
}

void writeHeap(){

}

/*void parseResponse(char response[MAXINPUTSIZE]){
	char delim[] = " ";
	char *token;

	for (token = strtok(response, delim); token; token = (NULL, delim)){
		
	}
}*/

void processResponse(char response[MAXINPUTSIZE]){
/*	char delim[] = " ";
	char *token;
	char commandTitle[32];

	token = strtok(response, delim);
	for(i = 0; i < NUMCOMMANDS; ++i){
		if(!strcmp(commands[i].title, token)){
			for(token = strtok(NULL, delim), j = 0; token; token = strtok(NULL, delim)){
				
				++j;
			}
		}
	}*/
	int count, i, j;
	int args[4];
	char commandTitle[16];
	count = sscanf(response, "%s %d %d %d %d", commandTitle, &args[0], &args[1], &args[2], &args[3]);
	printf("count %d\n", count);
	for(i = 0; i < NUMCOMMANDS; ++i){
		if(!strcmp(commandTitle, commandList[i])){
			if(count == commandArgNums[i]){
				printf("command: %s, numArgs: %d \n", commandTitle, count);
			}
			else{
				printf("Improper Usage of %s...\n", commandTitle);
				return;
			}
		}
	}

}

int main(int argc, char* argv[]){
	char response[MAXINPUTSIZE];
	commandList[0] = "allocate";
	commandArgNums[0] = 2;		
	commandList[1] = "blocklist";
       	commandArgNums[1] = 1;		
	commandList[2] = "free";
	commandArgNums[2] = 2;		
	commandList[3] = "writeheap";
	commandArgNums[3] = 4;
	
	int i;
	for(i = 0; i < 4; ++i){
		printf("command: %s, numargs: %d\n", commandList[i], commandArgNums[i]);
	}
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
