#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <softTone.h>
#define led1 22
#define led2 27
#define MAXFILAS 20
#define MAXCOLS 31
#define	PIN	18
#define	BUTTON	17
SAMPLE    *musica;
SAMPLE    *musica2;


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
BITMAP *ABC;
BITMAP *MABC;
BITMAP *micro;								//variable para guardar imagen de animacion del trueno
BITMAP *presionex;
BITMAP *trueno;


BITMAP *smuerteBMP;
BITMAP *smuerte;
BITMAP *svida;
BITMAP *svidaBMP;
BITMAP *numerovidas;
BITMAP *felicidades;
BITMAP *gameover;


int s=0;									//variable para ciclo de animacion de muerte
char nombre_jugador[20]="                   ";


int sizescreen_x=550;						//tamano horizontal de la ventana de juego
int sizescreen_y=650;						//Tamano vertical de la ventana de juego

int mh=0;									//variable para control de movimiento horizontal de la bola
int mv=1;									//variable de control de movimiento vertical de la bola
int bpx=239;								//Variable de posicion de en x de la bola
int bpy=555+12+7;								//Variable de posicion de en y de la bola

					
int vbarra=3;								//velocidad de la barra [pixeles/cilo]
int vbolay=2,vbolax=2;						//velocidad de la bola en 2 dimensiones

int dir=0;						
int px=235,py=553;							//Variable de posicion de la barra



int tr=1;									//Variable de animacion del trueno
int postrx=1;								//Posicion horizontal trueno
int postry=570;								//Posicion vertical trueno
int holdtr=0;								//Cuenta de animacion del trueno
int veltr=40;								//Variable de velocidad de animacion del trueno


int vidas=3;									//Variable de numero de vidas

int Avidas=0;								//Variable de animacion de las vidas
int holdvidas=0;							//Cuenta de animacion de vidas
int velvidas=10;							//Variable de velocidad de animacion de vidas

int holdmuerte=0;							//Cuenta de animacion de muerte
int velmuerte=10;							//Variable de velocidad de animacion de muerte
int ciclomuerte=0;							//Variable de control de juego (indica que perdio una vida)

int pausa=0;								//bandera para pausa
int victoria=0;								//bandera de ganador
int nfondo=0;



char matrizbloques [21][14];				//Matriz de almacenamiento para cargar los bloques del juego

char bloquesvacio [21][14]={
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
};
	
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

void sonido(){
  
  softToneCreate (PIN) ;
	 softToneWrite (PIN, 800) ;
	 digitalWrite(led1,HIGH);
          delay (50);
     digitalWrite (led1,LOW);
         softToneWrite (PIN, 0) ;
         
         //delay (500);
}

void sonido2(){
  
  softToneCreate (PIN) ;
	 softToneWrite (PIN, 1500) ;
	 digitalWrite(led2,HIGH);
          delay (50);
     digitalWrite (led2,LOW);    
         softToneWrite (PIN, 0) ;
         //delay (500);
}

///////////////----------FUNCIONES-----------////////////////
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
		//if (vbolax==2) usleep(7000);
		//else usleep(6500);
		
	
}


