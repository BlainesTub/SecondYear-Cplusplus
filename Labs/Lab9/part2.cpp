/* part4.cpp
   CSC 116 - Fall 2016 - Lab 9

*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

using std::string;

/* Consider the class IntStack below, which uses a vector to implement a
   istack of int values. The main function doesn't use the IntStack class,
   but instead uses the empty class Stack<T> to create stacks of an
   arbitrary type.

   To allow this file to compile before you've started working on it, all
   of the testing code is commented out in main(). You should uncomment it
   before starting your implementation.

   Task: Using the IntStack class as a model, implement the Stack<> class
   below (which must have push, pop and size methods).
*/

class IntStack {
public:
    void push(int v) {
        stack_values.push_back(v);
    }

    int pop() {
        if (size() <= 0) {
            throw std::runtime_error("Pop from empty istack");
        }

        int v = stack_values.back();
        stack_values.pop_back();
        return v;
    }

    int size() {
        return stack_values.size();
    }
private:
    std::vector<int> stack_values;
};

class StringStack {
public:
    void push(std::string v) {
        stack_values.push_back(v);
    }

    std::string pop() {
        if (size() <= 0) {
            throw std::runtime_error("Pop from empty istack");
        }

        std::string v = stack_values.back();
        stack_values.pop_back();
        return v;
    }

    int size() {
        return stack_values.size();
    }
private:
    std::vector<std::string> stack_values;
};

template<typename T>
class Stack{
public:

    void push(T v){
        stack_values.push_back(v);
    }
    
    T pop(){
        if(size() <= 0){
            throw std::runtime_error("Pop from empty istack");
        }

        T v = stack_values.back();
        stack_values.pop_back();
        return v;
    }
    int size() {
        return stack_values.size();
    }


private:
    std::vector<T> stack_values;   
};

int main()
{
    // TODO: After implementing the templated Stack class, replace
    // the type of the 'istack' object below with the new templated calls.
    Stack<int> istack;

    std::vector<int> int_contents {1,2,3,4,5};
    std::cout << "Pushing: ";
    for (auto num : int_contents) {
        std::cout << num << " ";
        istack.push(num);
    }
    std::cout << std::endl;

    std::cout << "Popping: ";
    while(istack.size() > 0)
        std::cout << istack.pop() << " ";
    std::cout << std::endl;

    // TODO: After implementing the templated Stack class, replace
    // the type of the 'istack' object below with the new templated calls.
    Stack<std::string> stringstack;

    std::vector<std::string> string_contents {"Apple", "Banana", "Grapefruit", "Kiwi", "Pear"};
    std::cout << "Pushing: ";
    for (auto str : string_contents) {
        std::cout << str << " ";
        stringstack.push(str);
    }
    std::cout << std::endl;

    std::cout << "Popping: ";
    while(stringstack.size() > 0)
        std::cout << stringstack.pop() << " ";
    std::cout << std::endl;

    return 0;
}

