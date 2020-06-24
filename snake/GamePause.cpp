#include "GamePause.h"

GamePause::GamePause(shared_ptr<Content>& content):content_s(content)
{
}

GamePause::~GamePause()
{
}

void GamePause::Init()
{
	pauseTitle_s.setFont(content_s->assets_s->GetFont(MAIN_FONT));
	pauseTitle_s.setString("Taking Rest");
	pauseTitle_s.setOrigin(pauseTitle_s.getLocalBounds().width / 2, pauseTitle_s.getLocalBounds().height / 2);
	pauseTitle_s.setPosition(content_s->window_s->getSize().x / 2, content_s->window_s->getSize().y / 2);
}

void GamePause::ProcessInput()
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
				case Keyboard::Space:
				{
					content_s->states_s->PopCurrent();
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

void GamePause::Update(Time deltaTime)
{
}

void GamePause::Draw()
{
	content_s->window_s->draw(pauseTitle_s);
	content_s->window_s->display();
}
