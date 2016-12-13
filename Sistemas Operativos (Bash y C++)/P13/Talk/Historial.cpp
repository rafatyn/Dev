#include "Historial.hpp"

historial::historial(void): //Constructor

    //Inicializa los punteros a NULL
    file(NULL),
    addr(NULL),
    fin(NULL)
{
    std::string ruta = getenv("HOME");  //Guarda en una string la direccion home del usuario actual
    ruta += "/.talk";   //Añade a la string la cadena ".talk" que representa

    struct stat x;  //Estructura que contendra las caracteristicas del directorio

    if(stat(ruta.c_str(), &x)){ //Comprueba si el directorio existe, sino lo crea
        int mk = mkdir(ruta.c_str(), 0777);     //Crea el directorio .talk dentro del home

        if (mk == -1) { //Comprueba si el mkdir dio error
           throw std::system_error(errno, std::system_category(), "No se ha podido crear el directorio del historial");
        }
    }

    int fd;
    ruta += "/talk.log";    //Añade el nombre del fichero que se quiere crear a la ruta donde se quiere crear
    fd = open(ruta.c_str(), O_RDWR | O_CREAT | O_APPEND, 0777); //Se abre el fichero, y si no existe se crea

    if (fd == -1){  //Comprueba si se pudo abrir el archivo o crear
        throw std::system_error(errno, std::system_category(), "El archivo no ha podido crearse");
    }

    ftruncate(fd, getpagesize()*256);   //Trunca el archivo al tamaño deseado

    addr = static_cast<char*>(mmap(NULL, 256*getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0));    //Mapea en memoria el archivo

    if (addr == MAP_FAILED){    //Comprueba si el mapeo funciono
        throw std::system_error(errno, std::system_category(), "Error mapeando el archivo");
    }

    file = addr;    //Pone el puntero que recorre el archivo al principio
    fin = addr + (256*getpagesize());   //El puntero que apunta al final del archivo es igual al que apunta al principio mas el tamaño del archivo

    while (file[0]!='\0') { //Recorre el fichero incrementando el puntero hasta el \0, es decir hasta lo ultimo escrito si el fichero ya tiene contenido
        file++;
    }

    int cl = close(fd); //Cierra el archivo

    if (cl == -1){  //Comprueba si el archivo ha cerrado correctamente
        throw std::system_error(errno, std::system_category(), "Error cerrando el archivo");
    }
}

historial::~historial(void) //Destructor
{
    int um = munmap(addr, 256*getpagesize());   //Desmapea la memoria reservada

    if (um == -1){  //Comprueba si el desmapeo fallo
        throw std::system_error(errno, std::system_category(), "Error desmapeando el archivo");
    }
}

void historial::meter(const Message &message)   //Funcion que mete el mensaje en el historial
{
   std::mutex mutex;    //Objeto que bloquea la funcion para que solo pueda acceder un hilo a ella a la vez
   std::lock_guard<std::mutex> lock(mutex); //Desbloquea el mutex cuando se acabe la funcion automaticamente

   std::string line(message.user);  //Crea la string donde se va a ir añadiendo el mensaje poco a poco
   line += " dijo el ";
   line += message.tiempo;
   line += ": ";
   line += message.text;
   line += "\n";
   if (file+line.length()>fin) {    //Comprueba si el mensaje cabe en el espacio disponible antes de llegar al final del archivo, si no es asi empieza a sobreescribir el pricipio
       file = addr;
   }
   line.copy(file, line.length(), 0);   //Copia El mensaje al archivo
   file += line.length();   //Incrementa el puntero con la cantidad de caracteres de la string
}
