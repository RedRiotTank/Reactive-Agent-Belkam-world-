#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include<cmath>
#include<stdlib.h> 
#include<fstream>
using namespace std;

void ComportamientoJugador::AjustesPrimeraIteracion(Sensores sensores, bool &bien_situado, int &fil, int &col, bool &primiter){

	if(sensores.nivel == 0 && primiter){
		bien_situado = true;
		fil = sensores.posF;
		col = sensores.posC;
		primiter = false;
	}

}

//Actualizaciones
void ComportamientoJugador::ActualizacionMapaYorientacion(Sensores sensores,int &fil, int &col, int &filAux, int &colAux, vector<vector<unsigned char>> &mapaResultado, vector<vector<unsigned char>> &mapaAuxiliar){

	if(bien_situado){
			actualizarPosYBruj(sensores,fil,col);
			PintarMapas(sensores,mapaResultado,fil,col);
		}
		else{
			actualizarPosYBruj(sensores,filAux,colAux);
			PintarMapas(sensores,mapaAuxiliar,filAux,colAux);
		}
}

void ComportamientoJugador::actualizarPosYBruj(Sensores sensores, int &fil, int &col){
	
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
		case actIDLE:
			girar_derecha = (rand()%2==0);
			break;
		}		

	if(sensores.nivel < 2){

		brujula = sensores.sentido;
	}
	

}

