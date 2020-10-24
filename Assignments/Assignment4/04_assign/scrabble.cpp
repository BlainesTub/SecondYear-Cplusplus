#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <fstream>
#include <cassert>

#include "scrabble.hpp"

// you can add/remove code from this file as long as you do not modify the declaration of each of the 
// 3 functions  below


int Score(const std::string &word)
{
	int score = 0;
    	for(auto ch : word){
		switch(ch){
			case 'a': case 'e': case 'i': case 'l': case'n': case'o':case'r':case's':case't':case'u':
				score = score+1;
				break;
			case'd':case'g':
				score=score+2;
				break;
			case'b':case'c':case'm':case'p':
				score=score+3;
				break;
			case'f':case'h':case'v':case'w':case'y':
				score=score+4;
				break;
			case'k':
				score=score+5;
				break;
			case'j':case'x':
				score=score+8;
				break;
			case'q':case'z':
				score=score+10;

		}
	}
	return score;
	//return -1;       //IS THIS SUPPOSED TO RETURN -1 or SCORE???
}


dict_type Read_Dictionary(const std::string &filename)
{
    dict_type dict;
    std::ifstream file{};
    file.open(filename);
    int count=0;
    std::string word;

    while(std::getline(file,word)){
     	dict.insert({word,Score(word)});
	count++;
	}	

    std::cout<<"Read "<<count<<" words."<<std::endl;
    return dict;
    
}

words_set_type Find_Best_Words(const dict_type &dict, std::string &tiles)
{
    	words_set_type allWords;
	words_set_type goodWords;
	int topScore = 0;

	allWords = Compute_Permutations(tiles);
	for(auto word : allWords){
		unsigned int len = word.size();
		for(unsigned int i = len; i>1; --i){
			std::string subWord = word.substr(0,i);
			if(dict.find(subWord) != dict.end() && (Score(subWord)) > topScore) {
				goodWords.clear();
				goodWords.insert(subWord);
				topScore = Score(subWord);
			}
			else if(dict.find(subWord) != dict.end() && Score(subWord) == topScore){
				goodWords.insert(subWord);
			}
		}
	}

    return goodWords;

}

