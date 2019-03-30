#include "Ref.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
using namespace std;

Ref::Ref(Game* game) 
	:Actor(game)
{
	//new CollisionComponent(this);
	sc = new SpriteComponent(this);
	cc = new CollisionComponent(this);
	sc->SetTexture(game->GetTexture("Assets/ref.png"));
	cc->SetSize(32, 32);
}