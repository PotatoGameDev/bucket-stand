#include "raylib.h"

// Size of the pong paddles
#define PADDLE_HEIGHT 80
#define PADDLE_WIDTH 20

// Speed of the paddles
#define PADDLE_SPEED 2.0f

// Ball radius
#define BALL_RADIUS 50

int main() {
  // Window dimensions
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Pong Game");

  // Position of player and AI paddles
  Rectangle player = {0, screenHeight / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH,
                      PADDLE_HEIGHT};
  Rectangle ai = {screenWidth - PADDLE_WIDTH,
                  screenHeight / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH,
                  PADDLE_HEIGHT};

  // Position and velocity of ball
  Vector2 ballPos = {screenWidth / 2, screenHeight / 2};
  Vector2 ballVelocity = {3.0f, 2.0f};

  SetTargetFPS(60);

  Texture2D ballTexture = LoadTexture("SoccerBall.png");

  float rotation = 0.0;

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_UP))
      player.y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_DOWN))
      player.y += PADDLE_SPEED;

    // AI follows the ball
    if (ai.y + PADDLE_HEIGHT / 2 < ballPos.y)
      ai.y += PADDLE_SPEED;
    if (ai.y + PADDLE_HEIGHT / 2 > ballPos.y)
      ai.y -= PADDLE_SPEED;

    // Ball collision with paddles
    if (CheckCollisionCircleRec(ballPos, BALL_RADIUS, player) ||
        CheckCollisionCircleRec(ballPos, BALL_RADIUS, ai))
      ballVelocity.x *= -1;

    // Ball collision with top and bottom
    if (ballPos.y >= GetScreenHeight() - BALL_RADIUS ||
        ballPos.y <= BALL_RADIUS)
      ballVelocity.y *= -1;

    ballPos.x += ballVelocity.x;
    ballPos.y += ballVelocity.y;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(player, WHITE);
    DrawRectangleRec(ai, WHITE);
//    DrawTextureV(ballTexture,
//                 Vector2{static_cast<float>(ballPos.x - BALL_RADIUS),
//                         static_cast<float>(ballPos.y - BALL_RADIUS)},
//                 WHITE);
    // DrawCircleV(ballPos, BALL_RADIUS, WHITE);
    Rectangle sourceRec = {0, 0, static_cast<float>(ballTexture.width),
                           static_cast<float>(ballTexture.height)};
    Rectangle destRec = {ballPos.x, ballPos.y,
                         static_cast<float>(ballTexture.width),
                         static_cast<float>(ballTexture.height)};
    Vector2 origin = {static_cast<float>(ballTexture.width / 2),
                      static_cast<float>(ballTexture.height / 2)};
    DrawTexturePro(ballTexture, sourceRec, destRec, origin, rotation, WHITE);
    rotation += 5.0;
    EndDrawing();
  }

  DrawCircleV(ballPos, BALL_RADIUS, WHITE);
  CloseWindow();
  return 0;
}
