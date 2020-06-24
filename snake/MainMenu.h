#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace Engine;
using namespace std;
using namespace sf;

class MainMenu:public Engine::State
{
private:
	shared_ptr<Content>content_s;
	Text gameTitle_s;
	Text playButton_s;
	Text exitButton_s;

	bool isPlayButtonPressed;
	bool isExitButtonPressed;

	bool isPlayButtonSelected;
	bool isExitButtonSelected;

public:
	MainMenu(shared_ptr<Content>& content);
	~MainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

};