void movimientobola()
{
		if(mh==1)//Si mh es igual a 1, la bola se mueve hacia la derecha
		{
			if(bpx+2>=sizescreen_x-23) mh=0;	
			else if((bpx+8 >=px && bpx+6 <= px) && (bpy+8>=py && bpy <= py+32))
			{
				mh=0;
			}			
			else bpx+=vbolax;
		}
	
		if(mh==0)//Si mh es igual a 0, la bola se mueve hacia la izquierda
		{
			if(bpx-2<=17) mh=1;
			else if((bpx <=px+71 && bpx+5 >= px+71) && (bpy+14>=py && bpy <= py+32))
			{
				mh=1;
			}			
			else bpx-=vbolax;
		}
	
		if(mv==1)//Si mv es igual a 1, la bola se mueve hacia arriba
		{
			if(bpy-2<=24) mv=0;	
			else bpy-=vbolay;
		}
	
		if(mv==0)//Si mv es igual a 0, la bola se mueve hacia abajo
		{
			if(bpy>=postry-7)
			{
				mv=2;
				ciclomuerte=1;
				mh=2;
			}
			else if((bpy+10 >=py && bpy+13 <= py+5) && (bpx+14>=px && bpx <= px+9))
			{
				mv=1;
				mh=0;
				vbolax=2;
				sonido2();
			}
			else if((bpy+10 >=py && bpy+13 <= py+5) && (bpx+14>=px+9 && bpx <= px+18))
			{
				mv=1;
				vbolax=2;
				sonido2();
			}
			else if((bpy+10 >=py && bpy+13 <= py+5) && (bpx+14>=px+18 && bpx <= px+36))
			{
				mv=1;
				vbolax=1;
				sonido2();
			}
			else if((bpy+10 >=py && bpy+13 <= py+5) && (bpx+14>=px+36 && bpx <= px+45))
			{
				mv=1;
				vbolax=2;
				sonido2();
				
			}
			else if((bpy+10 >=py && bpy+13 <= py+5) && (bpx+14>=px+45 && bpx <= px+55))
			{
				mv=1;
				mh=1;
				vbolax=2;
				sonido2();
			}
						
			else bpy+=vbolay;
		}
		
		
		draw_sprite(buffer,bola,bpx,bpy); 
	
	
}


void init_allegro()					//Funcion de inicializacion de la libreria Allegro
{
		allegro_init();
		install_keyboard();
	    set_color_depth(32);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, sizescreen_x,sizescreen_y,0,0);
	
}


void movbarra()						//Funcion de movimiento e impresion de la barra
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



void animtrueno()					//Funcion de animacion del trueno (piso)
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
	while (s<21)
	{
		//play_sample(musica2,100,100,1000,0);
		draw_sprite(buffer,fondo,0,0); 		//Se dibuja la imagen de fondo en el buffer
		blit(smuerteBMP,smuerte,20*s,0,0,0,20,20);			//Corte de BMP para imprimir seccion especifica
		draw_sprite(buffer,smuerte,bpx,bpy-5);					//Carga de corte del BMP
		animtrueno();
		draw_sprite(buffer,borde,0,0);		//Dibuja el borde en el buffer	
		draw_sprite(buffer,svida,106,610); 	//Imprime en buffer la animacion de las vidas
		imprimirbloques(matrizbloques);		//Imprime en buffer la matriz de bloques actualizada
		movbarra();	
		textout_ex(buffer,font, nombre_jugador, 365, 620, makecol(0,255,0), -1);
		pantalla();							//Actualiza la pantalla con el contenido del buffer
		usleep(100000);						//Ciclo de retraso (se debe cambiar el valor dependiendo del hardware)
		clear(buffer);
		s++;
		play_sample(musica2,100,100,1000,0);
		play_sample(musica,500,100,1000,0);
	}
	ciclomuerte=0;	
	s=0;
		
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

void vidasrestantes()
{
	if (vidas==2)
	{
		numerovidas = load_bitmap("tres.bmp",NULL);
		draw_sprite(buffer,numerovidas,165,609);		
	}
	
	else if (vidas==1)
	{
		numerovidas = load_bitmap("dos.bmp",NULL);
		draw_sprite(buffer,numerovidas,165,609);	
	}
	
	if (vidas==0)
	{
		numerovidas = load_bitmap("uno.bmp",NULL);
		draw_sprite(buffer,numerovidas,165,609);		
	}
	
}


void pausa_y_rastreo()
{
			 if (key[KEY_G])					//Activacion de modo rastreo (para propositos de pruebas de bugs)
             {
				 px=bpx-27+5;					//La posicion de la barra siempre estara por debajo de la bola
			 }
			 
			 else if (key[KEY_P])
			 {
				 pausa = 1;
				 usleep(500000);
				
			 }
			 
			  while (pausa==1)
				{
					if(key[KEY_P])
					{
						pausa=0;
						usleep(200000);
					}
				}
	
}


