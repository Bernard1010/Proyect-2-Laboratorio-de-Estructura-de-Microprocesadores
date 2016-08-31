#include <allegro.h>
#include <unistd.h>



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


int sizescreen_x=700;						//tamano horizontal de la ventana de juego
int sizescreen_y=1000;						//Tamano vertical de la ventana de juego

int mh=0;									//variable para control de movimiento horizontal de la bola
int mv=1;									//variable de control de movimiento vertical de la bola
int bpx=650;								//Variable de posicion de en x de la bola
int bpy=650;								//Variable de posicion de en y de la bola

int vbola=2;								//velocidad de la bola [pixeles/cilo]
int vbarra=3;								//velocidad de la barra [pixeles/cilo]


int dir=0;						
int px=350,py=800;							//Variable de posicion de la barra



int tr=1;									//Variable de animacion del trueno
int postrx=1;								//Posicion horizontal trueno
int postry=850;								//Posicion vertical trueno
int holdtr=0;								//Cuenta de animacion del trueno
int veltr=40;								//Variable de velocidad de animacion del trueno

//char matrizbloques [21][14];
char matrizbloquesombrilla [21][14]={
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




char matrizbloques [21][14]={
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

void imprimirbloques()
{
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<14;j++)
			{
				if(matrizbloques[i][j]=='A')
					{
						draw_sprite(buffer,bloque0,j*50+25,i*22+36);	
					}
					
				if(matrizbloques[i][j]=='B')
					{
						draw_sprite(buffer,bloque1,j*50+25,i*22+36);	
					}
				if(matrizbloques[i][j]=='C')
					{
						draw_sprite(buffer,bloque2,j*50+25,i*22+36);	
					}
				if(matrizbloques[i][j]=='D')
					{
						draw_sprite(buffer,bloque3,j*50+25,i*22+36);	
					}
				if(matrizbloques[i][j]=='E')
					{
						draw_sprite(buffer,bloque4,j*50+25,i*22+36);	
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
			else if((bpx+14 >=px && bpx+9 <= px) && (bpy+14>=py && bpy <= py+32))
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
			if(bpy-2<=30) mv=0;	
			else bpy-=vbola;
		}
	
		if(mv==0)//Si mv es igual a 0, la bola se mueve hacia abajo
		{
			if(bpy>=845)
			{
				mv=1;
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
				 if(!(px-2<=26))				 
				  px=px-vbarra;
				 
			 }
			  if(key[KEY_RIGHT])
             {
				 if(!(px+71>=sizescreen_x-26))
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


void comparabloques()
{
	
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<13;j++)
			{
					
					if(mv==0)
					{
						if(bpy+14>=36+22*i && bpy<=36+2+22*i && bpx>=24+50*j && bpx+14<+26+50*j+50)
						{
							if(matrizbloques[i][j]!=' ')
							{
								mv=1;
								matrizbloques[i][j]=' ';
							}
					
						}
				    }		
					if(mv==1)
					{
						if(bpy<=36+22+22*i && bpy>=36+20+22*i && bpx+14>=24+50*j && bpx<=26+50*j+50)
						{
							if(matrizbloques[i][j]!=' ')
							{
								mv=0;
								matrizbloques[i][j]=' ';
							}
					
						}
					}
			
			//////////////////////////////////////////////////
					if(mh==0)
					{
						if(bpy+14>=36+22*i && bpy<=36+22*i+22 && bpx<=25+50*j+50 && bpx>=25+50*j-1)
						{
							if(matrizbloques[i][j]!=' ')
							{
								mh=1;
								matrizbloques[i][j]=' ';
							}
					
						}
				    }		
					 if(mh==1)
					{
						if(bpy+14>=36+22*i && bpy<=36+22*i+22 && bpx+14>=25+50*j && bpx+14<=25+50*j+1)
						{
							if(matrizbloques[i][j]!=' ')
							{
								mh=0;
								matrizbloques[i][j]=' ';
							}
					
						}
					}
			
			}
	
		}
	
	
	
	
}

/*
void cargarmatrizbloques(char matriz_in,char matriz_out)
{
	
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<14;j++)
			{
				matriz_out[i][j]=matriz_in[i][j];			
			
			}

		}
	
}*/






int main() 
{
		init_allegro();
		     
        buffer=create_bitmap(sizescreen_x,sizescreen_y);
        fondo = load_bitmap("fondo.bmp",NULL);
        borde = load_bitmap("borde.bmp",NULL);
        barra = load_bitmap("barra.bmp",NULL);
        bola = load_bitmap("BolaR.bmp",NULL);
        bloque0 = load_bitmap("bloque0.bmp",NULL);
        bloque1 = load_bitmap("bloque1.bmp",NULL);
        bloque2 = load_bitmap("bloque2.bmp",NULL);
        bloque3 = load_bitmap("bloque3.bmp",NULL);
        bloque4 = load_bitmap("bloque4.bmp",NULL);
        trueno = load_bitmap("trueno1.bmp",NULL);
        
       
		//initmatriz();
        
        while(!key[KEY_ESC])
        {
             
              
             
             draw_sprite(buffer,fondo,0,0); 
             comparabloques();
             imprimirbloques();
             
             
             animtrueno();
             draw_sprite(buffer,borde,0,0); 
             movbarra();
             movimientobola();
             
             
             pantalla();
             //retraso();
             clear(buffer);
                                       
             
        }

}
END_OF_MAIN()

