#pragma once
#include "Actor.h"
class Tip:
	public Actor
{
public:
	Tip(class Game* game);
	~Tip();
	class AnimatedSprite* asc;
	class CollisionComponent* cc;
	class Collectible* collectible;
	int level = 0;
	float time = 0;
	void OnUpdate(float deltaTime);
	
};

