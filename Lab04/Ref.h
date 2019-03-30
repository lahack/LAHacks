#pragma once
#include "Actor.h"
#include "SDL/SDL.h"
class Ref :	public Actor
{
public:
	Ref(class Game* game);
	class SpriteComponent* sc;
	class CollisionComponent* cc;
};

