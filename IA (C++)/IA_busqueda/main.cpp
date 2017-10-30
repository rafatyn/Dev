// main.cpp
// Tutorial de programación de juegos en C++ y Allegro 5
//liballegro-5.0.10-monolith-mt.a

#include <stdio.h>
#include <iostream>

#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "simulationsystem.hpp"

using namespace std;

int main()
{

    SimulationSystem system;


    system.startingSystem();



    system.askForData();

    system.startingScreen();



    system.drawEmpty();

    system.draw();

    system.findPath();


    system.shutdownSystem();

    return 0;
}
