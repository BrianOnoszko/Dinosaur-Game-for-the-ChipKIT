/* dinoFunc.c
   This file written 2023 by Isac Ljungberg and Brian Onoszko
   Some parts are original code written by Axel Isaksson and F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "dinoGame.h"  /* Declaration of header file */
#include <math.h> /* Declaration of math used for the floor function*/

/*Code written by Axel Isaksson and F Lundevall -->*/
#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_init(void) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));

		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 32; j++)
			spi_send_recv(~data[i*32 + j]);
	}
}

/*<-- Code written by Axel Isaksson and F Lundevall*/

void iconClear(){ //clears icons. which is the data sent to the display
  int n,i;
  for(n = 0; n < 4; n++){
    for(i = 0; i < 128; i++){
      icon[n][i] = 255;
    }
  }
}

void setPixel (int x, int y, int color){ //sets a pixel based on x y coordinate in the icon 2d array
    int space = (int) floor(x / 32); //determines which of 4 areas
    int row = (int) floor(y / 8); //determines row
    int column = (int) floor((x % 32) / 8); //determines column
    int byteNum = (x % 32) % 8; //determines which byte within the row and column
    int bitNum = y % 8; //determines which bit within the byte
    if(x >= 0 && x <= 128 && y >= 0 && y <= 32){//doesn't write if pixel is outside of screen
      if(color){//sets black pixel
          (icon[space][row*32 + column*8+byteNum]) |= (0x1<<bitNum);
      }else{//sets white pixel
          (icon[space][row*32 + column*8+byteNum]) &= ~(0x1<<bitNum);
      }
    }
}

void drawDino(int x, int y){ //draws dino based on setPixel calls
  if(menu){//in menu, draw stationary dino
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
  }else{//not menu, draw dino frame 1 or 2
    if(frameDino){
      frameDino = 0;
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
    }else{
      frameDino = 1;
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
      setPixel((dinoX + 4), (dinoY + 7), 0);
    }
  }
}

void drawDuck(int x, int y){//draws dino while ducking, frame 1 or 2
  if(frameDino){
    frameDino = 0;
    setPixel((dinoX + 7), (dinoY + 0), 0);
    setPixel((dinoX + 8), (dinoY + 0), 0);
    setPixel((dinoX + 9), (dinoY + 0), 0);
    setPixel((dinoX + 10), (dinoY + 0), 0);
    setPixel((dinoX - 2), (dinoY + 1), 0);
    setPixel((dinoX - 1), (dinoY + 1), 0);
    setPixel((dinoX), (dinoY + 1), 0);
    setPixel((dinoX + 1), (dinoY + 1), 0);
    setPixel((dinoX + 2), (dinoY + 1), 0);
    setPixel((dinoX + 3), (dinoY + 1), 0);
    setPixel((dinoX + 4), (dinoY + 1), 0);
    setPixel((dinoX + 5), (dinoY + 1), 0);
    setPixel((dinoX + 6), (dinoY + 1), 0);
    setPixel((dinoX + 7), (dinoY + 1), 0);
    setPixel((dinoX + 9), (dinoY + 1), 0);
    setPixel((dinoX + 10), (dinoY + 1), 0);
    setPixel((dinoX), (dinoY + 2), 0);
    setPixel((dinoX + 1), (dinoY + 2), 0);
    setPixel((dinoX + 2), (dinoY + 2), 0);
    setPixel((dinoX + 3), (dinoY + 2), 0);
    setPixel((dinoX + 4), (dinoY + 2), 0);
    setPixel((dinoX + 5), (dinoY + 2), 0);
    setPixel((dinoX + 6), (dinoY + 2), 0);
    setPixel((dinoX + 7), (dinoY + 2), 0);
    setPixel((dinoX + 8), (dinoY + 2), 0);
    setPixel((dinoX + 9), (dinoY + 2), 0);
    setPixel((dinoX + 10), (dinoY + 2), 0);
    setPixel((dinoX + 2), (dinoY + 3), 0);
    setPixel((dinoX + 4), (dinoY + 3), 0);
    setPixel((dinoX + 6), (dinoY + 3), 0);
    setPixel((dinoX + 2), (dinoY + 4), 0);
  }else{
    frameDino = 1;
    setPixel((dinoX + 7), (dinoY + 0), 0);
    setPixel((dinoX + 8), (dinoY + 0), 0);
    setPixel((dinoX + 9), (dinoY + 0), 0);
    setPixel((dinoX + 10), (dinoY + 0), 0);
    setPixel((dinoX - 2), (dinoY + 1), 0);
    setPixel((dinoX - 1), (dinoY + 1), 0);
    setPixel((dinoX), (dinoY + 1), 0);
    setPixel((dinoX + 1), (dinoY + 1), 0);
    setPixel((dinoX + 2), (dinoY + 1), 0);
    setPixel((dinoX + 3), (dinoY + 1), 0);
    setPixel((dinoX + 4), (dinoY + 1), 0);
    setPixel((dinoX + 5), (dinoY + 1), 0);
    setPixel((dinoX + 6), (dinoY + 1), 0);
    setPixel((dinoX + 7), (dinoY + 1), 0);
    setPixel((dinoX + 9), (dinoY + 1), 0);
    setPixel((dinoX + 10), (dinoY + 1), 0);
    setPixel((dinoX), (dinoY + 2), 0);
    setPixel((dinoX + 1), (dinoY + 2), 0);
    setPixel((dinoX + 2), (dinoY + 2), 0);
    setPixel((dinoX + 3), (dinoY + 2), 0);
    setPixel((dinoX + 4), (dinoY + 2), 0);
    setPixel((dinoX + 5), (dinoY + 2), 0);
    setPixel((dinoX + 6), (dinoY + 2), 0);
    setPixel((dinoX + 7), (dinoY + 2), 0);
    setPixel((dinoX + 8), (dinoY + 2), 0);
    setPixel((dinoX + 9), (dinoY + 2), 0);
    setPixel((dinoX + 10), (dinoY + 2), 0);
    setPixel((dinoX + 2), (dinoY + 3), 0);
    setPixel((dinoX + 4), (dinoY + 3), 0);
    setPixel((dinoX + 6), (dinoY + 3), 0);
    setPixel((dinoX + 4), (dinoY + 4), 0);
  }
}

