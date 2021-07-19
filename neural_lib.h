//============================================================================
//    Constantes  
//============================================================================
#define N_IN    27       // Numero de neurona de entrada  9 cuadros x tres entradas
#define N_HID   41       // NEURONAS ESCONlDIDAS
#define N_OUT   9        // NEURONAS SALIDAS 
 
//   Brand new copy July 17, 2021 
//=======================================================================================================================
//  DEFINICION DE ESTRUCTURA DE LA Red
//=======================================================================================================================
float  Mid=0.5,            Eta=0.25,            Gain=1.5;  //1.50;  //Eta anterior 0.25
float  alfa=0.5;
int  four,xtal, five;
float Target[N_OUT];
float counselor_out[N_OUT];     //   new dec 2018
float Entrada[N_IN];

struct  capa_salida
	  {
	   float  pesos[N_OUT][N_HID];
	   float  error[N_OUT];
       float  moment[N_OUT][N_HID];   
	   float  out[N_OUT];
      } c_salida;

struct  capa_escondida
	  {
	   float  pesos[N_HID][N_IN];
	   float  error[N_HID];
       float  moment[N_HID][N_IN];   
	   float  out[N_HID];
      } c_escondida;

//===========================================================================================================================
//  RUTINAS DE CALCULO DE LA RED
//===========================================================================================================================

float peso_aleatorio(void)
{
  float tmp;
  tmp=random(100);      // original 100
  tmp=(tmp-50)/100;    // original 100
  return tmp;
}
//----------------------------------

//-------------------------------------
void inicializar_pesos(void)
{
   int k,i;
  // Inicializacion de pesos para la capa escondida
    for (k=0; k<N_HID ;k++)
    for (i=0; i<N_IN; i++)
    {
      c_escondida.pesos[k][i]=peso_aleatorio();
    }    
        
  // Inicializacion de pesos para la capa de salida      
  for (k=0; k<N_OUT; k++)
    for (i=0; i<N_HID; i++)
    { 
      //c_salida.pesos[k][i]=0;  
      c_salida.pesos[k][i]=peso_aleatorio();
    }  
}
//------------------------------------
void limpiar_pesos(void)
{
   int k,i;
  // Limpiar de pesos para la capa escondida
    for (k=0; k<N_HID ;k++)
    {
        //xtal=0;    
        for (i=0; i<N_IN; i++)
        {
          //c_escondida.pesos[k][i]=peso_aleatorio()*0.0;
          c_escondida.pesos[k][i]=0;
          //pump_xtal();    
        }    
    }    
}
//------------------------------------
void corregir_pesos_all(void)
{
  int k,i;
  float sum;

  // Calculo de error para la capa de salida
  for (k=0; k<N_OUT; k++)
	c_salida.error[k]=c_salida.out[k]*(1-c_salida.out[k])*(Target[k]-c_salida.out[k]);

  // Calculo de error para la capa escondida
  for (k=0; k<N_HID; k++)
  {
    sum=0;
    for (i=0; i<N_OUT; i++)
      sum=sum+c_salida.error[i]*c_salida.pesos[i][k];
      c_escondida.error[k]=c_escondida.out[k]*(1-c_escondida.out[k])*sum;
  }

  // Correccion de pesos para la capa de salida
  float delta;
  for (k=0; k<N_OUT; k++)
    for (i=0; i<N_HID; i++)
    { 
      delta=Eta*c_salida.error[k]*c_escondida.out[i];  
      c_salida.pesos[k][i]=c_salida.pesos[k][i]+delta+(alfa*c_salida.moment[k][i]); 
      c_salida.moment[k][i]=delta;    
    }
  // Correccion de pesos para la capa escondida */
    five=0;
    for (k=0; k<N_HID; k++)
    for (i=0; i<N_IN; i++)
    { 
      delta=Eta*c_escondida.error[k]*Entrada[i]; 
      c_escondida.pesos[k][i]= c_escondida.pesos[k][i]+delta+(alfa*c_escondida.moment[k][i]);
      c_escondida.moment[k][i]=delta;
    } 
   
}
//-------------------------------------
float sigmoide(float x)
{
  float out;

  if (x>30) x=30;
  if (x<-30) x=-30;
  out=pow((1+exp(-Gain*x)),-1);
  return(out);
}

//-------------------------------------
void calcular_capa_escondida(void)
{
  int k,i;
  xtal=0;
  for (k=0; k<N_HID; k++)
   {
    c_escondida.out[k]=0;
    for (i=0; i<N_IN; i++)
        {
         c_escondida.out[k]=c_escondida.out[k]+c_escondida.pesos[k][i]*Entrada[i];
            
        }
    c_escondida.out[k]=sigmoide(c_escondida.out[k]);
    }
}

//-------------------------------------
void calcular_capa_salida(void)
{
  int k,i;
  xtal=0;
  for (k=0; k<N_OUT; k++)
  {
    c_salida.out[k]=0;
    for (i=0; i<N_HID; i++)
        {
            c_salida.out[k]=c_salida.out[k]+c_salida.pesos[k][i]*c_escondida.out[i];
        }
    c_salida.out[k]=sigmoide(c_salida.out[k]);
        
    // if(k==4) c_salida.out[k]=0;    //   OJO Aberrante                 ! ! ! 
        
    //counselor_out[k]= c_salida.out[k];           //  OJO COPIA DE OUT`s  en counselor    
    //if(c_salida.out[k]<0.1) c_salida.out[k]=0.1;  
        
  }
  
}

//-------------------------------------
void Backpropagation(void)
{
    calcular_capa_escondida();
    calcular_capa_salida();
    //corregir_pesos(0);
}
//-------------------------------------
//-------------------------------------
void inyectar_ruido_pesos(void)
{
   int k,i,dice;
   float tmp; 
  // Inyeccion de ruido para pesos de la capa escondida
    for (k=0; k<N_HID ;k++)
    for (i=0; i<N_IN; i++)
    {
      dice=random(10);
      if(!dice) 
      {
        tmp=random(100);      
        tmp=(tmp-50)/100;  //    tmp entre +0.05 y -0.05
        c_escondida.pesos[k][i]=tmp;     //c_escondida.pesos[k][i]+tmp;
      }    
    }    
        
  // Inyeccion de ruido para pesos para la capa de salida      
  for (k=0; k<N_OUT; k++)
  for (i=0; i<N_HID; i++)
    { 
      dice=random(10);
      if(!dice) 
      {
        tmp=random(100);      
        tmp=(tmp-50)/100;  //    tmp entre +0.05 y -0.05
        c_salida.pesos[k][i]=tmp; //c_salida.pesos[k][i]+tmp;
      }    
 
    }  
}
//------------------------------------
//===========================



