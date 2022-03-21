#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include<cmath>
#include<stdlib.h> 
#include<fstream>
using namespace std;

void ComportamientoJugador::pM(Sensores sensores, vector<vector<unsigned char>> &map, int &fil, int &col){

	map[fil][col] = sensores.terreno[0];
	int sens;
	switch(brujula){
				case 0: // norte ^
					sens = 1;
					for(int i= - 1; i <= 1; i++){
						
						map[fil-1][col + i] = sensores.terreno[sens];
						sens++;
					}
					sens = 4;
					for(int i= -2; i <= 2; i++){
						map[fil -2][col + i] = sensores.terreno[sens];
						sens++;
					}
					sens = 9;
					for(int i= -3; i <= 3; i++){
						map[fil -3][col + i] = sensores.terreno[sens];
						sens++;
					}
				 	break;
				case 1: //este  -->
					sens = 1;
					for(int i= - 1; i <= 1; i++){
						map[fil + i][col + 1] = sensores.terreno[sens];
						sens++;
					}
					sens = 4;
					for(int i= -2; i <= 2; i++){
						map[fil + i][col + 2] = sensores.terreno[sens];
						sens++;
					}

					sens = 9;
					for(int i= -3; i <= 3; i++){
						map[fil + i][col + 3] = sensores.terreno[sens];
						sens++;
					}
					break;
				case 2: //sur V
					sens = 3;
					for(int i= - 1; i <= 1; i++){
						
						map[fil+1][col + i] = sensores.terreno[sens];
						sens--;
					}
					sens = 8;
					for(int i= -2; i <= 2; i++){
						map[fil +2][col + i] = sensores.terreno[sens];
						sens--;
					}
					sens = 15;
					for(int i= -3; i <= 3; i++){
						map[fil +3][col + i] = sensores.terreno[sens];
						sens--;
					}
					break;
				case 3: //oeste <--
					sens = 3;
					for(int i= - 1; i <= 1; i++){
						
						map[fil + i][col - 1] = sensores.terreno[sens];
						sens--;
					}
					sens = 8;
					for(int i= -2; i <= 2; i++){
						map[fil + i][col - 2] = sensores.terreno[sens];
						sens--;
					}
					sens = 15;
					for(int i= -3; i <= 3; i++){
						map[fil + i][col - 3] = sensores.terreno[sens];
						sens--;
					}
					break;
			}
}


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

void ComportamientoJugador::pintarMapaAuxiliar(Sensores sensores){

	mapaAuxiliar[filAux][colAux] = sensores.terreno[0];
	int sens;
	switch(brujulaAux){
				case 0: // norte ^
					sens = 1;
					for(int i= - 1; i <= 1; i++){
						
						mapaAuxiliar[filAux-1][colAux + i] = sensores.terreno[sens];
						sens++;
					}
					sens = 4;
					for(int i= -2; i <= 2; i++){
						mapaAuxiliar[filAux -2][colAux + i] = sensores.terreno[sens];
						sens++;
					}
					sens = 9;
					for(int i= -3; i <= 3; i++){
						mapaAuxiliar[filAux -3][colAux + i] = sensores.terreno[sens];
						sens++;
					}
				 	break;
				case 1: //este  -->
					sens = 1;
					for(int i= - 1; i <= 1; i++){
						mapaAuxiliar[filAux + i][colAux + 1] = sensores.terreno[sens];
						sens++;
					}
					sens = 4;
					for(int i= -2; i <= 2; i++){
						mapaAuxiliar[filAux + i][colAux + 2] = sensores.terreno[sens];
						sens++;
					}

					sens = 9;
					for(int i= -3; i <= 3; i++){
						mapaAuxiliar[filAux + i][colAux + 3] = sensores.terreno[sens];
						sens++;
					}
					break;
				case 2: //sur V
					sens = 3;
					for(int i= - 1; i <= 1; i++){
						
						mapaAuxiliar[filAux+1][colAux + i] = sensores.terreno[sens];
						sens--;
					}
					sens = 8;
					for(int i= -2; i <= 2; i++){
						mapaAuxiliar[filAux +2][colAux + i] = sensores.terreno[sens];
						sens--;
					}
					sens = 15;
					for(int i= -3; i <= 3; i++){
						mapaAuxiliar[filAux +3][colAux + i] = sensores.terreno[sens];
						sens--;
					}
					break;
				case 3: //oeste <--
					sens = 3;
					for(int i= - 1; i <= 1; i++){
						
						mapaAuxiliar[filAux + i][colAux - 1] = sensores.terreno[sens];
						sens--;
					}
					sens = 8;
					for(int i= -2; i <= 2; i++){
						mapaAuxiliar[filAux + i][colAux - 2] = sensores.terreno[sens];
						sens--;
					}
					sens = 15;
					for(int i= -3; i <= 3; i++){
						mapaAuxiliar[filAux + i][colAux - 3] = sensores.terreno[sens];
						sens--;
					}
					break;
			}
}

