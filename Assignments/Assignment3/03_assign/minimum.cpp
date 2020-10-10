#include <iostream>
#include <vector>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <string>
#include <set>
#include "matrix.hpp"


void printPassport(std::set<unsigned int> beanthere){
    std::cout<<"Passport:";
    for(auto i: beanthere){
        std::cout<<"["<<i<<"]";
    }
    std::cout<<std::endl;
}

// Compute minimum spanning tree of a graph
//
// Parameters:
//      G: input graph (represented by an adjacency matrix)
//
// Result:
//      a matrix representing the minimum spanning tree of G
//
matrix_type Minimum_Spanning_Tree(const matrix_type & G)
{
	unsigned int number_of_vertices = G.size();
    matrix_type result = Create_Matrix(number_of_vertices);
    

    std::set<unsigned int> beanthere = {0};
    unsigned int destj;
    unsigned int desti;  //Coordinates for our next destination!
    



    //Loop through each row IF beanthere!
    while(beanthere.size() < number_of_vertices){
        double min = INFINITY;      //Set the max limit for min 
        for(unsigned int j = 0; j<number_of_vertices; ++j){
            //loop through each path finding min, if NOT Beanthere!
            if(beanthere.find(j) != beanthere.end()){  //If you have been there, Check out connections!
                for(unsigned int i = 0; i<number_of_vertices; ++i){
                    //If index is smaller, && it we have not beanthere, update min
                    if (G.at(j).at(i) < min && beanthere.find(i) == beanthere.end()){
                        min = G.at(j).at(i);
                        destj = j;desti = i; 

                    }
                }
            }   
        }  

    




    //std::cout<<"The min is:"<<min<< "!"<<" At:" << destj<<","<<desti<<std::endl;
    //Lets go there!
    result.at(destj).at(desti) = min;
    result.at(desti).at(destj) = min;
    beanthere.insert(destj);beanthere.insert(desti); //Passport Stamp!
    //printPassport(beanthere);
    }
    //Print_Matrix(result, "Result Matrix!");
    return result;
    
}

// Calculate the overall cost of a graph
//
// Parameters:
//      G: input graph (represented by an adjacency matrix)
//
// Result:
//      the total sum of the costs of the edges in the graph
//
double Calculate_Cost(const matrix_type &G)
{   
    unsigned int number_of_vertices = G.size();
    double result = 0;
    unsigned int diag = 1;
 
    for(unsigned int j=0; j<number_of_vertices; ++j){
        for(unsigned int i = diag; i<number_of_vertices; ++i){
            result = (G.at(i).at(j) == INFINITY) ? result : result+G.at(i).at(j);
        }
        ++diag;
    }
    return result;
}