void comprobarvictoria(char matriz_1[21][14],char matriz_2[21][14])
{
		victoria = 1;
		
		for(int i=0;i<20;i++)
		{
			for(int j=0;j<14;j++)
			{
				if (matriz_1[i][j]!= matriz_2[i][j])
				{
					victoria=0;
				}
			
			}

		}
	
}	

void iniciojuego()
{
	if(key[KEY_F])
	{
		if(nfondo!=3)
		{
			nfondo++;
			usleep(100000);
		
		}
		else 
		{
			usleep(100000);
			nfondo=0;
		}
	}
	
	
	if(nfondo==0)
	{
		fondo = load_bitmap("fondo.bmp",NULL);				//^
	}
	
	else if(nfondo==1)
	{
		fondo = load_bitmap("fondoA.bmp",NULL);				//^
	}
	else if(nfondo==2)
	{
		fondo = load_bitmap("fondoR.bmp",NULL);				//^
	}
	else if(nfondo==3)
	{
		fondo = load_bitmap("fondoV.bmp",NULL);				//^
	}
	
	
	
	
	
	
	
	
	draw_sprite(buffer,fondo,0,0); 	//Se dibuja la imagen de fondo en el buffer
	draw_sprite(buffer,presionex,180,400);
	animtrueno();						//Funcion de animacion del trueno
	draw_sprite(buffer,borde,0,0);		//Dibuja el borde en el buffer
	movbarra();						//Funcion de movimiento y actualizacin de barra
	draw_sprite(buffer,bola,px+27-5,555-10);	//Imprime en buffer el sprite de la bola sobre la barra
	bpx=px+27-5;						//Actualiza la posicion de la bola sobre la barra
	draw_sprite(buffer,svida,106,610);	//Imprime en buffer la animacion de las vidas
	imprimirbloques(matrizbloques);	//Imprime en buffer la matriz de bloques actualizada
	animvidas();						//Funcion de animacion de contador de vidas
	draw_sprite(buffer,svida,106,610);	//Imprime en buffer la animacion de las vidas
	vidasrestantes();					//Funcion de actualizacion de vidas
	textout_ex(buffer,font, nombre_jugador, 365, 620, makecol(0,255,0), -1);
	pantalla();						//Actualiza la pantalla con el contenido del buffer
	//clear(buffer);						//Se limpia los contenidos del buffer
	usleep(7000);						//Ciclo de retraso (se debe cambiar el valor dependiendo del hardware)
}


void reiniciodevariables()
{
		vidas--;							//Reduccion de vida
		px=250;								//Posicion inicial barra
		bpx=264;							//Regresa la bola a su posicion inicial 								
		bpy=555-12-7;						//""555-12-7
		ciclomuerte=0;						//Reinicia condicion de variables del ciclo de juego
		mv = 1;								//""
		mh = rand() % 2;;						//""
		vbolax=rand()%2+1;						//velocidad de la bola en 2 dimensiones
		
}


void comparabloques(char matriz[21][14])
{
	
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<13;j++)
			{
					
					if(mv==0)
					{
						if(bpy+8>=23+16*i && bpy+8<=23+16*i+4 && bpx>=18+39*j-1 && bpx+8<=22+39*j+39+1)
						{
							if(matriz[i][j]!=' ')
							{
								mv=1;
								matriz[i][j]=' ';
								sonido();
							}
					
						}
				    }		
					if(mv==1)
					{
						if(bpy<=23+15+16*i && bpy>=23+4+16*i && bpx>=18+39*j && bpx+8<=22+39*j+39)
						{
							if(matriz[i][j]!=' ')
							{
								mv=0;
								matriz[i][j]=' ';
								sonido();
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
								sonido();
							}
					
						}
				    }		
					 if(mh==1)
					{
						if(bpy+8>=23+16*i && bpy<=23+16*i+16 && bpx+8>=18+39*j && bpx+8<=18+39*j+3)
						{
							if(matriz[i][j]!=' ')
							{
								mh=0;
								matriz[i][j]=' ';
								sonido();
							}
					
						}
					}
			
			}
	
		}
	
	
	
	
}

void cargarmatriz(char matriz_in[21][14],char matriz_out[21][14])
{
	
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<14;j++)
			{
				matriz_out[i][j]=matriz_in[i][j];			
			
			}

		}
	
}

