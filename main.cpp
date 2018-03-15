/**********************************************
			MARIO v0.2
			DEV
			YAROSLAV	28.07.17
************************************************/
#include "stdafx.h"
#include <windows.h> 
#include <glut.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <SOIL.h>
#include <bass.h>
#include <GameCollision.h>
#include <OtherGameFunction.h>
#include "Sound.h"
#include "AI.h"

using namespace std;
#define DispSizeX 600.0
#define DispSizeY 400.0


Sound g_snd;
AI g_ai;
//Lev conf
const int strLev = 20;
const int LenLev = 100;
int ArraySizeX = 60, ArraySizeY = 30, ArrayColors = 4;
int Score = 0;
int Health = 5;
GLuint *textureBG;
char* LevName = "LevGeom1.txt";
char* fileTextures1 = "LevDesign1.txt";//X
char* fileTextures2 = "LevDesign2.txt";//Y
char **OrderOfLevels;
GLfloat step = (GLfloat)1 / 16;
GLuint texture[4];
//SOUNG
char SoungName[] = "testSoung.mp3";
int speed = 10;
int gravity = 150;
boolean jump = false;
float TexCorX, TexCorY;
float AnimCorXChar = 0.01, AnimCorYChar = 0.67;
boolean CharAnimPlay = false;
boolean CollDet = false;
boolean Menu = true;
int CurWind = 0;
int CurCharPos = 1;// 1 -> right, 2 -> left
std::vector<int> Portal1;
std::vector<int> Portal2;


int СharacterPosX = 120, СharacterPosY = 120;
int Move = 0;

