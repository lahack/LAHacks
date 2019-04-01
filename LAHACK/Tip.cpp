#include "Tip.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "Collectible.h"
#include "Game.h"
#include "Player.h"
#include "Goomba.h"
#include <iostream>
using namespace std;


Tip::Tip(Game* game) :Actor(game)
{
	cc = new CollisionComponent(this);
	cc->SetSize(20, 20);
	collectible = new Collectible(this);
	collectible->setOnCollect([this, game] {
		game->player->SetState(ActorState::Paused);
		/*Mix_HaltChannel(game->backgroundMusicChannel);
		Mix_PlayChannel(-1, game->GetSound("Assets/Sounds/PowerUp.wav"), 0);*/
		for (size_t i = 0; i < game->goombas.size(); i++) {
			game->goombas[i]->SetState(ActorState::Paused);
		}
		Actor* temp = new Actor(game);
		SpriteComponent* sc = new SpriteComponent(temp, 200);
		sc->SetTexture(game->GetTexture("Assets/level_" + to_string(level) + ".png"));
		temp->SetPosition(Vector2(150, (level - 1)*448.0f + 45.0f));
		cout << "level: " << level << endl;
		game->player->SetState(ActorState::Active);
		game->cnt_collect++;
		SetState(ActorState::Paused);
		game->player->SetState(ActorState::Paused);
		time = 3.0f;
		game->set_Tip(this);
	});

	asc = new AnimatedSprite(this);
	std::vector<SDL_Texture*> triforce{
		GetGame()->GetTexture("Assets/Triforce0.png"),
		GetGame()->GetTexture("Assets/Triforce1.png"),
	};
	asc->AddAnimation("triforce", triforce);
	asc->SetAnimation("triforce");
}


Tip::~Tip()
{
}

void Tip::OnUpdate(float deltaTime)
{


}