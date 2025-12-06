#include "button.h"
#include "LPC17xx.h"
#include "../table.h"
#include "GLCD/GLCD.h" 
#include "../timer/timer.h"
#include "../pacman.h"
#include <stdio.h>
#include <stdlib.h>

void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	if(pausa == -1){
		pausa = 0;
		GUI_Text(15, 20, (uint8_t *) " PAUSA : INT_0 TO RESUME ", Black, Black);
	} else if(pausa == 0){
		pausa = -1;
		GUI_Text(15, 20, (uint8_t *) " PAUSA : INT_0 TO RESUME ", Red, Black);
	}
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	Pacman_updateMovement();
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	enable_timer(1);
	
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */  
	enable_timer(0);  
}