char **ArrayMap;
char **ArrayTexturesID_X;
char **ArrayTexturesID_Y;
int ButtonCord[2][3] = {
	{ 40, 40, 40 },
	{ 50, 80, 110 }
};
void InitSetting()
{

}
void CreateArray()
{
	//Create arrays
	textureBG = new GLuint[ArraySizeX / 15];
	ArrayMap = new char*[ArraySizeX];
	ArrayTexturesID_X = new char*[ArraySizeX];
	ArrayTexturesID_Y = new char*[ArraySizeX];
	for (int i = 0; i < ArraySizeX * 4; i++)
	{
		if (i < ArraySizeX)
		{
			ArrayMap[i] = new char[ArraySizeY];
			ArrayTexturesID_X[i] = new char[ArraySizeY];
			ArrayTexturesID_Y[i] = new char[ArraySizeY];
		}
	}
}
void InitArray()
{
	for (int i = 0; i < ArraySizeX; i++)
	{
		for (int r = 0; r < ArraySizeY + 4; r++)
		{
			ArrayMap[i][r] = '-';
			ArrayTexturesID_X[i][r] = '0';
			ArrayTexturesID_Y[i][r] = '0';
		}
		ArrayMap[i][ArraySizeY + 3] = '$';
		ArrayTexturesID_X[i][ArraySizeY + 3] = '$';
		ArrayTexturesID_Y[i][ArraySizeY + 3] = '$';
	}
}
void LoadBG(int sizeX, char curlvl)
{
	char a[22] = "Level/bg0/sky2.png";
	a[8] = curlvl;
	cout << a<<endl;
	for (int i = 0; i < sizeX * 40;i += 600)
	{
		a[13] = i / 600 + '0';
		if (!(textureBG[i / 600] = SOIL_load_OGL_texture(a,
			SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y)))
		{
			printf("BG not found.. Error\n");
			textureBG[i / 600] = SOIL_load_OGL_texture("textures/sky1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		}
	}
}
/*
	-1 - move NPC
	 0 - gravity
  1..4 - char anim
*/

void Timer(int value)
{
	switch (value)
	{
		case -1:
			g_ai.NPC_Move(ArrayMap, ArraySizeX, ArraySizeY, СharacterPosX, СharacterPosY, 10);
			glutTimerFunc(gravity + 100, Timer, -1);
			break;
		case 6:
			if (Move > -600)
				Move -= 5;
			else
				Move = 0;
			break;
		default:

		break;
	}//Game Timer
	if (CurCharPos == 1)
	{
		switch (value)
		{
		case 0:
			if (CollIsFloor(ArrayMap, ArraySizeY, ArraySizeX, СharacterPosX, СharacterPosY))
			{
				CollDet = true;
				jump = false;
			}
			if (!CollDet)
			{
				СharacterPosY -= 40;
				glutTimerFunc(gravity, Timer, 0);
			}
			else
			{
				if (!CharAnimPlay)
				{
					AnimCorXChar = 0.01f;
					AnimCorYChar = 0.01f;
				}
			}
			break;
		case 1:
			CharAnimPlay = true;
			AnimCorXChar = 0.01;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 2);
			break;
		case 2:
			AnimCorXChar = 0.2;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 3);
			break;
		case 3:
			AnimCorXChar = 0.01f;
			AnimCorYChar = 0.01f;
			glutTimerFunc(gravity, Timer, 4);
			break;
		case 4:
			AnimCorXChar = 0.4;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 5);
			CharAnimPlay = false;
			break;
		case 5:
			AnimCorXChar = 0.6;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 0);
			CharAnimPlay = false;
			break;
		default:

			break;
		}//Character Animation
	}
	else if( CurCharPos == 2 )
	{
		switch (value)
		{
		case 0:
			if (CollIsFloor(ArrayMap, ArraySizeY, ArraySizeX, СharacterPosX, СharacterPosY))
			{
				CollDet = true;
				jump = false;
			}
			if (!CollDet)
			{
				СharacterPosY -= 40;
				glutTimerFunc(gravity, Timer, 0);
			}
			else
			{
				if (!CharAnimPlay)
				{
					AnimCorXChar = 0.81f;
					AnimCorYChar = 0.01f;
				}
			}
			break;
		case 1:
			CharAnimPlay = true;
			AnimCorXChar = 0.01;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 2);
			break;
		case 2:
			AnimCorXChar = 0.2;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 3);
			break;
		case 3:
			AnimCorXChar = 0.01f;
			AnimCorYChar = 0.01f;
			glutTimerFunc(gravity, Timer, 4);
			break;
		case 4:
			AnimCorXChar = 0.4;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 5);
			CharAnimPlay = false;
			break;
		case 5:
			AnimCorXChar = 0.6;
			AnimCorYChar = 0.01;
			glutTimerFunc(gravity, Timer, 0);
			CharAnimPlay = false;
			break;
		default:

			break;
		}//Character Animation
	}

	glutPostRedisplay();
}
void NewGame()
{
	//Game Init
	ArraySizeY = 60;
	ArraySizeX = 65;
	CreateArray();
	InitArray();
	LoadBG(ArraySizeX, '1');
	LoadLevel(LevName, ArrayMap, ArraySizeY, ArraySizeX);
	LoadLevel(fileTextures1, ArrayTexturesID_X, ArraySizeY, ArraySizeX);
	LoadLevel(fileTextures2, ArrayTexturesID_Y, ArraySizeY, ArraySizeX);
	InitSetting();
	glutTimerFunc(gravity, Timer, -1);
	if (!CollIsFloor(ArrayMap, ArraySizeY, ArraySizeX, СharacterPosX, СharacterPosY) && !CollDet)
	{
		glutTimerFunc(gravity, Timer, 0);
	}
	else
	{
		CollDet = true;
		jump = false;
	}
}

