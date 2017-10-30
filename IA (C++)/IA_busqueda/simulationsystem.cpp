#include "simulationsystem.hpp"


void SimulationSystem::startingSystem() {
    display = NULL;
    n = 0,m = 0,pobs = 0;
    int imgw = 0;
    int imgh = 0;
    imgvacio = NULL;
    imgmuro = NULL;
    imginicio = NULL;
    imgfin = NULL;
    imgpersona = NULL;
    imgcamino = NULL;
    quit = false;
    modo = 'z';
    start.set_node(0,0);
    goal.set_node(0,0);
    //-------------------------------------------------Inicializa las addons y basicos------------------------------------------------//

    if(!al_init_native_dialog_addon()){
        al_show_native_message_box(display, "ERROR", "al_init_naative_dialog_addon()", "Cannot init allegro active dialog addon", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    if(!al_init()){
        al_show_native_message_box(display, "ERROR", "al_init()", "Cannot init allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    if(!al_install_keyboard()){
        al_show_native_message_box(display, "ERROR", "al_install_keyboard()", "Cannot install keyboard", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    if(!al_install_mouse()){
        al_show_native_message_box(display, "ERROR", "al_install_mouse()", "Cannot install mouse", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "ERROR", "al_init_image_addon()", "Cannot init image addon", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }
}

void SimulationSystem::askForData() {
    std::cout << "Introduzca el numero de filas de la matriz: ";
    std::cin >> n;
    std::cout << "Introduzca el numero de columnas de la matriz: ";
    std::cin >> m;

    while (modo != 'm' && modo != 'a') {
        std::cout << "Generar obstaculos de forma manual(m) o aleatoria(a)";
        std::cin >> modo;
    }

    if (modo =='a') {
        std::cout << "Introduzca el porcentage de obstaculos a generar(0-100): ";
        std::cin >> pobs;
    }


    obs_matrix.resize(n);
    for(int i = 0; i < obs_matrix.size(); i++) {
        obs_matrix[i].resize(m);
        for(int j = 0; j < obs_matrix[i].size(); j++) {
            obs_matrix[i][j] = 0;
        }
    }


    imgw = 800/m;
    imgh = 800/n;

    if(imgh < imgw){
        imgw = imgh;
    }else{
        imgh = imgw;
    }
}

void SimulationSystem::startingScreen() {
     //-------------------------------------------------Propiedades de la pantalla------------------------------------------------------//

    display = al_create_display(imgw*m, imgh*n);

    al_set_new_display_refresh_rate(1/60);
    al_set_display_flag(display,ALLEGRO_WINDOWED,1);
    al_set_display_flag(display,ALLEGRO_RESIZABLE,1);




    al_clear_to_color(al_map_rgb(225, 225, 225));

    //---------------------------------------------------Icono y tiutlo de la pantalla-------------------------------------------------//

    ALLEGRO_BITMAP *icon = al_load_bitmap("img/icon.png");
    al_set_display_icon(display, icon);
    al_set_window_title(display, "El coche autonomo");
}

void SimulationSystem::drawEmpty() {
    //--------------------------------------------------Impresion de la matriz vacia---------------------------------------------------//

    //Rellernar la matriz de vacios

    imgvacio = al_load_bitmap("img/Matriz.png");
    imgmuro = al_load_bitmap("img/muro.png");
    imginicio = al_load_bitmap("img/inicio.jpg");
    imgfin = al_load_bitmap("img/fin.jpg");
    imgpersona = al_load_bitmap("img/persona.png");
    imgcamino = al_load_bitmap("img/camino.png");

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            al_draw_scaled_bitmap(imgvacio,0,0,8,8,j*imgw,i*imgh,imgw,imgh,NULL);
        }
    }

}

void SimulationSystem::drawManually() {
    //---------------------------------------------------Modo manual  de obstaculos-------------------------------------------------//
    //Control del mouse
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_EVENT ev;

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_flip_display();

    //Click derecho: muro, Click izquierdo: borrar, Esc: salir
    int x = 0;
    int y = 0;

	bool salir = false;
    while (!salir) {
        al_wait_for_event(event_queue,&ev);

        if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = ev.mouse.y/imgw;
            y = ev.mouse.x/imgh;
        }


        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (ev.mouse.button & 1) {
                    while(ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                        x = ev.mouse.y/imgw;
                        y = ev.mouse.x/imgh;

                        obs_matrix[x][y] = 1;

                        al_draw_scaled_bitmap(imgvacio,0,0,8,8,y*imgw,x*imgh,imgw,imgh,NULL); //Soluciona problema de oscuridad cuando hay muros superpuestos
                        al_draw_scaled_bitmap(imgmuro,0,0,8,8,y*imgw,x*imgh,imgw,imgh,NULL);
                        al_flip_display();
                        al_wait_for_event(event_queue,&ev);
                    }
            } else {
                if (ev.mouse.button & 2) {
                    while(ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                        x = ev.mouse.y/imgw;
                        y = ev.mouse.x/imgh;

                        obs_matrix[x][y] = 0;

                        al_draw_scaled_bitmap(imgvacio,0,0,8,8,y*imgw,x*imgh,imgw,imgh,NULL);
                        al_flip_display();
                        al_wait_for_event(event_queue,&ev);
                    }
                }
            }

        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_I) {
                 start.set_node(x,y);

                al_draw_scaled_bitmap(imginicio,0,0,100,100,y*imgw,x*imgh,imgw,imgh,NULL);
                al_flip_display();
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_F) {
                goal.set_node(x,y);

                al_draw_scaled_bitmap(imgfin,0,0,100,100,y*imgw,x*imgh,imgw,imgh,NULL);
                al_flip_display();
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_P) {
                al_draw_scaled_bitmap(imgpersona,0,0,256,256,y*imgw,x*imgh,imgw,imgh,NULL);
                al_flip_display();
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_C) {
                al_draw_scaled_bitmap(imgcamino,0,0,567,567,y*imgw,x*imgh,imgw,imgh,NULL);
                al_flip_display();
            }

		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                	salir = true;
            }
        }
    }
}