void teclado_in(char nombre[20])
{
	int p=0;
	int pos=170;
	
	
	while(true)
	{
		usleep(100000);
		char tecla= readkey() >> 8;
		if(tecla==KEY_ENTER){
			break;
		}
		
		 else if(tecla==KEY_A){
			nombre[p]='A';
			blit(ABC,MABC,51,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		
		 else if(tecla==KEY_B){
			nombre[p]='B';
			blit(ABC,MABC,96,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		 else if(tecla==KEY_C){
			nombre[p]='C';
			blit(ABC,MABC,137,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		 else if(tecla==KEY_D){
			nombre[p]='D';
			blit(ABC,MABC,180,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_E){
			nombre[p]='E';
			blit(ABC,MABC,227,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_F){
			nombre[p]='F';
			blit(ABC,MABC,267,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_G){
			nombre[p]='G';
			blit(ABC,MABC,313,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_H){
			nombre[p]='H';
			blit(ABC,MABC,359,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_I){
			nombre[p]='I';
			blit(ABC,MABC,399,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_J){
			nombre[p]='J';
			blit(ABC,MABC,451,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_K){
			nombre[p]='K';
			blit(ABC,MABC,495,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_L){
			nombre[p]='L';
			blit(ABC,MABC,539,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_M){
			nombre[p]='M';
			blit(ABC,MABC,580,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_N){
			nombre[p]='N';
			blit(ABC,MABC,625,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_O){
			nombre[p]='O';
			blit(ABC,MABC,669,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_P){
			nombre[p]='P';
			blit(ABC,MABC,710,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_Q){
			nombre[p]='Q';
			blit(ABC,MABC,756,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_R){
			nombre[p]='R';
			blit(ABC,MABC,799,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_S){
			nombre[p]='S';
			blit(ABC,MABC,844,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_T){
			nombre[p]='T';
			blit(ABC,MABC,887,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_U){
			nombre[p]='U';
			blit(ABC,MABC,933,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_V){
			nombre[p]='V';
			blit(ABC,MABC,977,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_W){
			nombre[p]='W';
			blit(ABC,MABC,1021,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_X){
			nombre[p]='X';
			blit(ABC,MABC,1067,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_Y){
			nombre[p]='Y';
			blit(ABC,MABC,1111,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		
		else if(tecla==KEY_Z){
			nombre[p]='Z';
			blit(ABC,MABC,1155,3,0,0,40,40);
			draw_sprite(buffer,MABC,40*p+pos,300);
			pantalla();
			p++;
		}
		else if(tecla==KEY_BACKSPACE){
			
			clear(buffer);
			nombre[0]=' ';
			nombre[1]=' ';
			nombre[2]=' ';
			nombre[3]=' ';
			nombre[4]=' ';
			nombre[5]=' ';
			nombre[6]=' ';
			nombre[7]=' ';
			nombre[8]=' ';
			nombre[9]=' ';
			nombre[10]=' ';
			nombre[11]=' ';
			nombre[12]=' ';
			nombre[13]=' ';
			nombre[14]=' ';
			nombre[15]=' ';
			nombre[16]=' ';
			nombre[17]=' ';
			
			draw_sprite(buffer,fondo,0,0);
			draw_sprite(buffer,micro,0,50); 
			pantalla();
			p=0;
			
			
		}
		
	}
	
}

void screen_inicio()
{
	int mov=900;
	
	
	while(mov>=50)
	{		clear(buffer);
			draw_sprite(buffer,fondo,0,0); 
			draw_sprite(buffer,micro,0,mov); 
			pantalla();
			mov--;
		
	}
	
}





void cargasprites()
{
		buffer=create_bitmap(sizescreen_x,sizescreen_y);	//Creacion de espacio de juego
        fondo = load_bitmap("fondoA.bmp",NULL);				//^
        borde = load_bitmap("borde.bmp",NULL);				//^
        barra = load_bitmap("barra.bmp",NULL);				//^
        bola = load_bitmap("BolaR.bmp",NULL);				//^
        bloque0 = load_bitmap("bloque0.bmp",NULL);			//^
        bloque1 = load_bitmap("bloque1.bmp",NULL);			//^
        bloque2 = load_bitmap("bloque2.bmp",NULL);			//^
        bloque3 = load_bitmap("bloque4.bmp",NULL);			//^
        bloque4 = load_bitmap("bloque3.bmp",NULL);			//^
        trueno = load_bitmap("trueno1.bmp",NULL);			//^
        presionex=load_bitmap("presionex.bmp",NULL);
        svidaBMP = load_bitmap("vida.bmp",NULL);			//^
		svida = create_bitmap(62,25); 						//Carga de imagenes en los bitmaps declarados
		
		felicidades = load_bitmap("felicidades.bmp",NULL);
		gameover = load_bitmap("juegoterminado.bmp",NULL);
		
		        
        micro = load_bitmap("micronoid0.bmp",NULL);
        ABC = load_bitmap("letras0.bmp",NULL);
        MABC =create_bitmap(40,40);
        
        smuerteBMP = load_bitmap("muerter.bmp",NULL);		//^
        smuerte = create_bitmap(19,19);						//^
        svidaBMP = load_bitmap("vida.bmp",NULL);			//^
        svida = create_bitmap(62,25);						//Carga de imagenes en los bitmaps declarados
        
        blit(svidaBMP,svida,(-2+62)*12,0,0,0,62,25);		//Corte de BMP para imprimir seccion especifica
		draw_sprite(buffer,svida,106,610);					//Carga de corte del BMP
		blit(smuerteBMP,smuerte,0,0,0,0,19,19);			//Corte de BMP para imprimir seccion especifica
		draw_sprite(buffer,smuerte,bpx,bpy);					//Carga de corte del BMP
        	
}


int main() 
{
		wiringPiSetupGpio () ;
		pinMode (BUTTON, INPUT) ;
		pinMode (led1,OUTPUT);
		pinMode (led2,OUTPUT);
                         
	
 
		init_allegro();
		if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) { allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error); return 1; }
                set_volume(70, 70);
                musica = load_wav("Avicii & Nicky Romero - Nicktim (Original Mix).wav");
                musica2 = load_wav("Efecto_Electricidad.wav");
		cargasprites();  
		play_sample(musica,500,100,1000,1);
		reinicio:   
		draw_sprite(screen,fondo,0,0);
		cargarmatriz(bloquesdefecto,matrizbloques);
		screen_inicio();
		teclado_in(nombre_jugador);
		

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
     while (vidas != 0 && victoria==0)				//Juego (Contiene el juego principal y el ciclo de vidas)
     {
		 reiniciodevariables();						//Reinicia las variables de control y posiciones al inicio de cada vida
		 
		 while (!key[KEY_X])	//////////////////////////////////////////////////////////////////////Pausa entre vidas
		 {
			 iniciojuego(); 
			 usleep(100000);						//Funcion que controla el movimiento antes de que inicie la partida
			  if (digitalRead (BUTTON) == HIGH)	// Swap LED states
				{ 	vidas=3;
					goto reinicio;
					
				}
				
				
		 }
		 
        while(!key[KEY_ESC] && ciclomuerte==0  && victoria==0) ////////////////////////////////////////////Ciclo de juego
        {
             
              if(key[KEY_C])
              {
				cargarmatriz(bloquesvacio,matrizbloques);  
				}
             
			 pausa_y_rastreo();
			 
			  if (digitalRead (BUTTON) == HIGH)	// Swap LED states
				{ vidas=3;
					goto reinicio;
					
				}
             draw_sprite(buffer,fondo,0,0); 		//Se dibuja la imagen de fondo en el buffer
             comparabloques(matrizbloques);			//Funcion de verificacion de choques
             
             
             animtrueno();							//Funcion de animacion del trueno
             draw_sprite(buffer,borde,0,0);			//Dibuja el borde en el buffer	 
             movbarra();							//Funcion de movimiento y actualizacin de barra
             movimientobola();						//Funcion de movimiento y actualizacin de bola
             imprimirbloques(matrizbloques);		//Imprime en buffer la matriz de bloques actualizada
             animvidas();							//Funcion de animacion de contador de vidas
             draw_sprite(buffer,svida,106,610);		//Imprime en buffer la animacion de las vidas
             vidasrestantes();						//Funcion de actualizacion de vidas
             textout_ex(buffer,font, nombre_jugador, 365, 620, makecol(0,255,0), -1);
             pantalla();							//Actualiza la pantalla con el contenido del buffer
             
             //retraso();
             
             
             clear(buffer);							//Se limpia los contenidos del buffer
             comprobarvictoria(matrizbloques,bloquesvacio); //Comprueba que la matriz de juego sea igual a una matriz vacia
                  
        }
        
        
        while (ciclomuerte == 1) /////////////////////////////////////////////////////////////////////////Ciclo de muerte
        {
			animmuerte();							//Funcion que contiene la animacion de muerte
			ciclomuerte=0;	
			
		}
		
		
		while(victoria==1)
		{
			usleep(100000);
			draw_sprite(buffer,fondo,0,0); 							//Se dibuja la imagen de fondo en el buffer
			draw_sprite(buffer,felicidades,40,100); 					//Se dibuja la imagen de fondo en el buffer
			textout_ex(buffer,font, "Bernardo Rodriguez 201315419 ", 0, 200, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Felipe Herrero     201218785 ", 0, 215, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Sergio Gonzalez    201218363 ", 0, 230, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Alejandro Murillo  200016618 ", 0, 245, makecol(0,255,0), -1);
			
			textout_ex(buffer,font, "ARMv7 Processor rev 4 (v7l)", 250, 200, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Processor Model:   BCM2709 ", 250, 215, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Linux version:  4.4.11-v7+ ", 250 ,230, makecol(0,255,0), -1);
			textout_ex(buffer,font, "gcc version:         4.9.3 ", 250 ,245, makecol(0,255,0), -1);
			
			textout_ex(buffer,font, "Presione R para Reiniciar Juego", 0,400, makecol(255,255,255), -1);
			textout_ex(buffer,font, "Presione S para Salir del Juego", 0 ,415, makecol(255,255,0), -1);
			
			
			
			pantalla();
			
			
			if(key[KEY_R])
			{
				cargarmatriz(matrizbloquesombrilla,matrizbloques);
				vidas=3;
				victoria =0;			
			}
			else if(key[KEY_S])
			{
				break;
				
				
			}
			
			
			
			
		}
		
		
		while(vidas ==0 && victoria!=1)
		{
			usleep(100000);
			draw_sprite(buffer,fondo,0,0); 		//Se dibuja la imagen de fondo en el buffer
			draw_sprite(buffer,gameover,0,100); 		//Se dibuja la imagen de fondo en el buffer
			textout_ex(buffer,font, "Bernardo Rodriguez 201315419 ", 0, 200, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Felipe Herrero     201218785 ", 0, 215, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Sergio Gonzalez    201218363 ", 0, 230, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Alejandro Murillo  200016618 ", 0, 245, makecol(0,255,0), -1);
			
			textout_ex(buffer,font, "ARMv7 Processor rev 4 (v7l)", 250, 200, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Processor Model:   BCM2709 ", 250, 215, makecol(0,255,0), -1);
			textout_ex(buffer,font, "Linux version:  4.4.11-v7+ ", 250 ,230, makecol(0,255,0), -1);
			textout_ex(buffer,font, "gcc version:         4.9.3 ", 250 ,245, makecol(0,255,0), -1);
			
			textout_ex(buffer,font, "Presione R para Reiniciar Juego", 0,400, makecol(255,255,255), -1);
			textout_ex(buffer,font, "Presione S para Salir del Juego", 0 ,415, makecol(255,255,0), -1);
			
			
			
			pantalla();
			
			
			if(key[KEY_R])
			{
				cargarmatriz(matrizbloquesombrilla,matrizbloques);
				vidas=3;
										
			}
			else if(key[KEY_S])
			{
				break;
				
			}
			
			
		}
		
		
		
		
	}	
               
        
        allegro_exit();

}
END_OF_MAIN()