//Pintado de mapas
void ComportamientoJugador::PintarMapas(Sensores sensores, vector<vector<unsigned char>> &map, int &fil, int &col){

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

void ComportamientoJugador::pasarMapaAuxAmapa(Sensores sensores){

	pair<int,int> diferencia;
	fil = sensores.posF;
	col = sensores.posC;


	diferencia.first = abs(filAux-fil);
	diferencia.second = abs(colAux-col);

	

	for(int i=0; i<200; i++){
		for(int j=0; j<200; j++){

			if(mapaAuxiliar[i][j] != '?'){
				mapaResultado[i-diferencia.first][j - diferencia.second] = mapaAuxiliar[i][j];
			}

		}
	}


}

void ComportamientoJugador::CrearMapaProtExp(){

	int incNorte = 0, incSur = 0, incEste = 0, incOeste = 0;
	int objX=0, objY=0;

	
	//norte:
	for(int i = fil-1; i>=0; i--){
		for(int j = col-2; j<=col+2; j++){	//me he asegurado de que hay precipicios en los bordes, no da core.
			if(mapaResultado[i][j] == '?')
				incNorte++;
		}
	}
	
	//sur
	
	for(int i = fil+1; i<mapaResultado.size(); i++){
		
		for(int j = col-2; j<=col+2; j++){	//me he asegurado de que hay precipicios en los bordes, no da core.
			
			if(mapaResultado[i][j] == '?'){
				incSur++;
				
			}
		}
	}
	
	
	//este ->
	for(int j = col+1; j<mapaResultado.size(); j++){
		for(int i = fil-2; i<=fil+2; i++){	//me he asegurado de que hay precipicios en los bordes, no da core.
			if(mapaResultado[i][j] == '?')
				incEste++;
		}
	}

	//oeste <-
	for(int j = col-1; j>=0; j--){
		for(int i = fil-2; i<=fil+2; i++){	//me he asegurado de que hay precipicios en los bordes, no da core.
			if(mapaResultado[i][j] == '?')
				incOeste++;
		}
	}
	


	mapaPotencialExp[fil][col] = -3;
	
	if(incSur < incNorte  and incEste < incNorte and incOeste < incNorte){	//norte

		for(int i=fil; i>=0; i--){
			if(mapaResultado[i][col] == '?'){
				objX=i;
				objY=col;
			}
		}


	
		
		//radiales verticales:
		int puntos = fil - objX;//distancia a objetivo
		puntos = puntos*2;
		int contador = 0;
			//objetivo hacia el jugador.
			
			for(int i=objX; i != fil; i++){
				mapaPotencialExp[i][col] = puntos - contador;
				contador++;
			}
			
			contador = 0;
			//objetivo hacia arriba:
			
			for(int i=objX; i != 0; i--){
				mapaPotencialExp[i][col] = puntos - contador;
				contador++;
			}
			
			contador = 0;
		//radiales Horizontales:
			//a izq
			
			for(int j=objY; j >=0; j--){
				mapaPotencialExp[objX][j] = puntos-contador;
				contador++;
			}
			
			contador = 0;
			//a dcha
			for(int j=objY; j <=mapaResultado.size(); j++){
				mapaPotencialExp[objX][j] = puntos-contador;
				contador++;
			}
			
			contador = 0;





		
	}

	else if(incNorte < incSur and incEste < incSur and incOeste < incSur){ //sur

		for(int i=fil; i<mapaResultado.size(); i++){
				if(mapaResultado[i][col] == '?'){
					objX=i;
					objY=col;
				}
			}




	
		
		//radiales verticales:
		int puntos = objX - fil; //distancia a objetivo
		puntos = puntos*2;
		int contador = 0;
			//objetivo hacia el jugador.
			
			for(int i=objX; i != fil; i--){
				mapaPotencialExp[i][objY] = puntos - contador;
				contador++;
			}
			
			contador = 0;
			//objetivo hacia abajo:
			
			for(int i=objX; i != mapaResultado.size(); i++){
				mapaPotencialExp[i][objY] = puntos - contador;
				contador++;
			}
			
			contador = 0;
		//radiales Horizontales:
			//a izq
			
			for(int j=objY; j >=0; j--){
				mapaPotencialExp[objX][j] = puntos-contador;
				contador++;
			}
			
			contador = 0;
			//a dcha
			for(int j=objY; j <mapaResultado.size(); j++){
				mapaPotencialExp[objX][j] = puntos-contador;
				contador++;
			}
			
			contador = 0;



	}
	else if(incNorte < incEste and incSur < incEste and incOeste < incEste) {//este
		for(int j=col; j<=mapaResultado.size(); j++){
				if(mapaResultado[fil][j] == '?'){
					objX=fil;
					objY=j;
				}
			}

		
		
		//radiales horizontales:
		int puntos = objY - col;//distancia a objetivo
		puntos = puntos*2;
		int contador = 0;
			//objetivo hacia el jugador.
			
			for(int i=objY; i != col; i--){
				mapaPotencialExp[objX][i] = puntos - contador;
				contador++;
			}
			
			contador = 0;
			//objetivo hacia dcha:
			
			for(int i=objY; i < mapaResultado.size(); i++){
				mapaPotencialExp[objX][i] = puntos - contador;
				contador++;
			}
			
			contador = 0;
		//radiales verticales:
			//arriba
			
			for(int j=objX; j >=0; j--){
				mapaPotencialExp[j][objY] = puntos-contador;
				contador++;
			}
			
			contador = 0;
			//abajo
			for(int j=objX; j <mapaResultado.size(); j++){
				mapaPotencialExp[j][objY] = puntos-contador;
				contador++;
			}
			
			contador = 0;



	}

	
	else if(incNorte<incOeste and incSur<incOeste and incEste < incOeste){//oeste
		
		for(int j=col; j>=0; j--){
				if(mapaResultado[fil][j] == '?'){
					objX=fil;
					objY=j;
				}
			}

	
		
		//radiales horizontales:
		int puntos = col - objY;//distancia a objetivo
		puntos = puntos*2;
		int contador = 0;
			//objetivo hacia el jugador.
			
			for(int i=objY; i != col; i++){
				mapaPotencialExp[objX][i] = puntos - contador;
				contador++;
			}
			
			contador = 0;
			//objetivo hacia izq:
			
			for(int i=objY; i >= 0; i--){
				mapaPotencialExp[objX][i] = puntos - contador;
				contador++;
			}
			
			contador = 0;
		//radiales verticales:
			//arriba
			
			for(int j=objX; j >=0; j--){
				mapaPotencialExp[j][objY] = puntos-contador;
				contador++;
			}
			
			contador = 0;
			//abajo
			for(int j=objX; j <mapaResultado.size(); j++){
				mapaPotencialExp[j][objY] = puntos-contador;
				contador++;
			}
			
			contador = 0;




	}
		
	
//Diagonales superiores:
	int contador = 1;
	int contadorpotencial = mapaPotencialExp[objX][objY] - 2;
	
	
	for(int i=objX-1; i>=0; i--){
		if(objY-contador >= 0)
			mapaPotencialExp[i][objY-contador] = contadorpotencial;
		if(objY + contador < mapaResultado.size())
			mapaPotencialExp[i][objY+contador] = contadorpotencial;
		contador++;
		contadorpotencial = contadorpotencial - 2;
	}

	
	

	//diagonales inferiores:

	contador = 1;
	contadorpotencial=mapaPotencialExp[objX][objY] - 2;

	for(int i=objX+1; i<mapaResultado.size(); i++){
		if(objY-contador >= 0)
			mapaPotencialExp[i][objY-contador] = contadorpotencial;
		if(objY + contador < mapaResultado.size())
			mapaPotencialExp[i][objY+contador] = contadorpotencial;
		contador++;
		contadorpotencial = contadorpotencial - 2;
	}



}
//Objetos Prioritarios
int ComportamientoJugador::detectarObjetoPrioritario(Sensores sensores){
	//bikini, zapatillas y posicionamiento, RECARGA NO.

	if(!protocoloPrioritario)
		for(int i=1; i<= 15; i++)
			if((sensores.terreno[i] == 'K' && !tengoBikini) or (sensores.terreno[i] == 'D' && !tengoZapas) or sensores.terreno[i] == 'G' && !bien_situado )
				return i;
	return -1;
}

void ComportamientoJugador::CrearMapaPotencialPrioritario(Sensores sensores, int numCasilla, int brujula){ //supone que no hay obstaculos como muros o precipicios.
	int haciaAdelante = 0, haciaLado = 0;


	int potencialCampo = 1;


	//haciaAdelante:
	if(numCasilla >= 9 and numCasilla <= 15){
		haciaAdelante = 3;
	} else if (numCasilla >= 4 and numCasilla <=8){
		haciaAdelante = 2;
	} else if(numCasilla >= 1 and numCasilla <=3) {
		haciaAdelante = 1;
	}

	//haciaLado:

	if(numCasilla == 15 || numCasilla == 9)
		haciaLado = 3;
	else if(numCasilla == 10 || numCasilla ==4 || numCasilla == 14 || numCasilla == 8 )
		haciaLado = 2;
	else if(numCasilla == 1 || numCasilla == 5 || numCasilla == 11 || numCasilla == 3 || numCasilla == 7 || numCasilla == 13)
		haciaLado = 1;

	//Diseño del mapa:

	//haciaadelante:

	for(int i=1; i<=haciaAdelante; i++){
		switch (brujula){
			case 0:	//norte ^

				mapaPotencial[filPotPrio - i][colPotPrio] = potencialCampo;

			break;
			
			case 1: //este --> 
				mapaPotencial[filPotPrio][colPotPrio + i] = potencialCampo;
			break;

			case 2:	//sur V
				mapaPotencial[filPotPrio + i][colPotPrio] = potencialCampo;
			break;

			case 3: //oeste <--
				mapaPotencial[filPotPrio][colPotPrio - i] = potencialCampo;
			break;
		}
	
		potencialCampo++;
	}


	//Comprobamos si está a la izq,dcha o centro.

	bool izq = false, dcha = false, ctr = false;

	if(numCasilla == 1 or numCasilla == 4 or numCasilla == 5 or numCasilla == 9 or numCasilla == 10 or numCasilla == 11)
		izq = true;
	else if(numCasilla == 3 or numCasilla == 7 or numCasilla == 8 or numCasilla == 13 or numCasilla == 14 or numCasilla == 15)
		dcha = true;
	else
		ctr = true;

	//haciaLado:

	int factorOrient = 0;	// sirve para determinar posiciones en funcion de si el objeto está a la izq, a la derecha, o en el centro

	if(dcha)
		factorOrient = 1;
	else if (izq)
		factorOrient = -1;


	if(!ctr){

		for(int i=1; i<=haciaLado; i++){
		switch (brujula){
			case 0:	//norte ^

				mapaPotencial[filPotPrio - haciaAdelante][ colPotPrio + (factorOrient*i)] = potencialCampo;

			break;
			
			case 1: //este --> 
				mapaPotencial[filPotPrio + (factorOrient*i)][colPotPrio + haciaAdelante] = potencialCampo;
			break;

			case 2:	//sur V

				factorOrient = factorOrient * -1; // para invertirlo.
				mapaPotencial[filPotPrio + haciaAdelante][colPotPrio + (factorOrient*i)] = potencialCampo;
				factorOrient = factorOrient * -1; //para re invertirlo (pq si no s eestá cambiando todo el rato).
			break;

			case 3: //oeste <--
				factorOrient = factorOrient * -1;
				mapaPotencial[filPotPrio + (factorOrient*i)][colPotPrio - haciaAdelante] = potencialCampo;
				factorOrient = factorOrient * -1;
			break;
		}
	
		potencialCampo++;
		}

	}
	

	
	
	
}

void ComportamientoJugador::resetPrioritario(){
	protocoloPrioritario = false;
	 for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
          mapaPotencial[i][j] = 0;

	filPotPrio = colPotPrio = 4;

}


//Movimientos
Action ComportamientoJugador::movimientoDefault(Sensores sensores){


if(sensores.superficie[2] != '_')
	return actIDLE;

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

Action ComportamientoJugador::movimientoPrioritario(Sensores sensores, int brujula){	//Sistema de producción.

	Action resultado = actIDLE;

	mapaPotencial[filPotPrio][colPotPrio] = 0;
	
	//movimiento de avance
		
		switch (brujula){
				case 0:	//norte
					
					if(mapaPotencial[filPotPrio][colPotPrio-1] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actTURN_L;
					}
					else if(mapaPotencial[filPotPrio][colPotPrio+1] > mapaPotencial[filPotPrio][colPotPrio])
						resultado = actTURN_R;
					else if (mapaPotencial[filPotPrio - 1][colPotPrio] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actFORWARD;
						filPotPrio--;
					}
					
				break;
				case 1://este
					
					if(mapaPotencial[filPotPrio-1][colPotPrio] > mapaPotencial[filPotPrio][colPotPrio]){

						resultado = actTURN_L;
					}
					else if(mapaPotencial[filPotPrio+1][colPotPrio] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actTURN_R;
					}
					else if (mapaPotencial[filPotPrio][colPotPrio + 1] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actFORWARD;
						colPotPrio++;
						
					}
				break;

				case 2://sur
					if(mapaPotencial[filPotPrio][colPotPrio-1] > mapaPotencial[filPotPrio][colPotPrio])
						resultado = actTURN_R;
					else if(mapaPotencial[filPotPrio][colPotPrio+1] > mapaPotencial[filPotPrio][colPotPrio])
						resultado = actTURN_L;
					else if(mapaPotencial[filPotPrio+1] [colPotPrio] > mapaPotencial[filPotPrio][colPotPrio]){
						resultado = actFORWARD;
						filPotPrio++;
						
					}

				break;

				case 3://oeste
					
					if(mapaPotencial[filPotPrio-1][colPotPrio] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actTURN_R;
					}
					else if(mapaPotencial[filPotPrio+1][colPotPrio] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actTURN_L;
					}
					else if (mapaPotencial[filPotPrio][colPotPrio - 1] > mapaPotencial[filPotPrio][colPotPrio]){
						
						resultado = actFORWARD;
						colPotPrio--;
						
					}
				break;

		}

	return resultado;


}


Action ComportamientoJugador::movimientoPotExp(){
	bool norte = false, sur = false, este = false, oeste = false;
	int max = mapaPotencialExp[fil][col];
	cout << fil << endl;
	cout << col <<endl;
	cout<<mapaPotencialExp[fil][col]<<endl;

	if(fil != 0){

		if(mapaPotencialExp[fil-1][col] > max){
		cout<< "A" <<endl;
		norte = true;
		max = mapaPotencialExp[fil-1][col];
		}
	}

	if(fil != mapaPotencialExp.size()){

		if(mapaPotencialExp[fil+1][col] > max){
			cout<< "B" <<endl;
		sur = true;
		norte = false;
		max = mapaPotencialExp[fil+1][col];
		}
	}
	if(col != mapaPotencialExp.size()){
		if(mapaPotencialExp[fil][col+1] > max){
			cout<< "C" <<endl;
			este = true;
			sur = false;
			norte = false;
			max = mapaPotencialExp[fil][col+1];
		}
	}

	if(col != 0){

		if(mapaPotencialExp[fil][col-1] > max){
			cout<< "D" <<endl;
		oeste = true;
		este = false;
		sur = false;
		norte = false;
		max = mapaPotencialExp[fil][col-1];
		}	
	}
/*
	if(norte) cout << "norte" <<endl;
	if(sur) cout << "sur" <<endl;
	if(este) cout << "este" <<endl;
	if(oeste) cout << "oeste" <<endl;
*/

	if(norte && brujula == 0)
		return actFORWARD;
	else if(sur && brujula == 2)
		return actFORWARD;
	else if(este && brujula == 1)
		return actFORWARD;
	else if(oeste && brujula == 3)
		return actFORWARD;
	else {
		cout <<fil<<endl;
		cout <<col<<endl;
		switch (brujula)
		{
		case 0:
			if(oeste)
				return actTURN_L;
			
			if(este)
				return actTURN_R;

			if(sur)
				return actTURN_L;

			break;
		
		case 1:

			if(norte)
				return actTURN_L;
			
			if(oeste)
				return actTURN_R;

			if(sur)
				return actTURN_R;

			break;
		case 2:

			if(oeste)
				return actTURN_R;
			
			if(este)
				return actTURN_L;

			if(norte)
				return actTURN_L;
		break;

		case 3:

		if(norte)
				return actTURN_R;
			
			if(este)
				return actTURN_R;

			if(sur)
				return actTURN_L;
		break;

		}
	}



}
//Creación de archivos auxiliares:

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

void ComportamientoJugador::crearArchivoMapaPot(Sensores sensores){

	//-----
		ofstream archivo;
		archivo.open("mapapotencial.txt",ios::out);
		if(archivo.fail()){
			cout << "ERROR AL CREAR EL ARCHIVO";
			exit(1);
		} else {


			
			for(int i=0; i<9; i++){
				for(int j=0; j<9; j++){
					archivo<<mapaPotencial[i][j] << " ";
				}
				archivo << endl;
			}


			

		}
		archivo.close();

	//-----
}

void ComportamientoJugador::crearArchivoMapaPotExp(){

	//-----
		ofstream archivo;
		archivo.open("mapapotencialEXPLOR.txt",ios::out);
		if(archivo.fail()){
			cout << "ERROR AL CREAR EL ARCHIVO";
			exit(1);
		} else {


			
			for(int i=0; i<mapaPotencialExp.size(); i++){
				for(int j=0; j<mapaPotencialExp.size(); j++){
					archivo<<mapaPotencialExp[i][j] << " ";
				}
				archivo << endl;
			}


			

		}
		archivo.close();

	//-----
}

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	AjustesPrimeraIteracion(sensores, bien_situado, fil,col,primiter);
	
	//Actualización de mapas y orientación.
	ActualizacionMapaYorientacion(sensores,fil,col,filAux,colAux,mapaResultado,mapaAuxiliar);

	//crearArchivoMatrizAux(sensores);

	//Comprobación y ajuste de casillas K,D o G.
	if(sensores.terreno[0] == 'D')
		tengoZapas = true;
	
	if(sensores.terreno[0] == 'K')
		tengoBikini = true;

	if(sensores.terreno[0] == 'G' && !bien_situado){
		
		pasarMapaAuxAmapa(sensores);
		bien_situado = true;
	}

	if(sensores.terreno[0] == 'K' || sensores.terreno[0] == 'G' || sensores.terreno[0] == 'D')
		resetPrioritario();



	//Detección e iniciación del protocolo prioritario.

	if(!protocoloPrioritario)
		casillaSensorPrioritaria = detectarObjetoPrioritario(sensores);

	if(casillaSensorPrioritaria != -1 && !protocoloPrioritario){
		protocoloPrioritario = true;
		CrearMapaPotencialPrioritario(sensores,casillaSensorPrioritaria,brujula);
		

	}

	if(!protocoloPrioritario and bien_situado and tengoBikini and tengoZapas and !protocoloEXP){
		protocoloEXP = true;
		CrearMapaProtExp();
		crearArchivoMapaPotExp();
		

	}

	//crearArchivoMapaPot(sensores);

	//Selección de movimiento.

	if(protocoloPrioritario){
		cout << "P" << endl;
		accion = movimientoPrioritario(sensores,brujula);	//seguir mapa de potencial en vez de mapa normal.
		
	}
	else if(protocoloEXP){
		cout << "E" << endl;
		accion = movimientoPotExp();
		
	}
	else {
		cout << "D" << endl;
		accion = movimientoDefault(sensores);
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