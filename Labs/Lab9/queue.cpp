#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

template<typename T>
class Queue {
public:

    /* Add push, pop and size methods here */
    void push(T v){
        queueVec.push_back(v);
    }
    T pop(){
        if(queueVec.size() <= 0){
            throw std::runtime_error("Pop from empty istack");
        }
        T v;
        v = queueVec.at(0);
        queueVec.erase((queueVec.begin()));
        return v;
    }

    int size(){
        return queueVec.size();
    }
private:

    /* Add private data here */
    std::vector<T> queueVec;

};

int main() {
    // TODO: After implementing the templated Stack class, replace
    // the type of the 'istack' object below with the new templated calls.
    Queue<int> istack;

    std::vector<int> int_contents{1, 2, 3, 4, 5};
    std::cout << "Pushing: ";
    for (auto num : int_contents) {
        std::cout << num << " ";
        istack.push(num);
    }
    std::cout << std::endl;

    std::cout << "Popping: ";
    while (istack.size() > 0)
        std::cout << istack.pop() << " ";
    std::cout << std::endl;

    // TODO: After implementing the templated Stack class, replace
    // the type of the 'istack' object below with the new templated calls.
    Queue<std::string> stringstack;

    std::vector<std::string> string_contents{"Apple", "Banana", "Grapefruit", "Kiwi", "Pear"};
    std::cout << "Pushing: ";
    for (auto str : string_contents) {
        std::cout << str << " ";
        stringstack.push(str);
    }
    std::cout << std::endl;

    std::cout << "Popping: ";
    while (stringstack.size() > 0)
        std::cout << stringstack.pop() << " ";
    std::cout << std::endl;

    return 0;
}