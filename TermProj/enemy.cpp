#include "enemy.h"

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

void Enemy::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	Pawn::draw(modelLocation, objColorLocation);

	glm::mat4 RIFLE = glm::mat4(1.0f);
	RIFLE = glm::translate(RIFLE, glm::vec3(x, y, z));
	RIFLE = glm::rotate(RIFLE, glm::radians(rot + DEFAULT_ROT), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RIFLE));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
}

void Enemy::update()
{
	Pawn::update();

	float distance = sqrt(pow(target->z - z, 2)  + pow(target->x -x, 2));		//플레이어와의 거리
	float r = atan2((target->z - z), (target->x - x));
	rot = -r * 60;
	if (distance > range) 
	{	//사정거리 밖일 떄 이동
		x += cos(r) * speed;
		z += sin(r) * speed;
	}
	else this->attack();
}


void ARifleMan::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	Enemy::draw(modelLocation, objColorLocation);
	glBindTexture(GL_TEXTURE_2D, rifle_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, rifle_obj);
}


void ABazookaMan::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	Enemy::draw(modelLocation, objColorLocation);
	glBindTexture(GL_TEXTURE_2D, bazooka_texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, bazooka_obj);
}

