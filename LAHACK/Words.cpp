#include "Words.h"
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
#include "Math.h"
#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
// #include <zmq.hpp>


Words::Words(Game* game) :Actor(game)
{
	// SetPosition(Vector2(200, 200));
}


Words::~Words()
{
}

void Words::OnProcessInput(const Uint8* keyState) {
	if (readEnable) {
		if (!keyPressed) {
			if (keyState[SDL_SCANCODE_A]) {
				words = words + "A";
			}
			else if (keyState[SDL_SCANCODE_B]) {
				words = words + "B";
			}
			else if (keyState[SDL_SCANCODE_C]) {
				words = words + "C";
			}
			else if (keyState[SDL_SCANCODE_D]) {
				words = words + "D";
			}
			else if (keyState[SDL_SCANCODE_E]) {
				words = words + "E";
			}
			else if (keyState[SDL_SCANCODE_F]) {
				words = words + "F";
			}
			else if (keyState[SDL_SCANCODE_G]) {
				words = words + "G";
			}
			else if (keyState[SDL_SCANCODE_H]) {
				words = words + "H";
			}
			else if (keyState[SDL_SCANCODE_I]) {
				words = words + "I";
			}
			else if (keyState[SDL_SCANCODE_J]) {
				words = words + "J";
			}
			else if (keyState[SDL_SCANCODE_K]) {
				words = words + "K";
			}
			else if (keyState[SDL_SCANCODE_L]) {
				words = words + "L";
			}
			else if (keyState[SDL_SCANCODE_M]) {
				words = words + "M";
			}
			else if (keyState[SDL_SCANCODE_N]) {
				words = words + "N";
			}
			else if (keyState[SDL_SCANCODE_O]) {
				words = words + "O";
			}
			else if (keyState[SDL_SCANCODE_P]) {
				words = words + "P";
			}
			else if (keyState[SDL_SCANCODE_Q]) {
				words = words + "Q";
			}
			else if (keyState[SDL_SCANCODE_R]) {
				words = words + "R";
			}
			else if (keyState[SDL_SCANCODE_S]) {
				words = words + "S";
			}
			else if (keyState[SDL_SCANCODE_T]) {
				words = words + "T";
			}
			else if (keyState[SDL_SCANCODE_U]) {
				words = words + "U";
			}
			else if (keyState[SDL_SCANCODE_V]) {
				words = words + "V";
			}
			else if (keyState[SDL_SCANCODE_W]) {
				words = words + "W";
			}
			else if (keyState[SDL_SCANCODE_X]) {
				words = words + "X";
			}
			else if (keyState[SDL_SCANCODE_Y]) {
				words = words + "Y";
			}
			else if (keyState[SDL_SCANCODE_Z]) {
				words = words + "Z";
			}
			else if (keyState[SDL_SCANCODE_SPACE]) {
				words = words + " ";
			}
			else if (keyState[SDL_SCANCODE_RETURN]) {
				// readEnable = false;
				clear = true;

				std::string wordss = "A DOG IS ON A KEY";
				GetGame()->WriteFile(subj, binj, words, "C:\\Users\\haoqi\\PycharmProjects\\LAHACK\\request.txt");
				response = GetGame()->FileChanged("C:\\Users\\haoqi\\PycharmProjects\\LAHACK\\response.txt");
				while (response == "empty") {
					std::cout << response << std::endl;
					response = GetGame()->FileChanged("C:\\Users\\haoqi\\PycharmProjects\\LAHACK\\response.txt");
				}
				std::cout << "response is " << response << std::endl;
				
				// clear = false;
			}
			else if (keyState[SDL_SCANCODE_DELETE]) {
				if (words.length() > 0) {
					words = words.substr(0, words.length() - 1);
				}
			}
		}
	}
	keyPressed = keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_B] || keyState[SDL_SCANCODE_C] || keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_E]
		|| keyState[SDL_SCANCODE_F] || keyState[SDL_SCANCODE_G] || keyState[SDL_SCANCODE_H] || keyState[SDL_SCANCODE_I] || keyState[SDL_SCANCODE_J]
		|| keyState[SDL_SCANCODE_K] || keyState[SDL_SCANCODE_L] || keyState[SDL_SCANCODE_M] || keyState[SDL_SCANCODE_N] || keyState[SDL_SCANCODE_O]
		|| keyState[SDL_SCANCODE_P] || keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_R] || keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_T]
		|| keyState[SDL_SCANCODE_U] || keyState[SDL_SCANCODE_V] || keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_X] || keyState[SDL_SCANCODE_Y]
		|| keyState[SDL_SCANCODE_Z] || keyState[SDL_SCANCODE_DELETE];
}

void Words::OnUpdate(float deltaTime) {
	std::cout << "words: are " << words << std::endl;
	if (clear) {
		words = "";
		std::cout << "clear is clicked" << std::endl;
		// return;
	}


	SDL_Surface * surface = GetGame()->GetSurface(words);
	
	texture = SDL_CreateTextureFromSurface(GetGame()->renderer,
		surface);
	// SDL_FreeSurface(surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 10, 100, texW, texH };
	SDL_RenderCopy(GetGame()->renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(GetGame()->renderer);
}