void drawCactus1(int x, int y){
  setPixel((x + 0), (y - 1), 0);
  setPixel((x + 0), (y), 0);
  setPixel((x + 1), (y), 0);
  setPixel((x + 0), (y + 1), 0);
  setPixel((x + 1), (y + 1), 0);
  setPixel((x + 3), (y + 1), 0);
  setPixel((x + 0), (y + 2), 0);
  setPixel((x + 1), (y + 2), 0);
  setPixel((x + 3), (y + 2), 0);
  setPixel((x - 2), (y + 3), 0);
  setPixel((x + 0), (y + 3), 0);
  setPixel((x + 1), (y + 3), 0);
  setPixel((x + 3), (y + 3), 0);
  setPixel((x - 2), (y + 4), 0);
  setPixel((x + 0), (y + 4), 0);
  setPixel((x + 1), (y + 4), 0);
  setPixel((x + 2), (y + 4), 0);
  setPixel((x - 1), (y + 5), 0);
  setPixel((x + 0), (y + 5), 0);
  setPixel((x + 1), (y + 5), 0);
  setPixel((x + 0), (y + 6), 0);
  setPixel((x + 1), (y + 6), 0);
  setPixel((x + 0), (y + 7), 0);
  setPixel((x + 1), (y + 7), 0);
  setPixel((x + 0), (y + 8), 0);
  setPixel((x + 1), (y + 8), 0);
}

void drawCactus2(int x, int y){
  setPixel((x + 1), (y), 0);
  setPixel((x + 0), (y + 1), 0);
  setPixel((x + 1), (y + 1), 0);
  setPixel((x + 0), (y + 2), 0);
  setPixel((x + 1), (y + 2), 0);
  setPixel((x - 2), (y + 3), 0);
  setPixel((x + 0), (y + 3), 0);
  setPixel((x + 1), (y + 3), 0);
  setPixel((x - 2), (y + 4), 0);
  setPixel((x + 0), (y + 4), 0);
  setPixel((x + 1), (y + 4), 0);
  setPixel((x + 3), (y + 4), 0);
  setPixel((x - 1), (y + 5), 0);
  setPixel((x + 0), (y + 5), 0);
  setPixel((x + 1), (y + 5), 0);
  setPixel((x + 3), (y + 5), 0);
  setPixel((x + 0), (y + 6), 0);
  setPixel((x + 1), (y + 6), 0);
  setPixel((x + 2), (y + 6), 0);
  setPixel((x + 0), (y + 7), 0);
  setPixel((x + 1), (y + 7), 0);
  setPixel((x + 0), (y + 8), 0);
  setPixel((x + 1), (y + 8), 0);
}

void drawPtero(int x, int y){//draws pterodactyl frame 1 or 2
  if(frameDino){
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
  }else{
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
  }
}

