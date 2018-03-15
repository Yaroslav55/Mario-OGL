#pragma once
int CollBoxPosition(int CharacterPos, int offset);
void CollBox(int objX, int objY);
/*
False - collision detected
True - collision not detected
map - Level geom
*/
int Collision(char curkey, int offset, char **map, int ObjX, int ObjY, int L, int H, std::string pers = "other");
int CollisionWithItems(int itemsX, int itemsY, int ObjX, int ObjY);
/*
	curkey - pressed key
	map - Level geom
	L - level lenght
	H - level Hight
*/
int CollIsFloor(char **map, int L, int H, int ObjX, int ObjY);