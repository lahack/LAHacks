#include "PlayerMove.h"
#include "Component.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Math.h"
#include "Block.h"
#include "Player.h"
#include "Goomba.h"
#include "GoombaMove.h"
#include "AnimatedSprite.h"
#include "SDL/SDL_mixer.h"
#include <iostream>


PlayerMove::PlayerMove(Player* owner) :MoveComponent(owner)
{
}


PlayerMove::~PlayerMove()
{
}

void PlayerMove::ProcessInput(const Uint8* keyState) {
	if (keyState[SDL_SCANCODE_LEFT]) {
		if (!(keyState[SDL_SCANCODE_RIGHT]))//if right arrow isn't pressed
			this->SetForwardSpeed(-300);
		else
			this->SetForwardSpeed(0);
	}
	else if (keyState[SDL_SCANCODE_RIGHT]) {
		if (!(keyState[SDL_SCANCODE_LEFT]))//if left arrow isn't pressed
			this->SetForwardSpeed(300);
		else
			this->SetForwardSpeed(0);
	}
	else {
		this->SetForwardSpeed(0);
	}

	//if space bar is pressed
	if (keyState[SDL_SCANCODE_SPACE]) {
		if (!mSpacePressed&&!mInAir) {
			//cout << "jump" << endl;
			mInAir = true;
			mYSpeed = -700.0f;
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav"), 0);
		}
		mSpacePressed = true;
	}
	else {
		mSpacePressed = false;
	}
}

void PlayerMove::Update(float deltaTime) {
	Vector2 initial=mOwner->GetPosition();
	if (initial.x > 6368) {
		mOwner->SetState(ActorState::Paused);
		Mix_HaltChannel(mOwner->GetGame()->backgroundMusicChannel);
		Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav"), 0);
		return;
	}
	float newX = initial.x + this->GetForwardSpeed()*deltaTime;
	if(newX>=mOwner->GetGame()->cameraPos.x)
		mOwner->SetPosition(Vector2(newX, initial.y+mYSpeed*deltaTime));
	else
		mOwner->SetPosition(Vector2(initial.x, initial.y + mYSpeed * deltaTime));

	Vector2 newPosition = mOwner->GetPosition();
	bool outBound;
	if (newPosition.y >= 448) {
		mOwner->SetPosition(Vector2(newPosition.x, 500));
		PlayerDead(dynamic_cast<Player*>(mOwner));
		outBound = true;
	}
	else {
		outBound = false;
	}
	//check collision
	CollisionComponent* playerCC = mOwner->GetComponent<CollisionComponent>();
	bool notColliding = true;

	for (int i = 0; i < mOwner->GetGame()->blocks.size(); i++) {
		Vector2 offset = Vector2(0, 0);
		CollisionComponent* blockCC = mOwner->GetGame()->blocks[i]->cc;
		if (playerCC->GetMinOverlap(blockCC, offset) == CollSide::Left) {
			notColliding = false;
			offset.x = offset.x - 1;
		}
		else if (playerCC->GetMinOverlap(blockCC, offset) == CollSide::Right) {
		//cout << "right collide" << endl;
			notColliding = false;	
			offset.x = offset.x + 1;
		}
		mOwner->SetPosition(mOwner->GetPosition() + offset);
	}
	for (int i = 0; i < mOwner->GetGame()->blocks.size(); i++) {
		Vector2 offset = Vector2(0, 0);
		CollisionComponent* blockCC = mOwner->GetGame()->blocks[i]->cc;
		if (playerCC->GetMinOverlap(blockCC, offset) == CollSide::None) {
			continue;
		}
		if (playerCC->GetMinOverlap(blockCC, offset) == CollSide::Top&&mYSpeed>=0.0f) {
			//cout << "top" << endl;
			mYSpeed = 0.0f;
			mInAir = false;
			notColliding = false;
		}	
		else if (playerCC->GetMinOverlap(blockCC, offset) == CollSide::Bottom&&mYSpeed<0.0f) {
			mYSpeed = 0.0f;
			notColliding = false;
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav"), 0);
		}
	}

	//check goomba
	for (int i = 0; i < mOwner->GetGame()->goombas.size(); i++) {
		Vector2 offset = Vector2(0, 0);
		Goomba* currentGoomba = mOwner->GetGame()->goombas[i];
		if(!currentGoomba->dead)
		{
			CollisionComponent* goombaCC = currentGoomba->cc;
			if (playerCC->GetMinOverlap(goombaCC, offset) == CollSide::None) {
				continue;
			}
			else {
				if (playerCC->GetMinOverlap(goombaCC, offset) == CollSide::Top&&mYSpeed >= 0.0f) {
					GoombaDead(currentGoomba);
				}
				else if (playerCC->GetMinOverlap(goombaCC, offset) == CollSide::Left&&mInAir) {
					GoombaDead(currentGoomba);
				}
				else if (playerCC->GetMinOverlap(goombaCC, offset) == CollSide::Right&&mInAir) {
					GoombaDead(currentGoomba);
				}
				else {
					PlayerDead(dynamic_cast<Player*>(mOwner));
				}
			}
			mOwner->SetPosition(mOwner->GetPosition() + offset);
			break;
		}
	}

	//if is not colliding with any block and is not out of boundary
	if (notColliding&&(!outBound)) {
		mInAir = true;
	}
	
	//update the YSpeed for next frame
	mYSpeed += 2000.0f*deltaTime;
	
	//update camera
	float newCameraX= mOwner->GetPosition().x - 300;
	if(newCameraX>=mOwner->GetGame()->cameraPos.x)
		mOwner->GetGame()->cameraPos.x = newCameraX;
	if(mOwner->GetGame()->cameraPos.x<0)
		mOwner->GetGame()->cameraPos.x = 0;

	//update animatedSprite
	if(!(mOwner->GetState()==ActorState::Paused))
		updateSprite();
}

void PlayerMove::GoombaDead(Goomba* currentGoomba) {
	mYSpeed = -350.0f;
	mInAir = true;
	//currentGoomba->asc->SetTexture(mOwner->GetGame()->GetTexture("Assets/Goomba/Dead.png"));
	currentGoomba->asc->SetAnimation("dead");
	currentGoomba->gm->SetForwardSpeed(0);
	currentGoomba->dead = true;
	Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav"), 0);
	//currentGoomba->SetPosition(Vector2(currentGoomba->GetPosition().x, 448));
}

void PlayerMove::PlayerDead(Player* p) {
	p->asc->SetAnimation("dead");
	p->SetState(ActorState::Paused);
	Mix_HaltChannel(mOwner->GetGame()->backgroundMusicChannel);
	Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav"), 0);

}

void PlayerMove::updateSprite() {
	if (!mInAir) {
		if (GetForwardSpeed()> 0) {
			mOwner->GetComponent<AnimatedSprite>()->SetAnimation("runRight");
		}
		else if (GetForwardSpeed() < 0) {
			mOwner->GetComponent<AnimatedSprite>()->SetAnimation("runLeft");
		}
		else {
			mOwner->GetComponent<AnimatedSprite>()->SetAnimation("idle");
		}
	}
	else {
		if (GetForwardSpeed() > 0) {
			mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpRight");
		}
		else if (GetForwardSpeed() < 0) {
			mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpLeft");
		}
		else {
			std::string current = mOwner->GetComponent<AnimatedSprite>()->GetAnimName();
			if (current == "runRight" || current == "jumpRight" || current == "idle") {
				mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpRight");
			}
			else {
				mOwner->GetComponent<AnimatedSprite>()->SetAnimation("jumpLeft");
			}
		}
	}
}