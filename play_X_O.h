//--------------------------------------
//   play_X_O
//
//---------------------------------------

//-----------------------------------------------
void X_plays(void)            
{
    int valid = 1; //check is valid or not the positions
    char position;        
    do{
        position=getch();
        switch (position){
           case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':{
                    stringstream str;
                    str << position; int x; str >> x;
                    if(board[x]=='-'){
                                    board[x]='X';
                                    valid = 0;
                                    }
                    else{
                        moveto(100,120);  
                        settextstyle(4,0,2); 
                        setcolor(LIGHTRED);
                        outtext("You can not use this position");
                        Sleep(1000);
                        
                        plot_game_graphics();
                        moveto(260,320);  
                        settextstyle(4,0,2); 
                        setcolor(LIGHTRED);
                        outtext("Play: X");
                        
                    }   
                }
           break;   
        }        
    }while(valid);


}
//----------------------------------------------------------------
void O_plays(void)            
{
    int i;       
    do
    { 
    i=random(9);        
    if(board[i]=='-'){
                    board[i]='O';
                    break;
                    }   
    }
    while(1);
}



