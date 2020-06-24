#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace Engine;
using namespace std;
using namespace sf;

class GameOver :public Engine::State
{
private:
	shared_ptr<Content>content_s;
	Text gameOverTitle_s;
	Text retryButton_s;
	Text exitButton_s;

	bool isretryButtonPressed;
	bool isExitButtonPressed;

	bool isretryButtonSelected;
	bool isExitButtonSelected;

public:
	GameOver(shared_ptr<Content>& content);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

};



