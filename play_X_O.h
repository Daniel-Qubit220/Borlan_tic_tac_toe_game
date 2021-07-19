//--------------------------------------
//   play_X_O
//
//---------------------------------------
void fill_inputs(void) //CARGA TABLERO EN ENTRADA DE RED
{
 int i,j;

 // k=image_in_use;
    //{        
     for(j=0;j<9;j++)
        {
        i=3*j;  
        if(board[j]=='O') {Entrada[i]=0;Entrada[i+1]=0;Entrada[i+2]=1;} // 1 a la derecha para O 
        if(board[j]=='-') {Entrada[i]=0;Entrada[i+1]=1;Entrada[i+2]=0;} // 1 al centro par -  
        if(board[j]=='X') {Entrada[i]=1;Entrada[i+1]=0;Entrada[i+2]=0;} // 1 a la izquierda para X 
        }
    //}    
}
//--------------------------------------------------------------
void feed_forward(void)             //LA RED PROCESA 
{
    Gain=0.5;                            //       GAIN HIDDEN  0.5                                                                                                 //    GAIN   SETTING
    calcular_capa_escondida();
    Gain=1.5;                            //       Use to be 1.5
    calcular_capa_salida(); 
    
       
    if(b_flag){
        corregir_pesos_all();
        backpro_count++;
        }
}
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

void X_plays_aut(void)
{   int i;  
    do
    { 
    i=random(9);        
    if(board[i]=='-'){
                    board[i]='X';
                    play_order[moves_counter]=i;
                    break;
                    }   
    }
    while(1);
}

//----------------------------------------------------------------
void O_plays(void)            
{
    int i;
    if (!q_flag){
        do
        { 
        i=random(9);        
        if(board[i]=='-'){
                        board[i]='O';
                        play_order[moves_counter]=i;
                        last_O_move=i;
                        break;
                        }   
        }
        while(1);
        fill_inputs();
    }else{
        int index = 0;
        float max = 0.0;
        for (int i=0;i<9;i++){
            if (board[i]=='-' && c_salida.out[i]>max){
                max = c_salida.out[i];
                index=i;
                //printf("c_salida.out[%i]: %f ",i,c_salida.out[i]);       borrar
            }
        }
    //     printf("%s","\n");           borrar
        board[index]='O';
        play_order[moves_counter]=index;
        last_O_move=index;
        fill_inputs();
    }
    fill_inputs();
    if (!b_flag) feed_forward();
}




