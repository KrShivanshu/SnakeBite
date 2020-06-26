#include "GamePlay.h"
#include "GameOver.h"
#include "GamePause.h"

#include <stdlib.h>
#include <time.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

GamePlay::GamePlay(shared_ptr<Content>& content):content_s(content),score(0),snakeDirection({32.f,0.f}),elapsedTime(Time::Zero),isPaused(false)
{
	srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	content_s->assets_s->AddTexture(GRASS, "assets/textures/grass.png",true);
	content_s->assets_s->AddTexture(SNAKE, "assets/textures/snake.png");
	content_s->assets_s->AddTexture(FOOD, "assets/textures/food.png");
	content_s->assets_s->AddTexture(WALL, "assets/textures/wall.png",true);

	grass.setTexture(content_s->assets_s->GetTexture(GRASS));
	grass.setTextureRect(content_s->window_s->getViewport(content_s->window_s->getDefaultView()));

	for (auto &wall : walls)
	{
		wall.setTexture(content_s->assets_s->GetTexture(WALL));
	}
	walls[0].setTextureRect({ 0, 0, (int)content_s->window_s->getSize().x, 32 });

	walls[1].setTextureRect({ 0, 0, (int)content_s->window_s->getSize().x, 32 });
	walls[1].setPosition(0, content_s->window_s->getSize().y - 32);

	walls[2].setTextureRect({ 0, 0,32, (int)content_s->window_s->getSize().y });

	walls[3].setTextureRect({ 0, 0,32, (int)content_s->window_s->getSize().y });
	walls[3].setPosition(content_s->window_s->getSize().x - 32, 0);

	food.setTexture(content_s->assets_s->GetTexture(FOOD));
	food.setPosition(5*32.f,9*32.f);

	snake.Init(content_s->assets_s->GetTexture(SNAKE));

	scoreText.setFont(content_s->assets_s->GetFont(MAIN_FONT));
	scoreText.setString("Score: " + to_string(score));
	scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
	scoreText.setPosition(content_s->window_s->getSize().x / 2, 16.f);
	scoreText.setCharacterSize(20);
}

void GamePlay::ProcessInput()
{
	Event event;
	while (content_s->window_s->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			content_s->window_s->close();
		}
		else if (event.type == Event::KeyPressed)
		{
			Vector2f newDirection = snakeDirection;
			switch (event.key.code)
			{
			case Keyboard::Up:
				newDirection = { 0.f,-32.f };
				break;
			case Keyboard::Down:
				newDirection = { 0.f,32.f };
				break;
			case Keyboard::Left:
				newDirection = { -32.f,0.f };
				break;
			case Keyboard::Right:
				newDirection = { 32.f,0.f };
				break;
			case Keyboard::Space:
				content_s->states_s->Add(make_unique<GamePause>(content_s/*,score*/));
				break;
			default:
				break;
			}
			if (abs(snakeDirection.x) != abs(newDirection.x) || abs(snakeDirection.y) != abs(newDirection.y))
			{
				snakeDirection = newDirection;
			}
		}
	}
}

void GamePlay::Update(Time deltaTime)
{
	if (!isPaused) {
		elapsedTime += deltaTime;
		if (elapsedTime.asSeconds() > 0.1)
		{
			for (auto &wall : walls)
			{
				if (snake.IsOn(wall))
				{
					content_s->states_s->Add(make_unique<GameOver>(content_s,score), true);
					break;
				}
			}
			if (snake.IsOn(food))
			{
				snake.Grow(snakeDirection);
				int x = 0, y = 0;
				std::random_device rd; // obtain a random number from hardware
				std::mt19937 gen(rd()); // seed the generator
				std::uniform_int_distribution<> distrx(1, 13);
				std::uniform_int_distribution<> distry(1, 18);
				x = distrx(gen);
				y = distry(gen);
				food.setPosition(x*32, y*32);
				score += 1;
				scoreText.setString("Score: " + to_string(score));
			}
			else
			{
				snake.Move(snakeDirection);
			}
			if (snake.IsSelfIntersecting())
			{
				content_s->states_s->Add(make_unique<GameOver>(content_s,score), true);
			}
			elapsedTime = Time::Zero;
		}
	}
}

void GamePlay::Draw()
{
	content_s->window_s->clear();
	content_s->window_s->draw(grass);
	for (auto &wall : walls) {
		content_s->window_s->draw(wall);
	}
	content_s->window_s->draw(food);
	content_s->window_s->draw(snake);
	content_s->window_s->draw(scoreText);
	content_s->window_s->display();
}

void GamePlay::Start()
{
	isPaused = false;
}

void GamePlay::Pause()
{
	isPaused = true;
}
