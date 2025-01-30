#ifndef TASKS_H
#define TASKS_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>

template<typename T>
void Test(void (*foo)(T&, std::string, bool), T &g, std::string name, bool write_to_file)
{
    try{
        foo(g, name, write_to_file);
        std::cout << "\33[92m[" + name + " test of creating undirected graph is passed]\33[0m\n";
    }catch(const std::runtime_error& e){
        std::cout << "\33[91m[" + name + " test of creating undirected graph is passed]\33[0m\n";
    }
}


struct VertexProperties
{
    std::string name;
};

struct EdgeProperties
{
    int weight;
};

using namespace boost;
typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeProperties> Graph_VE;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;

// Добавление вершин и рёбер
void make_adjacencies(Graph &g, std::string name, bool write_to_file)
{
    add_edge(0, 1, g);
    add_edge(1, 2, g);
    add_edge(2, 3, g);
    add_edge(3, 4, g);
    add_edge(4, 0, g);
    if(write_to_file)
    {
        std::ofstream dotfile(name + ".dot");
        write_graphviz(dotfile, g);
    }
}

// Добавление свойств вершин и рёбер
void make_adjacencies_vertexes(Graph_VE &g, std::string name, bool write_to_file)
{
    // Добавляем вершины с именами
    g[0].name = "A";
    g[1].name = "B";
    g[2].name = "C";
    g[3].name = "D";
    g[4].name = "E";

    // Добавляем рёбра с весами
    add_edge(0, 1, {5}, g);
    add_edge(1, 2, {10}, g);
    add_edge(2, 3, {15}, g);
    add_edge(3, 4, {20}, g);
    add_edge(4, 0, {25}, g);

    if (write_to_file) {
        std::ofstream dotfile(name + ".dot");
        write_graphviz(dotfile, g,
            make_label_writer(get(&VertexProperties::name, g)),
            make_label_writer(get(&EdgeProperties::weight, g))
        );
    }
}

// Поиск в ширину (BFS - Breadth-First Search)
void bfs(Graph_VE &g, std::string name, bool write_to_file)
{
    g[0].name = "A";
    g[1].name = "B";
    g[2].name = "C";
    g[3].name = "D";
    g[4].name = "E";

    add_edge(0, 1, {5}, g);
    add_edge(1, 2, {10}, g);
    add_edge(2, 3, {15}, g);
    add_edge(3, 4, {20}, g);
    add_edge(4, 0, {25}, g);

    int start = 0;

    std::cout << "BFS from vertex " << start << ":\n";
    boost::array<int, 5> predecessors;
    predecessors[start] = start;
    boost::breadth_first_search(g, start,
        boost::visitor(
        boost::make_bfs_visitor(
            boost::record_predecessors(predecessors.begin(),
            boost::on_tree_edge{}))));
    for (size_t i = 0; i < predecessors.size(); ++i) {
        std::cout << "Vertex " << g[i].name << " <- " << g[predecessors[i]].name << "\n";
    }
}

// https://theboostcpplibraries.com/boost.graph-algorithms


#endif



