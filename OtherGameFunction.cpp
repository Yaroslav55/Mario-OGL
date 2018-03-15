/**********************************************
		MARIO
		DEV
		YAROSLAV	28.07.17
************************************************/
#include "stdafx.h"
#include <windows.h> 
#include <glut.h>
#include <fstream>
#include <iostream>
#include <SOIL.h>
#include <bass.h>
using namespace std;

#define DispSizeX 600.0
#define DispSizeY 400.0

const int strLev1 = 20;
const int H = 20;

void LoadTextures(GLuint tex[])
{
	tex[0] = SOIL_load_OGL_texture("textures/terrain.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	tex[1] = SOIL_load_OGL_texture("textures/mainCharacter.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	tex[2] = SOIL_load_OGL_texture("textures/mainCharacterMirror.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	tex[3] = SOIL_load_OGL_texture("textures/money.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	for (int i = 0;i<sizeof(tex) / sizeof(GLuint);i++)
	{
		if (tex[i] == 0)
			printf("Textures not found %d!.. Error\n", i + 1);
	}

	printf("Textures loaded!.. OK\n");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
int LoadLevel(char* name, char **data, int L, int H)
{
	ifstream FileData("Level/" + (string)name, ios::in | ios::binary);
	if (FileData)
	{
		printf("Level open.. OK\n");
		for (int r = 0; r < H; r++)
		{
			FileData.getline(data[r], L - 1, '$');
		}
	}
	else
	{
		cout << "Level cannot open: " << name << ".. Error" << endl;
		return -1;
	}
	FileData.close();
	return 0;
}

void RenderText(int x, int y, int z, char* text)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(0, 0, 0);
	glRasterPos3f(x, y, z);
	while (*text)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
}
void RenderButton(char* text, int posX, int posY, int height, int weight)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(posX, posY);
	glVertex2f(posX, posY + height);
	glVertex2f(posX + weight, posY + height);
	glVertex2f(posX + weight, posY);
	glEnd();

	RenderText(posX + 1, posY + 3, 0, text);
}
int ButtonCol(int mouse_x, int mouse_y, int x1, int y1, int Weight, int Height)
{
	if ((mouse_x > x1) && (mouse_x < x1 + Weight) &&
		(DispSizeY - mouse_y > y1) && (DispSizeY - mouse_y < y1 + Height))
		return 1;
	return 0;
}
void RenderGUI(char* title, int posX, int posY, int weight, int height, float r, float g, float b)
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(posX, posY);
	glVertex2f(posX, posY + height);
	glVertex2f(posX + weight, posY + height);
	glVertex2f(posX + weight, posY);
	glEnd();
	RenderText(240, 370, 0, title);
}
