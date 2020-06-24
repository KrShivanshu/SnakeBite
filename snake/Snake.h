#pragma once
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
//using namespace Engine;

class Snake : public sf::Drawable 
{
private:
	list<Sprite>s_body;
	list<Sprite>::iterator s_head;
	list<Sprite>::iterator s_tail;

public:
	Snake();
	~Snake();

	void Init(const Texture &texture);
	void Move(const Vector2f &direction);
	bool IsOn(const Sprite &other) const;
	void Grow(const Vector2f &direction);
	bool IsSelfIntersecting() const;
	void draw(RenderTarget &target, RenderStates states) const override;

};

