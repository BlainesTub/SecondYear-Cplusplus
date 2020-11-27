#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
  

void printvec(std::vector<int> vec){
    for(int i=0; i< (int(vec.size())); ++i){
        std::cout<<vec.at(i)<< " ";
    }
    std::cout<<std::endl;
}

int main(){
int c;
bool CRIME = false;
std::vector<int> WANTED; //The string that is WANTED and must be PURGED
std::vector<int> Town;   //The population that must be PURGED

    //Gathering Evidence
    while(std::cin>>c){
        //Gather Evidence about the Criminal
        if(CRIME == false && c!= -1){
            WANTED.push_back(c);
        }
        
        if(c == -1){    //A CRIME HAS BEEN COMITTED!!
            CRIME = true;
        }
        //Gather Evidence about the Town
        if(CRIME == true && c != -1){
            Town.push_back(c);
        }
    }
    //Print The Evidence
    std::cout<<"Data Set 1: ";
    printvec(WANTED);
    std::cout<<"Data Set 2: ";
    printvec(Town);

    //INVESTIGATION
        std::vector<int> suspect;

        
    for(int i=0; i<(int(Town.size())) && i < (int(Town.size() - WANTED.size())+1); ++i){  //iterate through each Townperson
        //create a vector at ith index
        suspect.clear();
        for(int j=0; j<int(WANTED.size()) && j < int(Town.size()- WANTED.size()); ++j){
            suspect.push_back(Town.at(i+j));     //inserts ith index of Town, plus the length of WANTED
        }
        if(suspect == WANTED){
            Town.erase(Town.begin()+i, Town.begin()+i +int(WANTED.size()));
        }
    }
    std::cout<<"Filtered: ";
    printvec(Town);
    return 0;
}
