#pragma once
#include "Bullet.h"
class Pawn : public Object
{
public:
	vector<ABullet*> bullet_vec;
	HpBar* hpbar = nullptr;
	int maxHp = 1.f;
	int hp = 1.f;
	int power = 1;
	float prevX;
	float prevZ;

	Pawn() { hpbar = new HpBar(); };
	~Pawn()
	{
		for (auto& bullet : bullet_vec) delete(bullet);
	}
	void setMaxHp(float hp);
	void setPos(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual void hit(float power);

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
	void block();
	inline void die() { active = false; }
	bool returnCollide(Object* obj);
};

