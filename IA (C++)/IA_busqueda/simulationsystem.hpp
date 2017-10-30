
#include<iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <time.h>


#include <vector>
#include <list>
#include<math.h>

#include "path.hpp"


using namespace std;

class SimulationSystem {

private:
    ALLEGRO_DISPLAY *display;
    int n,m,pobs; //n filas  m columnas
    int imgw;
    int imgh;
    ALLEGRO_BITMAP *imgvacio;
    ALLEGRO_BITMAP *imgmuro;
    ALLEGRO_BITMAP *imginicio;
    ALLEGRO_BITMAP *imgfin;
    ALLEGRO_BITMAP *imgpersona;
    ALLEGRO_BITMAP *imgcamino;
    bool quit;
    char modo;
    Node start;
    Node goal;
    vector< vector<int> > obs_matrix;

public:
    void startingSystem();
    void askForData();
    void startingScreen();
    void drawEmpty();
    void draw();

    void findPath();

    void shutdownSystem();

private:
    void drawManually();
    void drawRandomly();

    list<Path> search_new_path(list<Path>& new_path_list,Path& path);
    bool insert_path_close_list(list<Path>& close_list,Path& path); //Al insertar, en caso de caminos similares,se elimina el de mayor coste.
    void insert_path_open_list(list<Path>& open_list,list<Path>& close_list,Path path); //Al insertar, en caso de caminos similares,se para el mayor a la lista cerrada
    void sort_list(list<Path>& source_list); //Ordenar para que el primero sea el min

};
