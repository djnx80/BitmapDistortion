#include <stdio.h>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegroStart.h"


using namespace std;

//al_save_bitmap("efekt.bmp",mA.bitmapa);

allegroStart::allegroStart(int sW, int sH)
{
    al_okno = NULL;
    al_bitmapa = NULL;
    srand( time( NULL ) );
    screenH=sH;
    screenW=sW;
cout <<"ccc";
    if(!al_init()) { fprintf(stderr, "Allegro nie udalo sie uruchomic.\n"); }

    al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
    al_init_ttf_addon();
//  	al_install_audio();
//	al_init_acodec_addon();


}

allegroStart::~allegroStart()
{
   	al_destroy_display(al_okno);
}

ALLEGRO_DISPLAY *allegroStart::openWindow()
{
//    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  	al_okno = al_create_display(screenW, screenH);
	if(!al_okno) { fprintf(stderr, "Nie moge utworzyc okna!\n"); }
     return al_okno;
}

ALLEGRO_BITMAP *allegroStart::openBitmap(int sW, int sH)
{
    al_bitmapa = al_create_bitmap(sW, sH);
    return al_bitmapa;
}

