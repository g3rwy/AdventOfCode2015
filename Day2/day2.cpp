#include <stdio.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#define MIN(a,b,c) ( (a > b) ? ((b > c) ? (c) : (b)) : ((a > c) ? (c) : (a)))
#define MAX(a,b,c) ( (a > b) ? ((a > c) ? (a) : (c)) : ((b > c) ? (b) : (c)))

void get_nums(std::string& t,uint& a, uint& b, uint& c){
	char  s[t.length()];
	char* p;
	strcpy(s,t.c_str());

	p = strtok(s,"x");
	int i=0;
	while(p != NULL){
		if(i==0) a = std::stoul(p,nullptr,10);
		if(i==1) b = std::stoul(p,nullptr,10);
		if(i==2) c = std::stoul(p,nullptr,10);
		++i;
		p = strtok(NULL,"x");
	}
}

int main(){
	std::ifstream f;
	f.open("input.in",std::ifstream::in);

	
	std::string line;

	uint total = 0; // final result
	/* Part 1
	uint p1,p2,p3; // Area

	while(f.good()){
		uint l,w,h;		
		std::getline(f,line);
		get_nums(line,l,w,h);

		p1 = 2*l*w; 
		p2 = 2*w*h; 
		p3 = 2*h*l;

		total += p1 + p2 + p3 + MIN(p1/2,p2/2,p3/2);
	}
	*/

	// Part 2
	int i = 0;
	while(f.good()){
		uint l,w,h;		
		std::getline(f,line);
		get_nums(line,l,w,h);
		uint side1 = MIN(l,w,h);
		uint side2 = ((l+w+h) - MAX(l,w,h)) - MIN(l,w,h);

		total += side1*2 + side2*2 + (l*w*h);
	}

	printf("%u\n", total);
	f.close();
}	