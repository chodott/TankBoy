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


	static GLuint VAO[4]; //[0]:��ũ ���� [1]:������ [2]:��ũ �Ӹ� [3]:��ũ ����
	static GLuint VBO_pos[4], VBO_nor[4], VBO_tex[4];
	float x, y, z;
	float tankR = 0; //��ü ����
	float headR = 0; //�Ӹ� ����
	float heady = 0.0f; //�Ӹ� �ִϸ��̼ǿ� ���
	float maxRange = 5.0f;
	float minRange = 2.0f;
	float reload = 1.0f;
	int head_frame = 0; //�Ӹ� ��鸮�� �ִϸ��̼ǿ� ���
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
