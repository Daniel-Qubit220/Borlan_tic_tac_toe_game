/************************ tic_tac_toe.cpp **********************************

Deep Reinforcement Learning  
Program to apply Q learning to Neural ambientes

By:

Carlos Macancela
Krishna Roman
Washington Pijal

Julio 3, 2021 

/*********************************************************************/               
//----------------------------------------------
// GLOBALS
#define f_dimension     9   //   tamaño del agente, cuantos comportamientos participan 
char key; //To read the inputs of the keyboard
char board[9];//The game board
int  moves_counter; //Cout all moves, max moves 9
int player_selector;  //Chose a player
int win_O_bell; //If win O; = 1
int win_X_bell;// If win X; = 1

//----------------------------------------)))
//    end globals
//----------------------------------------)))
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip.h>
#include <windows.h>
#include <string>
#include <sstream>

#include "plot_game_board.h"
#include "play_X_O.h"
#include "check_game_win.h"

/******************* variables globales *********************/
using namespace std;


//-------------------------------------
//    inicia el modo grafico             
//-------------------------------------    
void grafico(void)
{
    int    GraphDriver;  /* The Graphics device driver */
    int    GraphMode;    /* The Graphics mode value */
    int    ErrorCode;    /* Reports any graphics errors */
   
    initgraph(&GraphDriver, &GraphMode, "");

    ErrorCode = graphresult();            /* Read result of initialization*/
    if( ErrorCode != grOk )              /* Error occured during init    */
    {
       printf(" Graphics System Error: %s", grapherrormsg( ErrorCode ) );
       exit( 1 );
    }
}

//-------------------------------------  
void erase_screen(void)
{
    setcolor(BLACK);  
    setfillstyle(SOLID_FILL,BLACK);     
    bar(0,0,1400,900);         //  200   150   303   253
    floodfill(255,205,BLACK);    
}
   
//------------------------------------------------------

void start_game(void){

    moveto(15,150);  //Welcome message
    settextstyle(4,0,4); 
    setcolor(GREEN);
    outtext("Welcome to a Tic Tac Toe");

    moveto(270,200);  
    settextstyle(4,0,4); 
    setcolor(GREEN);
    outtext("Game");

    moveto(75,250);  
    settextstyle(4,0,2); 
    setcolor(GREEN);
    outtext("S: Start");


    moveto(200,250);  
    settextstyle(4,0,2); 
    setcolor(GREEN);
    outtext("T: Train");

    moveto(325,250);  
    settextstyle(4,0,2); 
    setcolor(GREEN);
    outtext("C: Load Weights");
}
void clean_board(void)
{ 
  int i;
  for (i=0; i<9;i++)   board[i]='-';     
}

void end_game(void)                   //       ---------------->       END GAME
{   
 //init_game(); 
    moveto(255,110);  
    settextstyle(4,0,4); 
    setcolor(LIGHTBLUE);
    outtext("No Winner");

}

void end_game_win_X(void)                   //       ---------------->       END GAME
{   
 //init_game(); 
    moveto(260,110);  
    settextstyle(4,0,4); 
    setcolor(LIGHTBLUE);
    outtext("Win X");

}

void end_game_win_O(void)                   //       ---------------->       END GAME
{   
 //init_game(); 
    moveto(260,110);  
    settextstyle(4,0,4); 
    setcolor(LIGHTBLUE);
    outtext("Win O");

}
void init_game_var (void){
    moves_counter=0; //Start in 0 moves
    player_selector=random(2);  //play O o X
    //No one win the game
    win_O_bell=0; 
    win_X_bell=0; 

    clean_board(); 
}

void loop(void){
    init_game_var();             //Initialize all global variables
    plot_game_graphics();
    while(1)
    {  
        player_selector=player_selector^1;   // se alternan los jugadores      
             
        if(player_selector) {
            moveto(260,320);  
            settextstyle(4,0,2); 
            setcolor(LIGHTRED);
            outtext("Play: O");
            Sleep(1000);
            O_plays();
        }  
                    
        if(!player_selector) {
            moveto(260,320);  
            settextstyle(4,0,2); 
            setcolor(LIGHTRED);
            outtext("Play: X");
            X_plays();
        }                                   
        check_game_winner();     //Check Game winner
                          
        moves_counter++;                          
        plot_game_graphics();

        if(win_O_bell) {end_game_win_O();break;}
        if(win_X_bell) {end_game_win_X();break;} 
        if (moves_counter>8) {end_game();break;}        
    }      
        
}

void train(void){
    printf("Training\n");
    Sleep(2000);
    printf("End training, ready to play\n");
}


//===================================================================================================
void main(void)
{    
    clrscr();                   // limpia la pantalla
    grafico();                  // prepara modo grafico   
    cleardevice();              // limpia la pantalla windows
    setcolor(BLACK);
    bar(0,0,1400,900);  

    start_game();          //Start window
    
    
    do {
        //
       key=getch();
       switch (key) {
           case 's': case 'S':{
                                printf("start_game\n");
                                loop();
                              }
           break;   
           case 't': case 'T':{
                                train();
                                
                              }
           break;   
           case 'e': case 'E':{//exit
                                erase_screen();
                                start_game();
           }
           break;
           case 'c': case 'C':{
                                
                                printf("pesos cargados\n");
           }
           break;                
         }
   } while ((key!='x')&&(key!='X'));
   closegraph();
   clrscr();
}