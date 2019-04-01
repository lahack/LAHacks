#pragma once
#include "Actor.h"
#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
class Words :
	public Actor
{
public:
	Words(class Game* game);
	~Words();
	void OnProcessInput(const Uint8* keyState) override;
	void OnUpdate(float deltaTime) override;
	std::string words = "";
	bool readEnable = true;
	bool clear = false;
	SDL_Texture * texture;
	const Uint8* lastPressed;
	bool keyPressed = false;
	std::string subj;
	std::string binj;
	std::string response;
};

