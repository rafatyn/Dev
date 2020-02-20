#pragma once

#include "Message.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <system_error>
#include <mutex>


class historial{
    private:
        char *addr; //Puntero que contiene la direccion de memoria del principio del archivo
        char *file; //Puntero que va recorriendo el archivo y que se usa para escribir en el
        char *fin;  //Puntero que apunta a la direccion de memoria del final del archivo
    public:
        historial(void);    //Constructor
        ~historial(void);   //Destructor
        void meter(const Message &message); //Función que introduce el mensaje en el historial
};
