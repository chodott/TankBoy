# TankBoy
![image](https://github.com/chodott/TankBoy/assets/89974193/ff36ad5e-08af-47ef-8e52-c2d99bb3bf82)
- - -

# 게임 설명
- 맵 곳곳에서 생성되는 적을 무찌르는 게임
- 맵에 스폰되는 아이템을 획득하여 탱크의 성능 향상
- 탱크 밑의 HP Bar가 사라지면 게임 종료
- - -
# 기술 소개서
## 클래스 구조도
![image](https://github.com/chodott/AndroidProgramming/assets/89974193/2db69e09-a7c6-4bd3-92cc-19f9b10a6c8f)

- - -
## Pawn
- Hit -> 받은 데미지에 따른 HP 관리
- Attack -> rot값에 따라 Bullet 생성
  

## Tank
- 입력 값에 따라 이동, 회전 및 공격 수행
```c++
void ATank::update()
{
	Pawn::update();

	headR += BODY_ROTATE_SPEED * headDirection;
	tankR += HEAD_ROTATE_SPEED * bodyDirection;

	if (bMoved == true)
	{
		if (abs(tankSpeed) <= maxSpeed)
			tankSpeed += ACCELERATION * moveDirection;
		else tankSpeed = maxSpeed * moveDirection;
	}
	else
	{
		int sign = tankSpeed < 0 ? -1 : 1;
		tankSpeed -= DECELERATION * sign;
		if (abs(tankSpeed) <= 0.01f)
		{
			moveDirection = 0;
			tankSpeed = 0.0f;
		}
	}

	x += cos(-tankR * PI) * (tankSpeed);
	z += sin(-tankR * PI) * (tankSpeed);

	rot = tankR + headR;

	//x = (nextx >= 24.6f || nextx <= -24.6f) ? x : nextx;
	//z = (nextz >= 24.6f || nextz <= -24.6f) ? z : nextz;
}
```

## Enemy
- target이 공격 범위 내에 있을 시 attack
  
  ```c++
  void Enemy::update()
  {
	Pawn::update();

	float distance = sqrt((target->z - z) * (target->z - z) + (target->x -x) * (target->x - x)); //간격
	float r = atan2((target->z - z), (target->x - x));
	rot = -r * 60;
	if (distance > range) { //사정거리 보다 멀면 이동
		x += cos(r) * speed;
		z += sin(r) * speed;
	}
	else this->attack();
  }
```
