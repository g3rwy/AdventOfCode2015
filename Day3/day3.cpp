#include <stdio.h>
#include <iostream>

#define ARR_SIZE 3000

struct V2{int x,y;};

bool visited(V2 p[ARR_SIZE],int x, int y){
	for(int i=0;i<ARR_SIZE;++i){
		if(p[i].y != y) continue;
		else{
			if(p[i].x == x) return true;
		}
	}
	return false;
}

int main(){
	int santa_pos_x = 0;
	int santa_pos_y = 0;	

	V2* places = new V2[ARR_SIZE];
	places[0] = {0,0};

	FILE* f = fopen("input.in","r");
	int idx = 1;

	if(f == NULL) perror("can't open file");
	else{
		char c = 0;
		/* Part 2
		bool robot_or_santa = true;

		int rsanta_pos_x = 0;
		int rsanta_pos_y = 0;
		*/

		while(c != EOF){
			c = getc(f);
			/* Part 2
			if(robot_or_santa){
				robot_or_santa = false;
				santa_pos_x += (c == '>') + ((c == '<') * -1);
				santa_pos_y += (c == '^') + ((c == 'v') * -1);
				
				if(visited(places,santa_pos_x, santa_pos_y)) continue;
				places[idx] = {santa_pos_x,santa_pos_y};
			}
			else{
				robot_or_santa = true;
				rsanta_pos_x += (c == '>') + ((c == '<') * -1);
				rsanta_pos_y += (c == '^') + ((c == 'v') * -1);

				if(visited(places,rsanta_pos_x, rsanta_pos_y)) continue;
				places[idx] = {rsanta_pos_x,rsanta_pos_y};
			}
			*/
			
			santa_pos_x += (c == '>') + ((c == '<') * -1);
			santa_pos_y += (c == '^') + ((c == 'v') * -1);
				
			if(visited(places,santa_pos_x, santa_pos_y)) continue;
			places[idx] = {santa_pos_x,santa_pos_y};
			++idx;
		}
		fclose(f);
	}

	delete[] places;
	printf("%i\n",idx);
}