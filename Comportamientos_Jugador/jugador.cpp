#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include<cmath>
#include<stdlib.h> 
#include<fstream>
#include<iomanip>
using namespace std;

//Actualizaciones
void ComportamientoJugador::AjustesPrimeraIteracion(Sensores sensores, bool &bien_situado, int &fil, int &col, bool &primiter){

	if(sensores.nivel == 0 && primiter){
		bien_situado = true;
		fil = sensores.posF;
		col = sensores.posC;
		primiter = false;
	}

}

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

void ComportamientoJugador::comprobacionKDG(Sensores sensores){

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

}
//Pintado de mapas
void ComportamientoJugador::pintarPrecipicios(){

	for(int j=0; j<mapaResultado.size(); j++){
		mapaResultado[0][j] = 'P';
		mapaResultado[1][j] = 'P';
		mapaResultado[2][j] = 'P';
		mapaResultado[mapaResultado.size()-3][j] = 'P';
		mapaResultado[mapaResultado.size()-2][j] = 'P';
		mapaResultado[mapaResultado.size()-1][j] = 'P';
	}

	for(int i=3; i<mapaResultado.size()-3; i++){
		mapaResultado[i][0] = 'P';
		mapaResultado[i][1] = 'P';
		mapaResultado[i][2] = 'P';
		mapaResultado[i][mapaResultado.size()] = 'P';
		mapaResultado[i][mapaResultado.size()-1] = 'P';
		mapaResultado[i][mapaResultado.size()-2] = 'P';
	}
}

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

	for(int i=0; i<200; i++)
		for(int j=0; j<200; j++)
			if(mapaAuxiliar[i][j] != '?')
				mapaResultado[i-diferencia.first][j - diferencia.second] = mapaAuxiliar[i][j];
}


//Objetos Prioritarios
void ComportamientoJugador::inaccesibilidadPrio(){

		if(protocoloEXP && objetivoExplor.posX != -1 && objetivoExplor.posY != -1){

		int caso;

		if(col == objetivoExplor.posY && fil > objetivoExplor.posX)
			caso = 0;
		 else if(col == objetivoExplor.posY && fil < objetivoExplor.posX)
			caso = 2;
		 else if(fil == objetivoExplor.posX && col < objetivoExplor.posY)
			caso = 1;
		 else 
			caso = 3;
		
		
		switch (caso){
		case 0:
			if(fil - objetivoExplor.posX <= 3)
				while(mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'M' || mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'P')
					objetivoExplor.posX++;
			break;
		
		case 1:
			
			if(objetivoExplor.posY - col  <= 3)
				while(mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'M' || mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'P')
					objetivoExplor.posY--;
			break;

		case 2:
			if(objetivoExplor.posX  - fil<= 3)
				while(mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'M' || mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'P')
					objetivoExplor.posX--;
			break;

		case 3:
			if(col - objetivoExplor.posY  <= 3)
				while(mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'M' || mapaResultado[objetivoExplor.posX][objetivoExplor.posY] == 'P')
					objetivoExplor.posY++;
			break;
		}
		
		//Comprobamos si hemos llegado al destino.
		if(fil == objetivoExplor.posX && col == objetivoExplor.posY){
			
			proxReajuste = "";
			protocoloEXP = false;
			objetivoExplor.posX = -1;
			objetivoExplor.posY = -1;

			// Se reajusta el mapamapa potencial exploracion
      		mapaPotencialExp = vector<vector<int>>(mapaResultado.size(),vector<int>(mapaResultado.size()));
      		for(int i=0; i<mapaResultado.size(); i++)
        		for(int j=0; j<mapaResultado.size(); j++)
          			mapaPotencialExp[i][j] = 0;
		}
	}
}

void ComportamientoJugador::detectarEiniciarPrioritario(Sensores sensores){

	if(!protocoloPrioritario and !protRecarga and (!tengoBikini or !tengoZapas or !bien_situado))
		casillaSensorPrioritaria = detectarObjetoPrioritario(sensores);

	if(casillaSensorPrioritaria != -1 && !protocoloPrioritario and (!tengoBikini or !tengoZapas or !bien_situado)){
		protocoloPrioritario = true;
		CrearMapaPotencialPrioritario(sensores,casillaSensorPrioritaria,brujula);
	}

}

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

