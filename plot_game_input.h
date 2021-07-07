void erase_screen(void);
//-----------------------------------------------------------------------------------------
void plot_board(void)                   //          PRINT BOARD
{
      int i,x,y,x_board;   
      //char str[10];
      x_board=220;    
      y=50;
      x=x_board;

        setcolor(LIGHTGRAY);
        settextstyle(4,0,4); 
        //cout << " BOARD     "; 

        for(i=0;i<3;i++)
                {
                 if(board[i]=='-') outtextxy(x,y,"     ");   
                 if(board[i]=='O') outtextxy(x,y," O ");   
                 if(board[i]=='X') outtextxy(x,y," X "); 
                 x=x+65;    
                }  
        x=x_board;        
        y=y+60;         
        for(i=3;i<6;i++)
                {
                 if(board[i]=='-') outtextxy(x,y,"     ");   
                 if(board[i]=='O') outtextxy(x,y," O ");   
                 if(board[i]=='X') outtextxy(x,y," X "); 
                 x=x+65;    
                }          
        x=x_board;        
        y=y+60;         
        for(i=6;i<9;i++)
                {
                 if(board[i]=='-') outtextxy(x,y,"     ");   
                 if(board[i]=='O') outtextxy(x,y," O ");   
                 if(board[i]=='X') outtextxy(x,y," X "); 
                 x=x+65;    
                }       

        //line for x1, y1, x2, y2
        //horizontal
        line(210, 95, 440,95);
        line(210, 155, 440,155);

        //vertical

        line(285,40, 285,225);     
        line(353,40, 353,225);          
      
}


//------------------------------------------------------------
void plot_board_map(void)                   //          PRINT BOARD
{
 int i,x,y,x_board;   
 //char str[10];
    x_board=235;    
    y=230;
    x=x_board;
    
        setcolor(LIGHTGRAY);
        bar(x,y,x+100,y+100);
        
        //cout << " BOARD     "; 
    
        for(i=0;i<3;i++)
                {
                 if(i==0) outtextxy(x,y," 0 ");   
                 if(i==1) outtextxy(x,y," 1 ");   
                 if(i==2) outtextxy(x,y," 2 "); 
                 x=x+55;    
                }  
        x=x_board;        
        y=y+30;         
        for(i=3;i<6;i++)
                {
                 if(i==3) outtextxy(x,y," 3 ");   
                 if(i==4) outtextxy(x,y," 4 ");   
                 if(i==5) outtextxy(x,y," 5 ");  
                 x=x+55;    
                }          
        x=x_board;        
        y=y+30;         
        for(i=6;i<9;i++)
                {
                 if(i==6) outtextxy(x,y," 6 ");   
                 if(i==7) outtextxy(x,y," 7 ");   
                 if(i==8) outtextxy(x,y," 8 ");  
                 x=x+55;    
                }                      
      
}
//-


void plot_game_graphics(void)
{ 
        erase_screen();

        moveto(225,0); //Title 
        settextstyle(9,0,2); 
        setcolor(LIGHTGRAY);
        outtext("Tic Tac Toe Game");
        plot_board();
        plot_board_map();
}
