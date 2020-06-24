#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace Engine;
using namespace std;
using namespace sf;

class GamePause :
	public State
{
private:
	shared_ptr<Content>content_s;
	Text pauseTitle_s;
public:
	GamePause(shared_ptr<Content>&content);
	~GamePause();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;
};