void ComportamientoJugador::pasarMapaAuxAmapa(Sensores sensores){

pair<int,int> diferencia;
fil = sensores.posF;
col = sensores.posC;


diferencia.first = abs(filAux-fil);
diferencia.second = abs(colAux-col);

//cout << "la diferencia es: " + diferencia.first  + diferencia.second << endl;

for(int i=0; i<200; i++){
	for(int j=0; j<200; j++){

		if(mapaAuxiliar[i][j] != '?'){
			mapaResultado[i-diferencia.first][j - diferencia.second] = mapaAuxiliar[i][j];
		}

	}
}


}

void ComportamientoJugador::crearArchivoMatrizAux(Sensores sensores){

	//-----
		ofstream archivo;
		archivo.open("matrizAuxiliar.txt",ios::out);
		if(archivo.fail()){
			cout << "ERROR AL CREAR EL ARCHIVO";
			exit(1);
		} else {


			
			for(int i=0; i<200; i++){
				for(int j=0; j<200; j++){
					archivo<<mapaAuxiliar[i][j] << " ";
				}
				archivo << endl;
			}


			

		}
		archivo.close();

	//-----
}

void ComportamientoJugador::actualizarPosYBruj(Sensores sensores){
	if (bien_situado){

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



	} else {

		switch (ultimaAccion)
		{
		case actFORWARD:
				switch(brujulaAux){
				case 0: filAux--; break;
				case 1: colAux++; break;
				case 2: filAux++; break;
				case 3: colAux--; break;
			}
		break;

		case actTURN_L:
			brujulaAux = (brujulaAux+3)%4;
			girar_derecha = (rand()%2==0);
		break;
		case actTURN_R:
			brujulaAux = (brujulaAux+1)%4;
			girar_derecha = (rand()%2==0);
		break;
		}
	}
}

void ComportamientoJugador::SituarEnMapa(Sensores sensores) {
	fil = sensores.posF;
	col = sensores.posC;
	brujula = sensores.sentido;
	pintarMapa(sensores);
}

pair<bool,int> ComportamientoJugador::detectoObjetoPrioritario(Sensores sensores){
	pair<bool,int> res;
	
	//bikini, zapatillas y posicionamiento, RECARGA NO.


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

Action ComportamientoJugador::movimientoPrioritario(Sensores sensores){	//Sistema de producción.
pair<bool,int> prio = detectoObjetoPrioritario(sensores);

		if (prio.first == true)		//Siempre que lo vea delante de el, avanzará
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

void ComportamientoJugador::seleccionPosicionPrioritario(Sensores sensores){

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
}

Action ComportamientoJugador::think(Sensores sensores){

	brujulaAux = sensores.sentido;
	brujula = sensores.sentido;

	if(sensores.nivel == 0)
		bien_situado = true;

	Action accion = actIDLE;

	actualizarPosYBruj(sensores);

	pM(sensores,mapaAuxiliar,filAux,colAux);

	crearArchivoMatrizAux(sensores);

	if(sensores.terreno[0] == 'G'){
		

		


		pasarMapaAuxAmapa(sensores);

	}


	if(bien_situado){
		SituarEnMapa(sensores);
	}

	seleccionPosicionPrioritario(sensores);
	

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