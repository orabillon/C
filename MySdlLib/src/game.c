#include "game.h"
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"
#include "orn/orn_sound.h"
#include "orn/orn_animation.h"
#include "orn/orn_pad.h"
#include "orn/orn_lists.h"
#include <math.h>

/* Variable Jeu*/
orn_Font font;
orn_Texture texIndiana;
orn_Texture texIndiana2;
orn_Texture Vaisseau;

orn_Texture Texte;

orn_animation *Indiana;

orn_son Musique;
orn_fx Fx;

GameControllerState padControllerState;
GameControllerState oldPadControllerState;

List* listEntier;

void funPrint (void* data){
    printf(" %d ", *((int*)data));
}

void game_load(void)
{
    /* Variable Jeu*/
    font = orn_font_newFont("assets/fonts/Open24.ttf", 35);
    texIndiana = orn_graphics_newImage("assets/images/indiana.png");
    texIndiana2 = orn_graphics_newImage("assets/images/indiana.png");
    Vaisseau = orn_graphics_newImage("assets/images/player.png");


    listEntier = orn_list_new();

    if(orn_list_isEmpty(listEntier)){
        printf("Liste vide \n");
    };

    int tailleListe = orn_list_lenght(listEntier);
    printf("Taille de la liste : %d \n", tailleListe);

    int intTest = 14;
    int intTest1 = 69;
    int intTest2 = 44;
    int intTest3 = 214;
    int intTest4 = 148;

    orn_list_print(listEntier, " - "); 

    listEntier = orn_list_add_back(listEntier, &intTest, &funPrint);
    listEntier = orn_list_add_back(listEntier, &intTest1, &funPrint);
    listEntier = orn_list_remove_back(listEntier);
    listEntier = orn_list_add_front(listEntier, &intTest2, &funPrint);
    listEntier = orn_list_add_back(listEntier, &intTest3, &funPrint);
    listEntier = orn_list_add_front(listEntier, &intTest4, &funPrint);

    orn_list_print(listEntier, " - "); 

    int* pre = orn_list_first(listEntier);
    int* der = orn_list_last(listEntier);

    printf("Pre = %d  -  Der = %d\n", *pre, *der);

    listEntier = orn_list_remove_element(listEntier, &intTest2);
    orn_list_print(listEntier, " - "); 

   // listEntier = orn_list_clear(listEntier);
   // listEntier = orn_list_remove_back(listEntier);

    tailleListe = orn_list_lenght(listEntier);
    printf("Taille de la liste : %d \n", tailleListe);
  

    //unsigned char test[] = {0,1,2,3,4,5,6,7};
    unsigned char test[] = {1}; 
    Indiana = orn_animation_createAnimation(&texIndiana2,"WALK",25,24,test,8,0.0f,false,true);
    Texte = orn_font_newText("Ceci est un Téxt¨^e",font);
    orn_graphics_setTextureFlip(&Texte, true, true );
    orn_graphics_setTextureAngle(&Texte, 90);
    orn_graphics_setTextureFlip(&texIndiana2, false, true);
    orn_graphics_setTextureAngle(&texIndiana2, 25);
    
    orn_graphics_SetTextureColor(&Texte,150,2,66,255);

    Musique = orn_sound_musique_new("assets/sons/Spiritual.mp3");
    orn_sound_musique_volume(23);
    orn_sound_musique_play(&Musique,1);

    Fx = orn_sound_fx_new("assets/sons/Coin.wav");

    // chargement pad 
    updateControllerState(padController, &oldPadControllerState);
}

void game_reset(void){

}

void game_update(float dt)
{
    orn_animation_updateAnimation(Indiana);

    if(orn_keyboard_KeyPressed("space"))
    {
        orn_sound_fx_play(-1,&Fx,0);
    }

    updateControllerState(padController, &padControllerState);

    if (padControllerState.buttons[SDL_CONTROLLER_BUTTON_X] && !oldPadControllerState.buttons[SDL_CONTROLLER_BUTTON_X]) {
        printf("Bouton X enfoncé\n");
    }

    copyControllerState(&padControllerState, &oldPadControllerState);
}

void game_draw(void)
{
    orn_graphics_drawQuad_game(&texIndiana, 25, 24, 0, 15, 15);
    orn_graphics_drawQuad_game(&Vaisseau, 30, 16, 12, 50, 50);

    orn_graphics_draw(Texte, 15, 150);

    orn_animation_drawAnimation(Indiana,150,150);

}

void game_close(void)
{
    orn_animation_freeAnimation(Indiana);
    orn_font_freeFont(&font);
    orn_graphics_freeImage(&Texte);
    orn_graphics_freeImage(&texIndiana);
    orn_graphics_freeImage(&texIndiana2);
    orn_graphics_freeImage(&Vaisseau);
    orn_sound_musique_delete(&Musique);
    orn_sound_fx_delete(&Fx);
    orn_graphics_close();
}