void SimulationSystem::drawRandomly() {

    //Modo aleatorio de obstaculos
    srand(time(NULL));

    int totobs = ((m*n)*pobs)/100;
    int rnum[totobs];

    for(int i=0; i<totobs;i++){
        rnum[i]=-1;
    }
    bool repeat = false;
    cout << m << "   " << n << endl;

    for(int i = 0; i <totobs; i++){
        long int x = (rand() + rand()) % (n*m);
        repeat=false;


        for(int j = 0; j<totobs&&rnum[j]!=-1; j++){
            if(x==rnum[j]){
                repeat = true;
            }
        }
        if(repeat==true){
            i--;
        }else{
            rnum[i]=x;

            al_draw_scaled_bitmap(imgmuro,0,0,8,8,(x%m)*imgw,(x/m)*imgh,imgw,imgh,NULL);
            obs_matrix[x/m][x%m] = 1;
        }
    }
    al_flip_display();
}

void SimulationSystem::draw() {

    if(modo == 'a') drawRandomly();

    cout << "Esc para terminar de dibujar" << endl;
    drawManually();


}

void SimulationSystem::findPath() {
    //Estrategia A*

    list<Path> open_list;
    list<Path> close_list;
    bool solution = false;

    Path initial_path;
    initial_path.add_node(start.get_x(),start.get_y());
    initial_path.update_total_cost(goal.get_x(),goal.get_y());

    open_list.push_front(initial_path);

    int cont = 0;
    cout << start << goal << endl;


    while ((!open_list.empty()) && (!solution)) {

        if ((open_list.front().get_x() == goal.get_x()) && (open_list.front().get_y() == goal.get_y())) { //Si se ha llegado al objetivo hay solucion
            solution = true;
        }
        else {  //Si no se ha llegado al objetivo se analiza la primera trayectoria de la lista abierta
            Path aux = (*open_list.begin()).get_path();

            //Eliminando la primera trayectoria de la lista abierta
            open_list.pop_front();

            //Añadiendo la trayectoria a la lista cerrada
            bool explore = false;
            explore = insert_path_close_list(close_list,aux);

            //Calculo de nuevas trayectorias si es un camino no explorado(no presente en la lista cerrada)

            list<Path> new_path_list;
            if (explore) {
                search_new_path(new_path_list,aux);
            }

            //Añadiendo las nuevas trayectorias a la lista abierta, comprobando que no hayan caminos similares
            for(list<Path>::iterator list_iter = new_path_list.begin(); list_iter != new_path_list.end(); list_iter++) {
                insert_path_open_list(open_list,close_list,(*list_iter).get_path());
            }

            //Ordanacion de la lista abierta
            sort_list(open_list);
        }
    }


    //Dibujando la solucion si la hay;
    if (open_list.size() != 0) {
        Path solution_path = (*open_list.begin()).get_path();

        for(int i = 0; i < solution_path.size(); i++) {
            al_draw_scaled_bitmap(imgcamino,0,0,567,567,solution_path[i].get_y()*imgw,solution_path[i].get_x()*imgh,imgw,imgh,NULL);
        }
        al_flip_display();
    }
    else {
        cout << "NO HAY SOLUCION" << endl;
    }
}

