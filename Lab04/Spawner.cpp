#include "Spawner.h"
#include "Game.h"
#include "Actor.h"
#include "Player.h"
#include "Goomba.h"
#include "GoombaMove.h"
#include "PlayerMove.h"



Spawner::Spawner(Game* game):Actor(game)
{
}


Spawner::~Spawner()
{
}

void Spawner::OnUpdate(float deltaTime) {
	if (this->GetPosition().x - mGame->player->GetPosition().x < 600) {
		if (this->level == mGame->player->GetComponent<PlayerMove>()->level) {
			Goomba* goomba = new Goomba(mGame);
			goomba->GetComponent<GoombaMove>()->level = level;
			goomba->SetPosition(this->GetPosition());
			this->SetState(ActorState::Destroy);
		}
	}
}
