/**********************************************
				MARIO
				DEV
				YAROSLAV	28.07.17
************************************************/
#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <windows.h> 
#include <vector>
#include <glut.h>

int CollBoxPosition(int CharacterPos, int offset)
{
	int pos;
	pos = floor((CharacterPos - offset) / 10) * 10;

	if (fmod(pos, 40) != 0)
	{
		if (fmod(pos + 10, 40) == 0)
			pos += 10;
		else if (fmod(pos, 40) == 10)
		{
			pos -= 10;
		}
		else if (fmod(pos, 40) == 20)
		{
			pos -= 20;
		}
		else
		{
			printf("COLLISION BOX ERROR!%d\n", pos);
			return -1;
		}
	}
	return pos;
}
void CollBox(int objX, int objY)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	// Coll. Box
	glVertex2f(CollBoxPosition(objX, 10), CollBoxPosition(objY, 0));
	glVertex2f(CollBoxPosition(objX, 10), CollBoxPosition(objY, 0) + 40);
	glVertex2f(CollBoxPosition(objX, 10) + 40, CollBoxPosition(objY, 0) + 40);
	glVertex2f(CollBoxPosition(objX, 10) + 40, CollBoxPosition(objY, 0));
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

int Collision(char curkey, int offset, char **map,int ObjX,int ObjY,int L, int H, std::string pers)
{
	int i, r;
	for (i = 0; i < L; i++)
	{
		for (r = 0; r < H; r++)
		{
			if (map[r][i] == '#')
			{
				if (curkey == 'w')
				{
					if ((CollBoxPosition(ObjX, 0) == r * 40) &&
						(CollBoxPosition(ObjY, 0) + 40 == i * 40))
						return 0;

				}
				if (curkey == 'd')
				{
					if ((CollBoxPosition(ObjX, 20) + 40 == r * 40) &&
						(CollBoxPosition(ObjY, 0) == i * 40)
						//&&(СharacterPosX + offset == i * 40)
						)
						return 0;
				}
				if (curkey == 'a')
				{
					if ((CollBoxPosition(ObjX, -20) - 40 == r * 40) &&
						(CollBoxPosition(ObjY, 0) == i * 40)
						//&&(СharacterPosX + offset-40 == i * 40)
						)
						return 0;
				}
			}
			if (map[r][i] == '*')
			{

				if (pers == "player")
				{
					if ((CollBoxPosition(ObjX, 20) == r * 40) &&
						(CollBoxPosition(ObjY, 0) == i * 40))
					{
						map[r][i] = '-';
						return 3;
					}
				}
			}
		}
	}
	return 1;
}
int CollisionWithItems(int itemsX, int itemsY, int ObjX, int ObjY)
{
	if ((CollBoxPosition(itemsX, 0)== CollBoxPosition(ObjX, 0)) &&//GAME OVER
		(CollBoxPosition(itemsY, 0) == CollBoxPosition(ObjY, 0)))
		return 1;
	if ((CollBoxPosition(itemsX, 0) == CollBoxPosition(ObjX, 0)) &&// KILL ENEMY
		(CollBoxPosition(itemsY, 0)+40 == CollBoxPosition(ObjY, 0)))
		return 2;


	return 0;
}
int CollIsFloor(char **map, int L, int H, int ObjX, int ObjY)
{
	int i, r;
	boolean isfloor = false;
	for (i = 0; i < L; i++)//Find floor 
	{
		for (r = 0; r < H; r++)
		{
			if (map[r][i] == '#')
			{
				if ((CollBoxPosition(ObjX, 0) == r * 40) &&
					(CollBoxPosition(ObjY, -10) == i * 40 + 40))
				{
					isfloor = true;
					return true;
				}
			}
		}
	}
	return false;
}
