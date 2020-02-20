#include "Socket.hpp"
#include <thread>
#include <atomic>
#include <pthread.h>

sockaddr_in make_ip_address(const std::string &ip_address, int port)  //Crea una estructura sockaddr_in a partir del adireccion y del puerto
{
    sockaddr_in local_address{};
    local_address.sin_family=AF_INET;
    if(ip_address.size()==0){
        local_address.sin_addr.s_addr=htonl(INADDR_ANY);
    }else{
        char ip[255];
        strcpy(ip, ip_address.c_str());
        ip[254]='\0';
        inet_aton(ip, &local_address.sin_addr);
    }
    local_address.sin_port=htons(port);
    return local_address;
}

void enviar(Socket &s1, const sockaddr_in &address, std::atomic<bool>& quit)  //Envia un mensaje
{
    while(!quit){
        std::string message_text;
        std::getline(std::cin, message_text);
        if(message_text=="/quit"){
            quit=true;
        }else{
            Message message;
            strcpy(message.text, message_text.c_str());
            message.text[1023]='\0';
            s1.send_to(message,address);
        }
    }
}

void recibir(Socket &s1, Message &message, sockaddr_in &address, std::atomic<bool>& quit)  //Recibe un mensaje
{
    while(!quit){
        s1.receive_from(message,address);
    }
}

int main (void){
    
    try {
    
        std::atomic<bool> quit(false);
        sockaddr_in local_address = make_ip_address("127.0.0.1",2000);    
        sockaddr_in remote_address = make_ip_address("127.0.0.1",8080);
        
        Socket s1(local_address);
          
        Message message;
        
        std::thread hse(&enviar,std::ref(s1),std::cref(remote_address),std::ref(quit));  //Hilo que envia
        std::thread hrec(&recibir,std::ref(s1),std::ref(message),std::ref(remote_address),std::ref(quit));  //Hilo que recibe
        hse.join();
        pthread_cancel(hrec.native_handle());
        hrec.join();

    }        
    catch(std::bad_alloc& e) {
        std::cerr << program_invocation_name << ": memoria insuficiente" << std::endl;
        return 1;
    }
    catch(std::system_error& e) {
        std::cerr << program_invocation_name << ": " << e.what() << std::endl;
        return 2;
    }
    
    return 0;
}
