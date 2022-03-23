#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include<iostream>

using namespace std;

class ComportamientoJugador : public Comportamiento{
  public:
    void pM(Sensores sensores, vector<vector<unsigned char>> &map, int &fil,int &col) ;
    void resetPrioritario();
    void pasarMapaAuxAmapa(Sensores sensores);
    void actualizarPosYBruj(Sensores sensores,int &fil, int &col);
    int detectarObjetoPrioritario(Sensores sensores);  
    void crearArchivoMapaPot(Sensores sensores);

    void CrearMapaPotencialPrioritario(Sensores sensores, int numCasilla,int brujula);
    
    void crearArchivoMatrizAux(Sensores sensores);
    Action movimientoDefault(Sensores sensores);
    Action movimientoPrioritario(Sensores sensores, int brujula);


    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      casillaSensorPrioritaria = -1;
      ultimaAccion = actIDLE;
      tengoZapas = tengoBikini = false;
      
      girar_derecha = false;
      

      //mapa
      fil = col = 99;
      brujula = 0;    //(0 norte, 1 este, 2 sur y 3 oeste)
      bien_situado = false;


      
      //mapa relativo

      filAux = colAux = 99;
      brujula = 0;
      mapaAuxiliar = vector<vector<unsigned char>>(200,vector<unsigned char>(200));

      for(int i=0; i<200; i++)
        for(int j=0; j<200; j++)
          mapaAuxiliar[i][j] = '?';
      

      //mapa potencial
     
      filPotPrio = colPotPrio = 4; //en mitad del mapa, para que haya espacio de sobra.

      mapaPotencial = vector<vector<int>>(9,vector<int>(9));

      for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
          mapaPotencial[i][j] = 0;
      





     primiter = true;

      

      //movimiento
      protocoloPrioritario = false;
      PrioCentro = PrioIzq = prioDcha = false;
      primeraDeteccionObjetoPrioritario = false;
      
    }

    

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
    vector<vector<unsigned char>> mapaAuxiliar;
    vector<vector<int>> mapaPotencial;
    int fil, col;
    int filPotPrio,colPotPrio;
    int filAux, colAux, brujula;
    int casillaSensorPrioritaria;

    bool girar_derecha;
    bool tengoZapas, tengoBikini;
    bool protocoloPrioritario;
    bool PrioCentro, PrioIzq, prioDcha;
    bool primeraDeteccionObjetoPrioritario;
    bool primiter;
    Action ultimaAccion;
    bool seHaGiradoPorPrioridad = false;
    bool bien_situado; //nos dice si conocemos las coordenadas en las que estamos.

};

#endif
