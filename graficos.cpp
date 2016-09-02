#include <allegro.h>
#include <unistd.h>

#define MAXFILAS 20
#define MAXCOLS 31


BITMAP *buffer;								//buffer de almacenamiento de todos los sprites


BITMAP *barra;								//variable para guardar imagen de la barra

BITMAP *fondo;								//variable para guardar imagen del fondo

BITMAP *bola;								//variable para guardar imagen de la bola
BITMAP *bloque0;							//variable para guardar imagen de bloque
BITMAP *bloque1;							// ''       ''            ''
BITMAP *bloque2;							// ''       ''            ''
BITMAP *bloque3;							// ''       ''            ''
BITMAP *bloque4;							// ''       ''            ''
BITMAP *borde;


BITMAP *trueno;								//variable para guardar imagen de animacion del trueno

BITMAP *boomBMP;
BITMAP *boom;
BITMAP *svida;
BITMAP *svidaBMP;


int sizescreen_x=548;						//tamano horizontal de la ventana de juego
int sizescreen_y=650;						//Tamano vertical de la ventana de juego

int mh=0;									//variable para control de movimiento horizontal de la bola
int mv=1;									//variable de control de movimiento vertical de la bola
int bpx=239;								//Variable de posicion de en x de la bola
int bpy=555-12-7;								//Variable de posicion de en y de la bola

int vbola=2;								//velocidad de la bola [pixeles/cilo]
int vbarra=4;								//velocidad de la barra [pixeles/cilo]


int dir=0;						
int px=225,py=553;							//Variable de posicion de la barra



int tr=1;									//Variable de animacion del trueno
int postrx=1;								//Posicion horizontal trueno
int postry=570;								//Posicion vertical trueno
int holdtr=0;								//Cuenta de animacion del trueno`
int veltr=40;								//Variable de velocidad de animacion del trueno

int vidas=3;									//Variable de numero de vidas

int Avidas=0;								//Variable de animacion de las vidas
int holdvidas=0;							//Cuenta de animacion de vidas
int velvidas=10;							//Variable de velocidad de animacion de vidas

int muerte=0;								//Variable de animacion del trueno
int holdmuerte=0;							//Cuenta de animacion de muerte
int velmuerte=10;							//Variable de velocidad de animacion de muerte
int ciclomuerte=0;							//Variable de control de juego (indica que perdio una vida)

char matrizbloques [21][14];

char bloquesombrilla [21][14]={
	"      D      ",
	"     EEE     ",
	"    CCACC    ",
	"   BBBABBB   ",
	"   DDDADDD   ",
	"  DDDDADDDD  ",
	"  DDDDADDDD  ",
	"      A      ",
	"      A      ",
	"      A      ",
	"      A      ",
	"      A      ",
	"    B A      ",
	"     C       ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	
};


char bloquescolumnas [21][14]={
	"             ",
	"             ",
	"     E    E  ",
	" E   E E  EE ",
	" E E E EE EE ",
	"EEEEEEEEEEEEE",
	"DDDDDDDDDDDDD",
	" DDDDDDDDDDD ",
	" DDDEDDDEDDD ",
	" DDEDEDEDEDD ",
	" DDEDDEDDEDD ",
	" DDEDDDDDEDD ",
	" DDEDDDDDEDD ",
	" DDDDDDDDDDD ",
	" DDDDDDDDDDD ",
	" DDDDDDDDDDD ",
	"             ",
	"             ",
	"             ",
	" DDDDDDDDDDD ",
	
};



char bloquesdefecto [21][14]={
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"EEEEEEEEEEEEE",
	"DDDDDDDDDDDDD",
	"CCCCCCCCCCCCC",
	"BBBBBBBBBBBBB",
	"AAAAAAAAAAAAA",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	
};





void initmatriz()
{
		for(int i=0;i<20;i++)
		{
			for(int j=0;j<13;j++)
			{
					if(i==0)
					{
							matrizbloques[i][j]='A';
					}
					else if(i==1)
					{
							matrizbloques[i][j]='B';
					}
					else if(i==2)
					{
							matrizbloques[i][j]='C';
					}
					else if(i==3)
					{
							matrizbloques[i][j]='D';
					}
					else if(i==4)
					{
							matrizbloques[i][j]='E';
					}
					else if(i==5)
					{
							matrizbloques[i][j]='E';
					}
					
					
					
			}
		
		}
	
	
}

