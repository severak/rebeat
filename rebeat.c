#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "src/raygui.h"

int main(int argc, char *argv[])
{
    printf("re:Beat - sampler/sequencer/drum machine/thing");
    printf("----------------------------------------------");
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 640;
    const int screenHeight = 480;
    const int FPS = 25;

   
    InitAudioDevice();
    
    Sound snd[8];
    snd[0] = LoadSound("samples/juno1_tom.wav");
    snd[1] = LoadSound("samples/krabice_klavesy.wav");
    snd[2] = LoadSound("samples/pixi_clap.wav");
    snd[3] = LoadSound("samples/pixi_base.wav");
    snd[4] = LoadSound("samples/plechovka_mejdlo.wav");
    snd[5] = LoadSound("samples/juno1_basa.wav");
    snd[6] = LoadSound("samples/juno1_bass39.wav");
    snd[7] = LoadSound("samples/juno1_housle.wav");
    
    SetSoundVolume(snd[0], 0.5);
    SetSoundVolume(snd[1], 0.5);
    SetSoundVolume(snd[2], 0.5);
    SetSoundVolume(snd[3], 0.5);
    SetSoundVolume(snd[4], 0.5);
    SetSoundVolume(snd[5], 0.5);
    SetSoundVolume(snd[6], 0.5);
    SetSoundVolume(snd[7], 0.5);

    InitWindow(screenWidth, screenHeight, "re:Beat");
    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    int tickcnt = 0;
    bool running = 0;
    
    int step = 0;
    int BPM = 125;
    int SPB = 4;
    
    if (argc>1) {
        BPM = atoi(argv[1]);
    }
    
    int drums[128]= {0};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            if (IsKeyReleased(KEY_SPACE)) {
                if (running) {
                    running = false;
                    step = 0;
                } else {
                    running = true;
                }
            }
            
            if (IsKeyReleased(KEY_DELETE)) {
                int i = 0;
                for (i = 0; i<128;i++) {
                    drums[i] = 0;
                }
                
            }



            ClearBackground(RAYWHITE);
            DrawFPS(620,0);
            
            if (GuiButton((Rectangle){ 0, 0, 115, 30 }, "#01# Open song")) { }
            if (GuiButton((Rectangle){ 116, 0, 115, 30 }, "#02# Save song")) { }
            if (GuiButton((Rectangle){ 200, 0, 115, 30 }, running ? "#133# Stop" : "#131# Play")) { running = running ? false: true; }
            
            // DrawText("re:Beat READY...", 10, 0, 20, GREEN);
            // DrawText(TextFormat("step=%d, tick=%d", step, tickcnt), 470, 0, 20, LIGHTGRAY);
            int x;
            int y;
            for (x=0; x<16; x++) {
                for (y=0; y<8; y++) {
                    DrawRectangleLines(100 + (30*x), 30 + (30*y),30, 30, DARKBLUE);
                    if (drums[(16*y) + x]==1) {
                        DrawCircle(115 + (30*x), 35 + (30*y), 10, GRAY);
                    }
                    
                    if (IsMouseButtonReleased(0)) {
                        Vector2 mousePos = GetMousePosition();
                        if (mousePos.x >= 100 + (30*x) &&  mousePos.x <= 130 + (30*x) && mousePos.y >= 30 + (30*y) &&  mousePos.y <= 60 + (30*y)) {
                            drums[(16*y) + x] = drums[(16*y) + x]==0 ? 1 : 0;
                            // DrawText(TextFormat("Yes"), 100 + (30*x), 20 + (30*y), 20, RED);
                        }
                    }
                    
                    // if (IsMouseButtonDown(0)) {
                    //    DrawText(TextFormat("xlucrecia my reflection"), GetMouseX(), GetMouseY(), 20, RED);
                    // }
                }
            }
            
            DrawCircle(115+(step*30),285, 10, RED);
            
            DrawText("j1_tom", 0, 20 + (30*0), 10, DARKGRAY);
            DrawText("krabice", 0, 20 + (30*1), 10, DARKGRAY);
            DrawText("clap", 0, 20 + (30*2), 10, DARKGRAY);
            DrawText("pixi_base", 0, 20 + (30*3), 10, DARKGRAY);
            DrawText("plechovka", 0, 20 + (30*4), 10, DARKGRAY);
            DrawText("j1_basa", 0, 20 + (30*5), 10, DARKGRAY);
            DrawText("j1_bass39", 0, 20 + (30*6), 10, DARKGRAY);
            DrawText("j1_housle", 0, 20 + (30*7), 10, DARKGRAY);
            
            DrawText("press SPACE to start/stop", 100, 333, 20, BLUE);
            DrawText("press DELETE to ZAP data", 100, 353, 20, BLUE);
            DrawText("press ESC to exit...", 100, 373, 20, LIGHTGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
        
        if (running) {
            tickcnt = (tickcnt + 1) % (FPS / ( (BPM * SPB)/60));
            if (tickcnt == 0) {
                int i = 0;
                for (i = 0; i<8;i++) {
                    if (drums[(16*i) + step]==1) {
                        PlaySound(snd[i]);
                    }
                }
                
                step = (step + 1)  % 16;
            }
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    CloseAudioDevice();
    
    printf("KTHXBYE");
    return 0;
}