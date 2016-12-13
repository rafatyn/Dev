#include "Socket.hpp"

Socket::Socket(const sockaddr_in &address)
{
    fd = socket(AF_INET,SOCK_DGRAM,0);

    if (fd < 0) {
        throw std::system_error(errno, std::system_category(), "No se pudo crear el socket");
    }else{    
        std::cout << "Socket " << fd << " creado correctamente" << std::endl;
    }
    
    int result = bind(fd, (const sockaddr*)&address, sizeof(address));
    
    if (result < 0) {
        throw std::system_error(errno, std::system_category(), "No se pudo enlazar el socket");
    }else{    
        std::cout << "Socket " << fd << " enlazado correctamente a la direccion: " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
    }
}


Socket::~Socket(void)
{}

void Socket::send_to(const Message &message, const sockaddr_in& address)
{
    std::cout << "Enviando..." << std::endl;
    
    int result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));
   
    if (result < 0) {
        throw std::system_error(errno, std::system_category(), "No se pudo enviar el mensaje");
    }else{
        char* remote_ip = inet_ntoa(address.sin_addr);
        int remote_port = ntohs(address.sin_port);
        std::cout << "Mensaje enviado correctamente a " << remote_ip << ":" << remote_port << std::endl;
    }
}

void Socket::receive_from(Message &message, sockaddr_in& address)
{ 
    socklen_t src_len = sizeof(address);
    
    int result = recvfrom(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&address), &src_len);
    
    if (result < 0) {
        throw std::system_error(errno, std::system_category(), "No se pudo recibir el mensaje");
    }
    
    char* remote_ip = inet_ntoa(address.sin_addr);
    int remote_port = ntohs(address.sin_port);
    message.text[1023] = '\0';
    std::cout << "El usuario " << message.user  << " " << remote_ip << ":" << remote_port << " envió el mensaje '" << message.text << "'" << std::endl;
}