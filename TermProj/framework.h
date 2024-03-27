#pragma once
#include <Windows.h>
#include <vector>
#include "object.h"
#include "tank.h"
#include "enemy.h"
#include "controller.h"
#include "Obstacle.h"
class Framework
{
public:
	int GAME_LEVEL = 1;
	int bazooka_check = 0;
	int rifle_check = 0;
	int item_check = 0;

	float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
	float aveX, aveY, aveZ;
	float scaleX, scaleY, scaleZ;
	float minX = 0.0, minY = 0.0, minZ = 0.0;
	float maxX = 0.0, maxY = 0.0, maxZ = 0.0;
	float scaleAll;
	float sizeX, sizeY, sizeZ;



	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;
	
	vector<Object*> object_vec;
	Controller* controller;

	int loadObj(const char* filename);
	int loadObj_normalize_center(const char* filename);

	Framework() { 
		ATank* playerTank = new ATank();
		object_vec.emplace_back(playerTank);
		controller = new Controller(playerTank);
	}

	void InitBuffer();
	void InitTexture();
	void keyInput(unsigned char key, bool bPush);
	void keyInput(int key, bool bPush);

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
	void collide_check();
	void update_level(time_t start);
	bool select_button = 0;
};

