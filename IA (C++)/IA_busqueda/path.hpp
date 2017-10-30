
#include<vector>
#include<iostream>
#include <cstdlib>

#include "node.hpp"

using namespace std;

class Path {
private:
    vector<Node> path;
    int total_cost;

public:
    void add_node(int coor_x,int coor_y);
    friend ostream& operator<<(ostream& os, const Path& p);
    int get_x(); //Coordenada del último nodo
    int get_y(); //Coordenada del último nodo
    int get_x_before_last();
    int get_y_before_last();
    Path get_path();
    int size();
    Node operator[](unsigned int i);
    void update_total_cost(int goal_x, int goal_y);
    int get_total_cost();
    void copy_total_cost(int cost);

};
