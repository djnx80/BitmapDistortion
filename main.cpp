//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "allegroStart.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
#include <string>


#define PI 3.14159265

void point(unsigned char *pt, int xx, int yy, unsigned char r, unsigned char g, unsigned char b);
void drawTab(int sX, int sY, int eX, int eY);
void readPointTabAllegroCol(ALLEGRO_BITMAP *bmap, int sX, int sY, int eX, int eY);
void zmienObraz(float r);
void fakedFog();

using namespace std;

allegroStart mA(800,600);
ALLEGRO_DISPLAY *okno = mA.openWindow();
ALLEGRO_BITMAP  *bitmapa = mA.openBitmap(800,600);
ALLEGRO_KEYBOARD_STATE klawisz;
ALLEGRO_LOCKED_REGION *lr;
unsigned char *ptr;

ALLEGRO_COLOR obraz[810][610];
ALLEGRO_COLOR bufor[810][610];

//void *__gxx_personality_v0;


int main()
{
    float r=1;
    srand( time( NULL ) );
	bitmapa = al_load_bitmap("fotka.bmp");

    lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READWRITE);
    ptr = (unsigned char *)lr->data;
    readPointTabAllegroCol(bitmapa, 1,1,800,600);
    for (int ix=0; ix<800-1; ix++)    {
        for (int iy=0; iy<600-1; iy++)    {
            point(ptr,ix,iy,0,0,0);
            bufor[ix][iy]=obraz[ix][iy];
        }
    }
    al_unlock_bitmap(bitmapa);

    while( !al_key_down( & klawisz, ALLEGRO_KEY_ESCAPE ) )    {

        lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READWRITE);
        ptr = (unsigned char *)lr->data;
//		al_clear_to_color(al_map_rgb(100,0,0));
        zmienObraz(r);
        fakedFog();  // chociaz bardziej blur
        r+=2;
		drawTab(1,1,800,600);
        al_draw_bitmap(bitmapa,0,0,0);
        al_unlock_bitmap(bitmapa);
        al_flip_display();
        al_get_keyboard_state( & klawisz );
        al_rest(0.004);
    }
	return 0;
}

void fakedFog() {
    // usrednamy kolor, troche blur

    ALLEGRO_COLOR k1,k2,k3,k4,k5,k0;
    unsigned char rr[6],gg[6],bb[6];

    for (int x=2; x<800-2; x++)    {
        for (int y=2; y<600-2; y++)    {
            k1=bufor[x][y];
            k2=bufor[x-1][y];
            k3=bufor[x+1][y];
            k4=bufor[x][y-1];
            k5=bufor[x][y+1];
            al_unmap_rgb(k1,&rr[1],&gg[1],&bb[1]);
            al_unmap_rgb(k2,&rr[2],&gg[2],&bb[2]);
            al_unmap_rgb(k3,&rr[3],&gg[3],&bb[3]);
            al_unmap_rgb(k4,&rr[4],&gg[4],&bb[4]);
            al_unmap_rgb(k5,&rr[5],&gg[5],&bb[5]);
            rr[0] = (rr[1]+rr[2]+rr[3]+rr[4]+rr[5])/5;
            gg[0] = (gg[1]+gg[2]+gg[3]+gg[4]+gg[5])/5;
            bb[0] = (bb[1]+bb[2]+bb[3]+bb[4]+bb[5])/5;
            bufor[x][y] = al_map_rgb(rr[0],gg[0],bb[0]);
   //         bufor[x][y] = obraz[x][y];
        }
    }

}

void zmienObraz(float r)   {
float nx, ny;

float alfa=50;
float dx,dy;
float temp;

    for (int x=0; x<800-1; x++)    {
        for (int y=0; y<600-1; y++)    {
            //    bufor[x][y]=al_map_rgb(0,0,0);
            temp = sqrt(x*x+y*y*(r/100));
            dx = cos(temp*PI/300)*r;
           // dy = sin((x*temp)*PI/180)*r;
            dy = sin((x*y)/temp*PI/300)*r; // mozna sie pobawic wartosciami
            //
        //    dy = sin((x+y)*PI/180)*r;
//dy=0;
            nx = x+dx;
            ny = y+dy;
            if (nx>0 && nx<800 && ny>0 && ny<600)   {
           //         cout <<nx<<" "<<ny<<endl;
                bufor[(int)nx][(int)ny] = obraz[x][y];
            }
     //      bufor[x][y] = obraz[x][y];
        }
    }

}

void point(unsigned char *pt, int xx, int yy,unsigned char r, unsigned char g, unsigned char b) {
    // rysuje pixel w (xx,yy) o kolorze (r,g,b) i alfa=250;
    if (xx<mA.screenW && yy<mA.screenH && xx>=0 && yy>=0) {
        int pixel;
        pixel = xx+yy*mA.screenW;
        pt[pixel*4] = r;
        pt[pixel*4+1] = g;
        pt[pixel*4+2] = b;
        pt[pixel*4+3] = 250;
    }
}

void drawTab(int sX, int sY, int eX, int eY)  {
    unsigned char rr,gg,bb;
    for (int ix=sX; ix<eX; ix++)    {
        for (int iy=sY; iy<eY; iy++)    {
            al_unmap_rgb(bufor[ix][iy],&rr,&gg,&bb);
            point(ptr,ix,iy,rr,gg,bb);
        }
    }
}

void readPointTabAllegroCol(ALLEGRO_BITMAP *bmap, int sX, int sY, int eX, int eY)    {
    // odczytaj pixele do tablicy red/green/blue, start:(sx,sy), koniec:(ex,ey)
    if (sX<0) sX = 0;
    if (sY<0) sY = 0;
    if (sX>mA.screenW) sX = mA.screenW;
    if (sY>mA.screenH) sY = mA.screenH;

    for (int ix=sX; ix<eX; ix++)    {
        for (int iy=sY; iy<eY; iy++)    {
            obraz[ix][iy] = al_get_pixel(bmap, ix, iy);
        }
    }
}