void imprimirbloques(char matriz[21][14])
{
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<14;j++)
			{
				if(matriz[i][j]=='A')
					{
						draw_sprite(buffer,bloque0,j*39+22,i*16+23);	
					}
					
				if(matriz[i][j]=='B')
					{
						draw_sprite(buffer,bloque1,j*39+22,i*16+23);	
					}
				if(matriz[i][j]=='C')
					{
						draw_sprite(buffer,bloque2,j*39+22,i*16+23);	
					}
				if(matriz[i][j]=='D')
					{
						draw_sprite(buffer,bloque3,j*39+22,i*16+23);	
					}
				if(matriz[i][j]=='E')
					{
						draw_sprite(buffer,bloque4,j*39+22,i*16+23);	
					}
			
			
			}

		}
		
	
}


void pantalla()
{
     blit(buffer,screen,0,0,0,0,sizescreen_x,sizescreen_y);     
} 


void retraso()
{
		int x=0;
		while(x<=1000)
		{
				if(x==1000)
				{
						break;
				}
				else x++;
		}
	
}




void movimientobola()
{
		if(mh==1)//Si mh es igual a 1, la bola se mueve hacia la derecha
		{
			if(bpx+2>=sizescreen_x-33) mh=0;	
			else if((bpx+8 >=px && bpx+6 <= px) && (bpy+8>=py && bpy <= py+32))
			{
				mh=0;
			}			
			else bpx+=vbola;
		}
	
		if(mh==0)//Si mh es igual a 0, la bola se mueve hacia la izquierda
		{
			if(bpx-2<=23) mh=1;
			else if((bpx <=px+71 && bpx+5 >= px+71) && (bpy+14>=py && bpy <= py+32))
			{
				mh=1;
			}			
			else bpx-=vbola;
		}
	
		if(mv==1)//Si mv es igual a 1, la bola se mueve hacia arriba
		{
			if(bpy-2<=24) mv=0;	
			else bpy-=vbola;
		}
	
		if(mv==0)//Si mv es igual a 0, la bola se mueve hacia abajo
		{
			if(bpy>=postry-7)
			{
				mv=2;
				ciclomuerte=1;
				mh=2;
			}
			else if((bpy+10 >=py && bpy+13 <= py+5) && (bpx+14>=px && bpx <= px+64))
			{
				mv=1;
			}			
			else bpy+=vbola;
		}
		
		
		draw_sprite(buffer,bola,bpx,bpy); 
	
	
}


void init_allegro()//Funcion de inicializacion de la libreria Allegro
{
		allegro_init();
		install_keyboard();
	    set_color_depth(32);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, sizescreen_x,sizescreen_y,0,0);
	
}


void movbarra()//Funcion de movimiento e impresion de la barra
{
	
	if(key[KEY_LEFT])
             {
				 if(!(px-2<=20))				 
				  px=px-vbarra;
				 
			 }
			  if(key[KEY_RIGHT])
             {
				 if(!(px+71>=sizescreen_x-5))
				 px=px+vbarra;
				 
			 }
	 draw_sprite(buffer,barra,px,py); 
	
}



void animtrueno()//Funcion de animacion del trueno (piso)
{
	if (!(holdtr==veltr))
		{
			holdtr++;
		}
	else
		{
			if (tr==1)
				{
					trueno = load_bitmap("trueno1.bmp",NULL);
					tr = 2;
					holdtr = 0;
				}
			else if (tr==2)	
				{
					trueno = load_bitmap("trueno2.bmp",NULL);
					tr = 3;
					holdtr = 0;
				}
			else if (tr==3)
				{
					trueno = load_bitmap("trueno3.bmp",NULL);
					tr = 4;
					holdtr = 0;
				}
			else if (tr==4)
				{
					trueno = load_bitmap("trueno2.bmp",NULL);
					tr = 1;
					holdtr = 0;
				}
					
		}
	
	for (int t =0;t<30;t++)
		{
			draw_sprite(buffer,trueno,postrx+(30*t),postry);	
		}
}	


void animmuerte()
{
	if (holdmuerte == velmuerte && muerte==0)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 1;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==1)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 2;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==2)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 3;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==3)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 4;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==4)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 5;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==5)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 6;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==6)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 7;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==7)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 8;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==8)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 9;
			holdmuerte = 0;
		}			
		
	else if (holdmuerte == velmuerte && muerte==9)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 10;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==10)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 11;
			holdmuerte = 0;
		}
		
	else if (holdmuerte == velmuerte && muerte==11)
		{
			blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);
			draw_sprite(buffer,boom,bpx,bpy);
			muerte = 0;
			holdmuerte = 0;
		}
		
	else 
		{
			holdmuerte++;
			draw_sprite(buffer,boom,bpx,bpy);
		}
		
}


