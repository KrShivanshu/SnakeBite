#pragma once
#include<map>
#include<memory>
#include<string>

#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;
namespace Engine {

	class AssetMan
	{
	private:
		map<int, unique_ptr<Texture>>textures_s;
		map<int, unique_ptr<Font>>fonts_s;

	public:
		AssetMan();
		~AssetMan();
		void AddTexture(int id, const string &filepath, bool wantRepeated = false);
		void AddFont(int id, const string &filepath);
		
		const Texture &GetTexture(int id) const;
		const Font &GetFont(int id) const;
	};

}
