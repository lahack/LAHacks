#pragma once
#include "MoveComponent.h"
#include "Math.h"
class PlayerMove :
	public MoveComponent
{
public:
	PlayerMove(class Player* owner);
	~PlayerMove();
	//Vector2 velocity = Vector2(0, 0);
	void Update(float deltaTime) override;
	void ProcessInput(const Uint8* keyState) override;
	float mYSpeed = 0.0f;
	bool mSpacePressed = false;
	bool mInAir = false;
	void GoombaDead(class Goomba* currentGoomba);
	void PlayerDead(Player* p);
	void updateSprite();
	int depth = 0;
	int level = 0;
};

