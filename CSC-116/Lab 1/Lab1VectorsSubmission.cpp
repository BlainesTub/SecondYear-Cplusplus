#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec {};
    int buffer{};
    //read input
    std::cout<<"Enter a number: ";
    while(std::cin>>buffer){
        //std::cout<<std::cin.fail();   //Check if input is invalid
        vec.push_back(buffer);

        
        std::cout<<"Enter a number: ";
        
    }
    int it{4};
    //Print the number of values entered, and the contents
    vec.insert(it,2, 696969);
    std::cout << "Number of Values Entered: " << vec.size() << "\n";
    std::cout << "Values (forwards): ";
    for(auto val : vec){
        std::cout<< val << ", ";
    }
    std::cout << "\n";
    std::cout << "Values (reverse): ";
    for (int i= vec.size(); i>0; --i ) {
        std::cout << vec[i-1] << ", ";
    }
    std::cout << "\n";
    std::cout << std::endl;
    return 0;

}