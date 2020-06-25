#include "Snake.h"

Snake::Snake():s_body(list<Sprite>(4))
{
	s_head = --s_body.end();
	s_tail = s_body.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const Texture & texture)
{
	float x = 32.f;
	for (auto &piece : s_body)
	{
		piece.setTexture(texture);
		piece.setPosition({ x,32.f });
		x += 32.f;
	}
}

void Snake::Move(const Vector2f & direction)
{
	s_tail->setPosition(s_head->getPosition() + direction);
	s_head = s_tail;
	++s_tail;
	if (s_tail == s_body.end())
	{
		s_tail = s_body.begin();
	}
}

bool Snake::IsOn(const Sprite & other) const
{
	return other.getGlobalBounds().intersects(s_head->getGlobalBounds());
}

void Snake::Grow(const Vector2f & direction)
{
	Sprite newPiece;
	newPiece.setTexture(*(s_body.begin()->getTexture()));
	newPiece.setPosition(s_head->getPosition() + direction);

	s_head = s_body.insert(++s_head, newPiece);
}

bool Snake::IsSelfIntersecting() const
{
	bool flag = false;
	for (auto piece = s_body.begin(); piece != s_body.end(); ++piece)
	{
		if (s_head != piece)
		{
			flag = IsOn(*piece);
			if (flag)
			{
				break;
			}
		}
	}
	return flag;
}

void Snake::draw(RenderTarget & target, RenderStates  states) const
{
	for (auto &piece : s_body)
	{
		target.draw(piece);

	}
}