void Logic()
{
	g_snd.clean();
}
void GenerateLevel()
{
	int i, r;//cicle
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	for (i = 0; i < ArraySizeX; i++)
	{
		for (r = 0; r < ArraySizeY; r++)
		{
			if (ArrayMap[i][r] != '-')
			{
				if (ArrayMap[i][r] == '#')
				{
					glBindTexture(GL_TEXTURE_2D, texture[0]);
					TexCorX = step * (ArrayTexturesID_X[i][r] - '0');
					TexCorY = step * (ArrayTexturesID_Y[i][r] - '0');
					glBegin(GL_QUADS);
						glTexCoord2f(TexCorX, TexCorY);
						glVertex2f(i * 40 + Move, r * 40);
						glTexCoord2f(TexCorX, TexCorY + step);
						glVertex2f(i * 40 + Move, r * 40 + 40);
						glTexCoord2f(TexCorX + step, TexCorY + step);
						glVertex2f(i * 40 + 40 + Move, r * 40 + 40);
						glTexCoord2f(TexCorX + step, TexCorY);
						glVertex2f(i * 40 + 40 + Move, r * 40);
					glEnd();
				}
				else if (ArrayMap[i][r] == '*')
				{
					glBindTexture(GL_TEXTURE_2D, texture[3]);
					glBegin(GL_QUADS);
						glTexCoord2f(0, 0);
							glVertex2f(i * 40 + Move, r * 40 );
						glTexCoord2f(0, 1);
							glVertex2f(i * 40 + Move, r * 40 + 40 );
						glTexCoord2f(1, 1);
							glVertex2f(i * 40 + 40 + Move, r * 40 + 40 );
						glTexCoord2f(1, 0);
							glVertex2f(i * 40 + 40 + Move, r * 40 );
					glEnd();
				}
				else if (ArrayMap[i][r] == '$')
				{
					glBindTexture(GL_TEXTURE_2D, texture[0]);
					glBegin(GL_QUADS);
					glTexCoord2f(TexCorX, TexCorY);
					glVertex2f(r * 40, i * 40);
					glTexCoord2f(TexCorX, TexCorY + step);
					glVertex2f(r * 40, i * 40 + 40);
					glTexCoord2f(TexCorX + step, TexCorY + step);
					glVertex2f(r * 40 + 40, i * 40 + 40);
					glTexCoord2f(TexCorX + step, TexCorY);
					glVertex2f(r * 40 + 40, i * 40);
					glEnd();
				}
				else//NPC
				{
					g_ai.Add_NPC(r * 40, i * 40, ArrayMap[i][r]);
					ArrayMap[i][r] = '-';
					//glutTimerFunc(gravity, Timer, -1);
				}
			}
		}
	}

}
void RenderBG()
{
	//BG
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	for (int i = 0; i < ArraySizeX * 40;i += 600)
	{
		glBindTexture(GL_TEXTURE_2D, textureBG[i / 600]);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
				glVertex2f(i + Move, 0);
			glTexCoord2f(1, 0);
				glVertex2f(i + 600 + Move, 0);
			glTexCoord2f(1, 1);
				glVertex2f(i + 600 + Move, 400);
			glTexCoord2f(0, 1);
				glVertex2f(i + Move, 400);
		glEnd();
	}
}
void GameMenu()
{
	glutTimerFunc(gravity, Timer, 6);
	RenderText(510, 45, 0, "Version 0.2");
	RenderButton(" New game", ButtonCord[0][2], ButtonCord[1][2], 25, 70);
	RenderButton(" Setting", ButtonCord[0][1], ButtonCord[1][1], 25, 70);
	RenderButton(" Exit", ButtonCord[0][0], ButtonCord[1][0], 25, 70);
	switch (CurWind)
	{
	case 1:
		RenderGUI("Setting", 150, 45, 400, 200, 0.7, 1, 0.7);
		break;

	}
}
void Display() {
	Logic();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderBG();
	GenerateLevel();//Load level
	if (Menu)
	{
		GameMenu();
	}
	else
	{
		if (!CollIsFloor(ArrayMap, ArraySizeY, ArraySizeX, СharacterPosX, СharacterPosY) && CollDet)
		{
			CollDet = false;
			glutTimerFunc(gravity, Timer, 0);
		}
		/*
		glBegin(GL_LINES);
			for (i = 0; i < 400;i +=40)
			{
				glVertex2f(0, i);
				glVertex2f(600, i);

			}
		glEnd();
		*/
		//Character
		CollBox(СharacterPosX, СharacterPosY);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture[CurCharPos]);
		glBegin(GL_QUADS);
			glTexCoord2f(AnimCorXChar, AnimCorYChar);
			glVertex2f(СharacterPosX, СharacterPosY);
			glTexCoord2f(AnimCorXChar, AnimCorYChar + 0.48);
			glVertex2f(СharacterPosX, СharacterPosY + 40);
			glTexCoord2f(AnimCorXChar + 0.19, AnimCorYChar + 0.48);
			glVertex2f(СharacterPosX + 40, СharacterPosY + 40);
			glTexCoord2f(AnimCorXChar + 0.19, AnimCorYChar);
			glVertex2f(СharacterPosX + 40, СharacterPosY);
		glEnd();
		g_ai.NPCRend();
		char a = Health + '0';
		RenderText(СharacterPosX + 300, 45, 0, "Health ");
		RenderText(СharacterPosX + 355, 45, 0, &a);
		a = Score + '0';
		RenderText(СharacterPosX + 200, 45, 0, "Score ");
		RenderText(СharacterPosX +255, 45, 0, &a);
	}
	glFlush();
}
void MouseButton(int button, int state, int x, int y)
{
	if (ButtonCol(x, y, ButtonCord[0][2], ButtonCord[1][2], 70, 25))//New game
	{
		NewGame();
		Move = 0;
		Menu = false;
	}
	if (ButtonCol(x, y, ButtonCord[0][1], ButtonCord[1][1], 70, 25))//Setting
	{
		CurWind = 1;
	}
	else if (ButtonCol(x, y, ButtonCord[0][0], ButtonCord[1][0], 70, 25))//EXIT
	{
		exit(0);
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	int i;
	if (Collision('d', 10, ArrayMap, СharacterPosX, СharacterPosY, ArraySizeY, ArraySizeX, "player") == 3)
	{
		g_snd.play("sound/money.mp3");
		Score++;
	}
	switch (key) 
	{
		case 27:
			exit(0);
		break;
		case 'r':
			glutPostRedisplay();
			break;
		case 'd':
			if (Collision('d', -10, ArrayMap, СharacterPosX, СharacterPosY, ArraySizeY, ArraySizeX, "player") )
			{
				if (CurCharPos != 1)
					CurCharPos = 1;
				//cout << texture[1]<<endl;
				glTranslated(-speed, 0, 0);
				СharacterPosX += speed;
				glutPostRedisplay();
			}
			if (!CharAnimPlay)
				glutTimerFunc(gravity - 50, Timer, 1);
			break;
		case 'a':
			if (Collision('a', -10, ArrayMap, СharacterPosX, СharacterPosY, ArraySizeY, ArraySizeX, "player"))
			{
				if (CurCharPos != 2)
					CurCharPos = 2;
				glTranslated(speed, 0, 0);
				СharacterPosX -= speed;
				glutPostRedisplay();
			}
			if (!CharAnimPlay)
				glutTimerFunc(gravity - 50, Timer, 1);
			break;
		case 'w':
			if( !jump )
			{
				jump = true;
				for (i = 0;i < 10;i++)
				{
					if( Collision('w', 0, ArrayMap, СharacterPosX, СharacterPosY, ArraySizeY, ArraySizeX, "player") )
						СharacterPosY += speed + 10;
				}
				AnimCorXChar = 0.61f;
				AnimCorYChar = 0.01f;
				glutPostRedisplay();
			}
			break;
		default:
	
			glutPostRedisplay();
				break;
	}
}
void Initialize() {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, DispSizeX, 0.0, DispSizeY, -1.0, 1.0);
	//Game Init
	ArraySizeY = 30;
	ArraySizeX = 60;
	CreateArray();
	InitArray();
	LoadTextures(texture);
	g_ai.init();
	LoadBG(ArraySizeY, '0');
	glutKeyboardFunc(Keyboard);
	g_snd.init();
	g_snd.play("sound/start.mp3");
	g_ai.GetCharPos(&СharacterPosX, &СharacterPosY);
	if (Menu)
	{
		LoadLevel("menu.txt", ArrayMap, ArraySizeX, ArraySizeY);
		LoadLevel("menuTx1.txt", ArrayTexturesID_X, ArraySizeX, ArraySizeY);
		LoadLevel("menuTx2.txt", ArrayTexturesID_Y, ArraySizeX, ArraySizeY);
		glutMouseFunc(MouseButton);
	}
	//g_snd.play(SoungName);
}
int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(400, 250);
	glutCreateWindow("Mario v0.2");
	glutDisplayFunc(Display);
	Initialize();	// Main cycle 
	glutMainLoop();
	return 0;
}