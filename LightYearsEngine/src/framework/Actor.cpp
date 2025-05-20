#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "framework/MathUtility.h"


#include <SFML/Graphics.hpp>
#include "framework/Actor.h"



namespace ly

{


	sf::Texture& getDummyTexture()
	{
		static sf::Texture dummy;
		static bool initialized = false;

		if (!initialized) {
			sf::Image image({ 1, 1 }, sf::Color::White); // 1x1 white pixel
			if (!dummy.loadFromImage(image)) {
				std::cerr << "Dummy texture creation failed\n";
				throw std::runtime_error("Failed to create dummy texture");
			}
			initialized = true;
		}
		return dummy;
	}

	ly::Actor::Actor(World* ownworld, const std::string& texturpath ): mOwningWorld{ownworld}, mHasBeganPlay{false},  mTexture{}, mSprite{ getDummyTexture() }
	{
		if (!texturpath.empty())
		{
			std::cout << "Constructor received path: '" << texturpath << "'" << std::endl;

			setTexture(texturpath);
		}
	
		
		//mSprite = new Sprite{ mTexture };
		
	}
	void Actor::BeginPlayInteral()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}
	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}
	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);

		}
	}
	void Actor::Tick(float deltatyme)
	{
	//	LOG("user is ticking");
	}
	ly::Actor::~Actor()
	{
		LOG("Actor Destroyed");
	}

	void Actor::setTexture(const std::string& path)
	{
		AssetManager& assetManager = AssetManager::Get();

		if (path.empty()) {
			std::cerr << "Warning: Empty texture path\n";
			return;
		}
		mTexture = assetManager.LoadTexture(path);
		if (mTexture ==nullptr) {
		
			return;
		}

		mSprite.setTexture(*mTexture, true); // 'true' resets texture rect
		int textureWidth = mTexture->getSize().x;
		int TextureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{ textureWidth,TextureHeight } });
		CenterPivot();

	}
	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(mSprite);
	}
	void ly::Actor::SetActorLocation(const sf::Vector2f& newL)
	{
		mSprite.setPosition(newL);
	}
	void Actor::setActorRotation(const sf::Angle angle)
	{
	//	sf::Angle angle = sf::degrees(newRot);

		mSprite.setRotation(angle);
	}
	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}
	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		sf::Angle angle = sf::degrees(offsetAmt);
		setActorRotation(GetActorRotation()+ angle);
	}
	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}
	sf::Angle Actor::GetActorRotation() const
	{
		sf::Angle angle = mSprite.getRotation();
	
		return angle;
	}
	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}
	sf::Vector2f Actor::GetActorRightDirection() const
	{
		sf::Angle deg = sf::degrees(90.f);
		return RotationToVector(GetActorRotation() +deg);
	}
	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.getCenter());
	}
}

