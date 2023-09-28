#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Vector2 size;
    Vector2 position;
    Vector2 speed;
    Vector2 acceleration;
    float maxSpeed;
    float accelerationRate;
    float decelerationRate;
    float facing;
    Texture2D sprite;
} Player;

void PlayerInit(Player* player, Vector2 size, Vector2 position, float maxSpeed, float accelerationRate, float decelerationRate, Texture2D sprite);
void PlayerUpdate(Player* player);
void PlayerDraw(Player* player);

#endif