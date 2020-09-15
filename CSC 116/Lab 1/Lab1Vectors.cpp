#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec {};
    int buffer{};

    std::cout<<"Enter a number: ";
    while(std::cin>>buffer){
        vec.push_back(buffer);
        std::cout<<"Enter a number: ";
    }

    std::cout << "vec contains " << vec.size() << " elements\n";
    std::cout << "Contents: ";
    for (int i= vec.size(); i>0; --i ) {
        std::cout << vec[i-1] << " ";
    }
    std::cout << std::endl;
    return 0;

}