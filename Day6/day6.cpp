#include <stdio.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

void get_nums(std::string& t,uint& x1, uint& y1, uint& x2, uint& y2, char& op){
	char  s[t.length()];
	char* p;
	strcpy(s,t.c_str());
	
	p = strtok(s," ");
	bool turning = false;
	int idx = 0;
	char nums1[10],nums2[10]; // no idea why but it works only when i get numbers out of the loop
	
	while(p != NULL){
		if(strcmp(p,"turn") == 0) turning = true;
		
		if(turning){
			if(idx == 1) op = strcmp("on",p) == 0;
			if(idx == 2) memcpy(nums1, p,strlen(p)+1);
			if(idx == 4) memcpy(nums2, p,strlen(p)+1);
		}
		else{
			if(idx == 1){
				op = 3;
				memcpy(nums1, p,strlen(p)+1);
			}
			if(idx == 3) memcpy(nums2, p,strlen(p)+1);
		}
		++idx;
		p = strtok(NULL," ");
	}
	
	p = strtok(nums1,",");
	x1 = std::stoul(p,nullptr,10);
	p = strtok(NULL,"");
	y1 = std::stoul(p,nullptr,10);
	
	p = strtok(nums2,",");
	x2 = std::stoul(p,nullptr,10);
	p = strtok(NULL,"");
	y2 = std::stoul(p,nullptr,10);
}

int main(){
	std::ifstream f;
	f.open("input.in",std::ifstream::in);
	std::string line;
	
	uint x1=0,y1=0,x2=0,y2=0;
	char op = 0;	
	
	uint lit = 0; // its lit
	
	// Part 1	bool grid[1000][1000] = {false};
	// Part 2
	uint grid[1000][1000] = {0};
	while(f.good()){
		std::getline(f,line);
		if(line == "") break;
		
		op = 0;
		get_nums(line,x1,y1,x2,y2,op);
		/* Part 1
		if(op == 3){
			for(short y = y1; y <= y2;++y)
				for(short x = x1; x <= x2;++x)
					grid[y][x] = !grid[y][x];
		}
		else{
			for(short y = y1; y <= y2;++y)
				for(short x = x1; x <= x2;++x)
					grid[y][x] = op;
		}
		*/
		
		// Part 2
		if(op == 3){
			for(short y = y1; y <= y2;++y)
				for(short x = x1; x <= x2;++x)
					grid[y][x] += 2;
		}
		else{
			for(short y = y1; y <= y2;++y)
				for(short x = x1; x <= x2;++x)
					grid[y][x] = (op == 1 ? grid[y][x]+1 : (grid[y][x] == 0 ? grid[y][x] : grid[y][x]-1));
		}
	}
	f.close();
	for(short y = 0; y < 1000;++y)
		for(short x = 0; x < 1000;++x)
			lit += grid[x][y];
	printf("%u\n",lit);
}
