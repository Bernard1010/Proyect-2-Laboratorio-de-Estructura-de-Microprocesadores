#include <allegro.h>
#include <unistd.h>

#define MAXFILAS 20
#define MAXCOLS 31


BITMAP *buffer;
BITMAP *roca;
BITMAP *barra;
BITMAP *fondo;
BITMAP *bola;
BITMAP *bloque0;
BITMAP *bloque1;
BITMAP *bloque2;
BITMAP *bloque3;
BITMAP *bloque4;


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
			if(bpx+2>=sizescreen_x-10) mh=0;			
			else bpx+=vbola;
		}
	
		if(mh==0)//Si mh es igual a 0, la bola se mueve hacia la izquierda
		{
			if(bpx-2<=5) mh=1;			
			else bpx-=vbola;
		}
	
		if(mv==1)//Si mv es igual a 1, la bola se mueve hacia arriba
		{
			if(bpy-2<=0) mv=0;			
			else bpy-=vbola;
		}
	
		if(mv==0)//Si mv es igual a 0, la bola se mueve hacia abajo
		{
			if(bpy>=sizescreen_y-14)
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
				 if(!(px-2<=0))				 
				  px=px-vbarra;
				 
			 }
			  if(key[KEY_RIGHT])
             {
				 if(!(px+71>=sizescreen_x))
				 px=px+vbarra;
				 
			 }
	 draw_sprite(buffer,barra,px,py); 
	
}




int main() 
{
		init_allegro();
		        
        buffer=create_bitmap(sizescreen_x,sizescreen_y);
        fondo = load_bitmap("fondo.bmp",NULL);
        barra = load_bitmap("barra.bmp",NULL);
        bola = load_bitmap("BolaR.bmp",NULL);
        bloque0 = load_bitmap("bloque0.bmp",NULL);
        bloque1 = load_bitmap("bloque1.bmp",NULL);
        bloque2 = load_bitmap("bloque2.bmp",NULL);
        bloque3 = load_bitmap("bloque3.bmp",NULL);
        bloque4 = load_bitmap("bloque4.bmp",NULL);
        
      
        
        while(!key[KEY_ESC])
        {
             
              
             
             draw_sprite(buffer,fondo,0,0); 
             
             
             for(int i=0;i<13;i++)
             {	
				 draw_sprite(buffer,bloque0,i*50+25,168);
				 draw_sprite(buffer,bloque1,i*50+25,190);
				 draw_sprite(buffer,bloque2,i*50+25,212);	
				 draw_sprite(buffer,bloque3,i*50+25,234);
				 draw_sprite(buffer,bloque4,i*50+25,256);  
				 
			 }
             
             
             movbarra();
             moviminetobola();
             
             
             pantalla();
             retraso();
                                       
             
        }

}
END_OF_MAIN()

