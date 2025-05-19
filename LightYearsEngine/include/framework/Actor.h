#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	class World;
	class Actor :public Object
	{
	public :
		Actor(World* ownworld , const std:: string& texturePath = "");
		void BeginPlayInteral();
	
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltatime);
		virtual ~Actor();
		void setTexture(const std::string& path);
		void Render(sf::RenderWindow& window);

	
	private:
		World* mOwningWorld;
		bool mHasBeganPlay;
		shared<sf::Texture> mTexture;
		sf::Texture empythTexture;
		sf::Sprite mSprite;
	
		
	};
}