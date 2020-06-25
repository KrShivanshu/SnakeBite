#include "Game.h"
#include <SFML/Graphics.hpp>
#include "MainMenu.h"

using namespace std;
using namespace Engine;
using namespace sf;

Game::Game():context_s(make_shared<Content>())
{
	context_s->window_s->create(VideoMode(480, 640), "Snake Bite", Style::Close);
	context_s->states_s->Add(make_unique<MainMenu>(context_s));
}

Game::~Game()
{
}

void Game::Run()
{
	
	Clock clock;
	Time timesincelastframe = Time::Zero;
	while (context_s->window_s->isOpen())
	{
		timesincelastframe += clock.restart();
		
		while (timesincelastframe > TIME_PER_FRAME)
		{
			timesincelastframe -= TIME_PER_FRAME;

			context_s->states_s->ProcessStateChange();
			context_s->states_s->GetCurrent()->ProcessInput();
			context_s->states_s->GetCurrent()->Update(TIME_PER_FRAME);
			context_s->states_s->GetCurrent()->Draw();
		}
	}
}
