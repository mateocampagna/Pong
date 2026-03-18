#include "raylib.h"

int main(void)
{
    int scoreP1 = 0;
    int scoreP2 = 0;
    
    const int screenWidth = 1000;
    const int screenHeight = 800;

    float rectWidth = 30.0f;
    float rectHeight = 150.0f;

    // players
    Vector2 player1Position = { 0.0f, (screenHeight / 2.0f) - (rectHeight / 2.0f) };
    Vector2 player2Position = { screenWidth - rectWidth, (screenHeight / 2.0f) - (rectHeight / 2.0f) };

    // ball
    float ballRadius=10.0f;
    Vector2 ballPos = {screenWidth/2.0f, screenHeight/2.0f};
    Vector2 ballVelocity = { 5.0f, 5.0f };

    InitWindow(screenWidth, screenHeight, "PONG in c!!");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        // --------- INPUTS ---------
        if (IsKeyDown(KEY_W)) player1Position.y -= 5.0f;
        if (IsKeyDown(KEY_S)) player1Position.y += 5.0f;

        if (IsKeyDown(KEY_UP)) player2Position.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) player2Position.y += 5.0f;

        // --------- LIMITS ---------
        if (player1Position.y < 0) player1Position.y = 0;
        if (player1Position.y + rectHeight > screenHeight)
            player1Position.y = screenHeight - rectHeight;

        if (player2Position.y < 0) player2Position.y = 0;
        if (player2Position.y + rectHeight > screenHeight)
            player2Position.y = screenHeight - rectHeight;

        // --------- BALL ---------
        ballPos.x += ballVelocity.x;
        ballPos.y += ballVelocity.y;

        // rebote arriba abajo
        if(ballPos.y - ballRadius <= 0 || ballPos.y + ballRadius >= screenHeight) ballVelocity.y *= -1;

        // --------- COLLISIONS ---------
        // player 1
        if(ballPos.x - ballRadius <= player1Position.x + rectWidth 
            && ballPos.y >= player1Position.y 
            && ballPos.y <= player1Position.y + rectHeight){ ballVelocity.x *= -1;}
        // player 2
        if(ballPos.x + ballRadius >= player2Position.x 
            && ballPos.y >= player2Position.y 
            && ballPos.y <= player2Position.y + rectHeight) { ballVelocity.x *= -1; }   
        
        // --------- SCORE ---------
        // p2 point
        if (ballPos.x < 0) {
            scoreP2++;
            ballPos = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            ballVelocity = (Vector2){ 5.0f, 4.0f };
        }

        // p1 point
        if (ballPos.x > screenWidth) {
            scoreP1++;
            ballPos = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            ballVelocity = (Vector2){ -5.0f, 4.0f };
        }
    
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText(TextFormat("%d", scoreP1), screenWidth/4, 20, 20, WHITE);
            DrawText(TextFormat("%d", scoreP2), 3*screenWidth/4, 20, 20, WHITE);

            DrawRectangle(player1Position.x, player1Position.y, rectWidth, rectHeight, WHITE);
            DrawRectangle(player2Position.x, player2Position.y, rectWidth, rectHeight, WHITE);
            DrawCircle(ballPos.x, ballPos.y, ballRadius, WHITE);
            
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}