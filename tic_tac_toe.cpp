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
char board_temp[9];
int  moves_counter; //Cout all moves, max moves 9
int player_selector;  //Chose a player
int win_O_bell; //If win O; = 1
int win_X_bell;// If win X; = 1
int b_flag;//Flag to do back propagation
int q_flag;//Flag to make agent to use the neural network's outputs
int stop;
int max_moves=8;
int last_O_move;
int backpro_count;
int play_order[9];
int bars_scale =50;

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

#include "neural_lib_mmt.h"
#include "plot_neural_items.h"
#include "plot_game_board.h"
#include "play_X_O.h"
#include "check_game_win.h"

#include "cargar_pesos.h"

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

void init_game_var (void){
    moves_counter=0; //Start in 0 moves
    player_selector=random(2);  //play O o X
    //No one win the game
    win_O_bell=0; 
    win_X_bell=0; 

    clean_board(); 
}

void end_game(void)                   //       ---------------->       END GAME
{   
    if (!b_flag){
    moveto(425,110);  
    settextstyle(4,0,4); 
    setcolor(LIGHTBLUE);
    outtext("No Winner");
    }
    else{
        init_game_var();
    }
}

void fill_board_noise(void)                                    
{
   int i,j;
   for (i=0; i<9;i++) 
   {
    j=random(4); 
    if(j==0) board[i]='-';
    if(j==1) board[i]='-';
    if(j==2) board[i]='O';       //  O
    if(j==3) board[i]='X';       // X
   }  
   for(i=0;i<N_OUT;i++) Target[i]=0.1;   
}

void end_game_win_X(void)                   //       ---------------->       END GAME
{   
    if (!b_flag){
    moveto(425,110);  
    settextstyle(4,0,4); 
    setcolor(LIGHTBLUE);
    outtext("Win X");
    }else{
        init_game_var();
    }
}

void end_game_win_O(void)                   //       ---------------->       END GAME
{   
    if (!b_flag){
    moveto(425,110);  
    settextstyle(4,0,4); 
    setcolor(LIGHTBLUE);
    outtext("Win O");
    }else{
        init_game_var();
    }
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
//-----------------------------------------------------------

void max_reward(void)
{
    board[last_O_move]='-';
    Target[last_O_move]=1.0;  
    fill_inputs();
    feed_forward();    
    
    fill_board_noise();
    Target[last_O_move]=0.1;
    fill_inputs();
    feed_forward();
    //getch(); 
}

//-----------------------------------------------------------
void O_explore(void)                                    
{
 int i,j,c=0;
//  last_O_move=O_last_move;  
  for(i=0;i<9;i++)        //    explora todos los cuadros
  {
    if(board[i]=='-')     //  se buscan cuadros vacios
         {
          board[i]='O';   //  se coloca una O para explorar
          check_game_winner(); //  se consulta a la red previamente entrenada
          if(win_O_bell)       //  se econtro un MAX
             {
              for (j=0;j<N_OUT;j++) Target[j]=0.0;  // se limpian todos los targets
              board[i]='-';            //  se limpia el tablero de la jugada de exploracion
              Target[i] = 1.0;
              fill_inputs();
              feed_forward();    
            
              for (j=0;j<9;j++) board_temp[j]=board[j]; //se recupera
              fill_board_noise();
              Target[i]=0.1;
              fill_inputs();
              feed_forward();
              for (j=0;j<9;j++)
              board[j]=board_temp[j];
              
              if (c==0){
                  board[last_O_move]='-';  //  se limpia el tablero de la ultima jugada de O
                  for (j=0;j<N_OUT;j++) Target[j]=0.0;  // se limpian todos los targets
                  Target[last_O_move]=0.8;   // se apunta a la ultima jugada de O que condujo a big reward

                  fill_inputs();
                  feed_forward();
                  
                  //noise balance begins
                  for (j=0;j<9;j++) board_temp[j]=board[j]; // se recupera
                  fill_board_noise();
                  
                  Target[last_O_move]=0.1;
                  fill_inputs();
                  feed_forward();
                  for (j=0;j<9;j++)
                  board[j]=board_temp[j];
                  board[last_O_move]='O';
                  c++;
              }
             }
          board[i]='-';         
        }
  }
}
//-----------------------------------------------------------
void train(void){
    printf("Training\n");
    init_game_var();
    while(1)
    {  
     player_selector=player_selector^1;   // se alternan los jugadores      
    
     if(player_selector)  {
                           if(b_flag) O_explore();
                           O_plays();
                          }
                    
     if(!player_selector) {
                            X_plays_aut();
                          }                                   
    
     check_game_winner();

     plot_train_game_graphics();

    if(win_O_bell)
    {
        cout << "last_O_move  " << last_O_move << endl;
        max_reward();
    }
    
     moves_counter++;      
     
     if (moves_counter>max_moves) {end_game();}
     plot_train_game_graphics();
     
     if(win_O_bell) end_game();
     if(win_X_bell) end_game();
         
     if(stop) {
         b_flag=b_flag^1;
         break;
    };
     if(kbhit()) {
         b_flag=b_flag^1;
         break;    
     }
    }
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
    
    randomize();
    start_game();          //Start window
    b_flag=0;
    q_flag=0;
    stop=1;
    
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
                                stop=stop^1;
                                b_flag=b_flag^1;
                                train();
                                
                              }
           break;   
           case 'e': case 'E':{//exit
                                erase_screen();
                                start_game();
           }
           break;
           case 'c': case 'C':{
                                CargarPesos();
                                printf("pesos cargados\n");
           }
           break;
           case 'R': case 'r':  {
                                   inicializar_pesos();
                                   backpro_count=0;
                                 }
            break;
            case 'g': case 'G': {
                                SalvarPesos();
                                }
	       break; 
           case ' ':          {                     //-------    HERE  ! !!!!!!!!!!!!!!!!         !!!!!!!!!!!!1
                                stop=stop^1;
            }
            case 'q': case 'Q':  {
                                q_flag=q_flag^1;
            }
         }
   } while ((key!='x')&&(key!='X'));
   closegraph();
   clrscr();
}