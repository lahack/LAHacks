#include "Thanos.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
using namespace std;

Thanos::Thanos(Game* game)
	:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	CollisionComponent* cc = new CollisionComponent(this);
	cc->SetSize(51, 60);
	
	sc->SetTexture(game->GetTexture("Assets/Thanos.png"));
}