void drawMenu(){
  //D
  setPixel((2), (2), 0);
  setPixel((3), (2), 0);
  setPixel((4), (2), 0);
  setPixel((5), (2), 0);
  setPixel((6), (2), 0);
  setPixel((7), (2), 0);
  
  setPixel((2), (3), 0);
  setPixel((3), (3), 0);
  setPixel((4), (3), 0);
  setPixel((5), (3), 0);
  setPixel((6), (3), 0);
  setPixel((7), (3), 0);

  setPixel((2), (4), 0);
  setPixel((3), (4), 0);
  setPixel((8), (4), 0);
  setPixel((9), (4), 0);

  setPixel((2), (5), 0);
  setPixel((3), (5), 0);
  setPixel((8), (5), 0);
  setPixel((9), (5), 0);
  
  setPixel((2), (6), 0);
  setPixel((3), (6), 0);
  setPixel((8), (6), 0);
  setPixel((9), (6), 0);

  setPixel((2), (7), 0);
  setPixel((3), (7), 0);
  setPixel((8), (7), 0);
  setPixel((9), (7), 0);

  setPixel((2), (8), 0);
  setPixel((3), (8), 0);
  setPixel((4), (8), 0);
  setPixel((5), (8), 0);
  setPixel((6), (8), 0);
  setPixel((7), (8), 0);

  setPixel((2), (9), 0);
  setPixel((3), (9), 0);
  setPixel((4), (9), 0);
  setPixel((5), (9), 0);
  setPixel((6), (9), 0);
  setPixel((7), (9), 0);

  //I
  setPixel((12), (2), 0);
  setPixel((13), (2), 0);
  setPixel((14), (2), 0);
  setPixel((15), (2), 0);
  setPixel((16), (2), 0);
  setPixel((17), (2), 0);

  setPixel((12), (3), 0);
  setPixel((13), (3), 0);
  setPixel((14), (3), 0);
  setPixel((15), (3), 0);
  setPixel((16), (3), 0);
  setPixel((17), (3), 0);

  setPixel((14), (4), 0);
  setPixel((15), (4), 0);

  setPixel((14), (5), 0);
  setPixel((15), (5), 0);

  setPixel((14), (6), 0);
  setPixel((15), (6), 0);

  setPixel((14), (7), 0);
  setPixel((15), (7), 0);

  setPixel((12), (8), 0);
  setPixel((13), (8), 0);
  setPixel((14), (8), 0);
  setPixel((15), (8), 0);
  setPixel((16), (8), 0);
  setPixel((17), (8), 0);
  
  setPixel((12), (9), 0);
  setPixel((13), (9), 0);
  setPixel((14), (9), 0);
  setPixel((15), (9), 0);
  setPixel((16), (9), 0);
  setPixel((17), (9), 0);

  //N
  setPixel((20), (2), 0);
  setPixel((21), (2), 0);
  setPixel((26), (2), 0);
  setPixel((27), (2), 0); 

  setPixel((20), (3), 0);
  setPixel((21), (3), 0);
  setPixel((26), (3), 0);
  setPixel((27), (3), 0); 

  setPixel((20), (4), 0);
  setPixel((21), (4), 0);
  setPixel((22), (4), 0);
  setPixel((23), (4), 0);
  setPixel((26), (4), 0);
  setPixel((27), (4), 0); 

  setPixel((20), (5), 0);
  setPixel((21), (5), 0);
  setPixel((24), (5), 0);
  setPixel((25), (5), 0);
  setPixel((26), (5), 0);
  setPixel((27), (5), 0); 

  setPixel((20), (6), 0);
  setPixel((21), (6), 0);
  setPixel((24), (6), 0);
  setPixel((25), (6), 0);
  setPixel((26), (6), 0);
  setPixel((27), (6), 0); 

  setPixel((20), (7), 0);
  setPixel((21), (7), 0);
  setPixel((26), (7), 0);
  setPixel((27), (7), 0); 

  setPixel((20), (8), 0);
  setPixel((21), (8), 0);
  setPixel((26), (8), 0);
  setPixel((27), (8), 0); 

  setPixel((20), (9), 0);
  setPixel((21), (9), 0);
  setPixel((26), (9), 0);
  setPixel((27), (9), 0);


  //O
  setPixel((32), (2), 0);
  setPixel((33), (2), 0);
  setPixel((34), (2), 0);
  setPixel((35), (2), 0);

  setPixel((32), (3), 0);
  setPixel((33), (3), 0);
  setPixel((34), (3), 0);
  setPixel((35), (3), 0);

  setPixel((30), (4), 0);
  setPixel((31), (4), 0);
  setPixel((36), (4), 0);
  setPixel((37), (4), 0);

  setPixel((30), (5), 0);
  setPixel((31), (5), 0);
  setPixel((36), (5), 0);
  setPixel((37), (5), 0);

  setPixel((30), (6), 0);
  setPixel((31), (6), 0);
  setPixel((36), (6), 0);
  setPixel((37), (6), 0);

  setPixel((30), (7), 0);
  setPixel((31), (7), 0);
  setPixel((36), (7), 0);
  setPixel((37), (7), 0);

  setPixel((32), (8), 0);
  setPixel((33), (8), 0);
  setPixel((34), (8), 0);
  setPixel((35), (8), 0);

  setPixel((32), (9), 0);
  setPixel((33), (9), 0);
  setPixel((34), (9), 0);
  setPixel((35), (9), 0); 


  //S
  setPixel((42), (2), 0);
  setPixel((43), (2), 0);
  setPixel((44), (2), 0);
  setPixel((45), (2), 0); 
  setPixel((46), (2), 0);
  setPixel((47), (2), 0);
  
  setPixel((42), (3), 0);
  setPixel((43), (3), 0);
  setPixel((44), (3), 0);
  setPixel((45), (3), 0);
  setPixel((46), (3), 0);
  setPixel((47), (3), 0);

  setPixel((40), (4), 0);
  setPixel((41), (4), 0);

  setPixel((40), (5), 0);
  setPixel((41), (5), 0);
  setPixel((42), (5), 0);
  setPixel((43), (5), 0);
  setPixel((44), (5), 0);
  setPixel((45), (5), 0);

  setPixel((42), (6), 0);
  setPixel((43), (6), 0);
  setPixel((44), (6), 0);
  setPixel((45), (6), 0);
  setPixel((46), (6), 0);
  setPixel((47), (6), 0);

  setPixel((46), (7), 0);
  setPixel((47), (7), 0);

  setPixel((40), (8), 0);
  setPixel((41), (8), 0);
  setPixel((42), (8), 0);
  setPixel((43), (8), 0);
  setPixel((44), (8), 0);
  setPixel((45), (8), 0);

  setPixel((40), (9), 0);
  setPixel((41), (9), 0);
  setPixel((42), (9), 0);
  setPixel((43), (9), 0);
  setPixel((44), (9), 0);
  setPixel((45), (9), 0);

  //A
  setPixel((52), (2), 0);
  setPixel((53), (2), 0);
  setPixel((54), (2), 0);
  setPixel((55), (2), 0);

  setPixel((52), (3), 0);
  setPixel((53), (3), 0);
  setPixel((54), (3), 0);
  setPixel((55), (3), 0);

  setPixel((50), (4), 0);
  setPixel((51), (4), 0);
  setPixel((56), (4), 0);
  setPixel((57), (4), 0);

  setPixel((50), (5), 0);
  setPixel((51), (5), 0);
  setPixel((52), (5), 0);
  setPixel((53), (5), 0);
  setPixel((54), (5), 0);
  setPixel((55), (5), 0);
  setPixel((56), (5), 0);
  setPixel((57), (5), 0);

  setPixel((50), (6), 0);
  setPixel((51), (6), 0);
  setPixel((52), (6), 0);
  setPixel((53), (6), 0);
  setPixel((54), (6), 0);
  setPixel((55), (6), 0);
  setPixel((56), (6), 0);
  setPixel((57), (6), 0);

  setPixel((50), (7), 0);
  setPixel((51), (7), 0);
  setPixel((56), (7), 0);
  setPixel((57), (7), 0);

  setPixel((50), (8), 0);
  setPixel((51), (8), 0);
  setPixel((56), (8), 0);
  setPixel((57), (8), 0);

  setPixel((50), (9), 0);
  setPixel((51), (9), 0);
  setPixel((56), (9), 0);
  setPixel((57), (9), 0);


  //U
  setPixel((60), (2), 0);
  setPixel((61), (2), 0);
  setPixel((66), (2), 0);
  setPixel((67), (2), 0);

  setPixel((60), (3), 0);
  setPixel((61), (3), 0);
  setPixel((66), (3), 0);
  setPixel((67), (3), 0);

  setPixel((60), (4), 0);
  setPixel((61), (4), 0);
  setPixel((66), (4), 0);
  setPixel((67), (4), 0);

  setPixel((60), (5), 0);
  setPixel((61), (5), 0);
  setPixel((66), (5), 0);
  setPixel((67), (5), 0);

  setPixel((60), (6), 0);
  setPixel((61), (6), 0);
  setPixel((66), (6), 0);
  setPixel((67), (6), 0);

  setPixel((60), (7), 0);
  setPixel((61), (7), 0);
  setPixel((66), (7), 0);
  setPixel((67), (7), 0);

  setPixel((62), (8), 0);
  setPixel((63), (8), 0);
  setPixel((64), (8), 0);
  setPixel((65), (8), 0);

  setPixel((62), (9), 0);
  setPixel((63), (9), 0);
  setPixel((64), (9), 0);
  setPixel((65), (9), 0);


  //R
  setPixel((70), (2), 0);
  setPixel((71), (2), 0);
  setPixel((72), (2), 0);
  setPixel((73), (2), 0);
  setPixel((74), (2), 0);
  setPixel((75), (2), 0);

  setPixel((70), (3), 0);
  setPixel((71), (3), 0);
  setPixel((72), (3), 0);
  setPixel((73), (3), 0);
  setPixel((74), (3), 0);
  setPixel((75), (3), 0);

  setPixel((70), (4), 0);
  setPixel((71), (4), 0);
  setPixel((76), (4), 0);
  setPixel((77), (4), 0);

  setPixel((70), (5), 0);
  setPixel((71), (5), 0);
  setPixel((72), (5), 0);
  setPixel((73), (5), 0);
  setPixel((74), (5), 0);
  setPixel((75), (5), 0);

  setPixel((70), (6), 0);
  setPixel((71), (6), 0);
  setPixel((72), (6), 0);
  setPixel((73), (6), 0);
  setPixel((74), (6), 0);
  setPixel((75), (6), 0);

  setPixel((70), (7), 0);
  setPixel((71), (7), 0);
  setPixel((76), (7), 0);
  setPixel((77), (7), 0);

  setPixel((70), (8), 0);
  setPixel((71), (8), 0);
  setPixel((76), (8), 0);
  setPixel((77), (8), 0);

  setPixel((70), (9), 0);
  setPixel((71), (9), 0);
  setPixel((76), (9), 0);
  setPixel((77), (9), 0);


  //G
  setPixel((88), (2), 0);
  setPixel((89), (2), 0);
  setPixel((90), (2), 0);
  setPixel((91), (2), 0);

  setPixel((88), (3), 0);
  setPixel((89), (3), 0);
  setPixel((90), (3), 0);
  setPixel((91), (3), 0);
  
  setPixel((86), (4), 0);
  setPixel((87), (4), 0);

  setPixel((86), (5), 0);
  setPixel((87), (5), 0);
  setPixel((90), (5), 0);
  setPixel((91), (5), 0);
  setPixel((92), (5), 0);
  setPixel((93), (5), 0);

  setPixel((86), (6), 0);
  setPixel((87), (6), 0);
  setPixel((92), (6), 0);
  setPixel((93), (6), 0);

  setPixel((86), (7), 0);
  setPixel((87), (7), 0);
  setPixel((92), (7), 0);
  setPixel((93), (7), 0);

  setPixel((88), (8), 0);
  setPixel((89), (8), 0);
  setPixel((90), (8), 0);
  setPixel((91), (8), 0);

  setPixel((88), (9), 0);
  setPixel((89), (9), 0);
  setPixel((90), (9), 0);
  setPixel((91), (9), 0);


  //A
  setPixel((98), (2), 0);
  setPixel((99), (2), 0);
  setPixel((100), (2), 0);
  setPixel((101), (2), 0);

  setPixel((98), (3), 0);
  setPixel((99), (3), 0);
  setPixel((100), (3), 0);
  setPixel((101), (3), 0);

  setPixel((96), (4), 0);
  setPixel((97), (4), 0);
  setPixel((102), (4), 0);
  setPixel((103), (4), 0);

  setPixel((96), (5), 0);
  setPixel((97), (5), 0);
  setPixel((98), (5), 0);
  setPixel((99), (5), 0);
  setPixel((100), (5), 0);
  setPixel((101), (5), 0);
  setPixel((102), (5), 0);
  setPixel((103), (5), 0);

  setPixel((96), (6), 0);
  setPixel((97), (6), 0);
  setPixel((98), (6), 0);
  setPixel((99), (6), 0);
  setPixel((100), (6), 0);
  setPixel((101), (6), 0);
  setPixel((102), (6), 0);
  setPixel((103), (6), 0);

  setPixel((96), (7), 0);
  setPixel((97), (7), 0);
  setPixel((102), (7), 0);
  setPixel((103), (7), 0);

  setPixel((96), (8), 0);
  setPixel((97), (8), 0);
  setPixel((102), (8), 0);
  setPixel((103), (8), 0);

  setPixel((96), (9), 0);
  setPixel((97), (9), 0);
  setPixel((102), (9), 0);
  setPixel((103), (9), 0);


  //M
  setPixel((106), (2), 0);
  setPixel((107), (2), 0);
  setPixel((114), (2), 0);
  setPixel((115), (2), 0);

  setPixel((106), (3), 0);
  setPixel((107), (3), 0);
  setPixel((114), (3), 0);
  setPixel((115), (3), 0);

  setPixel((106), (4), 0);
  setPixel((107), (4), 0);
  setPixel((108), (4), 0);
  setPixel((109), (4), 0);
  setPixel((112), (4), 0);
  setPixel((113), (4), 0);
  setPixel((114), (4), 0);
  setPixel((115), (4), 0);

  setPixel((106), (5), 0);
  setPixel((107), (5), 0);
  setPixel((110), (5), 0);
  setPixel((111), (5), 0);
  setPixel((114), (5), 0);
  setPixel((115), (5), 0);

  setPixel((106), (6), 0);
  setPixel((107), (6), 0);
  setPixel((110), (6), 0);
  setPixel((111), (6), 0);
  setPixel((114), (6), 0);
  setPixel((115), (6), 0);

  setPixel((106), (7), 0);
  setPixel((107), (7), 0);
  setPixel((114), (7), 0);
  setPixel((115), (7), 0);

  setPixel((106), (8), 0);
  setPixel((107), (8), 0);
  setPixel((114), (8), 0);
  setPixel((115), (8), 0);

  setPixel((106), (9), 0);
  setPixel((107), (9), 0);
  setPixel((114), (9), 0);
  setPixel((115), (9), 0);


  //E
  setPixel((118), (2), 0);
  setPixel((119), (2), 0);
  setPixel((120), (2), 0);
  setPixel((121), (2), 0);
  setPixel((122), (2), 0);
  setPixel((123), (2), 0);
  setPixel((124), (2), 0);
  setPixel((125), (2), 0);

  setPixel((118), (3), 0);
  setPixel((119), (3), 0);
  setPixel((120), (3), 0);
  setPixel((121), (3), 0);
  setPixel((122), (3), 0);
  setPixel((123), (3), 0);
  setPixel((124), (3), 0);
  setPixel((125), (3), 0);

  setPixel((118), (4), 0);
  setPixel((119), (4), 0);

  setPixel((118), (5), 0);
  setPixel((119), (5), 0);
  setPixel((120), (5), 0);
  setPixel((121), (5), 0);

  setPixel((118), (6), 0);
  setPixel((119), (6), 0);
  setPixel((120), (6), 0);
  setPixel((121), (6), 0);

  setPixel((118), (7), 0);
  setPixel((119), (7), 0);

  setPixel((118), (8), 0);
  setPixel((119), (8), 0);
  setPixel((120), (8), 0);
  setPixel((121), (8), 0);
  setPixel((122), (8), 0);
  setPixel((123), (8), 0);
  setPixel((124), (8), 0);
  setPixel((125), (8), 0);

  setPixel((118), (9), 0);
  setPixel((119), (9), 0);
  setPixel((120), (9), 0);
  setPixel((121), (9), 0);
  setPixel((122), (9), 0);
  setPixel((123), (9), 0);
  setPixel((124), (9), 0);
  setPixel((125), (9), 0);


  //JUMP
  setPixel(64, 16, 0);
  setPixel(64, 17, 0);
  setPixel(64, 18, 0);
  setPixel(64, 19, 0);
  setPixel(62, 19, 0);
  setPixel(63, 20, 0);

  setPixel(66, 16, 0);
  setPixel(68, 16, 0);
  setPixel(66, 17, 0);
  setPixel(68, 17, 0);
  setPixel(66, 18, 0);
  setPixel(68, 18, 0);
  setPixel(66, 19, 0);
  setPixel(68, 19, 0);
  setPixel(67, 20, 0);

  setPixel(70, 16, 0);
  setPixel(70, 17, 0);
  setPixel(70, 18, 0);
  setPixel(70, 19, 0);
  setPixel(70, 20, 0);
  setPixel(74, 16, 0);
  setPixel(74, 17, 0);
  setPixel(74, 18, 0);
  setPixel(74, 19, 0);
  setPixel(74, 20, 0);
  setPixel(71, 17, 0);
  setPixel(72, 18, 0);
  setPixel(73, 17, 0);

  setPixel(76, 16, 0);
  setPixel(77, 16, 0);
  setPixel(76, 17, 0);
  setPixel(78, 17, 0);
  setPixel(76, 18, 0);
  setPixel(77, 18, 0);
  setPixel(76, 19, 0);
  setPixel(76, 20, 0);



  //DUCK
  setPixel(85, 16, 0);
  setPixel(86, 16, 0);
  setPixel(85, 17, 0);
  setPixel(87, 17, 0);
  setPixel(85, 18, 0);
  setPixel(87, 18, 0);
  setPixel(85, 19, 0);
  setPixel(87, 19, 0);
  setPixel(85, 20, 0);
  setPixel(86, 20, 0);

  setPixel(89, 16, 0);
  setPixel(91, 16, 0);
  setPixel(89, 17, 0);
  setPixel(91, 17, 0);
  setPixel(89, 18, 0);
  setPixel(91, 18, 0);
  setPixel(89, 19, 0);
  setPixel(91, 19, 0);
  setPixel(90, 20, 0);

  setPixel(94, 16, 0);
  setPixel(93, 17, 0);
  setPixel(95, 17, 0);
  setPixel(93, 18, 0);
  setPixel(93, 19, 0);
  setPixel(95, 19, 0);
  setPixel(94, 20, 0);

  setPixel(97, 16, 0);
  setPixel(99, 16, 0);
  setPixel(97, 17, 0);
  setPixel(99, 17, 0);
  setPixel(97, 18, 0);
  setPixel(98, 18, 0);
  setPixel(97, 19, 0);
  setPixel(99, 19, 0);
  setPixel(97, 20, 0);
  setPixel(99, 20, 0);


  //Start
  setPixel(106, 16, 0);
  setPixel(107, 16, 0);
  setPixel(105, 17, 0);
  setPixel(106, 18, 0);
  setPixel(107, 19, 0);
  setPixel(105, 20, 0);
  setPixel(106, 20, 0);

  setPixel(109, 16, 0);
  setPixel(110, 16, 0);
  setPixel(111, 16, 0);
  setPixel(110, 17, 0);
  setPixel(110, 18, 0);
  setPixel(110, 19, 0);
  setPixel(110, 20, 0); 

  setPixel(114, 16, 0);
  setPixel(113, 17, 0);
  setPixel(115, 17, 0);
  setPixel(113, 18, 0);
  setPixel(114, 18, 0);
  setPixel(115, 18, 0);
  setPixel(113, 19, 0);
  setPixel(115, 19, 0);
  setPixel(113, 20, 0);
  setPixel(115, 20, 0);

  setPixel(117, 16, 0);
  setPixel(118, 16, 0);
  setPixel(117, 17, 0);
  setPixel(119, 17, 0);
  setPixel(117, 18, 0);
  setPixel(118, 18, 0);
  setPixel(117, 19, 0);
  setPixel(119, 19, 0);
  setPixel(117, 20, 0);
  setPixel(119, 20, 0);

  setPixel(121, 16, 0);
  setPixel(122, 16, 0);
  setPixel(123, 16, 0);
  setPixel(122, 17, 0);
  setPixel(122, 18, 0);
  setPixel(122, 19, 0);
  setPixel(122, 20, 0);

  //Button 1
  setPixel(69, 22, 0);
  setPixel(70, 22, 0);
  setPixel(71, 22, 0);
  setPixel(68, 23, 0);
  setPixel(72, 23, 0);
  setPixel(67, 24, 0);
  setPixel(73, 24, 0);
  setPixel(67, 25, 0);
  setPixel(73, 25, 0);
  setPixel(67, 26, 0);
  setPixel(73, 26, 0);
  setPixel(68, 27, 0);
  setPixel(72, 27, 0);
  setPixel(69, 28, 0);
  setPixel(70, 28, 0);
  setPixel(71, 28, 0);
  //Arrow up
  setPixel(69, 25, 0);
  setPixel(70, 24, 0);
  setPixel(71, 25, 0);

  //Button 2
  setPixel(91, 22, 0);
  setPixel(92, 22, 0);
  setPixel(93, 22, 0);
  setPixel(90, 23, 0);
  setPixel(94, 23, 0);
  setPixel(89, 24, 0);
  setPixel(95, 24, 0);
  setPixel(89, 25, 0);
  setPixel(95, 25, 0);
  setPixel(89, 26, 0);
  setPixel(95, 26, 0);
  setPixel(90, 27, 0);
  setPixel(94, 27, 0);
  setPixel(91, 28, 0);
  setPixel(92, 28, 0);
  setPixel(93, 28, 0);
  //Arrow down
  setPixel(91, 25, 0);
  setPixel(92, 26, 0);
  setPixel(93, 25, 0);


  //Button 3
  setPixel(113, 22, 0);
  setPixel(114, 22, 0);
  setPixel(115, 22, 0);
  setPixel(112, 23, 0);
  setPixel(116, 23, 0);
  setPixel(111, 24, 0);
  setPixel(117, 24, 0);
  setPixel(111, 25, 0);
  setPixel(117, 25, 0);
  setPixel(111, 26, 0);
  setPixel(117, 26, 0);
  setPixel(112, 27, 0);
  setPixel(116, 27, 0);
  setPixel(113, 28, 0);
  setPixel(114, 28, 0);
  setPixel(115, 28, 0);
}