void comparabloques(char matriz[21][14])
{
	
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<13;j++)
			{
					
					if(mv==0)
					{
						if(bpy+8>=23+16*i && bpy+8<=23+16*i+2 && bpx>=18+39*j-1 && bpx+8<=22+39*j+39+1)
						{
							if(matriz[i][j]!=' ')
							{
								mv=1;
								matriz[i][j]=' ';
							}
					
						}
				    }		
					if(mv==1)
					{
						if(bpy<=23+16+16*i && bpy>=23+4+16*i && bpx>=18+39*j && bpx+8<=22+39*j+39)
						{
							if(matriz[i][j]!=' ')
							{
								mv=0;
								matriz[i][j]=' ';
							}
					
						}
					}
			
			//////////////////////////////////////////////////
					if(mh==0)
					{
						if(bpy+8>=23+16*i && bpy<=23+16*i+16 && bpx<=18+39*j+39 && bpx>=18+39*j)
						{
							if(matriz[i][j]!=' ')
							{
								mh=1;
								matriz[i][j]=' ';
							}
					
						}
				    }		
					 if(mh==1)
					{
						if(bpy+8>=23+16*i && bpy<=23+16*i+16 && bpx+8>=18+39*j && bpx+8<=18+39*j+1)
						{
							if(matriz[i][j]!=' ')
							{
								mh=0;
								matriz[i][j]=' ';
							}
					
						}
					}
			
			}
	
		}
	
	
	
	
}


void cargar(char matriz_in[21][14],char matriz_out[21][14])
{
	
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<14;j++)
			{
				matriz_out[i][j]=matriz_in[i][j];			
			
			}

		}
	
}


