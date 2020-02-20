#pragma once

#include <fstream>
#include "amuleto_t.hpp"
#include "mazmorra_t.hpp"
#include "pasillo_t.hpp"
#include "jugador_t.hpp"

using namespace std;

class tablero_t{

  private:
  
    int n_;
    int m_;
    char* map_;
    mazmorra_t* mazmorra_;
    int n_mazmorras_;
    pasillo_t* pasillo_;
    int n_pasillos_;
    jugador_t jugador_;
    amuleto_t amuleto_;

  public:

    tablero_t(void);
    ~tablero_t(void);
    bool game_over(void);
    void crear_fichero(void);
    void cargar(void);
    void redimensiona_pasillos(void);
    void destruye_pasillos(void);
    void generar_aleatorio(void);
    void movimientos(void);
    void partida (void);
    void pintar_amuleto(void);
    void situar_amuleto(void);
    void redimensionar_mazmorras(void);
    void pintar_personaje(void);
    void situa_personaje(void);
    void crea_pasillos(void);
    void pintar_pasillos(void);
    void pintar_mazmorras(void);
    void crea_mazmorras(void);
    void destruye_mazmorra(void);
    char get(int i, int j);
    void set(int i, int j, char x);
    int get_n(void);
    int get_m(void);
    void limpiar(void);
    void mostrar(void);
    void redimensiona(int n, int m);
    
  private:
  
    void crea(void);
    void destruye(void);
    int pos(int i, int j);
    
};