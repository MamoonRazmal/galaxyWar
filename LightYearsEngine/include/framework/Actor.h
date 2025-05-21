#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Object.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	
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
		void SetActorLocation(const sf::Vector2f& newL);
		void setActorRotation( const sf::Angle angle);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);
		sf::Vector2f GetActorLocation() const;
		sf::Angle GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::Vector2u GetWindowsSize()const { return mOwningWorld->GetWindowSize(); }
		World* GetWorld() const { return mOwningWorld; }
		bool IsActorOutOfWindowBounds()const;
		sf::FloatRect GetActorGlobalBounds()const;
	
	private:
		void CenterPivot();
		World* mOwningWorld;
		bool mHasBeganPlay;
		shared<sf::Texture> mTexture;
		sf::Texture empythTexture;
		sf::Sprite mSprite;
	
		
	};
}