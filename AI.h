#pragma once
#include <iostream>
#include <vector>

class AI
{
	public:
		int texture[2];//NPC tex
		int Health = 5;
		int *CharX;
		int *CharY;
		AI();
		~AI();
		void init();
		void Add_NPC(int posX, int posY, char NPC_ID);
		void NPC_Move(char **map, int sizeX, int sizeY, int СharacterX, int СharacterY, int speed);
		void NPCRend();
		void NPC_NextFrame(int num);
		void EnemyAnim(unsigned int iterat);
		void EnemyAnim_M(unsigned int iterat);
		void GetCharPos(int *x, int *y);
	private:	
		float TexCorX = 0.01;
		float TexCorY = 0.01;
		std::vector<float> EnemyPosX;
		std::vector<int> EnemyPosY;
		std::vector<char> EnemyID;
		std::vector<float> NPC_TexCordX;
		std::vector<float> NPC_TexCordY;
		std::vector<int> NPC_CurAnim;
};
