#include "fantasma.h"
#include "pacman.h"
#include "table.h"
#include "GLCD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int X_fan = 14;
int Y_fan = 14;
int bad = 1;
int hits = 0;
int wait = 0;
int In_Box = 1;
int Tempo_blu =0;

void Fantasma_render() {
    // Colore del fantasmino
    uint16_t color = Red;
		int y, x;

	
		if(bad == 0){
			color = Blue;
		}
    // Offset base per centrare nella cella della griglia
    uint16_t baseX = 12 + 8 * X_fan; // Offset da sinistra
    uint16_t baseY = 39 + 8 * Y_fan; // Offset dall'alto

    // Disegna il corpo del fantasmino
    for (y = -2; y <= 2; y++) { // Altezza da -3 a 3 (7 pixel totali)
        for (x = -3; x <= 3; x++) { // Larghezza da -3 a 3 (7 pixel totali)
            // Disegna la testa semicircolare (equazione del cerchio: x^2 + y^2 <= r^2 con r=3)
            if (y <= 0 && (x * x + y * y <= 9)) {
                LCD_SetPoint(baseX + x, baseY + y, color);
            }
            // Disegna il corpo rettangolare sotto la testa
            else if (y > 0) {
                LCD_SetPoint(baseX + x, baseY + y, color);
            }
        }
    }

    // Disegna i piedi ondulati del fantasmino
    for (x = -3; x <= 3; x++) {
        int footY = 3; // Y di base per i piedi
        if (x % 2 == 0) { // Alterna i piedi su e giù
            LCD_SetPoint(baseX + x, baseY + footY, color);
        } else {
            LCD_SetPoint(baseX + x, baseY + footY + 1, color);
        }
    }
}

int  Fantasma_canGO(int X, int Y){
		int i=1;

		if(Griglia[Y][X]!=1){
			i=0;
		}
		if( In_Box == 0 && Griglia[Y][X]==3 ){
			i=1;
		}
		return i;
}

void Fantasma_moveTO(int X, int Y){
	X_fan=X;
	Y_fan=Y;
	
	if (X== X_POS && Y == Y_POS){
		if(bad==1){
			hits++;
		}
		if( bad == 0){
			Fantasma_clear();
			X_fan = 13;
			Y_fan = 15;
			bad = 1;
			wait = 3;
			In_Box = 1;
			points = points + 100;
		}
	}
}

void Fantasma_clear(){
	int k=0, i=0, j=0;
	for(k=0; k<7; k++){
		LCD_DrawLine(9+X_fan*8, k+37+Y_fan*8, 15+X_fan*8, k+37+Y_fan*8, Black);
	}
	if(Griglia[Y_fan][X_fan] == 0){
		LCD_SetPoint(8+4+X_fan*8, 36+4+Y_fan*8, Green);
		LCD_SetPoint(8+5+X_fan*8, 36+4+Y_fan*8, Green);
		LCD_SetPoint(8+4+X_fan*8, 36+5+Y_fan*8, Green);
		LCD_SetPoint(8+5+X_fan*8, 36+5+Y_fan*8, Green);
	}
	if(Griglia[Y_fan][X_fan] == 50){
			
		i=Y_fan;
		j=X_fan;
			LCD_DrawLine(1+8+j*8, 36+3+i*8, 16-1+j*8, 36+3+i*8, Cyan);
			LCD_DrawLine(1+8+j*8, 36+4+i*8, 16-1+j*8, 36+4+i*8, Cyan);
			LCD_DrawLine(1+8+j*8, 36+5+i*8, 16-1+j*8, 36+5+i*8, Cyan);

	
			LCD_DrawLine(8+3+j*8, 1+36+i*8, 8+3+j*8, 36+7+i*8, Cyan);
			LCD_DrawLine(8+4+j*8, 1+36+i*8, 8+4+j*8, 36+7+i*8, Cyan);
			LCD_DrawLine(8+5+j*8, 1+36+i*8, 8+5+j*8, 36+7+i*8, Cyan);
	}
}


	
	int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Funzione per calcolare il prossimo movimento
static Node queue[MAX_QUEUE_SIZE];
static int queueSize = 0;

// Funzioni per la gestione della coda di priorità
void push(Node n) {
    queue[queueSize++] = n;
}

Node pop() {
    int bestIdx = 0;
		int i;
    for (i = 1; i < queueSize; i++) {
        if (queue[i].priority < queue[bestIdx].priority) {
            bestIdx = i;
        }
    }
    Node best = queue[bestIdx];
    queue[bestIdx] = queue[--queueSize];
    return best;
}

bool isEmpty() {
    return queueSize == 0;
}

bool isInBounds(int x, int y, int N_colonne, int N_righe) {
    return x >= 0 && x < N_colonne && y >= 0 && y < N_righe;
}


// Funzione principale per calcolare la prossima posizione del fantasma
int Fantasma_Compute_nextPOS() {
		int x,y,i;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    
    bool visited[N_righe][N_colonne];
    int prev[N_righe][N_colonne][2];
    
    // Inizializzazione
    for (y = 0; y < N_righe; y++) {
        for (x = 0; x < N_colonne; x++) {
            visited[y][x] = false;
            prev[y][x][0] = -1;
            prev[y][x][1] = -1;
        }
    }

    queueSize = 0; // Resetta la coda
    push((Node){X_fan, Y_fan, 0, heuristic(X_fan, Y_fan, X_POS, Y_POS)});
    
    while (!isEmpty()) {
        Node current = pop();
        
        // Controlla se il fantasma ha raggiunto Pac-Man
        if (current.x == X_POS && current.y == Y_POS) {
            // Risali il percorso per trovare la prossima mossa
            int cx = X_POS, cy = Y_POS;
            while (prev[cy][cx][0] != X_fan || prev[cy][cx][1] != Y_fan) {
                int px = prev[cy][cx][0];
                int py = prev[cy][cx][1];
                cx = px;
                cy = py;
            }
            return cx + cy * N_colonne;
        }
        
        if (visited[current.y][current.x]) continue;
        visited[current.y][current.x] = true;
        
        for ( i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (isInBounds(nx, ny, N_colonne, N_righe) && !visited[ny][nx] && Fantasma_canGO(nx, ny) == 0) {
                push((Node){
                    nx, ny,
                    current.cost + 1,
                    current.cost + 1 + heuristic(nx, ny, X_POS, Y_POS)
                });
                prev[ny][nx][0] = current.x;
                prev[ny][nx][1] = current.y;
            }
        }
    }
    
    // Nessun percorso trovato
    return X_fan + Y_fan * N_colonne;
}


int Fantasma_Escape() {
		int i;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    
    int bestX = X_fan;
    int bestY = Y_fan;
    int maxH = -1; // Valore minimo iniziale per la distanza (si cerca di massimizzarlo)

    // Esplora tutte le direzioni
    for (i = 0; i < 4; i++) {
        int nx = X_fan + dx[i];
        int ny = Y_fan + dy[i];

        // Verifica che la cella sia valida e accessibile
        if (nx >= 0 && nx < N_colonne && ny >= 0 && ny < N_righe && Fantasma_canGO(nx, ny) == 0) {
            // Calcola l'euristica per questa cella
            int h = heuristic(nx, ny, X_POS, Y_POS);

            // Se questa cella è più lontana da Pac-Man, aggiornala
            if (h > maxH) {
                maxH = h;
                bestX = nx;
                bestY = ny;
            }
        }
    }

    // Restituisce la prossima posizione come indice della griglia
    return bestX + bestY * N_colonne;
}
