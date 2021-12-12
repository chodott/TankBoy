#include "manage.h"

#define PLATE_SIZE 5.0f
#define PI 3.141592/180
#define BLOCK_AMOUNT 30
#define RIFLE_AMOUNT 30
#define ITEM_AMOUNT 10

//평면
unsigned int ground_texture;
float plate[] = {
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, PLATE_SIZE, 0.0f, PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, PLATE_SIZE, 0.0f, -PLATE_SIZE, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

//정육면체
float vertices[] = { 
-1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f, 1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f, 1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f,
1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f, -1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f, -1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f,
-1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f, 1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f, 1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f,
1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f, -1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f, -1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f,
-1.0, 1.0, 1.0, -1.0f, 0.0f, 0.0f, -1.0, 1.0, -1.0, -1.0f, 0.0f, 0.0f, -1.0, -1.0, -1.0, -1.0f, 0.0f, 0.0f,
-1.0, -1.0, -1.0, -1.0f, 0.0f, 0.0f, -1.0, -1.0, 1.0, -1.0f, 0.0f, 0.0f, -1.0, 1.0, 1.0, -1.0f, 0.0f, 0.0f,
1.0, 1.0, 1.0, 1.0f, 0.0f, 0.0f, 1.0, 1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f,
1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0, -1.0, 1.0, 1.0f, 0.0f, 0.0f, 1.0, 1.0, 1.0, 1.0f, 0.0f, 0.0f,
-1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f, 1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f, 1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f,
1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f, -1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f, -1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f,
-1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f, 1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f, 1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f,
1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f, -1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f, -1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f
};

//포물선 점
float track[] = {
	0,0,0,0,0,0
};

class Point {
public:
	float x, y, z;
};

//총알
class Bullet {
public:
	Point point[100] = {};
	float size = 0.1f;
	float x, y, z;
	float r = 0;
	float speed = 0.2f;
	int tic = 0;
	bool active = 0;
	Bullet() : x{ 0 }, y{ 0 }, z{ 0 } {}

	void move() {
		if (this->active) {
			this->x = this->point[tic].x;
			this->y = this->point[tic].y;
			this->z = this->point[tic].z;
			this->tic += 3;
		if (this->tic == 100)  this->active = 0;
		else if (this->point[tic].y <= 0) this->active = 0;
		}
	}

	void enemy_move() { //총알이 같은 클래스라 적 총알 매커니즘 따로 구현했슴다!
		if (this->active) {
			this->x += cos(this->r) * this->speed;
			this->z += sin(this->r) * this->speed;
		}
	}

	void draw(GLuint VAO, unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->active) {
			glm::mat4 TANKBULLET = glm::mat4(1.0f);
			TANKBULLET = glm::translate(TANKBULLET, glm::vec3(this->x, this->y, this->z));
			TANKBULLET = glm::rotate(TANKBULLET, glm::radians(this->r), glm::vec3(0, 1, 0));
			TANKBULLET = glm::scale(TANKBULLET, glm::vec3(this->size, this->size, this->size));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TANKBULLET));
			glUniform3f(objColorLocation, 0.0, 0.0, 0.0);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else return;
	}

	
};

//탱크
class Tank {
public:
	GLuint VAO[2];
	GLuint VBO_pos[4], VBO_nor[4], VBO_tex[4];
	Bullet *bullet[10];
	Point point[100] = {};
	float tankSpeed = 0.0f;
	float maxSpeed = 0.12f;
	float tankR = 0; //몸체 각도
	float headR = 0; //머리 각도
	float maxRange = 10.0f;
	float minRange = 2.0f;
	float range = 4.3f;
	float size = 0.1f;
	float x, y, z;
	unsigned int body_texture;
	int hp = 5;
	int bulletCnt = 0;
	int obj = 0;
	bool death = 0;
	bool moving = 0;
	bool push = 0;
	
