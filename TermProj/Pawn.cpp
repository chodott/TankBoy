#include "Pawn.h"

void Pawn::setMaxHp(float hp)
{
	maxHp = hp;
	this->hp = hp;
	hpbar->maxHp = hp;
}

void Pawn::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	hpbar->draw(modelLocation, objColorLocation);
}

void Pawn::update()
{
	hpbar->update(x, y, z, hp);
}

bool Pawn::returnCollide(Object* obj)
{
	vector<int> delete_vec;
	for (int i = 0; i < bullet_vec.size(); ++i)
	{
		bool bCrashed = bullet_vec[i]->returnCollide(obj);
		if (bCrashed == false) continue;
		delete_vec.emplace_back(i);
		((Pawn*)obj)->hit(power);
	}
	sort(delete_vec.begin(), delete_vec.end(), greater<int>());
	for (int i : delete_vec)
	{
		bullet_vec.erase(bullet_vec.begin() + i);
	}
	return this->Object::returnCollide(obj);
}
