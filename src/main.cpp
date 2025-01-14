#include "raylib.h"

typedef enum GameScreen
{
    MENU,
    GAME,
    SETTINGS
} GameScreen;

typedef struct Player
{
    Vector2 position;
    Texture2D texture;
    float speed;
    float health;
    char PlayerUsername[16];
    bool isRotatedToTheLeft;
    bool isJumping;
    bool isSneaking;
    bool isRunning;
    bool isAttacking;
    bool isWalking;
} Player;

typedef struct Block
{
    Vector2 position;
    Texture2D texture;
    char blockName[35];
    bool isSolid;
    bool isResistantToExplosion;
    bool isBreakable;
    bool isDamaging;
    float damage;
    float durability;
} Block;

int main()
{
    // Virtual resolution (fixed resolution for the game)
    int virtualWidth = 800;
    int virtualHeight = 600;

    // Initialize the window with resizable flag
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(virtualWidth, virtualHeight, "Viney");

    // Initialize audio device
    InitAudioDevice();

    // Create a RenderTexture2D to handle the texture rendering and scaling
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

    // Load custom fonts
    Font gameFont = LoadFont("./src/assets/fonts/regular.ttf");
    Font gameFontBold = LoadFont("./src/assets/fonts/bold.ttf");

    // Load the music
    Music bgMusic = LoadMusicStream("./src/assets/audio/bgMusic.mp3");
    PlayMusicStream(bgMusic);

    // Define the game state
    GameScreen currentScreen = MENU;

    // Boolean flag to track music state
    bool isMusicPlaying = true;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update the music stream
        UpdateMusicStream(bgMusic);

        // Get the current window size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        // Calculate the scale factor
        float scaleX = (float)screenWidth / virtualWidth;
        float scaleY = (float)screenHeight / virtualHeight;
        float scale = (scaleX < scaleY) ? scaleX : scaleY; // To maintain the aspect ratio

        // Calculate the offset to center the virtual resolution
        float offsetX = (screenWidth - (virtualWidth * scale)) * 0.5f;
        float offsetY = (screenHeight - (virtualHeight * scale)) * 0.5f;

        // Start drawing to the RenderTexture (virtual resolution)
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        if (currentScreen == MENU)
        {
            // Draw menu elements
            DrawTextEx(gameFont, "Viney's Universe", (Vector2){300, 200}, 20, 2, BLACK); // Adjusted coordinates

            // Draw Start Game button
            Rectangle startButton = {300, 300, 200, 50};
            DrawRectangleRec(startButton, LIGHTGRAY);
            DrawTextEx(gameFont, "Start Game", (Vector2){startButton.x + 20, startButton.y + 10}, 20, 2, BLACK);

            // Draw Settings button
            Rectangle settingsButton = {300, 400, 200, 50};
            DrawRectangleRec(settingsButton, LIGHTGRAY);
            DrawTextEx(gameFont, "Settings", (Vector2){settingsButton.x + 20, settingsButton.y + 10}, 20, 2, BLACK);

            // Check for button clicks
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePoint = GetMousePosition();
                // Adjust mouse coordinates according to the scale factor and offset
                mousePoint.x = (mousePoint.x - offsetX) / scale;
                mousePoint.y = (mousePoint.y - offsetY) / scale;
                if (CheckCollisionPointRec(mousePoint, startButton))
                {
                    currentScreen = GAME;
                }
                else if (CheckCollisionPointRec(mousePoint, settingsButton))
                {
                    currentScreen = SETTINGS;
                }
            }
        }
        else if (currentScreen == GAME)
        {
            // Draw game elements
            DrawTextEx(gameFont, "Game Screen", (Vector2){300, 200}, 20, 2, BLACK); // Adjusted coordinates
            Rectangle gameToMenuButton = {300, 400, 200, 50};
            DrawRectangleRec(gameToMenuButton, LIGHTGRAY);
            DrawTextEx(gameFont, "Go Back", (Vector2){gameToMenuButton.x + 20, gameToMenuButton.y + 10}, 20, 2, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePoint = GetMousePosition();
                // Adjust mouse coordinates according to the scale factor and offset
                mousePoint.x = (mousePoint.x - offsetX) / scale;
                mousePoint.y = (mousePoint.y - offsetY) / scale;
                if (CheckCollisionPointRec(mousePoint, gameToMenuButton))
                {
                    currentScreen = MENU;
                }
            }
        }
        else if (currentScreen == SETTINGS)
        {
            // Draw settings elements
            DrawTextEx(gameFont, "Settings", (Vector2){200, 200}, 20, 2, BLACK); // Adjusted coordinates

            DrawTextEx(gameFont, "Music (on/off)", (Vector2){165, 315}, 20, 2, BLACK);
            Rectangle musicIsPlayingButton = {300, 300, 200, 50};
            DrawRectangleRec(musicIsPlayingButton, LIGHTGRAY);
            DrawTextEx(gameFont, "Switch", (Vector2){musicIsPlayingButton.x + 20, musicIsPlayingButton.y + 10}, 20, 2, BLACK);

            Rectangle settingsToMenuButton = {300, 500, 200, 50};
            DrawRectangleRec(settingsToMenuButton, LIGHTGRAY);
            DrawTextEx(gameFont, "Go Back", (Vector2){settingsToMenuButton.x + 20, settingsToMenuButton.y + 10}, 20, 2, BLACK);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePoint = GetMousePosition();
                // Adjust mouse coordinates according to the scale factor and offset
                mousePoint.x = (mousePoint.x - offsetX) / scale;
                mousePoint.y = (mousePoint.y - offsetY) / scale;
                if (CheckCollisionPointRec(mousePoint, settingsToMenuButton))
                {
                    currentScreen = MENU;
                }
                else if (CheckCollisionPointRec(mousePoint, musicIsPlayingButton))
                {
                    if (isMusicPlaying)
                    {
                        PauseMusicStream(bgMusic);
                        isMusicPlaying = false;
                    }
                    else
                    {
                        ResumeMusicStream(bgMusic);
                        isMusicPlaying = true;
                    }
                }
            }
        }

        // End drawing to the RenderTexture
        EndTextureMode();

        // Begin drawing to the screen
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the RenderTexture (virtual resolution) to the screen (screen resolution) so everything is scaled and responsive.
        DrawTexturePro(target.texture,
                       (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height},
                       (Rectangle){offsetX, offsetY, (float)virtualWidth * scale, (float)virtualHeight * scale},
                       (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    // Unload resources and close the window
    UnloadFont(gameFont);
    UnloadFont(gameFontBold);
    UnloadRenderTexture(target);
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}