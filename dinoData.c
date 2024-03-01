/* dinoData.c
   Code written by Isac Ljungberg and Brian Onoszko
   using original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "dinoGame.h"  /* Declatations for these labs */
#include <math.h> //math used for the floor function

/* Array of arrays sent to display to display the game*/
uint8_t* icon[4] = {
	icon0, icon1, icon2, icon3,
};

uint8_t icon0[] = {
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
};

uint8_t icon1[] = {
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
};

uint8_t icon2[] = {
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
};

uint8_t icon3[] = {
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
};


/* DINO NORMAL
  setPixel((dinoX + 4), dinoY, 0);
  setPixel((dinoX + 5), dinoY, 0);
  setPixel((dinoX + 6), dinoY, 0);
  setPixel((dinoX + 7), dinoY, 0);
  setPixel((dinoX + 4), (dinoY + 1), 0);
  setPixel((dinoX + 6), (dinoY + 1), 0);
  setPixel((dinoX + 7), (dinoY + 1), 0);
  setPixel((dinoX), (dinoY + 2), 0);
  setPixel((dinoX + 4), (dinoY + 2), 0);
  setPixel((dinoX + 5), (dinoY + 2), 0);
  setPixel((dinoX + 6), (dinoY + 2), 0);
  setPixel((dinoX + 7), (dinoY + 2), 0);
  setPixel((dinoX), (dinoY + 3), 0);
  setPixel((dinoX + 1), (dinoY + 3), 0);
  setPixel((dinoX + 3), (dinoY + 3), 0);
  setPixel((dinoX + 4), (dinoY + 3), 0);
  setPixel((dinoX + 5), (dinoY + 3), 0);
  setPixel((dinoX + 1), (dinoY + 4), 0);
  setPixel((dinoX + 2), (dinoY + 4), 0);
  setPixel((dinoX + 3), (dinoY + 4), 0);
  setPixel((dinoX + 4), (dinoY + 4), 0);
  setPixel((dinoX + 5), (dinoY + 4), 0);
  setPixel((dinoX + 6), (dinoY + 4), 0);
  setPixel((dinoX + 1), (dinoY + 5), 0);
  setPixel((dinoX + 2), (dinoY + 5), 0);
  setPixel((dinoX + 3), (dinoY + 5), 0);
  setPixel((dinoX + 4), (dinoY + 5), 0);
  setPixel((dinoX + 6), (dinoY + 5), 0);
  setPixel((dinoX + 2), (dinoY + 6), 0);
  setPixel((dinoX + 4), (dinoY + 6), 0);
  setPixel((dinoX + 2), (dinoY + 7), 0);
  setPixel((dinoX + 4), (dinoY + 7), 0);
*/

/* DINO DUCKING
  setPixel((dinoX + 7), (dinoY + 3), 0);
  setPixel((dinoX + 8), (dinoY + 3), 0);
  setPixel((dinoX + 9), (dinoY + 3), 0);
  setPixel((dinoX + 10), (dinoY + 3), 0);
  setPixel((dinoX - 2), (dinoY + 4), 0);
  setPixel((dinoX - 1), (dinoY + 4), 0);
  setPixel((dinoX), (dinoY + 4), 0);
  setPixel((dinoX + 1), (dinoY + 4), 0);
  setPixel((dinoX + 2), (dinoY + 4), 0);
  setPixel((dinoX + 3), (dinoY + 4), 0);
  setPixel((dinoX + 4), (dinoY + 4), 0);
  setPixel((dinoX + 5), (dinoY + 4), 0);
  setPixel((dinoX + 6), (dinoY + 4), 0);
  setPixel((dinoX + 7), (dinoY + 4), 0);
  setPixel((dinoX + 9), (dinoY + 4), 0);
  setPixel((dinoX + 10), (dinoY + 4), 0);
  setPixel((dinoX), (dinoY + 5), 0);
  setPixel((dinoX + 1), (dinoY + 5), 0);
  setPixel((dinoX + 2), (dinoY + 5), 0);
  setPixel((dinoX + 3), (dinoY + 5), 0);
  setPixel((dinoX + 4), (dinoY + 5), 0);
  setPixel((dinoX + 5), (dinoY + 5), 0);
  setPixel((dinoX + 6), (dinoY + 5), 0);
  setPixel((dinoX + 7), (dinoY + 5), 0);
  setPixel((dinoX + 8), (dinoY + 5), 0);
  setPixel((dinoX + 9), (dinoY + 5), 0);
  setPixel((dinoX + 10), (dinoY + 5), 0);
  setPixel((dinoX + 2), (dinoY + 6), 0);
  setPixel((dinoX + 4), (dinoY + 6), 0);
  setPixel((dinoX + 6), (dinoY + 6), 0);
  setPixel((dinoX + 2), (dinoY + 7), 0);
  setPixel((dinoX + 4), (dinoY + 7), 0);
*/

