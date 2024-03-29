#pragma once
#include "object.h"
#include "Bullet.h"
class ATank : public Pawn
{
public:
	static int obj_body;
	static int obj_head;
	static int obj_cannon;
	static unsigned int body_texture;
	static unsigned int head_texture;
	static unsigned int cannon_texture;

	static GLuint VAO[4]; //[0]:��ũ ���� [1]:������ [2]:��ũ �Ӹ� [3]:��ũ ����
	static GLuint VBO_pos[4], VBO_nor[4], VBO_tex[4];

	vector<ABullet*> bullet_vec;
	float maxSpeed = 0.12f;
	float maxRange = 5.0f;
	float minRange = 2.0f;

	float tankR = 0; //��ü ����
	float headR = 0; //�Ӹ� ����
	float heady = 0.0f; //�Ӹ� �ִϸ��̼ǿ� ���
	float tankSpeed = 0.0f;
	float reload = 1.0f;
	float hp = 0;
	int head_frame = 0; //�Ӹ� ��鸮�� �ִϸ��̼ǿ� ���
	int power = 5;
	int timer = 0;
	int headDirection = 0;	//1 : Left / -1: Right
	int bodyDirection = 0;
	int moveDirection = 0; //1: front / -1: back

	bool bMoved = false;
	bool bPushedSpace = false;
	bool supermode = false;
	bool death = false;

	void draw(unsigned int modelLocation, unsigned int objColorLocation);

	void moveForward(int direction);

	void stopMove(int direction);

	void update();

	void charge();

	void attack();

	void hit();

	void turnHead(int direction);

	void stopHead(int direction);

	void turnBody(int direction);

	void stopBody(int direction);

	void upgrade(int skill);

};
