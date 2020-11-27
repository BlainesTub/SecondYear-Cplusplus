#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <set>
#include <map>
#include <list>
#include <vector>

// definition of the class
class directed_graph {
private:
    // Add any attributes or private methods you need here
	double defaultWeight;
	
	std::set<int> reachPassport;
	int reachOnion =0;
	typedef std::pair<int,int> pair;
	typedef std::map<std::pair<int,int>,double> mapType;
	mapType graphMap;
public:
    // Add constructors here (as described in the specification)
	directed_graph(){
	   	defaultWeight = -1;
	}
	directed_graph(double w){
	   defaultWeight = w;  //I think this sets double weight to w.
	}
	//Now these are members
	
	bool is_empty(){
		if(graphMap.begin() == graphMap.end()){
			return true;
		}
		else{
			return false;
		}
	}
	
	void add_edge(const int from, const int to){
		//add an edge with no specified weight
		pair verticies(from,to);
		graphMap.insert({verticies, defaultWeight});
	}

	void add_edge(const int from, const int to, const double weight){
		//add edge with specified weight
		pair verticies(from,to);
		//graphMap.insert({verticies, weight});
		//I believe this iis a n alternate method
		graphMap[verticies]=weight;
	}

    bool edge_exists(const int from, const int to){
		//if the query does not return the ending iterator, return true. otherwise
		pair verticies(from,to);
		if(graphMap.find({verticies}) != graphMap.end()){
			return true;
		}
		//if not found, return false
		else return false;
	}
    bool vertex_exists(const int vertex){
		//loop through de map
		//check 1st and 2nd element. hooray!
		for(auto mapblob : graphMap){
			if(mapblob.first.first == vertex || mapblob.first.second == vertex){
					return true;
			}
		}
		return false;
	}

    std::set<int> vertices(){
		std::set<int> v;
		for(auto mapblob : graphMap){
			v.insert(mapblob.first.first);
			v.insert(mapblob.first.second);	
		}
		return v;
	}
    std::set<std::pair<int, int>> edges(){
		std::set<pair> e;
		for(auto mapblob : graphMap){
				e.insert(mapblob.first);
		}
		return e;
	}

    bool remove_edge(const int from, const int to){
		pair query(from,to);
		mapType::iterator mapIt;

		mapIt = graphMap.find(query);
		if(mapIt != graphMap.end()){  //If the thing is found!
			graphMap.erase(mapIt);
			return true;
		}
		else{
			return false;
		}
	}
    bool remove_vertex(const int vertex){
	    	bool purged = false;
		//loop through the map. Delete all verticies 1st + 2nd
		for(auto mapblob : graphMap){
			if(mapblob.first.first == vertex || mapblob.first.second == vertex){
				pair verts(mapblob.first.first,mapblob.first.second);
				mapType::iterator mapIt = graphMap.find(verts);
				graphMap.erase(mapIt);
				purged = true;
			}
		}
		return purged;
	}
    std::set<int> predecessors(int vertex){
	std::set<int> p;
    	    for(auto mapblob : graphMap){
		if(mapblob.first.second == vertex) p.insert(mapblob.first.first);
	}
	return p;
    }
    std::set<int> successors(int vertex){
	    std::set<int> s;
	    for(auto mapblob : graphMap){
		  if(mapblob.first.first == vertex)  s.insert(mapblob.first.second);
	    }
	    return s;
    }

    double weight(const int from, const int to){
	    pair verts(from,to);
	    mapType::iterator mapIt = graphMap.find(verts);
	    double w = mapIt->second;
	    if(!edge_exists(from,to)){ 
		    throw std::runtime_error("edge does not exist");
	    }	
	    return w;
    }

    directed_graph transpose(){
	directed_graph graphTrans;
	for(auto mapblob : graphMap){
	//	pair rVert(mapblob.first.second, mapblob.first.first);
		double weight = mapblob.second;
		graphTrans.add_edge(mapblob.first.second, mapblob.first.first, weight);
	}
	return graphTrans;
    }
    directed_graph complement(double defaultValue=0){
	defaultValue += 0;
	directed_graph graphComp;
	std::set<int> verts = vertices();
	for(auto v1: verts){
		for(auto v2: verts){
			if(!edge_exists(v1,v2)){
				graphComp.add_edge(v1,v2,0);
			}
		}		
   	 }
	return graphComp;
    }
    directed_graph subgraph(std::set<int> subgraphVertices){
	    directed_graph graphSub;
	    std::set<int> subVerts = subgraphVertices;
	    for(auto mapblob : graphMap){
		int v1 = mapblob.first.first;
		int v2 = mapblob.first.second;
		double w = mapblob.second;
		if(subVerts.find(v1) != subVerts.end() && subVerts.find(v2) != subVerts.end()){
			graphSub.add_edge(v1,v2,w);
		}
	    }
	    return graphSub;
    }
    bool is_reachable(const int from, const int to){
	    std::set<int> verts = vertices(); 
	    if(reachOnion != 0) reachPassport.insert(from);  //If not the first layer, Add to passport
	    ++reachOnion;
	    //std::cout<<"At layer["<<reachOnion<<"]"<<std::endl;
	    //test trivial case
   	    //std::cout<<"	TrivTest ["<<from<<"]->["<<to<<"]"<<std::endl;
	    if(edge_exists(from,to) && (reachPassport.find(to) == reachPassport.end() || from == to) ){    //if edge exists AND Not been there. Or is same    
		    //std::cout<<"	Success! ClearingPassport && Layer"<<std::endl;
		    reachPassport.clear();
		    reachOnion = 0;
		    return true;
	    }

	    else{ //Otherwise, check each connection
		    //std::cout<<"	from [" << from << "] to ["<< to <<"] failed."<<std::endl;  
	    	for(auto v : verts){    
			//std::cout<<"	checking["<<from<<"]->["<<v<<"]"<<std::endl;
			if(edge_exists(from,v) && reachPassport.find(v) == reachPassport.end()){           //If There is a connection, and not been there
				//std::cout<<"  edge exists from ["<<from<<"]->["<<v<<"]"<<std::endl;
				if(is_reachable(v, to)){      //Run Findmate!   
					//std::cout<<"	linkedSuccess!"<<std::endl;
					return true;
				}
			}	
		
		}
	    //std::cout<<"  Search Failed. Retracting"<<std::endl;
	    --reachOnion;
	    //std::cout<<"At Layer["<<reachOnion<<"]"<<std::endl;
	    if(reachOnion == 0) reachPassport.clear();
	    return false;
    	}
    }
    void print(std::string title="");
}; // directed_graph


void directed_graph::print(std::string title)
{
    std::set<int> setV {vertices()};
    std::set<std::pair<int,int>> setE {edges()};
    std::cout << "Graph " << title << ". It has " << setV.size() 
              << " vertices and "<< setE.size() << " edges" << std::endl;

    for (int v: setV) {
        std::cout << "Vertex [" ;
        std::cout << v ;
        std::cout << "]"<< std::endl;
     }

    for (auto e: setE) {
        assert(edge_exists(e.first, e.second));
        std::cout << "Edge [" << e.first << "] -> [" << e.second << "] weight [" << weight(e.first, e.second) << "]" << std::endl;
    }
    
} // end of print

// Put your code here if you choose to define each method outside of the class definition

#endif
