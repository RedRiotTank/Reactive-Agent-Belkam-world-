#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include<iostream>

using namespace std;

class ComportamientoJugador : public Comportamiento{
  public:
    void pM(Sensores sensores, vector<vector<unsigned char>> &map, int &fil,int &col) ;
    void pintarMapa(Sensores sensores);
    void pintarMapaAuxiliar(Sensores sensores);
    void pasarMapaAuxAmapa(Sensores sensores);
    void actualizarPosYBruj(Sensores sensores);
    pair<bool,int> detectoObjetoPrioritario(Sensores sensores);  
    void SituarEnMapa(Sensores sensores);
    void seleccionPosicionPrioritario(Sensores sensores);
    void crearArchivoMatrizAux(Sensores sensores);
    Action movimientoDefault(Sensores sensores);
    Action movimientoPrioritario(Sensores sensores);


    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado

      ultimaAccion = actIDLE;
      tengoZapas = tengoBikini = false;
      
      girar_derecha = false;
      

      //mapa
      fil = col = 99;
      brujula = 0;    //(0 norte, 1 este, 2 sur y 3 oeste)
      bien_situado = false;


      
      //mapa relativo

      filAux = colAux = 99;
      brujulaAux = 0;
      mapaAuxiliar = vector<vector<unsigned char>>(200,vector<unsigned char>(200));

      for(int i=0; i<200; i++)
        for(int j=0; j<200; j++)
          mapaAuxiliar[i][j] = '?';
      
      

     

      

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
    int fil, col, brujula;
    int filAux, colAux, brujulaAux;


    bool girar_derecha;
    bool tengoZapas, tengoBikini;
    bool protocoloPrioritario;
    bool PrioCentro, PrioIzq, prioDcha;
    bool primeraDeteccionObjetoPrioritario;
    
    Action ultimaAccion;
    bool bien_situado; //nos dice si conocemos las coordenadas en las que estamos.


};

#endif
