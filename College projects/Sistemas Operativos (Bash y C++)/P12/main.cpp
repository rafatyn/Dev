#include "Socket.hpp"

std::atomic<bool> quit(false);
        
sockaddr_in make_ip_address(const std::string &ip_address, int port)  //Crea una estructura sockaddr_in a partir del adireccion y del puerto
{
    sockaddr_in local_address{};
    local_address.sin_family=AF_INET;
    if(ip_address.size()==0){
        local_address.sin_addr.s_addr= INADDR_ANY;
    }else{
        char ip[255];
        strcpy(ip, ip_address.c_str());
        ip[254]='\0';
        inet_aton(ip, &local_address.sin_addr);
    }
    local_address.sin_port=htons(port);
    return local_address;
}

std::vector<sockaddr_in> tt;

void enviar(Socket &s1, const sockaddr_in &address, const std::atomic<bool> &server, std::string &user)  //Envia un mensaje
{
    while(!quit){
        Message message;
        std::string message_text;
        if(quit!=true)
            std::getline(std::cin, message_text);
        if(message_text=="/quit"||quit==true){
            quit=true;
        }
        else{
            strcpy(message.text, message_text.c_str());         //Copia mensaje
            message.text[1023]='\0';
            strcpy(message.user, user.c_str());         //Copia usuario
            message.user[1023]='\0';
            if(server){         //Envia a todos si es el server
                for(int i=0; i<tt.size(); i++){
                    s1.send_to(message,tt[i]);
                }
            }else{
                s1.send_to(message,address);        //Envia normal como cliente
            }
        }
    }
}

void recibir(Socket &s1, Message &message, sockaddr_in &address, const std::atomic<bool> &server)  //Recibe el mensaje
{
    int x=1;
    while(!quit){
        s1.receive_from(message,address);
        if(server){         //Funcion de reenviar a todos
            for(int i=0; i<tt.size(); i++){         //Recorrer vector de users
                if(ntohs(tt[i].sin_port)==ntohs(address.sin_port)&&inet_ntoa(tt[i].sin_addr)==inet_ntoa(address.sin_addr)){
                    x=0;
                }else{
                    x=1;
                }
            }
            if(x==1){               //Ampliar el vector de users
                tt.push_back(address);
            }
            for(int i=0; i<tt.size(); i++){         //Enviar a todos los users
                s1.send_to(message,tt[i]);
            }
        }
    }
}

void int_signal_handler(int signum)
{
        if((signum == SIGINT)||(signum == SIGTERM)||(signum == SIGHUP)){            //Intercepta las señales
            quit = true;
            std::cout << std::endl << "Introduzca YES si quiere cerrar el programa" << std::endl;            
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
        const char* us = std::getenv("USER");
        if(us != nullptr){
            user = us;
        }
        int c;
        
        while ( (c = getopt(argc, argv, "hspcu:01")) != -1) {       //Procesa la linea de comandos
            switch(c){
                case 'h':
                    std::cout << "Usage: [-c direction] client, [-s] server, [-p port] port" << std::endl;
                    break;
                case 'p':
                    port_option = argv[optind];
                    break;
                case 's':
                    server_option = true;
                    break;
                case 'c':
                    ip_option = optarg;
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
        
        if(port_option.size()){         //Procesa el puerto
            port = std::stoi(port_option);
        }
        
        int pp=0;
        std::cout << "Puerto propio: ";
        std::cin >> pp;
        std::cin.get();
        
        sockaddr_in local_address{};
        sockaddr_in remote_address{};
        
        //Crea las struct segun la linea de comandos
        if(server_option){          
            local_address = make_ip_address("127.0.0.1",pp);    
            remote_address = make_ip_address("127.0.0.1",port);
        }else{
            if(ip_option.size()){
                local_address = make_ip_address("127.0.0.1",0);    
                remote_address = make_ip_address(ip_option,port);
            }else{
                local_address = make_ip_address("127.0.0.1",0);    
                remote_address = make_ip_address("127.0.0.1",pp);
            }
        }
        
        //Crea socket     
        Socket s1(local_address);
        
        Message message;
                
        std::thread hse(&enviar,std::ref(s1),std::cref(remote_address),std::cref(server_option),std::ref(user));  //Hilo de enviar 
        std::thread hrec(&recibir,std::ref(s1),std::ref(message),std::ref(remote_address),std::cref(server_option));  //Hilo de ecibir
        hse.join();
        pthread_cancel(hrec.native_handle());
        hrec.join();
        
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