//Ordenar para que el primero sea el min
void SimulationSystem::sort_list(list<Path>& source_list) {

    if (source_list.size() != 0) {
        Path min_path;

        min_path = (*source_list.begin()).get_path();
        int min_cost = min_path.get_total_cost();
        list<Path>::iterator min_iter = source_list.begin();
        int iter_total_cost = 0;

        for(list<Path>::iterator list_iter = source_list.begin(); list_iter != source_list.end(); list_iter++) {
            iter_total_cost = (*list_iter).get_total_cost();

                if (iter_total_cost < min_cost) {
                    min_path = (*list_iter).get_path();
                    min_cost = iter_total_cost;
                    min_iter = list_iter;
                }
        }

        source_list.erase(min_iter);

        source_list.push_front(min_path);
    }
}
list<Path> SimulationSystem::search_new_path(list<Path>& new_path_list,Path& path) {
    int new_x;
    int new_y;
    bool exist;

    //Hacia arriba
    new_x = path.get_x()-1;
    new_y = path.get_y();
    exist = true;

    if ((new_x < 0) || (new_x > obs_matrix.size()-1)) exist = false;
    if ((new_y < 0) || (new_y > obs_matrix[0].size()-1)) exist = false;

    if(exist && (obs_matrix[new_x][new_y] != 1)) { //Si no hay obstáculos

        if (((new_x) != path.get_x_before_last()) || ((new_y) != path.get_y_before_last())) { //Si no es por el que ha venido
            Path aux;

            aux = path;
            aux.add_node(new_x,new_y);
            aux.update_total_cost(goal.get_x(),goal.get_y());
            //cout << aux << endl;
            new_path_list.push_front(aux);
        }
    }


    //Hacia la derecha
    new_x = path.get_x();
    new_y = path.get_y()+1;
    exist = true;

    if ((new_x < 0) || (new_x > obs_matrix.size()-1)) exist = false;
    if ((new_y < 0) || (new_y > obs_matrix[0].size()-1)) exist = false;

    if(exist && (obs_matrix[new_x][new_y] != 1)) { //Si no hay obstáculos

        if (((new_x) != path.get_x_before_last()) || ((new_y) != path.get_y_before_last())) { //Si no es por el que ha venido
            Path aux;

            aux = path;
            aux.add_node(new_x,new_y);
            aux.update_total_cost(goal.get_x(),goal.get_y());
            //cout << aux << endl;
            new_path_list.push_front(aux);
        }
    }

    //Hacia abajo

    new_x = path.get_x()+1;
    new_y = path.get_y();
    exist = true;

    if ((new_x < 0) || (new_x > obs_matrix.size()-1)) exist = false;
    if ((new_y < 0) || (new_y > obs_matrix[0].size()-1)) exist = false;

    if(exist && (obs_matrix[new_x][new_y] != 1)) { //Si no hay obstáculos

        if (((new_x) != path.get_x_before_last()) || ((new_y) != path.get_y_before_last())) { //Si no es por el que ha venido
            Path aux;

            aux = path;
            aux.add_node(new_x,new_y);
            aux.update_total_cost(goal.get_x(),goal.get_y());
            //cout << aux << endl;
            new_path_list.push_front(aux);
        }
    }

    //Hacia la izquierda

    new_x = path.get_x();
    new_y = path.get_y()-1;
    exist = true;

    if ((new_x < 0) || (new_x > obs_matrix.size()-1)) exist = false;
    if ((new_y < 0) || (new_y > obs_matrix[0].size()-1)) exist = false;

    if(exist && (obs_matrix[new_x][new_y] != 1)) { //Si no hay obstáculos

        if (((new_x) != path.get_x_before_last()) || ((new_y) != path.get_y_before_last())){ //Si no es por el que ha venido
            Path aux;

            aux = path;
            aux.add_node(new_x,new_y);
            aux.update_total_cost(goal.get_x(),goal.get_y());

            new_path_list.push_front(aux);
        }
    }


    return new_path_list;
}

