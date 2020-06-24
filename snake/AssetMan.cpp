#include "AssetMan.h"

using namespace Engine;
using namespace std;

AssetMan::AssetMan()
{
}

AssetMan::~AssetMan()
{
}

void AssetMan::AddTexture(int id, const string & filepath, bool wantRepeated)
{
	auto texture = make_unique<Texture>();
	if (texture->loadFromFile(filepath))
	{
		texture->setRepeated(wantRepeated);
		textures_s[id] = move(texture);
	}
}

void AssetMan::AddFont(int id, const string & filepath)
{
	auto font = make_unique<Font>();
	if (font->loadFromFile(filepath)) {
		fonts_s[id] = move(font);
	}
}

const Texture & AssetMan::GetTexture(int id) const
{
	// TODO: insert return statement here
	return *(textures_s.at(id).get());
}

const Font & AssetMan::GetFont(int id) const
{
	// TODO: insert return statement here
	return *(fonts_s.at(id).get());
}
