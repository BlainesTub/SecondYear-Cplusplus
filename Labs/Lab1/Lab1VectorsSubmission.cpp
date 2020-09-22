#include <iostream>
#include <vector>

int main() {
    bool aBool {false};
    std::cout << std::boolalpha;
    std::cout << aBool << std::endl;
    std::cout << std::noboolalpha;
    std::cout << aBool << std::endl;




    std::vector<int> vec {};
    std::vector<int> vecsort{};
    int buffer{};
    //read input
    std::cout<<"Enter a number: ";
    while(std::cin>>buffer){
        //std::cout<<std::cin.fail();   //Check if input is invalid
        vec.push_back(buffer);

        
        std::cout<<"Enter a number: ";
        
    }

    //Sort the values

    //Sort the values


    //Print the number of values entered, and the contents
    std::cout << "Number of Values Entered: " << vec.size() << "\n";
    std::cout << "Values (forwards): ";
    for(auto val : vec){
        std::cout<< val << ", ";
    }
    std::cout << "\n";
    std::cout << "Values (reverse): ";
    for (int i= vec.size(); i>0; --i ) {
        std::cout << vec.at(i-1) << ", ";
    }
    std::cout << "\n";

    //SOOooooooooooooortinggggggggggg
    int smallest{vec.at(0)};
    int smallestidx{};
    //std::cout<<"FirstIndex" << smallest <<"\n";
    //std::cout<<vec.size();
    for(int i=vec.size(); i>0; --i){
        for(int j=vec.size(); j>0; --j){
            if(vec.at(j-1) < smallest){
                smallest = vec.at(j-1);
                smallestidx = (j-1);
            }
            //std::cout<<"Smallest: "<< smallest << "\n";
        }
        vecsort.push_back(vec.at(smallestidx));
        //std::cout<<" Overwriting: "<<vec.at(smallestidx);
        vec.at(smallestidx) = 9999;
        smallestidx = 0;
    }
    //std::cout<<"Smallest: "<< smallest << "\n";
    //std::cout<<"Smallestidx: "<< smallestidx << "\n";

        std::cout << "Values (sorted): ";
    for(auto val : vecsort){
        std::cout<< val << ", ";
    }





    std::cout << std::endl;

    return 0;

}