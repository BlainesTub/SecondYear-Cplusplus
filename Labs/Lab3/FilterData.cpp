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
std::vector<int> WANTED;
std::vector<int> Town;

    //Gathering Evidence
    while(std::cin>>c){
        //Gather Evidence about the Criminal
        if(CRIME == false && c!= -1){
            WANTED.push_back(c);
        }
        //A CRIME HAS BEEN COMITTED!!
        if(c == -1){
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
        //bool matching = false;
        //int warrant;
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
