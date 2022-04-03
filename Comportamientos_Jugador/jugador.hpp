#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include<iostream>

using namespace std;

class ComportamientoJugador : public Comportamiento{
  struct Posicion{
    int posX, posY;
  };
  public:
    void finProtExplor(Sensores sensores);
    void ColocarObstaculosExploracion();
    void inaccesibilidadPrio();
    void detectarEiniciarExploracion(Sensores sensores);
    void detectarEiniciarPrioritario(Sensores sensores);
    void comprobacionKDG(Sensores sensores);
    void resetExplor();
    void AjustesPrimeraIteracion(Sensores sensores, bool &bien_situado, int &fil, int &col, bool &primiter);
    void ActualizacionMapaYorientacion(Sensores sensores,int &fil, int &col, int &filAux, int &colAux, vector<vector<unsigned char>> &mapaResultado, vector<vector<unsigned char>> &mapaAuxiliar);
    void pintarPrecipicios();
    
    void PintarMapas(Sensores sensores, vector<vector<unsigned char>> &map, int &fil,int &col) ;
    Posicion CrearMapaProtExp(bool reajuste, Posicion pos);
    void resetPrioritario();
    void pasarMapaAuxAmapa(Sensores sensores);
    void actualizarPosYBruj(Sensores sensores,int &fil, int &col);
    int detectarObjetoPrioritario(Sensores sensores);  
    void crearArchivoMapaPot(Sensores sensores);
    void crearArchivoMapaProtExp();

    void CrearMapaPotencialPrioritario(Sensores sensores, int numCasilla,int brujula);
    
    void crearArchivoMatrizAux(Sensores sensores);
    Action movimientoDefault(Sensores sensores);
    Action movimientoPrioritario(Sensores sensores, int brujula);
    Action movimientoProtExp();

    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      ticksDefault = 0;
      pintarPrecipicios();
      // Dar el valor inicial a las variables de estado
      MaximoPotencialExp = 0;
      proxReajuste = "";
      objetivoExplor.posX = -1;
      objetivoExplor.posY = -1;
      casillaSensorPrioritaria = -1;
      ultimaAccion = actIDLE;
      tengoZapas = tengoBikini = false;
      protocoloEXP = false;
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
      

      //mapa potencial prioritario
     
      filPotPrio = colPotPrio = 4; //en mitad del mapa, para que haya espacio de sobra.

      mapaPotencial = vector<vector<int>>(9,vector<int>(9));

      for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
          mapaPotencial[i][j] = 0;
      
     primiter = true;


      //mapa potencial exploracion
      mapaPotencialExp = vector<vector<int>>(mapaResultado.size(),vector<int>(mapaResultado.size()));

      for(int i=0; i<mapaResultado.size(); i++)
        for(int j=0; j<mapaResultado.size(); j++)
          mapaPotencialExp[i][j] = 0;

      //movimiento
      protocoloPrioritario = false;
      
    }

    

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
    vector<vector<unsigned char>> mapaAuxiliar;
    vector<vector<int>> mapaPotencial;
    vector<vector<int>> mapaPotencialExp;
    int fil, col;
    int filPotPrio,colPotPrio;
    int filAux, colAux, brujula;
    int casillaSensorPrioritaria;
    
    bool girar_derecha;
    bool tengoZapas, tengoBikini;
    bool protocoloPrioritario, protocoloEXP;
    bool primiter;
    Action ultimaAccion;
    bool bien_situado;
    Posicion objetivoExplor;
    string proxReajuste;
    int MaximoPotencialExp;
    int ticksDefault;
    
    

};

#endif
