#include "Actor.h"

class Game;


class Thanos : public Actor {
public:
	Thanos(Game* game);
	int row = 83;
	int col = 2;
};