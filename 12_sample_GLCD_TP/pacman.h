extern int X_POS;
extern int Y_POS;
extern int vite;
extern int points;
extern int tempo;
extern int pausa;
extern int vittoria;
extern char Buffer_P[13];
extern char Buffer_T[10];

void Pacman_clear();
void Pacman_render();
int Pacman_canGO(int X, int Y);
void Pacman_moveTO(int X, int Y);
void Pacman_updateMovement();
void Pacman_printLife();