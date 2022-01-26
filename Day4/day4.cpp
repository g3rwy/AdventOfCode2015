#include <stdio.h>
#include <fstream>
#include "md5.h"

int main(){
	std::ifstream f;
	f.open("input.in",std::ifstream::in);

	std::string key;
	std::getline(f,key);
	f.close();
	
	uint1 hash[16];
	unsigned long long int it = 1;

	while(true){
		md5_hex(key + std::to_string(it),hash);
		
		/* Part 1
		if(hash[0] == 0 && hash[1] == 0 && hash[2] < 0x10) // < 0x10 means its smaller than 16 so it must have leading 0
			break;
		*/
		
		// Part 2
		if(hash[0] == 0 && hash[1] == 0 && hash[2] == 0)
			break;

		++it;
	}
	printf("%llu",it);
}	
