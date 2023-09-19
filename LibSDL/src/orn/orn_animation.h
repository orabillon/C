#ifndef __orn_animation_h__
#define __orn_animation_h__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "orn_graphics.h"
#include "orn_param.h"

/**
 * Structure animation
 * @param  *texture                 orn_texture
 * @param  *typeAnimation           Type de l'animation (ex : WALK / FALL / IDLE / FIRE ...)
 * @param  iWidth                   Largeur de l'animation
 * @param  iHeight                  Hauteur de l'animation
 * @param  *tabListeImage           Liste des numero d'image de l'animation
 * @param  iTailleTaubleauImage     Taille du tableau d'image
 * @param  fSpeed                   Vitesse de l'animation
 * @param  bRepeat                  Faut-il répéter l'animation
 * @param  current_frame            Image en cour
 * @param  bFinish                  Faut-il répéter l'animation
 */
typedef struct orn_animation
{
    orn_Texture *texture;
    char *typeAnimation;
    int iWidth;
    int iHeight;
    int tabListeImage[NOMBRE_IMAGE_MAX_ANIMATION];
    int iTailleTaubleau;
    float fSpeed;
    bool bRepeat;
    float current_frame;
    bool bFinish;
    bool bAnimationEnCour;

} orn_animation;

orn_animation *orn_animation_createAnimation(orn_Texture *tex, char *typeAnimation, int iWidth, int iHeight, int tabListeImage[], int iTailleTaubleau, float fSpeed, bool bRepeat, bool bEnCour);
void orn_animation_freeAnimation(orn_animation *animation);

void orn_animation_updateAnimation(orn_animation *animation);
void orn_animation_drawAnimation(orn_animation *animation, int iX, int iY);

void orn_animation_startAnimation(orn_animation *animation);
void orn_animation_stopAnimation(orn_animation *animation);

#endif