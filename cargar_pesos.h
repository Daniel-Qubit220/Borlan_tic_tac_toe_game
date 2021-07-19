
//================================================================================================================

int CargarPesos(void)
{
	int k, i, aux;
	float numero;
	FILE *in_file;
	aux=0;
	if ((in_file = fopen ("net_hid_weights.dat", "rt")) == NULL)
		aux=1;
	else
	{
		fseek(in_file, 0, SEEK_SET);
		for (k=0; k<N_HID; k++)
			for (i=0; i<N_IN; i++)
			{
				fscanf(in_file, "%f", &numero);
				c_escondida.pesos[k][i]=numero;
			}
	}
	fclose(in_file);
	if ((in_file = fopen ("net_out_weights.dat", "rt")) == NULL)
		aux=aux+2;
	else
	{
		fseek(in_file, 0, SEEK_SET);
		for (k=0; k<N_OUT; k++)
			for (i=0; i<N_HID; i++)
			{
				fscanf(in_file, "%f", &numero);
				c_salida.pesos[k][i]=numero;
			}
	}
	fclose (in_file);
	
    moveto(420,445);
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    outtext("Pesos Cargados");
    return(aux);
}
//-----------------------------------------------
int SalvarPesos(void)
{
	int k, i, aux;
	float numero;
	FILE *out_file;
	aux=0;
	if ((out_file = fopen ("net_hid_weights.dat", "wt")) == NULL)
		aux=1;
	else
	{
		fseek(out_file, 0, SEEK_SET);
		for (k=0; k<N_HID; k++)
			for (i=0; i<N_IN; i++)
			{
				numero=c_escondida.pesos[k][i];
				fprintf(out_file, "%f %c", numero,'\n');
			}
		  }
	if ((out_file = fopen ("net_out_weights.dat", "wt")) == NULL)
		aux=aux+2;
	else
	{
		fseek(out_file, 0, SEEK_SET);
		for (k=0; k<N_OUT; k++)
			for (i=0; i<N_HID; i++)
			{
              numero=c_salida.pesos[k][i];
              fprintf(out_file, "%f %c", numero, '\n');
			}
    }
	fclose(out_file);
    moveto(300,20);
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    outtext("Pesos Salvados ");
	return(aux);
}

//-----------------------------------------------
