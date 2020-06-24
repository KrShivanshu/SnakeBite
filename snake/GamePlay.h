#pragma once

#include <memory>
#include <array>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "State.h"
#include "Snake.h"

using namespace std;
using namespace sf;
using namespace Engine;
class GamePlay:public State
{
private: 
	shared_ptr<Content>content_s;
	Sprite grass;
	Sprite food;
	Snake snake;
	array<Sprite, 4> walls;
	Text scoreText;
	int score;
	Vector2f snakeDirection;
	Time elapsedTime;
	bool isPaused;

public:
	GamePlay(shared_ptr<Content>&content);
	~GamePlay();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

	void Start() override;
	void Pause() override;

};

