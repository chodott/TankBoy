#include "enemy.h"


void Enemy::update()
{
	float distance = sqrt((target->z - this->z) * (target->z - this->z) + (target->x - this->x) * (target->x - this->x)); //간격
	this->rotate = atan2((target->z - this->z), (target->x - this->x));
	if (distance > this->range && this->condition == 0) { //사정거리 보다 멀면 이동
		this->x += cos(this->rotate) * this->speed;
		this->z += sin(this->rotate) * this->speed;
	}
	else this->attack();

	for (auto& bullet : bullet_vec)
	{
		bullet->update();
	}

}

void Enemy::attack()
{
	time_t now = time(NULL);
	if (now - attacked_time < reloadLength) return;

	bullet_vec.emplace_back(new ABullet(x, y, z, glm::radians(-rotate)));
	attacked_time = now;
}


void ARifleMan::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	//라이플맨
	glm::mat4 RIFLE = glm::mat4(1.0f);
	RIFLE = glm::translate(RIFLE, glm::vec3(x, y, z));
	RIFLE = glm::rotate(RIFLE, -this->rotate + 90.0f, glm::vec3(0, 1, 0));
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
}


void ABazookaMan::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	glm::mat4 BAZOOKA = glm::mat4(1.0f);
	BAZOOKA = glm::translate(BAZOOKA, glm::vec3(this->x, this->y, this->z));
	BAZOOKA = glm::rotate(BAZOOKA, -rotate + 90.0f, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(BAZOOKA));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bazooka_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, bazooka_obj);

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
