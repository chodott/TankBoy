#include "enemy.h"


void Enemy::block()
{
}

void Enemy::update()
{
	prevX = x;
	prevZ = z;
	float distance = sqrt((target->z - z) * (target->z - z) + (target->x -x) * (target->x - x)); //간격
	float r = atan2((target->z - z), (target->x - x));
	rotate = -r * 60;
	if (distance > this->range && this->condition == 0) { //사정거리 보다 멀면 이동
		x += cos(r) * speed;
		z += sin(r) * speed;
	}
	else this->attack();


	for (auto& bullet : bullet_vec)
	{
		bullet->update();
	}

	Pawn::update();
}

void Enemy::attack()
{
	time_t now = time(NULL);
	if (now - attacked_time < reloadLength) return;
	bullet_vec.emplace_back(new ABullet(x, y, z, -rotate));
	attacked_time = now;
}


void ARifleMan::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	//라이플맨
	glm::mat4 RIFLE = glm::mat4(1.0f);
	RIFLE = glm::translate(RIFLE, glm::vec3(x, y, z));

	RIFLE = glm::rotate(RIFLE, glm::radians(rotate + 90.f), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RIFLE));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rifle_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, rifle_obj);

	for (auto& bullet : bullet_vec)
	{
		bullet->draw(modelLocation, objColorLocation);
	}

	Pawn::draw(modelLocation, objColorLocation);
}


void ABazookaMan::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	glm::mat4 BAZOOKA = glm::mat4(1.0f);
	BAZOOKA = glm::translate(BAZOOKA, glm::vec3(this->x, this->y, this->z));
	BAZOOKA = glm::rotate(BAZOOKA, glm::radians(rotate + 90.f), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(BAZOOKA));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bazooka_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, bazooka_obj);

	for (auto& bullet : bullet_vec)
	{
		bullet->draw(modelLocation, objColorLocation);
	}

	Pawn::draw(modelLocation, objColorLocation);
}


GLuint ARifleMan::VAO;
GLuint ARifleMan::VBO[3];
int ARifleMan::rifle_obj;
unsigned int ARifleMan::rifle_texture;

time_t ARifleMan::spawnTime = 0.f;
time_t ARifleMan::spawnLength = 5.f;

GLuint ABazookaMan::VAO;
GLuint ABazookaMan::VBO[3];
unsigned ABazookaMan::bazooka_texture;
int ABazookaMan::bazooka_obj;

time_t ABazookaMan::spawnTime = 0.f;
time_t ABazookaMan::spawnLength = 10.f;
