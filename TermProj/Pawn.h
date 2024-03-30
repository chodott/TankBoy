#pragma once
#include "Bullet.h"
class Pawn : public Object
{
public:
	vector<ABullet*> bullet_vec;
	HpBar* hpbar = nullptr;
	int maxHp = 1.f;
	int hp = 1.f;
	int power = 0;
	float prevX;
	float prevZ;

	Pawn() { hpbar = new HpBar(); };
	void setMaxHp(float hp);
	void setPos(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void hit(float power) { hp -= power; }

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
	bool returnCollide(Object* obj);
};

