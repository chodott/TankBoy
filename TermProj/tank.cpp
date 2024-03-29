#include "Tank.h"

void ATank::draw(unsigned int modelLocation, unsigned int objColorLocation)
{
	Pawn::draw(modelLocation, objColorLocation);
	//탱크 출력
	glm::mat4 TANK = glm::mat4(1.0f);
	TANK = glm::translate(TANK, glm::vec3(this->x, (this->heady / 2.0f), this->z));
	TANK = glm::rotate(TANK, glm::radians(this->tankR + 90.0f), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TANK));
	glUniform3f(objColorLocation, 0.7, 0.7, 0.7);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->body_texture);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, this->obj_body);

	//머리 출력
	glm::mat4 HEAD = glm::mat4(1.0f);
	//코드 수정 필요
	if (head_frame >= 3) {
		head_frame = 0;
		if (heady > 0.0f) heady = 0.0f;
		else heady = 0.03f;
	}
	this->head_frame++;
	HEAD = glm::translate(HEAD, glm::vec3(x, heady, z));
	HEAD = glm::rotate(HEAD, glm::radians(headR + tankR + 90.0f), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(HEAD));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->head_texture);
	glBindVertexArray(VAO[2]);
	glDrawArrays(GL_TRIANGLES, 0, this->obj_head);

	//발사구 출력
	glm::mat4 CANNON = glm::mat4(1.0f);
	CANNON = HEAD;
	CANNON = glm::translate(CANNON, glm::vec3(0.0f, 0.7f, 0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(CANNON));
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, this->cannon_texture);
	glBindVertexArray(VAO[3]);
	glDrawArrays(GL_TRIANGLES, 0, this->obj_cannon);

	for (auto& bullet : bullet_vec) 
		bullet->draw(modelLocation, objColorLocation);

}

void ATank::moveForward(int direction)
{
	moveDirection = direction;
	bMoved = true;
}

void ATank::stopMove(int direction)
{
	if (direction != moveDirection) return;
	bMoved = false;
}

void ATank::update()
{
	headR += 5.f * headDirection;
	tankR += 1.f * bodyDirection;

	if (bMoved == true)
	{
		if (abs(tankSpeed) <= maxSpeed)
			tankSpeed += 0.004f * moveDirection;
		else tankSpeed = maxSpeed * moveDirection;
	}
	else
	{
		int sign = tankSpeed < 0 ? -1 : 1;
		tankSpeed -= 0.006f * sign;
		if (abs(tankSpeed) <= 0.01f)
		{
			moveDirection = 0;
			tankSpeed = 0.0f;
		}
	}

	float nextx = x + cos(-tankR * PI) * (3 * tankSpeed);
	float nextz = z + sin(-tankR * PI) * (3 * tankSpeed);
	if (nextx >= 24.6f || nextx <= -24.6f) x = x;
	else x += cos(-tankR * PI) * tankSpeed;
	if (nextz >= 24.6f || nextz <= -24.6f) z = z;
	else z += sin(-tankR * PI) * tankSpeed;

	for (auto& bullet : bullet_vec) bullet->update();

	Pawn::update();

}

void ATank::charge()
{
	if (!bPushedSpace) return;
	//포물선 업데이트
	if (minRange <= maxRange) this->minRange += 0.1f;
	float gap = minRange / 100.0f;
	float gravity = 0.03f / 100.0f;
	float height_accel = 2.0f / 100.0f;
	for (int i = 0; i < 100; i++) {
		//point[i].x = x + cos(-(tankR + headR) * PI) * (float)(gap * i);
		//point[i].z = z + sin(-(tankR + headR) * PI) * (float)(gap * i);
		//point[i].y = 0.7f + height_accel * i;
		height_accel -= gravity;
	}
}

void ATank::attack()
{
	bullet_vec.emplace_back(new ABullet(x,y,z, -(tankR + headR)));
}

void ATank::hit()
{

}

void ATank::turnHead(int direction)
{
	headDirection = direction;
}

void ATank::stopHead(int direction)
{
	if (direction != headDirection) return;

	headDirection = 0;
}

void ATank::turnBody(int direction)
{
	bodyDirection = direction;
}

void ATank::stopBody(int direction)
{
	if (direction != bodyDirection) return;

	bodyDirection = 0;
}


void ATank::upgrade(int skill)
{
	switch (skill)
	{
	case 0: power += 1; break;
	case 1: if (reload > 0.3); reload -= 0.1f; break;
	case 2: maxRange + 1.0f; break;
	case 3: hp += 5; break;
	case 4:
		if (supermode) power += 1;
		else supermode = 1;
		break;
	}
}

int ATank::obj_body = 0;
int ATank::obj_head = 0;
int ATank::obj_cannon = 0;

unsigned int ATank::body_texture = 0;
unsigned int ATank::head_texture = 0;
unsigned int	ATank::cannon_texture = 0;

GLuint ATank::VAO[4];
GLuint ATank::VBO_pos[4];
GLuint ATank::VBO_nor[4];
GLuint ATank::VBO_tex[4];