/* CACTUS A OBSTACLE
  setPixel((x + 3), (y - 1), 0);
  setPixel((x + 3), (y), 0);
  setPixel((x + 4), (y), 0);
  setPixel((x + 3), (y + 1), 0);
  setPixel((x + 4), (y + 1), 0);
  setPixel((x + 6), (y + 1), 0);
  setPixel((x + 3), (y + 2), 0);
  setPixel((x + 4), (y + 2), 0);
  setPixel((x + 6), (y + 2), 0);
  setPixel((x + 1), (y + 3), 0);
  setPixel((x + 3), (y + 3), 0);
  setPixel((x + 4), (y + 3), 0);
  setPixel((x + 6), (y + 3), 0);
  setPixel((x + 1), (y + 4), 0);
  setPixel((x + 3), (y + 4), 0);
  setPixel((x + 4), (y + 4), 0);
  setPixel((x + 5), (y + 4), 0);
  setPixel((x + 2), (y + 5), 0);
  setPixel((x + 3), (y + 5), 0);
  setPixel((x + 4), (y + 5), 0);
  setPixel((x + 3), (y + 6), 0);
  setPixel((x + 4), (y + 6), 0);
  setPixel((x + 3), (y + 7), 0);
  setPixel((x + 4), (y + 7), 0);
  setPixel((x + 3), (y + 8), 0);
  setPixel((x + 4), (y + 8), 0);
*/

/* CACTUS B OBSTACLE
  setPixel((x + 4), (y), 0);
  setPixel((x + 3), (y + 1), 0);
  setPixel((x + 4), (y + 1), 0);
  setPixel((x + 3), (y + 2), 0);
  setPixel((x + 4), (y + 2), 0);
  setPixel((x + 1), (y + 3), 0);
  setPixel((x + 3), (y + 3), 0);
  setPixel((x + 4), (y + 3), 0);
  setPixel((x + 1), (y + 4), 0);
  setPixel((x + 3), (y + 4), 0);
  setPixel((x + 4), (y + 4), 0);
  setPixel((x + 6), (y + 4), 0);
  setPixel((x + 2), (y + 5), 0);
  setPixel((x + 3), (y + 5), 0);
  setPixel((x + 4), (y + 5), 0);
  setPixel((x + 6), (y + 5), 0);
  setPixel((x + 3), (y + 6), 0);
  setPixel((x + 4), (y + 6), 0);
  setPixel((x + 5), (y + 6), 0);
  setPixel((x + 3), (y + 7), 0);
  setPixel((x + 4), (y + 7), 0);
  setPixel((x + 3), (y + 8), 0);
  setPixel((x + 4), (y + 8), 0);
*/

/* PTERODACTYL A OBSTACLE
  setPixel((x + 2), (y), 0);
  setPixel((x + 4), (y), 0);
  setPixel((x + 1), (y+1), 0);
  setPixel((x + 2), (y+1), 0);
  setPixel((x + 4), (y+1), 0);
  setPixel((x + 5), (y+1), 0);
  setPixel((x), (y+2), 0);
  setPixel((x + 1), (y+2), 0);
  setPixel((x + 2), (y+2), 0);
  setPixel((x + 4), (y+2), 0);
  setPixel((x + 5), (y+2), 0);
  setPixel((x + 2), (y+3), 0);
  setPixel((x + 3), (y+3), 0);
  setPixel((x + 4), (y+3), 0);
  setPixel((x + 5), (y+3), 0);
  setPixel((x + 6), (y+3), 0);
  setPixel((x + 7), (y+3), 0);
  setPixel((x + 8), (y+3), 0);
  setPixel((x + 3), (y+4), 0);
  setPixel((x + 4), (y+4), 0);
  setPixel((x + 5), (y+4), 0);
  setPixel((x + 6), (y+4), 0);
  setPixel((x + 7), (y+4), 0);
  setPixel((x + 4), (y+5), 0);
  setPixel((x + 5), (y+5), 0);
  setPixel((x + 6), (y+5), 0);
*/

