#include "MainMenu.h"
#include "GamePlay.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(shared_ptr<Content>&content):content_s(content), isPlayButtonPressed(false), isExitButtonPressed(false), isPlayButtonSelected(true), isExitButtonSelected(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	content_s->assets_s->AddFont(MAIN_FONT, "assets/COOPBL.TTF");
	gameTitle_s.setFont(content_s->assets_s->GetFont(MAIN_FONT));
	gameTitle_s.setString("Snake on loose");
	gameTitle_s.setOutlineThickness(2.f);
	
	gameTitle_s.setOrigin(gameTitle_s.getLocalBounds().width/2, gameTitle_s.getLocalBounds().height/2);
	gameTitle_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().x / 2 - 150.f);
	gameTitle_s.setCharacterSize(35);

	content_s->assets_s->AddFont(SECOND_FONT, "assets/waltographUI.ttf");
	playButton_s.setFont(content_s->assets_s->GetFont(SECOND_FONT));
	playButton_s.setString("Hunt");
	playButton_s.setOrigin(playButton_s.getLocalBounds().width / 2, playButton_s.getLocalBounds().height / 2);
	playButton_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().x / 2 + 20.f);
	playButton_s.setCharacterSize(27);

	//content_s->assets_s->AddFont(SECOND_FONT, "assets/waltographUI.ttf");
	exitButton_s.setFont(content_s->assets_s->GetFont(SECOND_FONT));
	exitButton_s.setString("Exit");
	exitButton_s.setOrigin(exitButton_s.getLocalBounds().width / 2, exitButton_s.getLocalBounds().height / 2);
	exitButton_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().x / 2 + 80.f);
	exitButton_s.setCharacterSize(27);
}

void MainMenu::ProcessInput()
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
					if (!isPlayButtonSelected)
					{
						isPlayButtonSelected = true;
						isExitButtonSelected = false;
					}
					break;
				}
				case Keyboard::Down:
				{
					if (!isExitButtonSelected)
					{
						isPlayButtonSelected = false;
						isExitButtonSelected = true;
					}
					break;
				}
				case Keyboard::Return:
				{
					isPlayButtonPressed = false;
					isExitButtonPressed = false;
					if (isPlayButtonSelected)
						isPlayButtonPressed = true;
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

void MainMenu::Update(Time deltaTime)
{
	if (isPlayButtonSelected)
	{
		playButton_s.setFillColor(Color::Yellow);
		exitButton_s.setFillColor(Color::White);
	}
	else
	{
		playButton_s.setFillColor(Color::White);
		exitButton_s.setFillColor(Color::Yellow);
	}
	if (isPlayButtonPressed)
		content_s->states_s->Add(make_unique<GamePlay>(content_s), true);
		
	else if (isExitButtonPressed)
		content_s->window_s->close();
}

void MainMenu::Draw()
{
	content_s->window_s->clear(Color::Black);
	content_s->window_s->draw(gameTitle_s);
	content_s->window_s->draw(playButton_s);
	content_s->window_s->draw(exitButton_s);
	content_s->window_s->display();
}
