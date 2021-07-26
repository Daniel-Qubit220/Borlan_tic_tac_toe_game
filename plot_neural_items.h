//--------------------------------
// plot_neural_items
//
//----------

void plot_inputs(void)
{
	int y,x,i,temp;
	x=10;
	y=120;
    
    setcolor(BLACK); //Erase old inputs
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y-1,x+140,y-bars_scale); 
    
    setcolor(WHITE); //Draw the white line
    line(x,y,x+130,y);    
     
	for(i=0;i<N_IN;i++){ //Draw the 24 inputs of the Neural Network
		setfillstyle(SOLID_FILL,LIGHTGREEN);     //                                                                                        PLOT outputs  !!
		temp=Entrada[i]*bars_scale;              
		bar(x,y,x+3,y-temp);  
		x=x+5;         
	}    
}
//----------------------------------------------------------            
void plot_hidden_outputs(void)
{
	int y,x,i,temp;
	x=10;
	y=180; 

	setcolor(BLACK); //Erase old hidden outputs 
	setfillstyle(SOLID_FILL,BLACK);
	bar(x,y-1,x+200,y-bars_scale);  

	setcolor(WHITE);//Draw the white line
	line(x,y,x+165,y); 

	for(i=0;i<N_HID;i++){
		setfillstyle(SOLID_FILL,BROWN); //PLOT HIDDEN Outputs!!
		if(b_flag) setfillstyle(SOLID_FILL,LIGHTRED); ;               
		temp=c_escondida.out[i]*bars_scale;              
		bar(x,y,x+2,y-temp); 
		x=x+4;            
	}   
}
//----------------------------------------------------------            
void plot_outputs(void)
{
	int y,x,i,temp;
	x=10;
	y=240;

	setcolor(BLACK); //Erase old outputs plot         
	setfillstyle(SOLID_FILL,BLACK);
	bar(x,y-1,x+200,y-bars_scale);  


	setcolor(WHITE); //Draw the white line
	line(x,y,x+130,y);  

	for(i=0;i<N_OUT;i++){
		setfillstyle(SOLID_FILL,LIGHTCYAN);     //                                                                                        PLOT outputs  !!
		temp= c_salida.out[i]*bars_scale;              
		bar(x,y,x+3,y-temp);
		x=x+10;           
	}   
  
}
//---------------------------------------------------------------------------------------
void plot_targets(void)
{
	int y,x,i,temp;

	x=10;
	y=300; 

	setcolor(BLACK); // Erase old targets plot
	setfillstyle(SOLID_FILL,BLACK);
	bar(x,y-1,x+200,y-bars_scale);   

	setcolor(WHITE); //Draw white line
	setlinestyle(SOLID_LINE,0,0);   
	line(x,y,x+130,y);     
	for(i=0;i<N_OUT;i++){
		setcolor(BLUE);  //Plot targets
		temp= Target[i]*bars_scale;
		cout<<Target[i]<<" ";              
		bar(x,y,x+3,y-temp);         
		x=x+10;           
	}
	cout<<endl;

}
//-------------------------------------------------------------

//---------------------------------------------------------------------------------------
void plot_hidden_weights(void)                           ////       PLOT HIDDEN WEIGHTS
{
	int i,j,sx,sy,x,y,color,scale; 
	float timp;   
	    
	x=475;
	scale=4;    
   
	for(j=0;j<N_IN;j++){ 
		y=30; 
		sx = x+j*scale;             //   pesos[N_HID_1][N_IN];
		for(i=0;i<N_HID;i++){    
			sy = y+i*scale;
			timp=c_escondida.pesos[i][j];  
			color=LIGHTGRAY; 
			if(timp<-0.001) color=BLUE;        // fROZEN
			if(timp>0.001) color=RED;          // HOT !     
			setcolor(color); 
			setfillstyle(SOLID_FILL,color); 
			bar(sx,sy,sx+scale,sy+scale) ;      
			y++;  
		}
		x++;  
	} 
}