	Tank() : x{ 0 }, y{ 0 }, z{ 0 } { //탱크 생성자
		for (int i = 0; i < 10; i++) {
			this->bullet[i] = new Bullet();
		}
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if(!this->death){
		//탱크 출력
		glm::mat4 TANK = glm::mat4(1.0f);
		TANK = glm::translate(TANK, glm::vec3(this->x, 0.1f, this->z));
		TANK = glm::rotate(TANK, glm::radians(this->tankR + 90.0f), glm::vec3(0, 1, 0));
		TANK = glm::scale(TANK, glm::vec3(this->size, this->size, this->size));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TANK));
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->body_texture);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, this->obj);
		
		//머리 출력
		glm::mat4 HEAD = glm::mat4(1.0f);
		HEAD = glm::translate(HEAD, glm::vec3(this->x, 0.2f, this->z));
		HEAD = glm::rotate(HEAD, glm::radians(this->headR + this->tankR + 90.0f), glm::vec3(0, 1, 0));
		HEAD = glm::scale(HEAD, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(HEAD));
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->body_texture);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, this->obj);

		////발사구 출력
		//glm::mat4 MOUSE = glm::mat4(1.0f);
		//MOUSE = HEAD;
		//MOUSE = glm::translate(MOUSE, glm::vec3(0.2f, 0, 0));
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(MOUSE));
		//glUniform3f(objColorLocation, 0.0, 1.0, 1.0);
		//glBindVertexArray(VAO[0]);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//총알 출력
		for (int i = 0; i < 10; i++) this->bullet[i]->draw(VAO[0], modelLocation, objColorLocation);

		//포물선 출력
		for (int i = 0; i < 100; i += 9) {
			glm::mat4 POINT = glm::mat4(1.0f);
			POINT = glm::translate(POINT, glm::vec3(this->point[i].x, this->point[i].y, this->point[i].z));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(POINT));
			glUniform3f(objColorLocation, 0.0, 0.0, 0.0);
			glPointSize(5);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		}
	}

	void move(int straight){ //이동 함수
		if (straight > 0) {
			if (moving == 1 && this->tankSpeed <= this->maxSpeed) this->tankSpeed += 0.004f;
			else if (keyStates[5] && moving == 0) {
				this->tankSpeed -= 0.006f;
				if (this->tankSpeed <= 0.0f) { this->tankSpeed = 0.0f; keyStates[5] = false;}
			}
		}
		else if(straight < 0) {
			if (moving == 1 && this->tankSpeed >= (-1.0f * this->maxSpeed)) this->tankSpeed -= 0.004f;
			else if (keyStates[7] && moving == 0) {
				this->tankSpeed += 0.006f;
				if ( this->tankSpeed >= 0.0f) { this->tankSpeed = 0.0f; keyStates[7] = false; }
			}
		}

		this->x = this->x + cos(-this->tankR * PI) * this->tankSpeed;
		this->z = this->z + sin(-this->tankR * PI) * this->tankSpeed;
	}

	void update() {
		for (int i = 0; i < 10; i++) this->bullet[i]->move();

		//포물선 업데이트
		float gap = this->range / 100.0f;
		float gravity = 0.02f / 100.0f;
		float height_accel = 2.0f / 100.0f;
		for (int i = 0; i < 100; i++) {
			this->point[i].x = this->x + cos(-(this->tankR + this->headR) * PI) * (float)(gap * i);
			this->point[i].z = this->z + sin(-(this->tankR + this->headR) * PI)* (float)(gap * i);
			this->point[i].y = 0.1f + height_accel * i;
			height_accel -= gravity;
		}
	}

	void attack() { //공격 함수
		this->bullet[this->bulletCnt]->active = 1;
		this->bullet[this->bulletCnt]->tic = 0; 
		for (int i = 0; i < 100; i++) this->bullet[bulletCnt]->point[i] = this->point[i];
		this->bullet[this->bulletCnt]->r = this->headR + this->tankR;
		this->bulletCnt = (this->bulletCnt + 1) % 10;
	}

	void hit() {
		this->hp -= 1;
		if (this->hp <= 0) this->death = 1;
	}

	void upgrade(int skill) {
		switch (skill) {
		case 0: this->size += 0.1f; break;
		case 1: break;
		case 2: break;
		case 3: break;
		}
	}

	bool collide(float extraX, float extraY, float extraZ, float extraSize) {
		float distance = sqrt((this->x - extraX) * (this->x - extraX) + (this->y - extraY) * (this->y - extraY) + (this->z - extraZ) * (this->z - extraZ));
		if (extraSize + this->size >= distance) return true;
		return false;
	}
};

//병사
GLuint rifle_VAO;
GLuint rifle_VBO[3];
unsigned int rifle_texture;
int rifle_obj;
class RifleMan {
public:
	time_t attack_timer = 0;
	Bullet bullet[3];
	float speed = 0.01;
	float x, y, z;
	float rotate = 0;
	float range = 2.0f;
	float size = 1.0f;
	int reload = 1;
	int hp = 1;
	int power = 0;
	int condition = 0;
	bool active = 0;

