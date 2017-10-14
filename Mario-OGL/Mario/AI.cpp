#include "stdafx.h"
#include "AI.h"
#include "GameCollision.h"
#include "glut.h"
#include "SOIL.h"

AI::AI()
{
}
AI::~AI()
{
}

void AI::init()
{
	//NPC
	texture[0] = SOIL_load_OGL_texture("textures/mainCharacter.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	texture[1] = SOIL_load_OGL_texture("textures/mainCharacterMirror.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//NPC mirror tex
	for (int i = 0;i<sizeof(texture) / sizeof(GLuint);i++)
	{
		if (texture[i] == 0)
			printf("Textures not found %d!.. Error\n", i + 1);
	}
}
void AI::GetCharPos(int *x, int *y)
{
	CharX = x;
	CharY = y;
}
void AI::Add_NPC(int posX, int posY, char NPC_ID)
{
	if( (NPC_ID == '0') || (NPC_ID == '1'))
	{
			EnemyPosX.push_back(posX);
			EnemyPosY.push_back(posY);
			EnemyID.push_back('0');//Only char!
			NPC_CurAnim.push_back(1);
			NPC_TexCordX.push_back(0.01f);
			NPC_TexCordY.push_back(0.01f);
	}
}
void AI::NPC_Move(char **map, int sizeX, int sizeY, int СharacterX, int СharacterY, int speed)
{
	int a;
	for (unsigned int i = 0; i < EnemyID.size();i++)
	{
		NPC_NextFrame(i);
		if (EnemyID[i] == '1')//Classic enemy
		{
			if (Collision('a', 10, map, EnemyPosX[i], EnemyPosY[i], sizeY, sizeX))//coll with wall
			{
				a = CollisionWithItems(EnemyPosX[i], EnemyPosY[i], СharacterX, СharacterY);
				if (a == 1)//Coll with character, game over
				{
					Health--;
					*CharY = 240;
				}
				else if (a == 2)//Coll with character up
				{
					EnemyID.erase(EnemyID.begin() + i);
					EnemyPosX.erase(EnemyPosX.begin() + i);
					EnemyPosY.erase(EnemyPosY.begin() + i);
					printf("Kill NPC !\n");
				}
				else
				{
					EnemyPosX[i] -= speed;
					glutPostRedisplay();
				}
			}
			else
			{
				EnemyID[i] = '0';

			}
		}
		else if (EnemyID[i] == '0')
		{
			if (Collision('d', 10, map, EnemyPosX[i], EnemyPosY[i], sizeY, sizeX))
			{
				a = CollisionWithItems(EnemyPosX[i], EnemyPosY[i], СharacterX, СharacterY);
				if (a == 2)//Coll with character up
				{
					EnemyID.erase(EnemyID.begin() + i);
					EnemyPosX.erase(EnemyPosX.begin() + i);
					EnemyPosY.erase(EnemyPosY.begin() + i);
					printf("Kill NPC !\n");
				}
				else if (a == 1)//Coll with character, game over
				{

				}
				else
				{
					EnemyPosX[i] += speed;
					glutPostRedisplay();
				}
			}
			else
				EnemyID[i] = '1';
		}
	}
}
void AI::NPCRend()
{
	for (unsigned int i = 0; i < EnemyID.size();i++)//Render Enemy
	{
		CollBox(EnemyPosX[i], EnemyPosY[i]);
	//	printf("%f\n", NPC_TexCordX[i]);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture[EnemyID[i] -'0']);
		glBegin(GL_QUADS);
			glTexCoord2f(NPC_TexCordX[i], NPC_TexCordY[i]);
				glVertex2f(EnemyPosX[i], EnemyPosY[i]);
			glTexCoord2f(NPC_TexCordX[i], NPC_TexCordY[i] +0.49);
				glVertex2f(EnemyPosX[i], EnemyPosY[i] + 40);
			glTexCoord2f(NPC_TexCordX[i] +0.2, NPC_TexCordY[i] +0.49);
				glVertex2f(EnemyPosX[i] + 40, EnemyPosY[i] + 40);
			glTexCoord2f(NPC_TexCordX[i] +0.2, NPC_TexCordY[i]);
				glVertex2f(EnemyPosX[i] + 40, EnemyPosY[i]);
		glEnd();
	}
}
void AI::NPC_NextFrame(int num)
{
	switch (EnemyID[num])
	{
		case '0':
		{
			EnemyAnim(num);
			break;
		}
		case '1':
		{
			EnemyAnim_M(num);
			break;
		}
		default:
			break;
	}
}
void AI::EnemyAnim(unsigned int iterat)
{
	switch ( NPC_CurAnim[iterat] )
	{
		case 1:
		{
			NPC_TexCordX[iterat] = 0.21f;
			NPC_TexCordY[iterat] = 0.01f;
			NPC_CurAnim[iterat] += 1;
			break;
		}
		case 2:
		{
			NPC_TexCordX[iterat] = 0.41f;
			NPC_TexCordY[iterat] = 0.01f;
			NPC_CurAnim[iterat] += 1;
			break;
		}
		case 3:
		{
			NPC_TexCordX[iterat] = 0.61f;
			NPC_TexCordY[iterat] = 0.01f;
			NPC_CurAnim[iterat] = 1;
			break;
		}
		default:
			break;
	}
}
void AI::EnemyAnim_M(unsigned int iterat)
{
	switch (NPC_CurAnim[iterat])
	{
	case 1:
	{
		NPC_TexCordX[iterat] = 0.21f;
		NPC_TexCordY[iterat] = 0.01f;
		NPC_CurAnim[iterat] += 1;
		break;
	}
	case 2:
	{
		NPC_TexCordX[iterat] = 0.41f;
		NPC_TexCordY[iterat] = 0.01f;
		NPC_CurAnim[iterat] += 1;
		break;
	}
	case 3:
	{
		NPC_TexCordX[iterat] = 0.61f;
		NPC_TexCordY[iterat] = 0.01f;
		NPC_CurAnim[iterat] = 1;
		break;
	}
	default:
		break;
	}
}