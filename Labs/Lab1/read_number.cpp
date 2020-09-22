#include <iostream>  //standard input-output stream. cin cout cerr
#include <vector>

int main(){
    int num{};
    std::cout << "Enter a number: ";   //"enter a number" is inserted (<<) into cout (coutput stream)
    while(std::cin>>num){ 
           
            std::cout << "You entered " << num << std::endl;
            std::cout << "Enter a number: ";
        }
    std::cout << "Input was Invalid. \n";
    return 0;
}

