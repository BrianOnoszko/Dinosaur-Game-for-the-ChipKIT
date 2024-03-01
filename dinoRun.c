/* dinoFunc.c
   This file written 2023 by Isac Ljungberg and Brian Onoszko
   Some parts are original code written by F Lundevall and Ture Teknolog

   For copyright and licensing, see file COPYING */


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "dinoGame.h"  /* Declaration of header file */
#include <math.h> /* Declaration of math used for the floor function*/

//declarations of variables
int dinoX = 3; //dino x position
int dinoY = 22; //dino y position
int dinoSizeX = 8; //collider size
int dinoSizeY = 8; //collider size
int groundY = 30; //ground y position
uint8_t grounded = 1;
double jumpVelo = 0;
int obsSpeed = -5;
int randomNr = 0; //counter used to generate random values
int menu = 1;
int gameOver = 0;
int score = 0;
int frameDino = 0;
int obsDelay = 128; //delay in frames between new obstacles being randomized


int obsX[] = { //array containing the current x coordinates of obstacles
  -10, -10, -10, -10, -10, -10, -10, -10,
};

int obsY[] = { //array containing the current y coordinates of obstacles
  0,0,0,0,0,0,0,0,
};

int obsType[] = { //array containing the current types of obstacles
  0,0,0,0,0,0,0,0,
};
/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Game Initilization */
void gameInit( void )
{
  TRISD |= 0xFE0;       //equivalent to TRISDSET

  T2CON = 0x0; //stops clock
  T2CONSET = T2CONSET | 0x70; //sets prescale to 1/256
  TMR2 = 0x0; //sets current time to 0
  PR2 = 31250; //sets timer max value
  IFSCLR(0) = 0x100; //clears interrupt flag
  IECSET(0) = 0x100; //enables interrupt
  T2CONSET = 0x8000; //starts timer

  return;
}

/* This function is called repetitively from the main program */
void run( void )
{
  randomNr++; //counter used to generate random numbers

  if(IFS(0) & 0x100){ //runs during timer interrupts, main game functions
    IFSCLR(0) = 0x100; //clears interrupt flag
    TMR2 = 0x0; //resets timer

    if(menu){ //menu logic
      score = 0;
      drawMenu();
      drawDino();
      int n1;
      for(n1 = 0; n1 < 128; n1++){
        setPixel(n1, groundY, 0);
      }
      display_image(0, icon0); //displays screen data
      display_image(32, icon1);
      display_image(64, icon2);
      display_image(96, icon3);
      iconClear();
      if(getbtns() & 0x1){
        menu = 0;
      }
    }else if(gameOver){ //on gameover, freezeframe and reset values
      dinoX = 3;
      dinoY = 22;
      dinoSizeX = 8; //collider size
      dinoSizeY = 8; //collider size
      groundY = 30;
      grounded = 1;
      jumpVelo = 0;

      int i;
      for(i = 0; i < 8; i++){
        obsX[i] = -10;
        obsY[i] = 0;
        obsType[i] = 0;
      } 
      
      /* Goes back to menu when button is pressed*/
      if(getbtns() & 0x1){
        gameOver = 0;
        menu = 1;
      }
    }else{ //in game logic
      score++; //increment score each frame
      if(getbtns() & 0x4){ //jumps on button press
        jump();
      }
      if(grounded){ //while grounded sets position and velocity to ground and zero
        jumpVelo = 0;
        if(getbtns() & 0x2){ //sets ground position and hitbox size while ducking
          dinoSizeY = 5;
          dinoY = groundY - dinoSizeY;
        }else{ //while not ducking
          dinoSizeY = 8;
          dinoY = groundY - dinoSizeY;
        }
      }else{ //midair logic
        if(getbtns() & 0x2){ //fall faster while ducking
          jumpVelo += 10;
        } else { //normal fall
          jumpVelo += 2;
        }
        dinoY = (int)(dinoY + jumpVelo); //dino ascends or descends based on current velocity
      }

      if((dinoY + jumpVelo) > groundY && jumpVelo > 0){ //sets position to ground and grounded to 1 if dino would be underground next frame
        dinoY = groundY - dinoSizeY;
        grounded = 1;
      }

      int n0;
      for(n0 = 0; n0<8; n0++){ //obstacle move code, loops for each obstacle

        obsX[n0] += obsSpeed; //moves obstacle by obstacle speed
        
        static int obstacleTimer = 0;
        obstacleTimer++;
        if(obstacleTimer >= 128){ //randomizes, aka resets x value and randomizes type and position for the most distant obstacle
          randomize();
          obstacleTimer = 0;
        }
      }

      collisionCheckAll(); //checks if any obstacle is colliding with dinosaur

      int n1;
      for(n1 = 0; n1 < 128; n1++){ //draws the ground
        setPixel(n1, groundY, 0);
      }
      if(getbtns() & 0x2){//draws dino either ducking or not ducking
        drawDuck();
      }else{
        drawDino();
      }

      
      drawNumberLine(123, 1, score);
      drawObstacles();
      display_image(0, icon0); //displays screen data
      display_image(32, icon1);
      display_image(64, icon2);
      display_image(96, icon3);
      iconClear(); //clears screen data
    }
  }
}
