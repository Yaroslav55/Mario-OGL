#pragma once
const int H1 = 20;
void LoadTextures(GLuint tex[]);
int LoadLevel(char* name, char **data, int L, int H);
void RenderText(int x, int y, int z, char* text);
void RenderButton(char* text, int posX, int posY, int height, int weight);
int ButtonCol(int mouse_x, int mouse_y, int x1, int y1, int Weight, int Height);
void RenderGUI(char* title, int posX, int posY, int weight, int height, float r, float g, float b);