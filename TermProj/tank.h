#pragma once
#include "Pawn.h"
#include "Item.h"

#define TANK_SIZE 1.f
#define BODY_ROTATE_SPEED 1.f
#define HEAD_ROTATE_SPEED 5.f
#define ACCELERATION 0.004f
#define DECELERATION 0.006f
#define UPGRADE_CNT 5

class ATank : public Pawn
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

	float maxSpeed = 0.12f;
	float maxRange = 5.0f;
	float minRange = 2.0f;

	float tankR = 0; //몸체 각도
	float headR = 0; //머리 각도
	float heady = 0.0f; //머리 애니메이션에 사용
	float tankSpeed = 0.04f;
	float reload = 1.0f;
	int head_frame = 0; //머리 흔들리는 애니메이션에 사용
	int timer = 0;
	int headDirection = 0;	//1 : Left / -1: Right
	int bodyDirection = 0;
	int moveDirection = 0; //1: front / -1: back

	bool bMoved = false;
	bool bPushedSpace = false;
	bool supermode = false;

	ATank() 
	{
		setMaxHp(20.f);
		hpbar->setType(false);
		setBoundary(TANK_SIZE, TANK_SIZE);
		power = 5.f;
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
	void hit(int power);

	void moveForward(int direction);
	void stopMove(int direction);
	void charge();
	void attack();
	void turnHead(int direction);
	void stopHead(int direction);
	void turnBody(int direction);
	void stopBody(int direction);
	void upgrade();

	bool returnCollide(Object* obj);
};
