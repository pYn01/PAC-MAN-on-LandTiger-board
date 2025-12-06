/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "../led/led.h"
#include "../pacman.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GLCD.h"
#include "../table.h"
#include "../RIT//RIT.h"
#include "../fantasma.h"



/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
int NextPos, NextX,NextY;

void TIMER0_IRQHandler (void)
{
 	if (LPC_TIM0->IR & 1) {  // MR0 interrupt (timer reached MR0)
        LPC_TIM0->IR = 1;  // Clear interrupt flag
				if(pausa==0 && tempo>0 ){
					
					if(wait == 0){
						if(Tempo_blu<=0){
							bad=1;
							if(Griglia[Y_fan][X_fan]==3){ 
								Fantasma_clear();
								Fantasma_moveTO(X_fan, Y_fan-1);
								Fantasma_render();
							}
							else{
								In_Box = 0;
								Fantasma_clear();
								NextPos=Fantasma_Compute_nextPOS();
								NextX = NextPos % N_colonne;
								NextY = NextPos / N_colonne;
								Fantasma_moveTO(NextX, NextY);
								Fantasma_render();
							}
						}
						else{
							Fantasma_clear();
							NextPos=Fantasma_Escape();
							NextX = NextPos % N_colonne;
							NextY = NextPos / N_colonne;
							Fantasma_moveTO(NextX, NextY);
							Fantasma_render();
						}
					}
					else if (wait > 0){
						wait --;
					}
					else{wait = 0;}
			}
    }
    else if (LPC_TIM0->IR & 2) {  // MR1 interrupt (timer reached MR1)
        LPC_TIM0->IR = 2;  // Clear interrupt flag
				if(pausa==0 && tempo>0 && tempo<30){
					
					if(wait == 0){
						if(Tempo_blu<=0){
							bad=1;
							if(Griglia[Y_fan][X_fan]==3){ 
								Fantasma_clear();
								Fantasma_moveTO(X_fan, Y_fan-1);
								Fantasma_render();
							}
							else{
								In_Box = 0;
								Fantasma_clear();
								NextPos=Fantasma_Compute_nextPOS();
								NextX = NextPos % N_colonne;
								NextY = NextPos / N_colonne;
								Fantasma_moveTO(NextX, NextY);
								Fantasma_render();
							}
						}
						else{
							Fantasma_clear();
							NextPos=Fantasma_Escape();
							NextX = NextPos % N_colonne;
							NextY = NextPos / N_colonne;
							Fantasma_moveTO(NextX, NextY);
							Fantasma_render();
						}
					}
					else if (wait > 0){
						wait --;
					}
					else{wait = 0;}
			}
    }
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void){
	if (LPC_TIM1->IR & 1) {  // MR0 interrupt (timer reached MR0)
        LPC_TIM1->IR = 1;  // Clear interrupt flag
				if(pausa==0 && tempo>0){
					tempo = tempo -1;
					
					if(Tempo_blu > 0){
						Tempo_blu--;
					}
					
					sprintf(Buffer_P, "Points= %d",points);
					sprintf(Buffer_T, "Tempo = %d",tempo);
	
					GUI_Text(0, 305, (uint8_t *) Buffer_P, Red, Black);
					GUI_Text(155, 305, (uint8_t *) Buffer_T, Red, Black);
					
					Pacman_printLife();
				}
    }
    else if (LPC_TIM1->IR & 2) {  // MR1 interrupt (timer reached MR1)
        LPC_TIM1->IR = 2;  // Clear interrupt flag
    }
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler(void) {
    if (LPC_TIM2->IR & 1) {
        LPC_TIM2->IR = 1; 
				if(pausa==0){
					if(tempo > 0 && vite >0){
						if(Pills<=0){
							pausa = 1;
							GUI_Text(80, 145, (uint8_t *) " YOU WIN ! ", Green, White);
						}
						else{						
							Pacman_updateMovement();					
						}
					}
					else{
						pausa = 1;
						GUI_Text(72, 145, (uint8_t *) " YOU LOSE ! ", Red, White);
					}
				}
    }
    else if (LPC_TIM2->IR & 2) {  // MR1 
        LPC_TIM2->IR = 2;
				if(pausa==0){
					if(tempo > 0 && vite >0){
						if(Pills<=0){
							pausa = 1;
							GUI_Text(80, 150, (uint8_t *) " YOU WIN ! ", Green, White);
						}
						else{						
							Pacman_updateMovement();					
						}
					}
					else{
						pausa = 1;
						GUI_Text(80, 150, (uint8_t *) " YOU LOSE ! ", Red, White);
					}
				}
    }
}


/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler(void) {
    if (LPC_TIM3->IR & 1) {  // MR0 interrupt (timer reached MR0)
        LPC_TIM3->IR = 1;  // Clear interrupt flag
			if(Power_Pills>0){			
				if(pausa==0 && points>120){
					int random_number;
					srand((tempo + points)* (Power_Pills + vite*3) * current_direction);

					random_number = rand();					
					Power_pills(random_number);
				}
			}
    }
    else if (LPC_TIM3->IR & 2) {  // MR1 interrupt (timer reached MR1)
        LPC_TIM3->IR = 2;  // Clear interrupt flag

    }
}

/******************************************************************************
**                            End Of File
******************************************************************************/

/*
void TIMER0_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) // MR0
	{ 
		// your code
		LPC_TIM0->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM0->IR & 2){ // MR1
		// your code	
		LPC_TIM0->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 4){ // MR2
		// your code	
		LPC_TIM0->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 8){ // MR3
		// your code	
		LPC_TIM0->IR = 8;			// clear interrupt flag 
	}
  return;
}*/