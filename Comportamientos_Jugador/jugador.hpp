#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{
  public:
    void pintarMapa(Sensores sensores);
    void actualizarPosYBruj(Sensores sensores);
    pair<bool,int> detectoObjetoPrioritario(Sensores sensores);  

    Action movimientoDefault(Sensores sensores);
    Action movimientoPrioritario(Sensores sensores);


    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado

      fil = col = 99;
      brujula = 0;    //(0 indica orientación norte, 1 este, 2 sur y 3 oeste)
      ultimaAccion = actIDLE;
      tengoZapas = tengoBikini = false;
      bien_situado = true;
      girar_derecha = false;
      protocoloPrioritario = false;
      PrioCentro = PrioIzq = prioDcha = false;
      
      
      
    }

    

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
    bool girar_derecha;
    bool tengoZapas, tengoBikini;
    bool protocoloPrioritario;
    bool PrioCentro, PrioIzq, prioDcha;

    int fil, col, brujula;
    Action ultimaAccion;
    bool bien_situado; //nos dice si conocemos las coordenadas en las que estamos.


};

#endif
