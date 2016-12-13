#include "Socket.hpp"

std::atomic<bool> quit(false);  //Bool atomico global que controla si se sale de los hilos
std::thread *hse;   //Declaracion del hilo d enviar
std::thread *hrec;  //Declaracion del hilo de recibir

void request_cancellation(std::thread *thread)  //Funcion que se encarga de cancelar el hilo que se le pasa por parametros
{
    pthread_cancel(thread->native_handle());
}

sockaddr_in make_ip_address(const std::string &ip_address, int port)  //Crea una estructura sockaddr_in a partir del adireccion y del puerto
{
    sockaddr_in local_address{};    //Crea una estructura vacia
    local_address.sin_family=AF_INET;   //Le asigna la familia del socket
    if(ip_address.size()==0){   //Si no se le pasa ip hace que el SO asigne una
        local_address.sin_addr.s_addr= INADDR_ANY;
    }else{
        char ip[255];   //Array de char que va a albergar la ip
        strcpy(ip, ip_address.c_str()); //Copia el contenido de ip_address a ip
        ip[254]='\0';   //Pone el ultimo caracter de ip a \0 para evitar errores
        inet_aton(ip, &local_address.sin_addr); //Guarda en la estructura sin_addr de dentro de la estructura anterior la direccion
    }
    local_address.sin_port=htons(port); //Guarda en sin_port el puerto pasado por prametros
    return local_address;   //Devuelve la estructura ya rellena
}

std::vector<sockaddr_in> tt;    //Vector que contiene a los usuarios conectados al servidor

void enviar(Socket &s1, const sockaddr_in &address, const std::atomic<bool> &server, std::string &user, historial &hist)  //Funcion que envia los mensajes
{
    while(!quit){
        Message message;    //Crea una estructura Message llamada message
        std::string message_text;   //Crea la string que va a contener el mensaje que el usuario meta por teclado
        if(quit!=true)
            std::getline(std::cin, message_text);   //Guarda el mensaje en massage_text
        if(message_text=="/quit"||quit==true){  //Si el mensaje que mete el usuario es /quit por quit a true y conlleva el cierre del programa
            quit=true;
        }else{
            strcpy(message.text, message_text.c_str());   //Copia el mensaje
            message.text[1023]='\0';    //Pone el ultimo caracter a \0 para evitar errores
            strcpy(message.user, user.c_str());    //Copia el usuario
            message.user[1023]='\0';    //Pone el ultimo caracter a \0 para evitar errores
            std::time_t result = std::time(nullptr);    //Guarda en la string result el tiempo en el que se envio el mensaje
            std::string tp = std::ctime(&result);   //Convierte ese tiempo a tiempo de calendario
            strncpy(message.tiempo, tp.c_str(), tp.size()-1);   //Copia el tiempo
            message.tiempo[1023]='\0';  //Pone el ultimo caracter a \0 para evitar errores
            hist.meter(message);    //Mete el mensaje en el historial
            if(server){ //Comprueba si es server
                for(int i=0; i<tt.size(); i++){ //Envia a todos los usuarios si es el server
                    s1.send_to(message,tt[i]);
                }
            }else{
                s1.send_to(message,address);    //Envia normal como cliente
            }
        }
    }
    request_cancellation(hrec); //Cuando se acaba el hilo de envio termina el de recibir para terminar el programa
}

void recibir(Socket &s1, Message &message, sockaddr_in &address, const std::atomic<bool> &server, historial &hist)  //Recibe el mensaje
{

    int x=1;

    while(!quit){
        s1.receive_from(message,address);   //Recibe el mensaje
        hist.meter(message);    //Mete el mensaje en el historial
        if(server){     //Comprueba si es server
            for(int i=0; i<tt.size()&&x; i++){      //Comprueba si el usuario ya esta en la lista de usarios
                if(ntohs(tt[i].sin_port)==ntohs(address.sin_port)&&inet_ntoa(tt[i].sin_addr)==inet_ntoa(address.sin_addr)){
                    x=0;
                }else{
                    x=1;
                }
            }
            if(x==1){   //Si no esta lo mete
                tt.push_back(address);
            }
            for(int i=0; i<tt.size(); i++){     //Enviar el mensaje a todos los usuarios menos al que lo envio
                if(ntohs(tt[i].sin_port)!=ntohs(address.sin_port)&&inet_ntoa(tt[i].sin_addr)!=inet_ntoa(address.sin_addr)){
                    s1.send_to(message,tt[i]);
                }
            }
        }
    }
}

