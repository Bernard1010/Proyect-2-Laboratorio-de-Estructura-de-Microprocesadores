#include <allegro.h>
#include <unistd.h>

#define MAXFILAS 20
#define MAXCOLS 31


BITMAP *buffer;


BITMAP *barra;

BITMAP *fondo;
BITMAP *borde;

BITMAP *bola;
BITMAP *bloque0;
BITMAP *bloque1;
BITMAP *bloque2;
BITMAP *bloque3;
BITMAP *bloque4;

BITMAP *trueno;


int sizescreen_x=700;						//tamano horizontal de la ventana de juego
int sizescreen_y=900;						//Tamano vertical de la ventana de juego

int mh=1;									//variable para control de movimiento horizontal de la bola
int mv=1;									//variable de control de movimiento vertical de la bola
int bpx=100;								//Variable de posicion de en x de la bola
int bpy=300;								//Variable de posicion de en y de la bola

int vbola=2;								//velocidad de la bola [pixel/cilo]
int vbarra=3;								//velocidad de la barra [pixel/cilo]


int dir=0;						
int px=350,py=800;							//Variable de posicion de la barra



int tr=1;									//Variable de animacion del trueno
int postrx=1;								//Posicion horizontal trueno
int postry=850;								//Posicion vertical trueno
int holdtr=0;								//Cuenta de animacion del trueno
int veltr=30;								//Variable de velocidad de animacion del trueno




void pantalla()
{
     blit(buffer,screen,0,0,0,0,sizescreen_x,sizescreen_y);     
} 


void retraso()
{
		int x=0;
		while(x<=9000)
		{
				if(x==9000)
				{
						break;
				}
				else x++;
		}
	
}




void moviminetobola()
{
		if(mh==1)//Si mh es igual a 1, la bola se mueve hacia la derecha
		{
			if(bpx+2>=sizescreen_x-26) mh=0;			
			else bpx+=vbola;
		}
	
		if(mh==0)//Si mh es igual a 0, la bola se mueve hacia la izquierda
		{
			if(bpx-2<=26) mh=1;			
			else bpx-=vbola;
		}
	
		if(mv==1)//Si mv es igual a 1, la bola se mueve hacia arriba
		{
			if(bpy-2<=26) mv=0;			
			else bpy-=vbola;
		}
	
		if(mv==0)//Si mv es igual a 0, la bola se mueve hacia abajo
		{
			if(bpy>=sizescreen_y-55)
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
        
      
        
        while(!key[KEY_ESC])
        {
             
              
             
             draw_sprite(buffer,fondo,0,0);
               
             
             
             for(int i=0;i<13;i++)
             {	
				 draw_sprite(buffer,bloque0,i*50+26,168);
				 draw_sprite(buffer,bloque1,i*50+26,190);
				 draw_sprite(buffer,bloque2,i*50+26,212);	
				 draw_sprite(buffer,bloque3,i*50+26,234);
				 draw_sprite(buffer,bloque4,i*50+26,256);  
				 
			 }
             
             animtrueno();
             draw_sprite(buffer,borde,0,0);
             movbarra();
             moviminetobola();
             
             
             pantalla();
             retraso();
                                       
             
        }

}
END_OF_MAIN()
