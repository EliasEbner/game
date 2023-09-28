#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "sign.h"
#include <stdio.h>


void PlayerMove(Player* player) {
    // update acceleration based on input
    if(IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) { player -> acceleration.y = -(player -> accelerationRate); }
    else if(IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) { player -> acceleration.y = player -> accelerationRate; }
    else {
        if(player -> speed.y != 0) {
            player -> acceleration.y = -(player -> decelerationRate) * fsignf(player -> speed.y);
        } else {
            player -> acceleration.y = 0;
        }
    }

    if(IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
        player -> acceleration.x = -(player -> accelerationRate);
        player -> facing = -1;
    } else if(IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
        player -> acceleration.x = player -> accelerationRate;
        player -> facing = 1;
    }
    else {
        if(player -> speed.x != 0) {
            player -> acceleration.x = -(player -> decelerationRate) *fsignf(player -> speed.x);
        } else {
            player -> acceleration.x = 0;
        }
    }
    

    // update speed based on acceleration
    if(fsignf(player -> speed.x) == fsignf(player -> speed.x + player -> acceleration.x) || fsignf(player -> speed.x) == 0) {
        if(fabsf(player -> speed.x + player -> acceleration.x * GetFrameTime()) > player -> maxSpeed) {
            player -> speed.x = player -> maxSpeed * sign(player -> acceleration.x);
        } else {
            player -> speed.x += player -> acceleration.x * GetFrameTime();
        }
    } else {
        player -> speed.x = 0;
    }

    if(fsignf(player -> speed.y) == fsignf(player -> speed.y + player -> acceleration.y) || fsignf(player -> speed.y) == 0) {
        if(fabsf(player -> speed.y + player -> acceleration.y * GetFrameTime()) > player -> maxSpeed) {
            player -> speed.y = player -> maxSpeed * sign(player -> acceleration.y);
        } else {
            player -> speed.y += player -> acceleration.y * GetFrameTime();
        }
    } else {
        player -> speed.y = 0;
    }
    
    
    // this is so that even when strafing, you move at the same speed
    // calculate the ratio between the speeds and normalise them to the maxSpeed
    Vector2 speedRatio = {
        (player -> speed.x) / Vector2Length(player -> speed),
        (player -> speed.y / Vector2Length(player -> speed))
    };
    // when speed = 0, the length of the vector will return 'nan',
    // so to prevent making the player's position into a nan when updating it, you just set
    // the speed ratios to 0
    if(!isnan(Vector2Length(player -> speed)) && Vector2Length(player -> speed) > player -> maxSpeed) {
        player -> speed.x = (player -> maxSpeed) * speedRatio.x;
        player -> speed.y = (player -> maxSpeed) * speedRatio.y;
    } 

    player -> position.x += (player -> speed.x) * GetFrameTime();
    player -> position.y += (player -> speed.y) * GetFrameTime();
}

void PlayerInit(Player* player, Vector2 size, Vector2 initialPosition, float maxSpeed, float accelerationRate, float decelerationRate, Texture2D sprite) {
    player -> size = size;
    player -> position = initialPosition;
    player -> maxSpeed = maxSpeed;
    player -> accelerationRate = accelerationRate;
    player -> decelerationRate = decelerationRate;
    player -> sprite = sprite;
    player -> facing = 1;
    player -> acceleration = Vector2Zero();
    player -> speed = Vector2Zero();
}

void PlayerChooseSprite(Player* player) {

}

void PlayerUpdate(Player* player) {
    PlayerMove(player);
}

void PlayerDraw(Player* player) {
    const Rectangle source = {0, 0, player -> facing * 32, 32};

    const Rectangle destination = {player -> position.x, player -> position.y, player -> size.x, player -> size.y};
    const Vector2 origin = {player -> size.x / 2, player -> size.y / 2};
    DrawTexturePro(player -> sprite, source, destination, origin, 0, WHITE);
}