//exploracion
void ComportamientoJugador::finProtExplor(Sensores sensores){

	if(protocoloEXP){

		if((sensores.terreno[2] == 'M' or sensores.terreno[2] == 'P' or (mapaPotencialExp[fil+1][col] < mapaPotencialExp[fil][col] and mapaPotencialExp[fil-1][col] < mapaPotencialExp[fil][col] and 
	mapaPotencialExp[fil][col+1] < mapaPotencialExp[fil][col] and mapaPotencialExp[fil-1][col] < mapaPotencialExp[fil][col-1] ))){
		proxReajuste = "";
			protocoloEXP = false;
			objetivoExplor.posX = -1;
			objetivoExplor.posY = -1;
			MaximoPotencialExp = 0;
			ticksDefault = 10;
			// Se reajusta el mapamapa potencial exploracion
			mapaPotencialExp = vector<vector<int>>(mapaResultado.size(),vector<int>(mapaResultado.size()));
			for(int i=0; i<mapaResultado.size(); i++)
				for(int j=0; j<mapaResultado.size(); j++)
					mapaPotencialExp[i][j] = 0;
	}
}
}

void ComportamientoJugador::ColocarObstaculosExploracion(){

	for(int i=0; i<mapaResultado.size(); i++){
		for(int j=0; j<mapaResultado.size(); j++){
			if(mapaResultado[i][j] == 'M' || mapaResultado[i][j] == 'P') 
				mapaPotencialExp[i][j] = -100;

			if(mapaPotencialExp[i][j] > MaximoPotencialExp)
				MaximoPotencialExp = mapaPotencialExp[i][j];
		}
	}

}