void animvidas()
{
	if (holdvidas == velvidas && Avidas==0)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 1;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==1)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 2;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==2)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 3;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==3)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 4;
			holdvidas = 0;
		}
	
	else if (holdvidas == velvidas && Avidas==4)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 5;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==5)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 6;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==6)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 7;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==7)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 8;
			holdvidas = 0;
		}		
		
	else if (holdvidas == velvidas && Avidas==8)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 9;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==9)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 10;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==10)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 11;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas && Avidas==11)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 12;
			holdvidas = 0;
		}
		
	else if (holdvidas == velvidas*4 && Avidas==12)
		{
			blit(svidaBMP,svida,(-2+62)*Avidas,0,0,0,62,25);
			draw_sprite(buffer,svida,106,610);
			Avidas = 0;
			holdvidas = 0;
		}
		
	else holdvidas++;						
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() 
{
		init_allegro();										//Funcion que inicia las funciones de allegro
		     
        buffer=create_bitmap(sizescreen_x,sizescreen_y);	//Creacion de espacio de juego
        fondo = load_bitmap("fondo.bmp",NULL);				//^
        borde = load_bitmap("borde.bmp",NULL);				//^
        barra = load_bitmap("barra.bmp",NULL);				//^
        bola = load_bitmap("BolaR.bmp",NULL);				//^
        bloque0 = load_bitmap("bloque0.bmp",NULL);			//^
        bloque1 = load_bitmap("bloque1.bmp",NULL);			//^
        bloque2 = load_bitmap("bloque2.bmp",NULL);			//^
        bloque3 = load_bitmap("bloque4.bmp",NULL);			//^
        bloque4 = load_bitmap("bloque3.bmp",NULL);			//^
        trueno = load_bitmap("trueno1.bmp",NULL);			//^
        boomBMP = load_bitmap("explosion.bmp",NULL);		//^
        boom = create_bitmap(14,14);						//^
        svidaBMP = load_bitmap("vida.bmp",NULL);			//^
        svida = create_bitmap(62,25);						//Carga de imagenes en los bitmaps declarados
        
        blit(svidaBMP,svida,(-2+62)*12,0,0,0,62,25);		//Corte de BMP para imprimir seccion especifica
		draw_sprite(buffer,svida,106,610);					//Carga de corte del BMP
		blit(boomBMP,boom,0+14*muerte,0,0,0,14,14);			//Corte de BMP para imprimir seccion especifica
		draw_sprite(buffer,boom,bpx,bpy);					//Carga de corte del BMP
		
        
        
		cargar(bloquesdefecto,matrizbloques);				//Funcion para cargar matriz de juego temporal desde
															//otra matriz de chars declarada
		
     
     ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
     while (vidas != 0)						//Juego (Contiene el juego principal y el ciclo de vidas)
     {
		 vidas--;							//Reduccion de vida
		 px=225;							//Posicion inicial barra
		 bpx=239;							//Regresa la bola a su posicion inicial 								
		 bpy=555-12-7;						//""
		 ciclomuerte=0;						//Reinicia condicion de variables del ciclo de juego
		 muerte = 0;						//""
		 mv = 0;							//""
		 mh = 0;							//""
		 
		 while (!key[KEY_X])	//////////////////////////////////////////////////////////////////////Pausa entre vidas
		 {
			 draw_sprite(buffer,fondo,0,0); 	//Se dibuja la imagen de fondo en el buffer
			 animtrueno();						//Funcion de animacion del trueno
			 draw_sprite(buffer,borde,0,0);		//Dibuja el borde en el buffer
			 movbarra();						//Funcion de movimiento y actualizacin de barra
			 draw_sprite(buffer,bola,px+27-5,555-10);	//Imprime en buffer el sprite de la bola sobre la barra
			 bpx=px+27-5;						//Actualiza la posicion de la bola sobre la barra
			 draw_sprite(buffer,svida,106,610);	//Imprime en buffer la animacion de las vidas
			 imprimirbloques(matrizbloques);	//Imprime en buffer la matriz de bloques actualizada
			 animvidas();						//Funcion de animacion de contador de vidas
			 draw_sprite(buffer,svida,106,610);	//Imprime en buffer la animacion de las vidas
			 pantalla();						//Actualiza la pantalla con el contenido del buffer
			 clear(buffer);						//Se limpia los contenidos del buffer
			 usleep(7000);						//Ciclo de retraso (se debe cambiar el valor dependiendo del hardware)
			 
		 }
		 
        while(!key[KEY_ESC] && ciclomuerte==0) ////////////////////////////////////////////////////////Ciclo de juego
        {
             
              
             if (key[KEY_G])					//Activacion de modo rastreo (para propositos de pruebas de bugs)
             {
				 px=bpx-27+5;					//La posicion de la barra siempre estara por debajo de la bola
			 }
			 
			 
             draw_sprite(buffer,fondo,0,0); 	//Se dibuja la imagen de fondo en el buffer
             comparabloques(matrizbloques);		//Funcion de verificacion de choques
             
             
             animtrueno();						//Funcion de animacion del trueno
             draw_sprite(buffer,borde,0,0);		//Dibuja el borde en el buffer	 
             movbarra();						//Funcion de movimiento y actualizacin de barra
             movimientobola();					//Funcion de movimiento y actualizacin de bola
             imprimirbloques(matrizbloques);	//Imprime en buffer la matriz de bloques actualizada
             animvidas();						//Funcion de animacion de contador de vidas
             draw_sprite(buffer,svida,106,610);	//Imprime en buffer la animacion de las vidas
             
             pantalla();						//Actualiza la pantalla con el contenido del buffer
             usleep(7000);						//Ciclo de retraso (se debe cambiar el valor dependiendo del hardware)
             clear(buffer);						//Se limpia los contenidos del buffer
                                       
             
        }
        
        
        while (muerte != 11) /////////////////////////////////////////////////////////////////////////Ciclo de muerte
        {
			draw_sprite(buffer,fondo,0,0); 		//Se dibuja la imagen de fondo en el buffer
			animtrueno();						//Funcion de animacion del trueno
			draw_sprite(buffer,borde,0,0);		//Dibuja el borde en el buffer	
			draw_sprite(buffer,svida,106,610); 	//Imprime en buffer la animacion de las vidas
			imprimirbloques(matrizbloques);		//Imprime en buffer la matriz de bloques actualizada
			movbarra();							//Funcion de movimiento y actualizacin de barra
			animmuerte();						//Funcion de la animacion de muerte
			
			pantalla();							//Actualiza la pantalla con el contenido del buffer
			usleep(5000);						//Ciclo de retraso (se debe cambiar el valor dependiendo del hardware)
			clear(buffer);						//Se limpia los contenidos del buffer
		}
	}	
}
END_OF_MAIN()

