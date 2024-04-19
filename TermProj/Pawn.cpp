#include "Pawn.h"

void Pawn::setMaxHp(float hp)
{
	maxHp = hp;
	this->hp = hp;
	hpbar->maxHp = hp;
}

void Pawn::hit(float power)
{
	hp -= power;
	if (hp > 0) return;
	die();
}

void Pawn::attack()
{
	time_t now = time(NULL);
	if (now - attacked_time < reloadLength) return;

	bullet_vec.emplace_back(new ABullet(x, y, z, -rot));
	attacked_time = now;
}

void Pawn::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	hpbar->draw(modelLocation, objColorLocation);

	for (auto& bullet : bullet_vec)
	{
		bullet->draw(modelLocation, objColorLocation);
	}
}

void Pawn::update()
{

	prevX = x;
	prevZ = z;

	hpbar->update(x, y, z, hp);
	for (auto& bullet : bullet_vec)
	{
		bullet->update();
	}
}

void Pawn::block()
{
	x = prevX;
	z = prevZ;
}

bool Pawn::returnCollide(Object* obj)
{
	vector<int> delete_vec;
	Pawn* pawn = dynamic_cast<Pawn*>(obj);
	for (int i = 0; i < bullet_vec.size(); ++i)
	{
		bool bCrashed = bullet_vec[i]->returnCollide(obj);
		if (bCrashed == false) continue;
		delete_vec.emplace_back(i);

		if (pawn == nullptr) continue;
		pawn->hit(power);
	}
	sort(delete_vec.begin(), delete_vec.end(), greater<int>());
	for (int i : delete_vec)
	{
		delete(bullet_vec[i]);
		bullet_vec.erase(bullet_vec.begin() + i);
	}
	return this->Object::returnCollide(obj);
}
