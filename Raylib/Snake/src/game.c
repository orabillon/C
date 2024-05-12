#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "game.h"
#include "src/Tools/orn_queue.h"
#include "src/Tools/orn_random.h"


/**
 * Represente le direction du snake
 */
typedef enum eDirection 
{
    LEFT,
    UP,
    RIGHT,
    DOWN
} eDirection;

/**
* Represente l'etat du jeu 
*/
typedef enum eGameState
{
    PLAY,
    PAUSE,
    GAMEOVER
} eGameState ;

/**
 * Represente un point 
 * @param x coordonne de la colonne 
 * @param y coordonne de la ligne
 */
typedef struct orn_point
{
    int x;
    int y;
} orn_point;

// ------------------- Variable du jeu ----------------------------------------------
int map[20][20];
int _tailleCase = 25;
int mapWidth = 20;
int mapHeight = 20;
eGameState gameState;
int offSetGame = 30;
 
Queue* snake;
orn_point head;
int snakeLength;
float snakeSpeed;
eDirection snakeDir;
eDirection NextDirection;

orn_point Apple;

float timer = 0;
int score = 0;
int marginWidth;
int marginHeight;

void printPoint(void* data) {

    orn_point* p = (orn_point*)data;
    printf("[%d - %d]",p->x, p->y );
}

bool isSnakeAt(int pLigne, int pColonne)
{
    bool isOk = false;

    for (int i = 0; i < snakeLength; i++)
    {
        orn_point *temp = orn_queue_getAtIndex(snake,i);
        if(temp != NULL)
        {
            if (temp->x == pColonne && temp->y == pLigne) 
            { 
                isOk = true; 
                break; 
            }
        }
        
    }

    return isOk;
}

void NewApple() 
{
    int c, l;
    bool isOk = false;
    do
    {
        c = (orn_random_nextInt(0, mapWidth)) - 1;
        l = (orn_random_nextInt(0, mapHeight)) - 1;

        isOk = isSnakeAt(l,c);

    } while (isOk);

    Apple.x = c;
    Apple.y = l;

    if(score%5 == 0)
    {
        snakeSpeed -= 0.05f; 
    }
}

void _init(void)
{
    // initialise le generateur de nombre aleatoire 
    orn_random_init(0);

    for (int i = 0; i < mapWidth; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            map[i][j] = 0;
        }
        
    }

    score = 0;

    snake = orn_queue_newQueue();
    head.x = mapWidth/2;
    head.y = mapHeight/2;
    orn_queue_enqueue(snake,&head);

    marginWidth = (GetScreenWidth() - mapWidth * _tailleCase)/2;
    marginHeight = 30;

    timer = 0;

    snakeSpeed = 0.5f;
    snakeDir = RIGHT;
    NextDirection = RIGHT;
    gameState = PAUSE;
    snakeLength = 3;

    orn_queue_getAtIndex(snake,0);

    NewApple();   
}

void SnakeMove(int pOffsetX, int pOffsetY)
{
    orn_point newHead = {0,0};
    newHead.x = head.x + pOffsetX;
    newHead.y = head.y + pOffsetY;
    
    head.x = newHead.x;
    head.y = newHead.y;

    // GameOver ?? 
    // condition sortie ecran
    if(head.x < 0 || head.x > mapWidth - 1 || head.y > mapHeight -1 || head.y < 0) 
    {
        gameState = GAMEOVER;
    }
    // le serpent se mort
    if (isSnakeAt(head.y, head.y))
    {
        gameState = GAMEOVER;
    }

    orn_queue_enqueue(snake,&newHead);

    if (orn_queue_lenght(snake) > snakeLength)
    {
        orn_queue_dequeue(snake);
    }

 }

void Play() 
{
    timer += GetFrameTime();

    if (IsKeyDown(KEY_RIGHT) && (snakeDir == UP || snakeDir == DOWN))
    { NextDirection = RIGHT; }
    if (IsKeyDown(KEY_LEFT) && (snakeDir == UP || snakeDir == DOWN))
    { NextDirection = LEFT; }
    if (IsKeyDown(KEY_UP) && (snakeDir == LEFT || snakeDir == RIGHT))
    { NextDirection = UP; }
    if (IsKeyDown(KEY_DOWN) && (snakeDir == LEFT || snakeDir == RIGHT))
    { NextDirection = DOWN; }
    if (IsKeyPressed(KEY_SPACE))
    { gameState = PAUSE; }

    if (timer >= snakeSpeed)
    {
        timer = 0;
        snakeDir = NextDirection;
        switch (snakeDir)
        {
            case LEFT:
                SnakeMove(-1, 0);

                break;
            case UP:
                SnakeMove(0, -1);
                break;
            case RIGHT:
                SnakeMove(1, 0);
                break;
            case DOWN:
                SnakeMove(0, 1);
                break;
            default:
                break;
        }
    }
     // est ce que le serpent mange la pomme ?? 
    if (head.x == Apple.x && head.y == Apple.y) 
    {
        NewApple();
        snakeLength++;
        score++;
    }
 }



void Load(void)
{
    _init();
}

void Update(void)
{
    switch (gameState)
    {
        case PLAY: 
            Play();
            break;

        case PAUSE:
            if (IsKeyPressed(KEY_SPACE))
            { 
                gameState = PLAY;
            }
            break;

        case GAMEOVER:
            if (IsKeyPressed(KEY_SPACE))
            { 
                _init(); 
            }
            break;
    }
 
}

void Draw(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Map
    for (int l = 0; l < mapHeight; l++)
    {
        for (int c = 0; c < mapWidth; c++)
        {
            int x = c * _tailleCase;
            int y = l * _tailleCase;

            DrawRectangleLines( x + marginWidth , y + marginHeight,_tailleCase - 1, _tailleCase - 1, GRAY);
        }
    }

// Apple
DrawRectangle(Apple.x * _tailleCase + marginWidth, Apple.y * _tailleCase + marginHeight, _tailleCase - 1, _tailleCase - 1, RED);

// Snake
for (int i = 0; i < snakeLength; i++)
{
    orn_point *temp = orn_queue_getAtIndex(snake,i);
    if(temp != NULL)
    {
        int x = temp->x * _tailleCase;
        int y = temp->y * _tailleCase;

        DrawRectangle(x + marginWidth, y + marginHeight, _tailleCase - 1, _tailleCase - 1, DARKBLUE);
    }
}

char statusJeu[15];

switch (gameState)
{
    case PLAY: 
        strcpy(statusJeu, "Play");
        break;
    case PAUSE:
        strcpy(statusJeu, "Pause");
        break;
    case GAMEOVER:
        strcpy(statusJeu, "Game Over");
        break;
}

char eScore[10];
char szScore[100] = "score : ";
char szEtat[100] = "Etat du jeu :";
sprintf(eScore, "%d", score);
strcat(szScore, eScore);
strcat(szEtat, statusJeu);

if (gameState == GAMEOVER) 
{
    DrawText(szScore, 10, 2 * marginHeight + mapHeight * _tailleCase, 20, RED);
    DrawText(szEtat, GetScreenWidth() - 250, 2 * marginHeight + mapHeight * _tailleCase, 20, RED);
}
else
{
    DrawText(szScore, 10, 2 * marginHeight + mapHeight * _tailleCase, 20, DARKBLUE);
    DrawText(szEtat, GetScreenWidth() - 250, 2 * marginHeight + mapHeight * _tailleCase, 20, DARKBLUE);
}

    EndDrawing();
}

void UnLoad(void)
{

}