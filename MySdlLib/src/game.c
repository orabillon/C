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
List* listEntier2;

void funPrint (void* data){
    printf(" %d ", *((int*)data));
}
void multiplyByTwo(void *data) {
    *(int*)data *= 2;
}
// Fonction pour filtrer les éléments supérieurs à un certain seuil
int isGreaterThan(void *data) {
    int value = *(int*)data;
    return value > 350;
}

void game_load(void)
{
    /* Variable Jeu*/
    font = orn_font_newFont("assets/fonts/Open24.ttf", 35);
    texIndiana = orn_graphics_newImage("assets/images/indiana.png");
    texIndiana2 = orn_graphics_newImage("assets/images/indiana.png");
    Vaisseau = orn_graphics_newImage("assets/images/player.png");


    listEntier = orn_list_newList();
    listEntier2 = orn_list_newList();

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
    int intTest5 = 500;

    int intTest6 = 140;
    int intTest7 = 690;
    int intTest8 = 440;
    int intTest9 = 2140;
    int intTest10 = 1480;
    int intTest11 = 5000;

    listEntier = orn_list_addBack(listEntier, &intTest, &funPrint);
    listEntier = orn_list_addBack(listEntier, &intTest1, &funPrint);
    listEntier = orn_list_addFront(listEntier, &intTest2, &funPrint);
    listEntier = orn_list_addBack(listEntier, &intTest3, &funPrint);
    listEntier = orn_list_addFront(listEntier, &intTest4, &funPrint);
    listEntier = orn_list_addBack(listEntier, &intTest5, &funPrint);
    listEntier = orn_list_addFront(listEntier, &intTest11, &funPrint);
    listEntier = orn_list_addBack(listEntier, &intTest9, &funPrint);
    listEntier = orn_list_addFront(listEntier, &intTest10, &funPrint);

    listEntier2 = orn_list_addBack(listEntier2, &intTest6, &funPrint);
    listEntier2 = orn_list_addBack(listEntier2, &intTest7, &funPrint);
    listEntier2 = orn_list_addFront(listEntier2, &intTest8, &funPrint);
    listEntier2 = orn_list_addBack(listEntier2, &intTest9, &funPrint);
    listEntier2 = orn_list_addFront(listEntier2, &intTest10, &funPrint);
    listEntier2 = orn_list_addFront(listEntier2, &intTest11, &funPrint);
    listEntier2 = orn_list_addBack(listEntier2, &intTest3, &funPrint);
    listEntier2 = orn_list_addFront(listEntier2, &intTest4, &funPrint);

 
    orn_list_print(listEntier, " - "); 

    listEntier = orn_list_removeInRange(listEntier,5,7);

    orn_list_print(listEntier, " - "); 
    
    listEntier = orn_list_clear(listEntier); 
    listEntier2 = orn_list_clear(listEntier2); 

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