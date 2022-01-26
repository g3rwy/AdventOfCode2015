#include <fstream>
#include <stdio.h>
#include <cstring>
#include <string>

const char* vowels = "aeiou";

/* ---- Part 1
bool is_nice(const std::string& s){	
	bool cont_vowels = false;
	bool double_letter = false;
	bool not_cont_strings = false;
	
	char c, old_c;
	short vowels_count = 0;
	
	for(short i=0;i<17;++i){
		c = s[i];
		vowels_count += (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c =='u');
		const char temp_str[2] = {old_c,c};
		
		cont_vowels      = vowels_count >= 3; 
		double_letter    = (c == old_c) || double_letter;
		not_cont_strings = (strcmp("ab",temp_str) == 0 || strcmp("cd",temp_str) == 0 || strcmp("pq",temp_str) == 0 || strcmp("xy",temp_str) == 0) || not_cont_strings;

		old_c = c;
	}
	
	return cont_vowels && double_letter && !not_cont_strings;
}
*/

// ---- Part 2
bool is_nice(const std::string& s){

	bool cont_pairs = false;
	bool oreo = false;
	
	for(int i=0;i < 15 ;++i){
			std::size_t idx = s.rfind(s.substr(i,2));
			if(idx - i >= 2){
				cont_pairs = true;
				break;
			}
	}
	
	for(int i=0;i < 15;++i){
		if(s[i] == s[i+2]){
			oreo = true;
			break;
		}
	}

	return cont_pairs && oreo;
}

int main(){
    std::ifstream f;
	f.open("input.in",std::ifstream::in);
	
	std::string word;
	word.reserve(17);
	uint nice_words = 0;
	
	while(f.good()){
		std::getline(f,word);
		if(word.length() < 1) continue;
		nice_words += is_nice(word);
	}
	printf("%u\n",nice_words);
}