void drawObstacle(int x, int y, int type){//draw obstacle corresponding to obstacle type
  if(type == 0){ //draw nothing, null type obstacle
    setPixel(x, y, 0);
  }

  if(type == 1){
    drawCactus2(x, y);
    drawCactus1(x + 5, y);
  }

  if(type == 2){
    drawCactus2(x, y);
  }

  if(type == 3){
    drawPtero(x, y);
  }

  if(type == 4){
    drawCactus1(x, y);
  }

  if(type == 5){
    drawCactus1(x, y);
    drawCactus2(x + 5, y);
    drawCactus1(x + 10, y);
  }
}

void drawObstacles(){//draws all obstacles
  int n;
  for(n = 0; n < 8; n++){
      drawObstacle(obsX[n], obsY[n], obsType[n]);
  }
}


void randomize(){//randomizes the type and location
  static int obsIndex = 0;
  obsType[obsIndex] = (randomNr % 5) + 1;
  obsX[obsIndex] = 150 + (randomNr % 16);
  if(obsType[obsIndex] == 3){
    obsY[obsIndex] = 0 + randomNr % 20;
  }else{
    obsY[obsIndex] = 22;
  }
  obsIndex++;
  if(obsIndex >= 8){
    obsIndex = 0;
  }
}

int getbtns (void){//buttons
    return (PORTD >> 5) & 0x7;
}