/* PTERODACTYL B OBSTACLE
  setPixel((x + 2), (y), 0);
  setPixel((x + 1), (y+1), 0);
  setPixel((x + 2), (y+1), 0);
  setPixel((x), (y+2), 0);
  setPixel((x + 1), (y+2), 0);
  setPixel((x + 2), (y+2), 0);
  setPixel((x + 2), (y+3), 0);
  setPixel((x + 3), (y+3), 0);
  setPixel((x + 4), (y+3), 0);
  setPixel((x + 5), (y+3), 0);
  setPixel((x + 6), (y+3), 0);
  setPixel((x + 7), (y+3), 0);
  setPixel((x + 8), (y+3), 0);
  setPixel((x + 3), (y+4), 0);
  setPixel((x + 4), (y+4), 0);
  setPixel((x + 5), (y+4), 0);
  setPixel((x + 6), (y+4), 0);
  setPixel((x + 7), (y+4), 0);
  setPixel((x + 4), (y+5), 0);
  setPixel((x + 5), (y+5), 0);
  setPixel((x + 6), (y+5), 0);
  setPixel((x + 4), (y+6), 0);
*/

/*Font pseudo bitmaps for numbers*/
int pseudo0X[] = {1,2,0,3,0,3,0,3,0,3,1,2,};
int pseudo0Y[] = {0,0,1,1,2,2,3,3,4,4,5,5,};
int pseudo1X[] = {3,2,3,1,3,3,3,3,};
int pseudo1Y[] = {0,1,1,2,2,3,4,5,};
int pseudo2X[] = {1,2,0,3,2,1,0,0,1,2,3,};
int pseudo2Y[] = {0,0,1,1,2,3,4,5,5,5,5,};
int pseudo3X[] = {1,2,0,3,2,2,0,3,1,2,};
int pseudo3Y[] = {0,0,1,1,2,3,4,4,5,5,};
int pseudo4X[] = {2,3,1,3,0,1,2,3,3,3,3,};
int pseudo4Y[] = {0,0,1,1,2,2,2,2,3,4,5,};
int pseudo5X[] = {0,1,2,3,0,0,1,2,3,0,3,1,2,};
int pseudo5Y[] = {0,0,0,0,1,2,2,2,3,4,4,5,5,};
int pseudo6X[] = {2,1,0,0,1,2,0,3,1,2,};
int pseudo6Y[] = {0,1,2,3,3,3,4,4,5,5,};
int pseudo7X[] = {1,2,3,3,2,2,1,1,};
int pseudo7Y[] = {0,0,0,1,2,3,4,5,};
int pseudo8X[] = {1,2,0,3,1,2,0,3,0,3,1,2,};
int pseudo8Y[] = {0,0,1,1,2,2,3,3,4,4,5,5,};
int pseudo9X[] = {1,2,0,3,0,3,1,2,2,1,};
int pseudo9Y[] = {0,0,1,1,2,2,3,3,4,5,};

