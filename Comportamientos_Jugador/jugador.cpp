#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::pintarMapa(Sensores sensores){

	mapaResultado[fil][col] = sensores.terreno[0];
	int sens;
	switch(brujula){
				case 0: // norte ^
					sens = 1;
					for(int i= - 1; i <= 1; i++){
						
						mapaResultado[fil-1][col + i] = sensores.terreno[sens];
						sens++;
					}
					sens = 4;
					for(int i= -2; i <= 2; i++){
						mapaResultado[fil -2][col + i] = sensores.terreno[sens];
						sens++;
					}
					sens = 9;
					for(int i= -3; i <= 3; i++){
						mapaResultado[fil -3][col + i] = sensores.terreno[sens];
						sens++;
					}
				 	break;
				case 1: //este  -->
					sens = 1;
					for(int i= - 1; i <= 1; i++){
						mapaResultado[fil + i][col + 1] = sensores.terreno[sens];
						sens++;
					}
					sens = 4;
					for(int i= -2; i <= 2; i++){
						mapaResultado[fil + i][col + 2] = sensores.terreno[sens];
						sens++;
					}

					sens = 9;
					for(int i= -3; i <= 3; i++){
						mapaResultado[fil + i][col + 3] = sensores.terreno[sens];
						sens++;
					}
					break;
				case 2: //sur V
					sens = 3;
					for(int i= - 1; i <= 1; i++){
						
						mapaResultado[fil+1][col + i] = sensores.terreno[sens];
						sens--;
					}
					sens = 8;
					for(int i= -2; i <= 2; i++){
						mapaResultado[fil +2][col + i] = sensores.terreno[sens];
						sens--;
					}
					sens = 15;
					for(int i= -3; i <= 3; i++){
						mapaResultado[fil +3][col + i] = sensores.terreno[sens];
						sens--;
					}
					break;
				case 3: //oeste <--
					sens = 3;
					for(int i= - 1; i <= 1; i++){
						
						mapaResultado[fil + i][col - 1] = sensores.terreno[sens];
						sens--;
					}
					sens = 8;
					for(int i= -2; i <= 2; i++){
						mapaResultado[fil + i][col - 2] = sensores.terreno[sens];
						sens--;
					}
					sens = 15;
					for(int i= -3; i <= 3; i++){
						mapaResultado[fil + i][col - 3] = sensores.terreno[sens];
						sens--;
					}
					break;
			}


	
}



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	
	switch(ultimaAccion){
		case actFORWARD:
			switch(brujula){
				case 0: fil--; break;
				case 1: col++; break;
				case 2: fil++; break;
				case 3: col--; break;
			}
			break;
		case actTURN_L:
			brujula = (brujula+3)%4;
			//girar_derecha = (rand()%2==0);
			break;
		case actTURN_R:
			brujula = (brujula+1)%4;
			//girar_derecha = (rand()%2==0);
			break;

	}


	if(bien_situado){
		fil = sensores.posF;
		col = sensores.posC;
		brujula = sensores.sentido;
		pintarMapa(sensores);
		
	}








	//Decidir la nueva accion


//agua A arboles B
	


	if((sensores.superficie[2] == '_' and sensores.terreno[2] != 'M' and sensores.terreno[2] != 'P' and sensores.terreno[2] != 'A' and sensores.terreno[2] != 'B') 
		or  (sensores.terreno[2] == 'A' and tengoBikini) 
		or (sensores.terreno[2] == 'B' and tengoZapas)){
		
		accion = actFORWARD;
	}
	else {
		accion = actTURN_R;
	}

	


	//detectar si estamos encerrados
	
//----------
	if(protEncerrado){
		
	}



// No se que es esto -------------------------------------------
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Este" << endl; break;
		case 2: cout << "Sur " << endl; break;
		case 3: cout << "Oeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;



//----------------------------------------------------------------------
	// Determinar el efecto de la ultima accion enviada
	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}