void jump(){//jump function depends on buttons check
  if(grounded && !(getbtns() & 0x2)){//depends on buttons check and being grounded
    jumpVelo = -10;
    grounded = 0;
  }
}

drawPseudoBitmap(int x0, int y0, int x[], int y[], int length){//reads specific pseudo bitmaps and draws on display
	int n;
	for(n = 0; n < length; n++){
		setPixel(x0 + x[n], y0 + y[n], 0);
	}
}


drawNumber(int x, int y, int n){//reads number pseudo bitmaps and draws on display
  int length;;
  switch(n){
    case 0:
      length = 12;
      drawPseudoBitmap(x, y, pseudo0X, pseudo0Y, length);
      break;
    case 1:
      length = 8;
      drawPseudoBitmap(x, y, pseudo1X, pseudo1Y, length);
      break;
    case 2:
      length = 11;
      drawPseudoBitmap(x, y, pseudo2X, pseudo2Y, length);
      break;
    case 3:
      length = 10;
      drawPseudoBitmap(x, y, pseudo3X, pseudo3Y, length);
      break;
    case 4:
      length = 11;
      drawPseudoBitmap(x, y, pseudo4X, pseudo4Y, length);
      break;
    case 5:
      length = 13;
      drawPseudoBitmap(x, y, pseudo5X, pseudo5Y, length);
      break;
    case 6:
      length = 10;
      drawPseudoBitmap(x, y, pseudo6X, pseudo6Y, length);
      break;
    case 7:
      length = 8;
      drawPseudoBitmap(x, y, pseudo7X, pseudo7Y, length);
      break;
    case 8:
      length = 12;
      drawPseudoBitmap(x, y, pseudo8X, pseudo8Y, length);
      break;
    case 9:
      length = 10;
      drawPseudoBitmap(x, y, pseudo9X, pseudo9Y, length);
      break;

  }
}