ComportamientoJugador::Posicion ComportamientoJugador::CrearMapaProtExp(bool reajuste, Posicion pos){

	int incNorte = 0, incSur = 0, incEste = 0, incOeste = 0;
	int objX=0, objY=0;

	Posicion ObjetivoExplor;

	if(!reajuste){
		//norte:
		for(int i = fil-1; i>=0; i--)
			for(int j = col-2; j<=col+2; j++)	
				if(mapaResultado[i][j] == '?')
					incNorte++;
			
		
		//sur:
		for(int i = fil+1; i<mapaResultado.size(); i++)
			for(int j = col-2; j<=col+2; j++)	
				if(mapaResultado[i][j] == '?')
					incSur++;
					
		//este:
		for(int j = col+1; j<mapaResultado.size(); j++)
			for(int i = fil-2; i<=fil+2; i++)	
				if(mapaResultado[i][j] == '?')
					incEste++;
			
		//oeste:
		for(int j = col-1; j>=0; j--)
			for(int i = fil-2; i<=fil+2; i++)	
				if(mapaResultado[i][j] == '?')
					incOeste++;

	}


		
	
	if(incNorte == 0 && incSur == 0 && incEste == 0 && incOeste == 0 && !reajuste){
		objetivoExplor.posX = objetivoExplor.posY = -1;
		return objetivoExplor;
	} else {
		
		mapaPotencialExp[fil][col] = -3;
		
		if(incSur < incNorte  and incEste < incNorte and incOeste < incNorte || proxReajuste == "norte"){	//norte
			proxReajuste = "norte";
			objX=0;
			objY=col;

			if(reajuste){ objX = pos.posX; objY = pos.posY;}
			
			//radiales verticales:
				int puntos = (fil - objX)*100;//distancia a objetivo
				int contador = 0;

				//objetivo hacia el jugador.
				for(int i=objX; i != mapaResultado.size(); i++){
					mapaPotencialExp[i][objY] = puntos - contador;
					contador++;
					int contadorColumna = 1;
					for(int j=objY+1; j!=mapaResultado.size(); j++){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
					contadorColumna = 1;
					for(int j=objY-1; j!=-1; j--){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }

				}
				contador = 0;

				//objetivo hacia arriba:
				for(int i=objX; i !=-1; i--){
					mapaPotencialExp[i][col] = puntos - contador;
					contador++;
					int contadorColumna = 1;
					for(int j=objY+1; j!=mapaResultado.size(); j++){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
					contadorColumna = 1;
					for(int j=objY-1; j!=-1; j--){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
				}
				contador = 0;

		}
		else if(incNorte < incSur and incEste < incSur and incOeste < incSur || proxReajuste == "sur"){ //sur
			proxReajuste = "sur";
			objX=mapaResultado.size()-1;
			objY=col;
			if(reajuste){ objX = pos.posX; objY = pos.posY;}		
			//radiales verticales:

				int puntos = (objX - fil)*100; //distancia a objetivo
				int contador = 0;

				//objetivo hacia el jugador.
				for(int i=objX; i != -1; i--){
					mapaPotencialExp[i][objY] = puntos - contador;
					contador++;
					int contadorColumna = 1;
					for(int j=objY+1; j!=mapaResultado.size(); j++){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
					contadorColumna = 1;
					for(int j=objY-1; j!=-1; j--){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
				}
				contador = 0;

				//objetivo hacia abajo:
				for(int i=objX; i != mapaResultado.size(); i++){
					mapaPotencialExp[i][objY] = puntos - contador;
					contador++;
					int contadorColumna = 1;
					for(int j=objY+1; j!=mapaResultado.size(); j++){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
					contadorColumna = 1;
					for(int j=objY-1; j!=-1; j--){mapaPotencialExp[i][j] = mapaPotencialExp[i][objY] - contadorColumna; contadorColumna++; }
				}
				contador = 0;
		}
		else if(incNorte < incEste and incSur < incEste and incOeste < incEste || proxReajuste == "este") {//este
				proxReajuste = "este";
				objX=fil;
				objY=mapaResultado.size()-1;
				if(reajuste){ objX = pos.posX; objY = pos.posY;}
			//radiales horizontales:
				int puntos = (objY - col)*100; //distancia a objetivo
				int contador = 0;

				//objetivo hacia el jugador.
				for(int i=objY; i != -1; i--){
					mapaPotencialExp[objX][i] = puntos - contador;
					contador++;
					int contadorfilas = 1;
					for(int j=objX-1; j!= -1; j--){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
					contadorfilas = 1;
					for(int j=objX+1; j!=mapaResultado.size(); j++){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
				}
				contador = 0;

				//objetivo hacia dcha:
				for(int i=objY; i < mapaResultado.size(); i++){
					mapaPotencialExp[objX][i] = puntos - contador;
					contador++;
					int contadorfilas = 1;
					for(int j=objX-1; j!= -1; j--){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
					contadorfilas = 1;
					for(int j=objX+1; j!=mapaResultado.size(); j++){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
				}
				contador = 0;

		}
		else if(incNorte<incOeste and incSur<incOeste and incEste < incOeste || proxReajuste == "oeste"){//oeste	
			proxReajuste = "oeste";
			objX=fil;
			objY=0;
			if(reajuste){ objX = pos.posX; objY = pos.posY;}
			//radiales horizontales:

				int puntos = (col - objY) * 10;//distancia a objetivo
				int contador = 0;

				//objetivo hacia el jugador.
				for(int i=objY; i != mapaResultado.size(); i++){
					mapaPotencialExp[objX][i] = puntos - contador;
					contador++;
					int contadorfilas = 1;
					for(int j=objX-1; j!= -1; j--){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] -contadorfilas; contadorfilas++; }
					contadorfilas = 1;
					for(int j=objX+1; j!=mapaResultado.size(); j++){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
				}
				contador = 0;

				//objetivo hacia izq:
				for(int i=objY; i >= 0; i--){
					mapaPotencialExp[objX][i] = puntos - contador;
					contador++;
					int contadorfilas = 1;
					for(int j=objX-1; j!= -1; j--){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
					contadorfilas = 1;
					for(int j=objX+1; j!=mapaResultado.size(); j++){mapaPotencialExp[j][i] = mapaPotencialExp[objX][i] - contadorfilas; contadorfilas++; }
				}
				contador = 0;
		}

		ObjetivoExplor.posX = objX;
		ObjetivoExplor.posY = objY;

		return ObjetivoExplor;
	}
}

void ComportamientoJugador::detectarEiniciarExploracion(Sensores sensores){
	
	if(!protRecarga and !protocoloPrioritario and bien_situado and tengoBikini and tengoZapas and !protocoloEXP and ticksDefault == 0){
		
		protocoloEXP = true;
		Posicion nula;
		nula.posX = -1;
		nula.posY = -1;
		
		objetivoExplor = CrearMapaProtExp(false, nula);
		
		
		if(objetivoExplor.posX == -1 && objetivoExplor.posY == -1)
			protocoloEXP = false;
	
		crearArchivoMapaProtExp();
	}
}

//recarga

void ComportamientoJugador::protocoloRecarga(Sensores sensores, Posicion &resultado){
	ticksGeneral--;
	
	Posicion pos;
	pos.posX =-1;
	pos.posY=-1;

	int cercano = 10000;
	if(ticksGeneral == 2000 || ticksGeneral == 1000){
		protRecarga = true;
		resetPrioritario();
		finProtExplor(sensores);

		for(int i=0; i<mapaResultado.size(); i++)
			for(int j=0; j<mapaResultado.size(); j++)
				if(mapaResultado[i][j] == 'X'){
					pos.posX = i;
					pos.posY = j;
					recargas.push_back(pos);
					
				}
			
		if(recargas.empty())
			protRecarga = false;
		else{
			
			vector<Posicion>::const_iterator recarga;
			for(recarga = recargas.cbegin(); recarga != recargas.cend(); recarga++){
				
				if(cercano > (abs((*recarga).posX - fil) + abs((*recarga).posY - col))){
					
					cercano = abs((*recarga).posX - fil) + abs((*recarga).posY - col);
					pos.posX = (*recarga).posX;
					pos.posY = (*recarga).posY;
				}
			
			}
			CrearMapaPotencialRecarga(pos);
			crearArchivoMapaProtrecarga();
			cout << "recargacercana: " << pos.posX << " " << pos.posY << endl;
		}
	}	
}

void ComportamientoJugador::finrecargaAbrupto(){
	protRecarga = false;
			recargaMasCercana.posX = -1;
			recargaMasCercana.posY = -1;
			ticksDefault = 3;
			ticksMantenerseEnRecarga = 100;
			enRecarga = false;

			for(int i=0; i<mapaResultado.size(); i++)
				for(int j=0; j<mapaResultado.size(); j++)
					mapaPotencialRecarga[i][j] = 0;
}

void ComportamientoJugador::CrearMapaPotencialRecarga(Posicion recarga){

	if(recarga.posX != -1 && recarga.posY != -1){
			int objX=recarga.posX;
			int objY=recarga.posY;
			//radiales horizontales:

				int puntos = (col - objY) * 10;//distancia a objetivo
				int contador = 0;

				//objetivo hacia el jugador.
				for(int i=objY; i != mapaResultado.size(); i++){
					mapaPotencialRecarga[objX][i] = puntos - contador;
					contador++;
					int contadorfilas = 1;
					for(int j=objX-1; j!= -1; j--){mapaPotencialRecarga[j][i] = mapaPotencialRecarga[objX][i] -contadorfilas; contadorfilas++; }
					contadorfilas = 1;
					for(int j=objX+1; j!=mapaResultado.size(); j++){mapaPotencialRecarga[j][i] = mapaPotencialRecarga[objX][i] - contadorfilas; contadorfilas++; }
				}
				contador = 0;

				//objetivo hacia izq:
				for(int i=objY; i >= 0; i--){
					mapaPotencialRecarga[objX][i] = puntos - contador;
					contador++;
					int contadorfilas = 1;
					for(int j=objX-1; j!= -1; j--){mapaPotencialRecarga[j][i] = mapaPotencialRecarga[objX][i] - contadorfilas; contadorfilas++; }
					contadorfilas = 1;
					for(int j=objX+1; j!=mapaResultado.size(); j++){mapaPotencialRecarga[j][i] = mapaPotencialRecarga[objX][i] - contadorfilas; contadorfilas++; }
				}
				contador = 0;

	}

}

void ComportamientoJugador::finProtRecarga(Sensores sensores){
	if(protRecarga){

		if(ticksMantenerseEnRecarga > 0 && sensores.terreno[0] == 'X'){
			enRecarga = true;

		} else { enRecarga = false;}

		if(sensores.terreno[0] == 'X' and !enRecarga){
			finrecargaAbrupto();

		}
	}
}
//Movimientos
Action ComportamientoJugador::movimientoDefault(Sensores sensores){


if(sensores.superficie[2] != '_')
	return actTURN_L;

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

Action ComportamientoJugador::movimientoProtExp(){
	bool norte = false, sur = false, este = false, oeste = false;
	int max = mapaPotencialExp[fil][col];


	if(fil != 0){

		if(mapaPotencialExp[fil-1][col] >max){
		
		norte = true;
		max = mapaPotencialExp[fil-1][col];
		}
	}

	if(fil != mapaPotencialExp.size()){

		if(mapaPotencialExp[fil+1][col] > max){
			
		sur = true;
		norte = false;
		max = mapaPotencialExp[fil+1][col];
		}
	}
	if(col != mapaPotencialExp.size()){
		if(mapaPotencialExp[fil][col+1] >max){
		
			este = true;
			sur = false;
			norte = false;
			max = mapaPotencialExp[fil][col+1];
		}
	}

	if(col != 0){

		if(mapaPotencialExp[fil][col-1] > max){
			//<< "D" <<endl;
		oeste = true;
		este = false;
		sur = false;
		norte = false;
		max = mapaPotencialExp[fil][col-1];
		}	
	}


	if(norte && brujula == 0)
		return actFORWARD;
	else if(sur && brujula == 2)
		return actFORWARD;
	else if(este && brujula == 1)
		return actFORWARD;
	else if(oeste && brujula == 3)
		return actFORWARD;
	else {

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


Action ComportamientoJugador::movimientoRecarga(){
	bool norte = false, sur = false, este = false, oeste = false;
	int max = mapaPotencialRecarga[fil][col];


	if(enRecarga){
		ticksMantenerseEnRecarga--;
		return actIDLE;
	}

	if(fil != 0){

		if(mapaPotencialRecarga[fil-1][col] >max){
		
		norte = true;
		max = mapaPotencialRecarga[fil-1][col];
		}
	}

	if(fil != mapaPotencialRecarga.size()){

		if(mapaPotencialRecarga[fil+1][col] > max){
			
		sur = true;
		norte = false;
		max = mapaPotencialRecarga[fil+1][col];
		}
	}
	if(col != mapaPotencialRecarga.size()){
		if(mapaPotencialRecarga[fil][col+1] >max){
		
			este = true;
			sur = false;
			norte = false;
			max = mapaPotencialRecarga[fil][col+1];
		}
	}

	if(col != 0){

		if(mapaPotencialRecarga[fil][col-1] > max){
			//<< "D" <<endl;
		oeste = true;
		este = false;
		sur = false;
		norte = false;
		max = mapaPotencialRecarga[fil][col-1];
		}	
	}


	if(norte && brujula == 0)
		return actFORWARD;
	else if(sur && brujula == 2)
		return actFORWARD;
	else if(este && brujula == 1)
		return actFORWARD;
	else if(oeste && brujula == 3)
		return actFORWARD;
	else {

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

void ComportamientoJugador::crearArchivoMapaProtExp(){

	//-----
		ofstream archivo;
		archivo.open("mapapotencialEXPLOR.txt",ios::out);
		if(archivo.fail()){
			cout << "ERROR AL CREAR EL ARCHIVO";
			exit(1);
		} else {
			
			for(int j=0; j<mapaPotencialExp.size(); j++){
				archivo<< setw(5)<<j;
			}
			archivo<<endl;
			
			for(int i=0; i<mapaPotencialExp.size(); i++){
				for(int j=0; j<mapaPotencialExp.size(); j++){
					archivo<<setw(5)<<mapaPotencialExp[i][j];
				}
				archivo << endl;
			}


			

		}
		archivo.close();

	//-----
}

void ComportamientoJugador::crearArchivoMapaProtrecarga(){

	//-----
		ofstream archivo;
		archivo.open("mapapotencialReCaRga.txt",ios::out);
		if(archivo.fail()){
			cout << "ERROR AL CREAR EL ARCHIVO";
			exit(1);
		} else {
			
			for(int j=0; j<mapaPotencialRecarga.size(); j++){
				archivo<< setw(5)<<j;
			}
			archivo<<endl;
			
			for(int i=0; i<mapaPotencialRecarga.size(); i++){
				for(int j=0; j<mapaPotencialRecarga.size(); j++){
					archivo<<setw(5)<<mapaPotencialRecarga[i][j];
				}
				archivo << endl;
			}


			

		}
		archivo.close();

	//-----
}

//Think
Action ComportamientoJugador::think(Sensores sensores){
	pair<int,int> posic;
	if(bien_situado){
		posic.first = fil;
		posic.second = col;
		recorrido[posic] += 1;
	}

	if(sensores.colision){
		ultimaAccion = actIDLE;
		contadorReseteo++;
	}

	if(contadorReseteo == 5){
		cout << "A"<<endl;
		contadorReseteo = 0;
		resetPrioritario();
		finProtExplor(sensores);
		finrecargaAbrupto();
	}

	if(sensores.superficie[2] != '_')
		finrecargaAbrupto();


	Action accion = actIDLE;

	AjustesPrimeraIteracion(sensores, bien_situado, fil,col,primiter);
	
	//Actualización de mapas y orientación.
	ActualizacionMapaYorientacion(sensores,fil,col,filAux,colAux,mapaResultado,mapaAuxiliar);

	//Comprobación y ajuste de casillas K,D o G.
	comprobacionKDG(sensores);

	//Detección e iniciación del protocolo prioritario.
	detectarEiniciarPrioritario(sensores);
	
	//Detección, iniciación y creación del protocolo Explorar y su mapa de potencial.
	detectarEiniciarExploracion(sensores);

	
	//Comprobamos que el objetivo de exploración no sea innacesible (reducimos su rango)
	inaccesibilidadPrio();

	

	//colocamos los -100 en el mapa de pontencial de exploración.
	ColocarObstaculosExploracion();
	//Comprobamos si ha finalizado el protocolo de exploración 
	finProtExplor(sensores);

	
	protocoloRecarga(sensores,recargaMasCercana);
	finProtRecarga(sensores);

	//Selección de movimiento.

	if(protocoloPrioritario)
		accion = movimientoPrioritario(sensores,brujula);	
		
	else if(protocoloEXP){
		
		if(bien_situado)
			crearArchivoMapaProtExp();
		
		if(ultimaAccion == actIDLE)
			mapaPotencialExp[fil][col]--;

		accion = movimientoProtExp();
		
	} else if(protRecarga){
		if(ultimaAccion == actIDLE)
			mapaPotencialRecarga[fil][col]--;
		accion = movimientoRecarga();
	}
	else {
		if(ticksDefault >0)
			ticksDefault--;
		accion = movimientoDefault(sensores);
}

//----------------------------------------------------------------------
	// Determinar el efecto de la ultima accion enviada
	


	if(bien_situado){

		if(giroEmergenciaCierro){
			contadorGiroEmergencia--;

		}

		
		if(recorrido[posic] > 5 and !giroEmergenciaCierro){
			pair<int,int> izq,dcha,arb,abj;
			izq = dcha = posic;
			izq.second--;
			dcha.second++;
			cout << "A" << endl;
			if(recorrido[izq] > 5 && recorrido[dcha] > 5){
				accion = actTURN_L;
				giroEmergenciaCierro = true;
				cout << "B" << endl;
			}
				
		}

		if(contadorGiroEmergencia == 0 && giroEmergenciaCierro){
			contadorGiroEmergencia = 10;
			giroEmergenciaCierro = false;
		}

	}

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