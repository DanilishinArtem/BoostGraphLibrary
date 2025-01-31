#ifndef TASKS_H
#define TASKS_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

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
typedef adjacency_list<vecS, vecS, directedS, VertexProperties, EdgeProperties> Graph_VE_d;

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

    std::vector<int> predecessors(num_vertices(g), -1);
    boost::iterator_property_map<int*, boost::identity_property_map> pred_map(predecessors.data(), boost::identity_property_map());
    predecessors[start] = start;

    boost::breadth_first_search(g, start,
        boost::visitor(
        boost::make_bfs_visitor(
            boost::record_predecessors(pred_map, boost::on_tree_edge{}))));

    for (size_t i = 0; i < predecessors.size(); ++i) {
        if (predecessors[i] != -1) { // Выводим только корректные вершины
            std::cout << "Vertex " << g[i].name << " <- " << g[predecessors[i]].name << "\n";
        } else {
            std::cout << "Vertex " << g[i].name << " <- (No predecessor)\n";
        }
    }

    if (write_to_file) {
        std::ofstream dotfile(name + ".dot");
        write_graphviz(dotfile, g,
            make_label_writer(get(&VertexProperties::name, g)),
            make_label_writer(get(&EdgeProperties::weight, g))
        );
    }
}

void Dijkstra(Graph_VE_d &g, std::string name, bool write_to_file)
{
    g[0].name = "A";
    g[1].name = "B";
    g[2].name = "C";
    g[3].name = "D";
    g[4].name = "E";

    add_edge(0, 1, {10}, g);
    add_edge(0, 4, {5}, g);
    add_edge(1, 2, {1}, g);
    add_edge(2, 3, {4}, g);
    add_edge(3, 0, {7}, g);
    add_edge(4, 1, {3}, g);
    add_edge(4, 2, {9}, g);
    add_edge(4, 3, {2}, g);

    int start = 0;

    std::vector<int> distances(num_vertices(g), std::numeric_limits<int>::max());
    std::vector<int> predecessors(num_vertices(g), -1);

    // Run Dijkstra algorithm
    boost::dijkstra_shortest_paths(g, start, 
        boost::predecessor_map(predecessors.data()).distance_map(distances.data())
    );

    std::cout << "Shortest pathes from edge " << g[start].name << ":\n";
    for(size_t i = 0; i < distances.size(); i++)
    {
        std::cout << "To " << g[i].name << " = " << distances[i] << "\n";
    }

    if (write_to_file) {
        std::ofstream dotfile(name + ".dot");
        write_graphviz(dotfile, g,
            make_label_writer(get(&VertexProperties::name, g)),
            make_label_writer(get(&EdgeProperties::weight, g))
        );
    }
}

// https://theboostcpplibraries.com/boost.graph-algorithms
// https://habr.com/ru/articles/471652/
// https://www.boost.org/doc/libs/1_82_0/libs/graph/doc/index.html

#endif