void drawNumberLine(int x, int y, int n){//draw numbers in sequence, used for score
  int placeCount = 0;
  while(n > 0){
    drawNumber(x - placeCount, y, n % 10);
      n = floor(n / 10);
      placeCount += 5;
    }
}

void drawCharacter(int x, int y, int n){//draws single character
  int i = 0;
  for(i = 0; i < lettersLength[n]; i++){
    setPixel(x + lettersX[n][i],y + lettersY[n][i], 0);
  }
}

void drawCharacterLine(int x, int y, int letters[], int lineLength){//draws characters in sequence
  int n;
  for(n = 0; n < lineLength; n++){
    drawCharacter(x + n*6, y, letters[n]);
  }
}

void collision(){//result of collision
  int lettersGO[] = {6,0,12,4,14,21,4,17};
  drawCharacterLine(32, 1, lettersGO, 8);
  gameOver = 1;
}

void collisionCheck(int n){//math for checking collision of dinosaur with specified obstacle
  int typeSizeX;
  int typeSizeY;
  switch (obsType[n]) //sets obstacle size based on type
  {
  case 1:
    typeSizeX = 3;
    typeSizeY = 8; 
    break;
  case 2:
    typeSizeX = 3;
    typeSizeY = 8; 
    break;
  case 3:
    typeSizeX = 8;
    typeSizeY = 6; 
    break;
  case 4:
    typeSizeX = 8;
    typeSizeY = 8; 
    break;
  case 5:
    typeSizeX = 13;
    typeSizeY = 8; 
    break;
  default:
    break;
  }
  /* collisions maths */
  if((dinoX <= (obsX[n]) && (obsX[n]) <= (dinoX + dinoSizeX)) || (dinoX <= (obsX[n] + typeSizeX) && (obsX[n] + typeSizeX) <= (dinoX + dinoSizeX))){
    if((dinoY <= (obsY[n]) && (obsY[n]) <= (dinoY + dinoSizeY)) || (dinoY <= (obsY[n] + typeSizeY) && (obsY[n] + typeSizeY) <= (dinoY + dinoSizeY))){
      collision();
    }
  }
}

void collisionCheckAll(){//check all obstacles for collision, with all corners
  int n;
  for(n = 0; n < 8; n++){
      collisionCheck(n); //check dino collision with specified obst
  }
}