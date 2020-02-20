#include "Socket.hpp"

Socket::Socket(const sockaddr_in &address)  //Constructor
{
    fd = socket(AF_INET,SOCK_DGRAM,0);  //Crea el socket segun los parametros introducidos

    if (fd < 0) {   //Comprueba si se ha creado bien el socket
        throw std::system_error(errno, std::system_category(), "No se pudo crear el socket");
    }else{
        std::cout << "Socket " << fd << " creado correctamente" << std::endl;
    }

    int result = bind(fd, (const sockaddr*)&address, sizeof(address));  //Asigna una direccion y puerto al socket

    if (result < 0) {   //Comprueba si el bind ha fallado
        throw std::system_error(errno, std::system_category(), "No se pudo enlazar el socket");
    }else{
        std::cout << "Socket " << fd << " enlazado correctamente a la direccion: " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
    }
}


Socket::~Socket(void)   //Destructor
{}

void Socket::send_to(const Message &message, const sockaddr_in& address)    //Funcion que envia los mensajes
{
    std::cout << "Enviando..." << std::endl;

    int result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));    //Envia la struct message a la direccion de address

    if (result < 0) {   //Comprueba si se ha enviado bien
        throw std::system_error(errno, std::system_category(), "No se pudo enviar el mensaje");
    }else{
        char* remote_ip = inet_ntoa(address.sin_addr);  //Guarda en remote_ip la ip a donde se quiere enviar el mensaje
        int remote_port = ntohs(address.sin_port);  //Guarda en remote_port el puerto a donde se quiere enviar el mensaje
        std::cout << "Mensaje enviado correctamente a " << remote_ip << ":" << remote_port << std::endl;
    }
}

void Socket::receive_from(Message &message, sockaddr_in& address)   //Funcion que recibe los mensajes
{
    socklen_t src_len = sizeof(address);    //Guarda en src_len el tamaño de la direccion que hhay en address

    int result = recvfrom(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&address), &src_len);   //Recibe una estructura de la direccion address

    if (result < 0) {   //Comprueba si ha recibido bien
        throw std::system_error(errno, std::system_category(), "No se pudo recibir el mensaje");
    }

    char* remote_ip = inet_ntoa(address.sin_addr);  //Guarda en remote_ip la ip a donde se quiere enviar el mensaje
    int remote_port = ntohs(address.sin_port);  //Guarda en remote_port el puerto a donde se quiere enviar el mensaje
    message.text[1023] = '\0';  //Asigna al ultimo caracter un \0 para evitar errores mostrando el mensaje
    std::cout << "El usuario " << message.user << " a la hora: " << message.tiempo << " con direccion" << remote_ip << ":" << remote_port << " envió el mensaje '" << message.text << "'" << std::endl;
}
