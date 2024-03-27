#pragma once
#include "object.h"
class ATank : public Object
{
public:
	static int obj_body;
	static int obj_head;
	static int obj_cannon;
	static unsigned int body_texture;
	static unsigned int head_texture;
	static unsigned int cannon_texture;


	static GLuint VAO[4]; //[0]:탱크 몸통 [1]:포물선 [2]:탱크 머리 [3]:탱크 포신
	static GLuint VBO_pos[4], VBO_nor[4], VBO_tex[4];
	float x, y, z;
	float tankR = 0; //몸체 각도
	float headR = 0; //머리 각도
	float heady = 0.0f; //머리 애니메이션에 사용
	float maxRange = 5.0f;
	float minRange = 2.0f;
	float reload = 1.0f;
	int head_frame = 0; //머리 흔들리는 애니메이션에 사용
	int power = 5;
	int timer = 0;
	int maxhp = 20;
	int hp = 20;
	int headDirection = 0;	//1 : Left / -1: Right

	bool bPushedSpace = false;
	bool supermode = false;
	bool death = false;

	void draw(unsigned int modelLocation, unsigned int objColorLocation);

	void move();

	void update();

	void charge();

	void attack();

	void hit();

	void turnHead(int direction);

	void stopHead(int direction);

	void upgrade(int skill);

};
