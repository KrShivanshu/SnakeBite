#include "GameOver.h"
#include "GamePlay.h"
#include <SFML/Window/Event.hpp>

GameOver::GameOver(shared_ptr<Content>&content) :content_s(content), isretryButtonPressed(false), isExitButtonPressed(false), isretryButtonSelected(true), isExitButtonSelected(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	content_s->assets_s->AddFont(MAIN_FONT, "assets/COOPBL.TTF");
	gameOverTitle_s.setFont(content_s->assets_s->GetFont(MAIN_FONT));
	gameOverTitle_s.setString("Game Over");
	gameOverTitle_s.setOrigin(gameOverTitle_s.getLocalBounds().width / 2, gameOverTitle_s.getLocalBounds().height / 2);
	gameOverTitle_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().x / 2 - 150.f);
	gameOverTitle_s.setCharacterSize(30);

	content_s->assets_s->AddFont(SECOND_FONT, "assets/waltographUI.ttf");
	retryButton_s.setFont(content_s->assets_s->GetFont(SECOND_FONT));
	retryButton_s.setString("Retry");
	retryButton_s.setOrigin(retryButton_s.getLocalBounds().width / 2, retryButton_s.getLocalBounds().height / 2);
	retryButton_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().x / 2);
	retryButton_s.setCharacterSize(23);

	//content_s->assets_s->AddFont(SECOND_FONT, "assets/waltographUI.ttf");
	exitButton_s.setFont(content_s->assets_s->GetFont(SECOND_FONT));
	exitButton_s.setString("Spare");
	exitButton_s.setOrigin(exitButton_s.getLocalBounds().width / 2, exitButton_s.getLocalBounds().height / 2);
	exitButton_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().x / 2 + 50.f);
	exitButton_s.setCharacterSize(20);
}

void GameOver::ProcessInput()
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
			switch (event.key.code)
			{
			case Keyboard::Up:
			{
				if (!isretryButtonSelected)
				{
					isretryButtonSelected = true;
					isExitButtonSelected = false;
				}
				break;
			}
			case Keyboard::Down:
			{
				if (!isExitButtonSelected)
				{
					isretryButtonSelected = false;
					isExitButtonSelected = true;
				}
				break;
			}
			case Keyboard::Return:
			{
				isretryButtonPressed = false;
				isExitButtonPressed = false;
				if (isretryButtonSelected)
					isretryButtonPressed = true;
				else
					isExitButtonPressed = true;
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void GameOver::Update(Time deltaTime)
{
	if (isretryButtonSelected)
	{
		retryButton_s.setFillColor(Color::Yellow);
		exitButton_s.setFillColor(Color::White);
	}
	else
	{
		retryButton_s.setFillColor(Color::White);
		exitButton_s.setFillColor(Color::Yellow);
	}
	if (isretryButtonPressed)
		content_s->states_s->Add(make_unique<GamePlay>(content_s), true);
	else if (isExitButtonPressed)
		content_s->window_s->close();
}

void GameOver::Draw()
{
	content_s->window_s->clear(Color::Red);
	content_s->window_s->draw(gameOverTitle_s);
	content_s->window_s->draw(retryButton_s);
	content_s->window_s->draw(exitButton_s);
	content_s->window_s->display();
}
