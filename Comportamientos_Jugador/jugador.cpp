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

void ComportamientoJugador::actualizarPosYBruj(Sensores sensores){
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
			girar_derecha = (rand()%2==0);
			break;
		case actTURN_R:
			brujula = (brujula+1)%4;
			girar_derecha = (rand()%2==0);
			break;
	}
}

//bikini, zapatillas y posicionamiento, RECARGA NO.
pair<bool,int> ComportamientoJugador::detectoObjetoPrioritario(Sensores sensores){
	pair<bool,int> res;
	
	//bikini
	if(!tengoBikini){
		//lado izq
		for(int i=1; i <= 11; i++){

			if(sensores.terreno[i] == 'K'){
				res.first = true;
				res.second = i;
				return res;
			}

			if(i == 1)
				i = 3;

			if(i == 5)
				i == 8;
		}

		//centro
		if(sensores.terreno[2] == 'K'){
			res.first = true;
			res.second = 2;
			return res;
		}

		if(sensores.terreno[6] == 'K'){
			res.first = true;
			res.second = 6;
			return res;
		}

		if(sensores.terreno[12] == 'K'){
			res.first = true;
			res.second = 12;
			return res;
		}

		// derecho
		for(int i=3; i <= 11; i++){

			if(sensores.terreno[i] == 'K'){
				res.first = true;
				res.second = i;
				return res;
			}

			if(i == 3)
				i = 6;

			if(i == 8)
				i == 12;

		}
	}
	
	if(sensores.terreno[0] == 'K'){
		res.first = false;
		res.first = 0;
		return res;
	}

	//zapatillas:
	if(!tengoZapas){
		//lado izq
		for(int i=1; i <= 11; i++){

			if(sensores.terreno[i] == 'D'){
				res.first = true;
				res.second = i;
				return res;
			}

			if(i == 1)
				i = 3;

			if(i == 5)
				i == 8;

		}

		//centro
		if(sensores.terreno[2] == 'D'){
			res.first = true;
			res.second = 2;
			return res;
		}

		if(sensores.terreno[6] == 'D'){
			res.first = true;
			res.second = 6;
			return res;
		}

		if(sensores.terreno[12] == 'D'){
			res.first = true;
			res.second = 12;
			return res;
		}

		//lado derecho

	
		for(int i=3; i <= 11; i++){
			if(sensores.terreno[i] == 'D'){
				res.first = true;
				res.second = i;
				return res;
			}

			if(i == 3)
				i = 6;

			if(i == 8)
				i == 12;
		}
	}
	
	if(sensores.terreno[0] == 'D'){
		res.first = false;
		res.first = 0;
		return res;
	}

	//posicionamiento
	if(!bien_situado){
		//lado izq
		for(int i=1; i <= 11; i++){

			if(sensores.terreno[i] == 'G'){
				res.first = true;
				res.second = i;
				return res;
			}

			if(i == 1)
				i = 3;

			if(i == 5)
				i == 8;

		}

		//centro
		if(sensores.terreno[2] == 'G'){
			res.first = true;
			res.second = 2;
			return res;
		}

		if(sensores.terreno[6] == 'G'){
			res.first = true;
			res.second = 6;
			return res;
		}

		if(sensores.terreno[12] == 'G'){
			res.first = true;
			res.second = 12;
			return res;
		}

		//lado derecho

	
		for(int i=3; i <= 11; i++){
			if(sensores.terreno[i] == 'G'){
				res.first = true;
				res.second = i;
				return res;
			}

			if(i == 3)
				i = 6;

			if(i == 8)
				i == 12;
		}
	}
	
	if(sensores.terreno[0] == 'G'){
		res.first = false;
		res.first = 0;
		return res;
	}

	res.first = false;
	res.second = -1;

	return res;
}

Action ComportamientoJugador::movimientoDefault(Sensores sensores){

	if(!protocoloPrioritario and ((sensores.superficie[2] == '_' and sensores.terreno[2] != 'M' and sensores.terreno[2] != 'P' and sensores.terreno[2] != 'A' and sensores.terreno[2] != 'B') 
		or  (sensores.terreno[2] == 'A' and tengoBikini) 
		or (sensores.terreno[2] == 'B' and tengoZapas)) ){
		
		return actFORWARD;
	}
	else if (!protocoloPrioritario and !girar_derecha ){
		return actTURN_L;
	} else if (!protocoloPrioritario){
		return actTURN_R;
	}
}

Action ComportamientoJugador::movimientoPrioritario(Sensores sensores){
pair<bool,int> prio = detectoObjetoPrioritario(sensores);

		if (prio.first == true)
			return actFORWARD;
		else {

			if(prio.first == false){
				if(PrioIzq){
					PrioIzq = false;
					return actTURN_L;
					
				}

				if(prioDcha){
					prioDcha = false;
					return actTURN_R;
				}
			}
		}

		if(prio.second == 0)
			protocoloPrioritario = false;

		if(sensores.terreno[0] == 'K')
			tengoBikini = true;

		if(sensores.terreno[0] == 'D')
			tengoZapas = true;	

}

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	actualizarPosYBruj(sensores);

	if(bien_situado){
		fil = sensores.posF;
		col = sensores.posC;
		brujula = sensores.sentido;
		pintarMapa(sensores);
		
	}

	if(!protocoloPrioritario){

		pair<bool,int> prot;
		prot = detectoObjetoPrioritario(sensores);

		if(prot.first == true){
			
			protocoloPrioritario = true;

			if (prot.second == 1 || prot.second == 4 || prot.second == 5 
			|| prot.second == 9 || prot.second == 10 || prot.second == 11)
			PrioIzq = true;

			else if (prot.second == 3 || prot.second == 7 || prot.second == 8
			|| prot.second == 13 || prot.second == 14 || prot.second == 15)
			prioDcha = true;

			else if (prot.second == 2 || prot.second == 6 || prot.second == 12)
			PrioCentro = true;
		}
	}

	//Decidir la nueva accion

	accion = movimientoDefault(sensores);

	if(protocoloPrioritario){
		accion = movimientoPrioritario(sensores);
			
	}

//----------------------------------------------------------------------
	// Determinar el efecto de la ultima accion enviada
	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}





































//couts que se encontraban entre la decisión de la acción y el return final.

	/*
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
*/