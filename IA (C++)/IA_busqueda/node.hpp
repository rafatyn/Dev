#include<iostream>


using namespace std;

class Node {
private:
    int x;
    int y;

public:
    Node();
    Node(int coor_x, int coor_y);
    int get_x();
    int get_y();
    void set_node(int coor_x,int coor_y);

    friend ostream& operator<<(ostream& os, const Node& node);


};
