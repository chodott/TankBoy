#pragma once
#include <Windows.h>
#include <vector>
#include <queue>
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
	bool map[50][50]; // �� ������ 50x50

	time_t start_time; //�ð� ����


	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;
	
	vector<vector<Object*>> object_vec;
	Controller* controller;
	 priority_queue<int, vector<int>, greater<int>> deleteEnemy_pq;

	int loadObj(const char* filename);
	int loadObj_normalize_center(const char* filename);

	Framework() { 
		start_time = time(NULL); //���� �ð� ����
		ATank* playerTank = new ATank();
		object_vec.resize(5);
		object_vec[0].emplace_back(playerTank);
		controller = new Controller(playerTank);
		Wall* leftWall = new Wall(-25.f, 25.f, 0.f, 1);
		Wall* rightWall = new Wall(0.f, 25.f, -25.f, -1);
		Wall* floor = new Wall(0, 0, 0, 0);
		object_vec[4] = (vector<Object*>{leftWall, rightWall, floor});
		fill(&map[0][0], &map[49][49], false);

	}

	void InitBuffer();
	void InitTexture();
	void keyInput(unsigned char key, bool bPush);
	void keyInput(int key, bool bPush);

	void makeMap();
	void spawn(int level);
	void draw(GLuint s_program);
	void update();
	void checkCollide();
	void deleteTrash();
	void update_level(time_t start);
	bool select_button = 0;
};

