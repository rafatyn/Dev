#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <httpserver.h>

void go_Demonio(char *argv[])
{
    pid_t pid;
    umask(0);
    pid = fork();

    if (pid < 0) {
        std::cerr << strerror(errno) << '\n';
        exit(10);
    }

    if (pid > 0) {
        exit(0);
    }

    openlog(argv[0], LOG_NOWAIT | LOG_PID, LOG_USER);
    syslog(LOG_NOTICE, "Demonio iniciado con éxito\n");

    pid = setsid();
    if (pid < 0) {
        syslog(LOG_ERR, "No fue posible crear una nueva sesión\n");
        exit(11);
    }

    if ((chdir("/")) < 0) {
        syslog(LOG_ERR, "No fue posible cambiar el directorio de trabajo a /\n");
        exit(12);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int fd0 = open("/dev/null", O_RDONLY);
    int fd1 = open("/dev/null", O_WRONLY);
    int fd2 = open("/dev/null", O_WRONLY);

    QByteArray ug = qgetenv("USER");
    passwd* user = getpwnam(ug);
    if (user == NULL) qDebug() << errno << strerror(errno);
    seteuid(user->pw_uid);

    group* group = getgrnam(ug);
    setegid(group->gr_gid);
}

int main(int argc, char *argv[])
{
    bool gui = false;
    bool error = false;
    quint16 port = 0;

    for(int i=1; i<argc && !error; i++){
        if(QString(argv[i]) == "-d"){
            gui = true;
        }else if(QString(argv[i]) == "-p"){
            if(i+1 < argc){
                if(atoi(argv[i+1]) >= 1024 && atoi(argv[i+1]) <= 65535){
                    port = atoi(argv[i+1]);
                }else{
                    std::cout << "Invalid port, port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
                    error = true;
                }
            }else{
                std::cout << "Port needed: -p [port], port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
                error = true;
            }
            i++;
        }else if(QString(argv[i]) == "--help"){
            std::cout << "Usage: -d (demo version with GUI) -p [Port]" << std::endl;
            error = true;
        }else{
            std::cout << "Unrecognized option " << argv[i] << std::endl << "Usage: -d (demo version with GUI) -p [Port]" << std::endl;
            error = true;
        }
    }

    if(!gui && port == 0){
        std::cout << "Port needed: -p [port], port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
        error = true;
    }

    char *aaa[1];
    aaa[0] = argv[0];
    int x = 1;
    QApplication a(x, aaa);


    if(!error){
        MainWindow w(0, gui, port);

        if(gui)
            w.show();
        else{}
            //go_Demonio(argv);



          qttp::HttpServer* httpSvr = qttp::HttpServer::getInstance();
          httpSvr->initialize();
          // Create an action, named "action_usuarios", that will handle all requests
          auto action_usuarios = httpSvr->createAction([&](qttp::HttpData& data) {
            // Form the JSON content and let the framework handle the rest.
            QJsonObject& json = data.getResponse().getJson();
            for(int i=0; i<w.get_clients();i++){
                json[w.get_this_client_name(i)] = w.get_this_client(i).first.toString().append(":") + QString().setNum(w.get_this_client(i).second);
            }
            json["Usuarios conectados actualmente"] = QString().setNum(w.get_clients());
          });

          auto action_pendientes = httpSvr->createAction([&](qttp::HttpData& data) {
            // Form the JSON content and let the framework handle the rest.
            QJsonObject& json = data.getResponse().getJson();
            for(int i=0; i<w.get_pending_clients();i++){
                json[w.get_this_pending_client_name(w.get_this_client(i))] = w.get_this_pending_client(i).first.toString().append(":") + QString().setNum(w.get_this_pending_client(i).second);
            }
            json["Usuarios a la espera de enviar"] = QString().setNum(w.get_pending_clients());
          });

            auto action_uso = httpSvr->createAction([&](qttp::HttpData& data) {
              // Form the JSON content and let the framework handle the rest.
              QJsonObject& json = data.getResponse().getJson();
              if(!w.is_occupied()){
                    json["Estado del servidor"] = "Ocupado";
              }else{
                    json["Estado del servidor"] = "Libre";
              }
            });

            auto action_estadisticas = httpSvr->createAction([&](qttp::HttpData& data) {
              // Form the JSON content and let the framework handle the rest.
              QJsonObject& json = data.getResponse().getJson();
              json["Numero de paquetes de datos enviados"] = w.get_nFiles();
              json["Cantidad de datos enviados"] = w.get_nBytesReceived();
              json["Tiempo medio de envio de paquetes de información"] = w.get_total_transfer_time() / w.get_nFiles();
              json["Tamaño medio de paquetes de información"] = w.get_nBytesReceived() / w.get_nFiles();
            });

            auto action_usuario = httpSvr->createAction([&](qttp::HttpData& data) {

              QJsonValue user = data.getRequest().getJson()["user"];
              QJsonValue action = data.getRequest().getJson()["action"];

              QJsonObject& json = data.getResponse().getJson();
              QString accion("Accion: ");
              accion.append(action.toString());
              QString usuario(" sobre usuario: ");
              usuario.append(user.toString());
              if(w.user_action(user.toString(),action.toString())){
                    json[accion + usuario] = "Exito";
              }else{
                     json[accion + usuario] = "Fallo";
              }


            });

          // Register the action to handle http GET.
          action_usuarios->registerRoute(qttp::HttpMethod::GET, "/usuarios-conectados");
          action_pendientes->registerRoute(qttp::HttpMethod::GET, "/usuarios-pendientes");
          action_uso->registerRoute(qttp::HttpMethod::GET, "/uso");
          action_estadisticas->registerRoute(qttp::HttpMethod::GET, "/estadisticas");
          action_usuario->registerRoute(qttp::HttpMethod::GET, "/usuarios/:user/:action");


          // Libuv runs in its own thread.
          httpSvr->startServer();

        return a.exec();
    }
}