/*Font pseudo bitmaps for letters*/
int lettersXA[] = {1,2,3,0,4,0,4,0,1,2,3,4,0,4,0,4,};
int lettersYA[] = {0,0,0,1,1,2,2,3,3,3,3,3,4,4,5,5,};
int lettersXB[] = {0,1,2,3,0,4,0,1,2,3,0,4,0,4,0,1,2,3,};
int lettersYB[] = {0,0,0,0,1,1,2,2,2,2,3,3,4,4,5,5,5,5,};
int lettersXC[] = {1,2,3,0,4,0,0,0,4,1,2,3,};
int lettersYC[] = {0,0,0,1,1,2,3,4,4,5,5,5,};
int lettersXD[] = {0,1,2,3,0,4,0,4,0,4,0,4,0,1,2,3,};
int lettersYD[] = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,5,5,};
int lettersXE[] = {0,1,2,3,4,0,0,1,2,3,0,0,0,1,2,3,4,};
int lettersYE[] = {0,0,0,0,0,1,2,2,2,2,3,4,5,5,5,5,5,};
int lettersXF[] = {0,1,2,3,4,0,0,1,2,3,0,0,0,};
int lettersYF[] = {0,0,0,0,0,1,2,2,2,2,3,4,5,};
int lettersXG[] = {1,2,3,0,4,0,0,3,4,0,4,1,2,3,};
int lettersYG[] = {0,0,0,1,1,2,3,3,3,4,4,5,5,5,};
int lettersXH[] = {0,4,0,4,0,1,2,3,4,0,4,0,4,0,4,};
int lettersYH[] = {0,0,1,1,2,2,2,2,2,3,3,4,4,5,5,};
int lettersXI[] = {1,2,3,2,2,2,2,1,2,3,};
int lettersYI[] = {0,0,0,1,2,3,4,5,5,5,};
int lettersXJ[] = {1,2,3,4,4,4,4,0,4,1,2,3,};
int lettersYJ[] = {0,0,0,0,1,2,3,4,4,5,5,5,};
int lettersXK[] = {0,4,0,3,0,1,2,0,3,0,4,0,4,};
int lettersYK[] = {0,0,1,1,2,2,2,3,3,4,4,5,5,};
int lettersXL[] = {0,0,0,0,0,0,1,2,3,4,};
int lettersYL[] = {0,1,2,3,4,5,5,5,5,5,};
int lettersXM[] = {0,4,0,1,3,4,0,2,4,0,4,0,4,0,4,};
int lettersYM[] = {0,0,1,1,1,1,2,2,2,3,3,4,4,5,5,};
int lettersXN[] = {0,4,0,1,4,0,2,4,0,3,4,0,4,0,4,};
int lettersYN[] = {0,0,1,1,1,2,2,2,3,3,3,4,4,5,5,};
int lettersXO[] = {1,2,3,0,4,0,4,0,4,0,4,1,2,3,};
int lettersYO[] = {0,0,0,1,1,2,2,3,3,4,4,5,5,5,};
int lettersXP[] = {0,1,2,3,0,4,0,4,0,1,2,3,0,0,};
int lettersYP[] = {0,0,0,0,1,1,2,2,3,3,3,3,4,5,};
int lettersXQ[] = {1,2,3,0,4,0,4,0,4,0,3,1,2,4,};
int lettersYQ[] = {0,0,0,1,1,2,2,3,3,4,4,5,5,5,};
int lettersXR[] = {0,1,2,3,0,4,0,1,2,3,0,4,0,4,0,4,};
int lettersYR[] = {0,0,0,0,1,1,2,2,2,2,3,3,4,4,5,5,};
int lettersXS[] = {1,2,3,4,0,1,2,3,4,4,0,1,2,3,};
int lettersYS[] = {0,0,0,0,1,2,2,2,3,4,5,5,5,5,};
int lettersXT[] = {0,1,2,3,4,2,2,2,2,2,};
int lettersYT[] = {0,0,0,0,0,1,2,3,4,5,};
int lettersXU[] = {0,4,0,4,0,4,0,4,0,4,1,2,3,};
int lettersYU[] = {0,0,1,1,2,2,3,3,4,4,5,5,5,};
int lettersXV[] = {0,4,0,4,1,3,1,3,2,2,};
int lettersYV[] = {0,0,1,1,2,2,3,3,4,5,};
int lettersXW[] = {0,4,0,4,0,4,0,2,4,0,1,3,4,0,4};
int lettersYW[] = {0,0,1,1,2,2,3,3,3,4,4,4,4,5,5};
int lettersXX[] = {0,4,1,3,2,1,3,0,4,0,4,};
int lettersYX[] = {0,0,1,1,2,3,3,4,4,5,5,};
int lettersXY[] = {0,4,0,4,1,3,2,2,2,};
int lettersYY[] = {0,0,1,1,2,2,3,4,5,};
int lettersXZ[] = {0,1,2,3,4,4,2,3,1,0,0,1,2,3,4,};
int lettersYZ[] = {0,0,0,0,0,1,2,2,3,4,5,5,5,5,5,};

/* Arrays of arrays containings pseudo bitmaps for letters*/
int lettersLength[] = {16,18,12,16,17,13,14,15,10,12,13,10,15,15,14,14,14,16,14,10,13,10,15,11,9,15};
int* lettersX[] = {
	lettersXA, lettersXB, lettersXC, lettersXD, lettersXE, lettersXF, lettersXG, lettersXH, lettersXI, lettersXJ, lettersXK, lettersXL,
	lettersXM, lettersXN, lettersXO, lettersXP, lettersXQ, lettersXR, lettersXS, lettersXT, lettersXU, lettersXV, lettersXW, lettersXX,
	lettersXY, lettersXZ,
};

int* lettersY[] = {
	lettersYA, lettersYB, lettersYC, lettersYD, lettersYE, lettersYF, lettersYG, lettersYH, lettersYI, lettersYJ, lettersYK, lettersYL,
	lettersYM, lettersYN, lettersYO, lettersYP, lettersYQ, lettersYR, lettersYS, lettersYT, lettersYU, lettersYV, lettersYW, lettersYX,
	lettersYY, lettersYZ,
};