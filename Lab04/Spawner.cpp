#include "Spawner.h"
#include "Game.h"
#include "Actor.h"
#include "Player.h"
#include "Goomba.h"



Spawner::Spawner(Game* game):Actor(game)
{
}


Spawner::~Spawner()
{
}

void Spawner::OnUpdate(float deltaTime) {
	if (this->GetPosition().x - mGame->player->GetPosition().x < 600) {
		Goomba* goomba = new Goomba(mGame);
		goomba->SetPosition(this->GetPosition());
		this->SetState(ActorState::Destroy);
	}
}
