#include "pacman.h"
#include "table.h"
#include "fantasma.h"
#include "GLCD.h"
#include "../RIT/RIT.h"
#include <stdio.h>
#include <string.h>

int X_POS = 14;
int Y_POS = 29;
int vite = 1;
int points = 0;
int tempo = 60;
int pausa = -1;
int vittoria = 0;

char Buffer_P[13]="";
char Buffer_T[10]="";

void Pacman_clear(){
	int i=0;
	for(i=0; i<7; i++){
		LCD_DrawLine(9+X_POS*8, i+37+Y_POS*8, 15+X_POS*8, i+37+Y_POS*8, Black);
	}
}

void Pacman_render() {
    
	int x, y;
    // Colore di Pac-Man
    uint16_t color = Yellow;

    // Offset base per centrare nella cella della griglia
    uint16_t baseX = 12 + 8 * X_POS; // Offset da sinistra
    uint16_t baseY = 40 + 8 * Y_POS; // Offset dall'alto

    // Disegna Pac-Man (cerchio con bocca verso destra)
    for ( y = -3; y <= 3; y++) { // Altezza da -4 a 4 per un cerchio centrato
        for ( x = -3; x <= 4; x++) { // Larghezza da -4 a 4 per il cerchio
            // Equazione del cerchio: x^2 + y^2 <= r^2 (con r=3)
            if (x * x + y * y <= 9) { // Disegna punti entro il raggio
                // Bocca aperta verso destra (esclude parte del cerchio)
                if (!(x > 0 && y > -1 && y < 1)) { 
                    LCD_SetPoint(baseX + x, baseY + y, color);
                }
            }
        }
    }
}
	
		
int Pacman_canGO(int X, int Y){
	int i=0;
	
	if(Y==14 && X==-1){return i;}
	if(Y==14 && X==28){return i;}

	if(Griglia[Y][X]!=1){
		i=0;
	}
	else{i=1;}
	return i;
}



void Pacman_moveTO(int X, int Y){
	X_POS=X;
	Y_POS=Y;
		
	if(Griglia[Y_POS][X_POS]==0){
		points=points+10;
		Pills--;
	}
	if(Griglia[Y_POS][X_POS]==50){
		points=points+50;
		Pills--;
		bad = 0;
		Tempo_blu=10;
	}
	Griglia[Y_POS][X_POS]=2;
	if(Y_POS == Y_fan && X_POS == X_fan){
		if( bad == 1){
			hits++;
		}
		if( bad == 0){
			Fantasma_clear();
			X_fan = 13;
			Y_fan = 15;
			bad = 1;
			wait = 3;
			points = points + 100;
		}
	}
	vite = (points / 1000) + 1 - hits;
}



void Pacman_updateMovement() {
   int nextX = X_POS;
   int nextY = Y_POS;
	if(Y_POS==14 && X_POS==0 && current_direction==DIR_LEFT){
		next_direction=DIR_LEFT;
		Pacman_clear();
		Pacman_moveTO(27,14);
		Pacman_render();
	}
	if(Y_POS==14 && X_POS==27 && current_direction==DIR_RIGHT){
		next_direction=DIR_RIGHT;
		Pacman_clear();
		Pacman_moveTO(0,14);
		Pacman_render();
	}

	 nextX = X_POS;
   nextY = Y_POS;
	
	 switch (next_direction) {
      case DIR_UP:    nextY--; break;
      case DIR_DOWN:  nextY++; break;
      case DIR_LEFT:  nextX--; break;
      case DIR_RIGHT: nextX++; break;
      default: break;
    }
	
	if(next_direction==current_direction){
		if(Pacman_canGO(nextX,nextY)==0){
			Pacman_clear();
			Pacman_moveTO(nextX, nextY);
			Pacman_render();
		}
		else{
			Pacman_moveTO(X_POS, Y_POS);
		}
		
	} else{
		if(Pacman_canGO(nextX,nextY)==0){
			current_direction=next_direction;
			Pacman_clear();
			Pacman_moveTO(nextX, nextY);
			Pacman_render();
		} else{
					nextX = X_POS;
					nextY = Y_POS;
					
					switch (current_direction) {
						case DIR_UP:    nextY--; break;
						case DIR_DOWN:  nextY++; break;
						case DIR_LEFT:  nextX--; break;
						case DIR_RIGHT: nextX++; break;
						default: break;
					}
					
					if(Pacman_canGO(nextX,nextY)==0){
						Pacman_clear();
						Pacman_moveTO(nextX, nextY);
						Pacman_render();
					}
					else{
						Pacman_moveTO(X_POS, Y_POS);
					}
		}
	}
}

void Pacman_printLife(){
	int k, i, j;
	
		GUI_Text(40, 290, (uint8_t *) "  LIFE :                 ", Red, Black);

		for(k = 0; k<vite; k++){
					uint16_t startX = 110+k*15; // Punto di partenza x
					uint16_t startY = 290; // Punto di partenza y

					 for ( i = 0; i < 15; i++) {
							for ( j = 0; j < 15; j++) {
									// Calcolo delle coordinate relative
									uint16_t x = startX + j;
									uint16_t y = startY + i;

									// Logica per riempire il cuore
									if ((i == 0 && (j >= 4 && j <= 10)) || // Parte superiore curva
										(i == 1 && (j >= 3 && j <= 11)) ||
										(i == 2 && (j >= 2 && j <= 12)) ||
										(i == 3 && (j >= 1 && j <= 13)) || 
										(i == 4 && (j >= 1 && j <= 13)) || // Corpo centrale
										(i == 5 && (j >= 2 && j <= 12)) ||
										(i == 6 && (j >= 3 && j <= 11)) ||
										(i == 7 && (j >= 4 && j <= 10)) ||
										(i == 8 && (j >= 5 && j <= 9)) ||  // Punta inferiore
										(i == 9 && (j >= 6 && j <= 8))) {
											LCD_SetPoint(x, y, Red);
										}
									}
					}
		}
} 