//Al insertar, en caso de caminos similares, elimina el de mayor coste.
bool SimulationSystem::insert_path_close_list(list<Path>& close_list,Path& path) {
    //????????? la lista cerrada siempre estara sin caminos similares???????????????????????????
    //salir con al encontrar un camino similar??????

    bool exist = false;
    bool explore = false;

    int x_path = path.get_x();
    int y_path = path.get_y();
    int path_total_cost = path.get_total_cost();

    int iter_total_cost = 0;

    for(list<Path>::iterator list_iter = close_list.begin(); !exist && (list_iter != close_list.end()); list_iter++) {//Insertando la trayectoria en la lista cerrada
        if (((*list_iter).get_x() == x_path) && ((*list_iter).get_y() == y_path)) { //Detectando si es un camino similar
            exist = true;


            iter_total_cost = (*list_iter).get_total_cost();

            if (iter_total_cost > path_total_cost) {
                close_list.erase(list_iter);
                close_list.push_front(path);
                explore = true;

            }

        }
    }
    if (!exist) {
        close_list.push_front(path);
        explore = true;
    }

    return explore;
}

//Al insertar, en caso de caminos similares,se pasa el mayor a la lista cerrada
void SimulationSystem::insert_path_open_list(list<Path>& open_list,list<Path>& close_list,Path path) {

    bool exist = false;

    int x_path = path.get_x();
    int y_path = path.get_y();
    int path_total_cost = path.get_total_cost();

    int iter_total_cost = 0;

    for(list<Path>::iterator list_iter = open_list.begin(); !exist && (list_iter != open_list.end()); list_iter++) {//Insertando la trayectoria en la lista cerrada
        if (((*list_iter).get_x() == x_path) && ((*list_iter).get_y() == y_path)) { //Detectando si es un camino similar
            exist = true;

            iter_total_cost = (*list_iter).get_total_cost();

            if (iter_total_cost > path_total_cost) {
                Path aux;

                aux = (*list_iter).get_path();
                insert_path_close_list(close_list,aux);

                open_list.erase(list_iter);
                open_list.push_front(path);
            }
        }
    }
    if (!exist) {
        open_list.push_front(path);
    }

}

void SimulationSystem::shutdownSystem() {

    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_EVENT ev;

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    cout << "Esc para salir" << endl;

    bool salir = false;
    while (!((ev.type == ALLEGRO_EVENT_KEY_DOWN) && (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE))) {
        al_wait_for_event(event_queue,&ev);
    }

    al_destroy_display(display);
    al_destroy_bitmap(imgvacio);
    al_destroy_bitmap(imgmuro);
}
