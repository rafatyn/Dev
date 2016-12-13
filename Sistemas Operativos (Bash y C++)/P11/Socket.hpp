#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <system_error>
#include "Message.h"

class Socket{
    
    private:
        int fd;  //El identificador del socket
        
    public:
        Socket(const sockaddr_in &address);  //El constructor del socket
        ~Socket(void);  //El destructor del socket
        void send_to(const Message &message, const sockaddr_in& address);  //Función que envia de un socket a otro
        void receive_from(Message &message, sockaddr_in& address);  //Función que recibe mensajes de otro socket
};