#include "raylib.h"
#include "player.h"


int main(int argc, char* argv[]) {
	InitWindow(800, 600, "some game");
	ToggleFullscreen();
	SetTargetFPS(60);
	const float playerSize = 64;
	const float playerMaxSpeed = 500;
	const float playerAcceleration = 4000;
	const float playerDeceleration = 5000;
	const Texture2D playerSprite = LoadTexture("res/assets/player.png");
	Player player;
	
	PlayerInit(
		&player,
		(Vector2) {playerSize, playerSize}, // size
		(Vector2) {GetScreenWidth()/2 - playerSize/2, GetScreenHeight()/2 - playerSize/2}, // initial position
		playerMaxSpeed, // max speed
		playerAcceleration, // acceleration
		playerDeceleration,
		playerSprite // sprite
	);
	while(!WindowShouldClose()) {
		PlayerUpdate(&player);

		BeginDrawing();
			ClearBackground(GRAY);
			PlayerDraw(&player);
		EndDrawing();
	}
	CloseWindow();
	
	return 0;
}
