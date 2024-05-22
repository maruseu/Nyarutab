#include <math.h>
#include "raylib.h"
#include "getMouse.h"
#include "ico.h"

float lerp(float v0, float v1, float t) { return v0 + t * (v1 - v0); }

int colCmp(Color CA, Color CB){ return (CA.r==CB.r && CA.g==CB.g && CA.b==CB.b && CA.a==CB.a); }

void drawX(int x, int y, Color c) { DrawLine(x-2,y-2,x+2,y+2,c); DrawLine(x+2,y-2,x-2,y+2,c); }

int main(void){

    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(200, 200,"Nyarutab");
    SetTargetFPS(60);

    Texture2D PenTexture, BackTexture, FrontTexture;
    int PenOX=0, PenOY=0; //Pen origin
    float 
    x1 =   0, y1 =   0,
    x2 = 200, y2 =   0,
    x3 =   0, y3 = 200,
    x4 = 200, y4 = 200; //Rectangle corners

    int windowWid=200, windowHei=200;
    int DebugInfo=0;

    if(FileExists("./pen.png")) {
      Image Pen = LoadImage("./pen.png");
      for(int i=0;i<Pen.height;i++){
        for(int j=0;j<Pen.width;j++){
          if (colCmp(GetImageColor(Pen,j,i),(Color){255,0,0,255})) {
            PenOX=j;
            PenOY=i;
            ImageDrawPixel(&Pen, j, i, GetImageColor(Pen,j,i-1));
          }
        }
      }
      PenTexture = LoadTextureFromImage(Pen);
      UnloadImage(Pen);
    }
    
    if(FileExists("./front.png")) {  
      Image Front = LoadImage("./front.png");
      windowWid=Front.width;
      windowHei=Front.height;
      for(int i=0;i<Front.height;i++){
        for(int j=0;j<Front.width;j++){
          if (colCmp(GetImageColor(Front,j,i),(Color){255,0,0,255})) {
            x1=j;
            y1=i;
            ImageDrawPixel(&Front, j, i, GetImageColor(Front,j,i-1));
          }
          if (colCmp(GetImageColor(Front,j,i),(Color){0,255,0,255})) {
            x2=j;
            y2=i;
            ImageDrawPixel(&Front, j, i, GetImageColor(Front,j,i-1));
          }
          if (colCmp(GetImageColor(Front,j,i),(Color){0,0,255,255})) {
            x3=j;
            y3=i;
            ImageDrawPixel(&Front, j, i, GetImageColor(Front,j,i-1));
          }
          if (colCmp(GetImageColor(Front,j,i),(Color){255,0,255,255})) {//https://i.redd.it/zh4z7cem9kg51.png
            x4=j;
            y4=i;
            ImageDrawPixel(&Front, j, i, GetImageColor(Front,j,i-1));
          }
        }
      }
      FrontTexture = LoadTextureFromImage(Front);
      UnloadImage(Front);
    }
    if(FileExists("./back.png")) {  
      Image Back = LoadImage("./back.png");
      windowWid=Back.width;
      windowHei=Back.height;
      for(int i=0;i<Back.height;i++){
        for(int j=0;j<Back.width;j++){
          if (colCmp(GetImageColor(Back,j,i),(Color){255,0,0,255})) {
            x1=j;
            y1=i;
            ImageDrawPixel(&Back, j, i, GetImageColor(Back,j,i-1));
          }
          if (colCmp(GetImageColor(Back,j,i),(Color){0,255,0,255})) {
            x2=j;
            y2=i;
            ImageDrawPixel(&Back, j, i, GetImageColor(Back,j,i-1));
          }
          if (colCmp(GetImageColor(Back,j,i),(Color){0,0,255,255})) {
            x3=j;
            y3=i;
            ImageDrawPixel(&Back, j, i, GetImageColor(Back,j,i-1));
          }
          if (colCmp(GetImageColor(Back,j,i),(Color){255,0,255,255})) {
            x4=j;
            y4=i;
            ImageDrawPixel(&Back, j, i, GetImageColor(Back,j,i-1));
          }
        }
      }
      BackTexture = LoadTextureFromImage(Back);
      UnloadImage(Back);
    }

    int restX=3, restY=-8;
    Image imIco = LoadImageFromMemory(".png", __icon_png, __icon_png_len);
    SetWindowIcon(imIco);
    SetWindowSize(windowWid,windowHei);

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_F1)) DebugInfo=!DebugInfo;

        BeginDrawing();
        if(!DebugInfo) ClearBackground((Color){0,0,0,0});
        else ClearBackground(WHITE);

        float mouseX = mousePosX()-(int)GetMonitorPosition(GetCurrentMonitor()).x; //Get mouse input and offset it by monitor pos.
        float mouseY = mousePosY()-(int)GetMonitorPosition(GetCurrentMonitor()).y;

        float xMul = mouseX/(float)GetMonitorWidth(GetCurrentMonitor()); //Normalize mouse input
        float yMul = mouseY/(float)GetMonitorHeight(GetCurrentMonitor());

        float x1x = lerp(x1,x2,xMul); //Interpolate top based on mouse x
        float x1y = lerp(y1,y2,xMul);
        float x2x = lerp(x3,x4,xMul); //Interpolate bottom based on mouse x
        float x2y = lerp(y3,y4,xMul);

        int fx = lerp(x1x,x2x,yMul); //Interpolate top and bottom based on mouse y
        int fy = lerp(x1y,x2y,yMul);

        DrawTexture(BackTexture,0,0,WHITE);
        DrawTexture(PenTexture,fx-PenOX+(!getMouseBtn()*restX),fy-PenOY+(!getMouseBtn()*restY),WHITE);
        DrawTexture(FrontTexture,0,0,WHITE);

        if(DebugInfo){
          DrawLine(x1,y1,x2,y2,BLUE);
          DrawLine(x2,y2,x4,y4,BLUE);
          DrawLine(x3,y3,x4,y4,BLUE);
          DrawLine(x3,y3,x1,y1,BLUE);
          drawX(x1,y1,RED);
          drawX(x2,y2,GREEN);
          drawX(x3,y3,BLUE);
          drawX(x4,y4,MAGENTA);
          drawX(fx,fy,RED);
          DrawText(TextFormat("\
 fps: %i\n\
 mouse: %.0fx%.0f\n\
          %ix%i\n\
 mon index:%i\n\
 mon res: %ix%i\n\
 mon pos: %.0fx%.0f\n",
          GetFPS(),
          mouseX, mouseY,
          fx,fy,
          GetCurrentMonitor(),
          GetMonitorWidth(GetCurrentMonitor()),GetMonitorHeight(GetCurrentMonitor()),
          GetMonitorPosition(GetCurrentMonitor()).x,GetMonitorPosition(GetCurrentMonitor()).y
          ),0,0,10,BLACK);
        }
        EndDrawing();

    }
    
    return 0;
}