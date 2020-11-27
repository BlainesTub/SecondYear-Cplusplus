#include <iostream>  //standard input-output stream. cin cout cerr
#include <vector>


int PreIncrement(int &i){
    i = i + 1;
    return i;
    
}

int main(){
    int i=5;
    std::cout<< i << std::endl;
    std::cout<< PreIncrement(i) << std::endl;
    std::cout << i << std::endl;
    return 0;
}

