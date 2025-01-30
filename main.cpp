#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include "tasks.hpp"

using namespace boost;


int main(){
    // {
    //     Graph g(5);
    //     Test(&make_adjacencies, g, "First", true);
    // }
    // {
    //     Graph g(10);
    //     Test(&make_adjacencies, g, "Second", true);
    // }
    {
        Graph_VE g(5);
        Test(&make_adjacencies_vertexes, g, "Adjacencies_vertexes", true);
    }
    {
        Graph_VE g(5);
        Test(&bfs, g, "BFS", false);
    }
}




