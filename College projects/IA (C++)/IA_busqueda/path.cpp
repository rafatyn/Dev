#include "path.hpp"


void Path::add_node(int coor_x,int coor_y) {
    Node aux(coor_x,coor_y);

    path.push_back(aux);
}
//Coordenada del último nodo
int Path::get_x() {
    return path[path.size()-1].get_x();
}
//Coordenada del último nodo
int Path::get_y() {
    return path[path.size()-1].get_y();
}

int Path::get_x_before_last() {
    return path[path.size()-2].get_x();
}

int Path::get_y_before_last() {
    return path[path.size()-2].get_y();
}

Path Path::get_path() {
    Path aux;

    for (int i = 0; i< path.size(); i++) {
        aux.add_node(path[i].get_x(),path[i].get_y());
    }
    aux.copy_total_cost(total_cost);

    return aux;
}

int Path::size() {
    return path.size();
}

Node Path::operator[](unsigned int i) {
    return path[i];
}

void Path::update_total_cost(int goal_x, int goal_y) {
    total_cost = (path.size()-1) + (abs(get_x() - goal_x) + abs(get_y() - goal_y)); //coste real + coste virtual
}
int Path::get_total_cost() {
    return total_cost;
}

void Path::copy_total_cost(int cost) {
    total_cost = cost;
}

ostream& operator<<(ostream& os, const Path& p) {
    os << "{ ";
    for (int i = 0; i < p.path.size(); i++) {
        os << p.path[i];
    }
    os << " }";
    return os;
}