	void spawn(int level) { //소환
		this->active = 1;
		while (-1) {
			int x = rand() % 100;
			int z = rand() % 100;
			if (map[z][x] == 0) {
				this->x = (x - 50) * 0.1f;
				this->y = 0.1f;
				this->z = (z - 50) * 0.1f;
				break;
			}
		}
		this->power = level;
	}

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->active) {
			glm::mat4 RIFLE = glm::mat4(1.0f);
			RIFLE = glm::translate(RIFLE, glm::vec3(this->x, this->y, this->z));
			RIFLE = glm::rotate(RIFLE, -this->rotate + 90.0f, glm::vec3(0,1,0));
			RIFLE = glm::scale(RIFLE, glm::vec3(this->size, this->size, this->size));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RIFLE));
			glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, this->body_texture);
			glBindVertexArray(rifle_VAO);
			glDrawArrays(GL_TRIANGLES, 0, rifle_obj);
		}
		this->bullet[0].draw(rifle_VAO, modelLocation, objColorLocation);
	}

	void move(float tankX, float tankZ) {
		float distance = sqrt((tankZ - this->z) * (tankZ - this->z) + (tankX - this->x) * (tankX - this->x)); //간격
		this->rotate = atan2((tankZ - this->z), (tankX - this->x));
		if (distance > this->range && this->condition == 0) { //사정거리 보다 멀면 이동
			this->x += cos(this->rotate) * this->speed;
			this->z += sin(this->rotate) * this->speed;
		}
		else this->attack();

		//총알 이동
		this->bullet[0].enemy_move();
	}

	void update(float tankX, float tankZ) {
		if (this->active) {
			this->move(tankX, tankZ);
		}
	}

	void hit() {
		if (this->active) {
			this->hp -= 1;
			if (this->hp <= 0) this->active = 0;
		}
	}

	void attack() {
		if (time(NULL) - this->attack_timer > this->reload) {
			this->attack_timer = time(NULL);
			this->bullet[0].active = 1;
			this->bullet[0].x = this->x;
			this->bullet[0].y = 0.01f;
			this->bullet[0].z = this->z;
			this->bullet[0].r = this->rotate;
		}
	}

	bool collide(float extraX, float extraY, float extraZ,  float extraSize) {
		float distance = sqrt((this->x - extraX) * (this->x - extraX) + (this->y - extraY)* (this->y-extraY) +(this->z - extraZ) * (this->z - extraZ));
		if (extraSize + this->size >= distance) return true;
		return false;
	}
};

class Block {
public:
	float x, y, z;
	float size = 0.1;
	
	void getPos(float x, float y, float z) {
		this->x = x; this->y = y; this->z = z;
	}
	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		glm::mat4 BLOCK = glm::mat4(1.0f);
		BLOCK = glm::translate(BLOCK, glm::vec3(this->x, this->y, this->z));
		BLOCK = glm::scale(BLOCK, glm::vec3(this->size, this->size, this->size));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(BLOCK));
		glUniform3f(objColorLocation, 0.0, 0.0, 0.7);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};

class Item {
public:
	float x, y, z;
	float size = 0.1;
	float speed = 0.005;
	int skill = 0;
	bool active = 0;
	bool onfoot = 0;

	void draw(unsigned int modelLocation, unsigned int objColorLocation) {
		if (this->active) {
			glm::mat4 ITEM = glm::mat4(1.0f);
			ITEM = glm::translate(ITEM, glm::vec3(this->x, this->y, this->z));
			ITEM = glm::scale(ITEM, glm::vec3(this->size, this->size, this->size));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(ITEM));
			glUniform3f(objColorLocation, 0.0, 0.0, 0.7);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void spawn() {
		this->onfoot = 0;
		this->active = 1;
		while (-1) {
			int x = rand() % 100;
			int z = rand() % 100;
			if (map[z][x] == 0) {
				this->x = (x - 50) * 0.1f;
				this->y = 5.0f;
				this->z = (z - 50) * 0.1f;
				break;
			}
		}
	}

	void update() {
		if (this->active) {
			this->move();
		}
	}

	void move() {
		if (!this->onfoot) {
			if (this->y <= this->size / 2) { this->y = this->size / 2; this->onfoot = 1; }
			else this->y -= this->speed;
		}
	}
};


Tank tank;

Block block[BLOCK_AMOUNT];

RifleMan rifle[RIFLE_AMOUNT];

Item item[ITEM_AMOUNT];