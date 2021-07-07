//--------------------------------------
//  CHECK FOR GAME WINNERS
//
//---------------------------------------

void check_game_winner(void) 
{
  int i,j;
  win_O_bell=0; 
  win_X_bell=0;
    
  
       for(j=0;j<3;j++)     //   tres horizontales
        {
        i=3*j;  
         if((board[i]=='O')&& (board[i+1]=='O')&&(board[i+2]=='O'))  win_O_bell=1; 
        } 
 
        
        
        for(j=0;j<3;j++)  //   tres verticales
        {
         if((board[j]=='O')&& (board[j+3]=='O')&&(board[j+6]=='O'))  win_O_bell=1; 
        } 
        
        if((board[0]=='O')&& (board[4]=='O')&&(board[8]=='O'))  win_O_bell=1; //  diagonal   0-4-8
            
        if((board[2]=='O')&& (board[4]=='O')&&(board[6]=='O'))  win_O_bell=1; //  diagonal   2-4-6
            
 
        //========  
        
          for(j=0;j<3;j++)     //   tres horizontales
        {
         i=3*j;  
         if((board[i]=='X')&& (board[i+1]=='X')&&(board[i+2]=='X'))  win_X_bell=1; 
        } 
        
        for(j=0;j<3;j++)  //   tres verticales
        {
         if((board[j]=='X')&& (board[j+3]=='X')&&(board[j+6]=='X'))  win_X_bell=1; 
        } 
        
        if((board[0]=='X')&& (board[4]=='X')&&(board[8]=='X'))  win_X_bell=1; 
            
        if((board[2]=='X')&& (board[4]=='X')&&(board[6]=='X'))  win_X_bell=1;         
       
}
//--------------------------------------


