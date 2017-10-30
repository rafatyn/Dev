#include "node.hpp"
Node::Node() {}

Node::Node(int coor_x, int coor_y) {
    x = coor_x;
    y = coor_y;
}

int Node::get_x() {
    return x;
}

int Node::get_y() {
    return y;
}

void Node::set_node(int coor_x, int coor_y) {
    x = coor_x;
    y = coor_y;
}

ostream& operator<<(ostream& os, const Node& node) {
    os <<"(" << node.x << " " << node.y <<")";
    return os;
}

