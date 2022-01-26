#include <stdio.h>

int main(){
	FILE* f = fopen("input.in","r");
	int floor = 0;

	if(f == NULL) perror("can't open file");
	else{
		/* //Part 1
		char c = 0;
		while(c != EOF){
			c = getc(f);
		 	floor += ((c == '(')) + ((c == ')') * -1); // hehe branchless lets go
		}
		*/

		// Part 2
		int pos = 1;
		char c = 0;
		while(c != EOF){
			c = getc(f);
		 	floor += ((c == '(')) + ((c == ')') * -1);
		 	if(floor == -1){
		 		printf("%d\n",pos);
		 		return 0 ;
		 	}
		 	++pos;
		}

		fclose(f);
		printf("%d\n",floor);
	}
}