void int_signal_handler(int signum) //Funcion que termina el programa si se pulsa Ctrl+C o si se cierra la ventana o si se apaga el equipo
{
        if((signum == SIGINT)||(signum == SIGTERM)||(signum == SIGHUP)){    //Comprueba si son las señales deseadas
            quit = true;
            std::cout << std::endl << "Cerrando..." << std::endl;
            request_cancellation(hrec);     //Cancela el hilo que recibe
            request_cancellation(hse);      //Cancela el hlo que envia
        }
}

int main(int argc, char* argv[]){

    try {
        //Intercepta las señales
        signal(SIGINT, &int_signal_handler);
        signal(SIGTERM, &int_signal_handler);
        signal(SIGHUP, &int_signal_handler);

        //Declaracion de variables
        bool help_option = false;
        std::atomic<bool> server_option(false);
        std::string port_option;
        std::string ip_option;
        std::string user;
        const char* usu = std::getenv("USER");  //Guarda en usu el valor de la variable de entorno USER
        if(usu != nullptr){  //Si la variable existia el valor que devuelve lo mete en user
            user = usu;
        }
        int c;
        int option_index = 0;
        static struct option long_options[] = {     //Estructura que permite la aceptacion de opciones largas
            {"port",     required_argument, 0,  'p' },
            {"server",   no_argument,       0,  's' },
            {"client",   required_argument, 0,  'c' },
            {"help",     no_argument,       0,  'h' },
            {"username", required_argument, 0,  'u' },
            {0,          0,                 0,  0 }
        };

        for(int i=0; i<argc; i++){
            std::cout << argv[i] << " ";
        }
        while ( (c = getopt_long(argc, argv, "hspcu:01", long_options, &option_index)) != -1) {     //Funcion que procesa la linea de comandos
            switch(c){
                case 'h':
                    std::cout << "Usage: [-c/--client server ip] [-p/--port server port] client, [-s/--server server mode] [-p/--port input port] server, [-u/--username username]" << std::endl;
                    break;
                case 'p':
                    port_option = argv[optind];
                    break;
                case 's':
                    server_option = true;
                    break;
                case 'c':
                    ip_option = argv[optind];
                    break;
                case 'u':
                    user = optarg;
                case '?':
                    break;
                default:
                    std::cout << "La opcion " << c << " no es soportada" << std::endl;
                    break;
            }
        }
        if(!quit){
            int port = 0;

            if(port_option.length()){   //Si se le ha metido un puerto por comandos lo mete en port
                port = std::stoi(port_option);  //Convierte la string port_option en un int port
            }

            sockaddr_in local_address{};    //Inicializa la estructura local_address
            sockaddr_in remote_address{};   //Inicializa laestructura remote_address

            //Crea las struct segun la linea de comandos
            if(server_option){  //Si es servidor
                local_address = make_ip_address("127.0.0.1",0);
                remote_address = make_ip_address("127.0.0.1",port);
            }else{//Si es cliente
                local_address = make_ip_address("127.0.0.1",0);
                remote_address = make_ip_address(ip_option,port);
            }

            //Crea socket
            Socket s1(local_address);
            //Crea el historial y la estuctura message
            Message message;
            historial hist;
            //Le asigna a cada hilo una funcion
            hse = new std::thread(&enviar,std::ref(s1),std::cref(remote_address),std::cref(server_option),std::ref(user),std::ref(hist));  //Hilo de enviar
            hrec = new std::thread(&recibir,std::ref(s1),std::ref(message),std::ref(remote_address),std::cref(server_option),std::ref(hist));  //Hilo de ecibir
            //Hace al hilo principar esperar a que acaben los otros dos hilos
            hse->join();
            hrec->join();

        }
    }       //Evita el cerrado forzoso por errores
    catch(std::bad_alloc& e) {
        std::cerr << program_invocation_name << ": memoria insuficiente" << std::endl;
        return 1;
    }
    catch(std::system_error& e) {
        std::cerr << program_invocation_name << ": " << e.what() << std::endl;
        return 2;
    }
    catch(abi::__forced_unwind&) {
        throw;
    }
    return 0;
}
