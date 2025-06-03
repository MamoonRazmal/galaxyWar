#include "framework/Actor.h"
#include "framework/Core.h"

#include "framework/AssetManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "framework/MathUtility.h"

#include "framework/PhysicsSystem.h"




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

	ly::Actor::Actor(World* ownworld, const std::string& texturpath ): mOwningWorld{ownworld}, mHasBeganPlay{false},  mTexture{}, mSprite{ getDummyTexture() },mphysicBody{nullptr},mEnablePhysics{false},mTeamID{ GetNeutralTeamID()}
	{
		if (!texturpath.empty())
		{
		//	std::cout << "Constructor received path: '" << texturpath << "'" << std::endl;

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
		UpdatePhysicsBodyTransform();
	}
	void Actor::setActorRotation(const sf::Angle angle)
	{
	//	sf::Angle angle = sf::degrees(newRot);

		mSprite.setRotation(angle);
		UpdatePhysicsBodyTransform();
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
		sf::Angle deg = sf::degrees(0.f);
		return RotationToVector(GetActorRotation() +deg);
	}
	bool Actor::IsOtherHostile(Actor* actor) const
	{
		if (GetTeamID() == GetNeutralTeamID() || actor->GetTeamID() == GetNeutralTeamID())
		{
			return false;
		}
		return GetTeamID() != actor->GetTeamID();
	}
	void Actor::ApplyDamage(float damage)
	{
		
	}
	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.getCenter());
	}
	void Actor::UpdatePhysicsBodyTransform()
	{
		if (mphysicBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale,GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation().asRadians());
			mphysicBody->SetTransform(pos,rotation);
		}
	}
	void Actor::InitiallizePhysics()
	{
		if (!mphysicBody)
			mphysicBody = PhysicsSystem::Get().AddListener(this);


	}
	void Actor::UnInitializePhysics()
	{
		if (mphysicBody)
		{
			PhysicsSystem::Get().RemoveListener(mphysicBody);
			mphysicBody = nullptr;
		}
		
	}
	bool Actor::IsActorOutOfWindowBounds()const
	{
		float windwidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;
		
		float width = GetActorGlobalBounds().position.x;
		float height = GetActorGlobalBounds().position.y;
		sf::Vector2f actorPosition = GetActorLocation();
		if (actorPosition.x < -width)
		{
			return true;
		}
		if (actorPosition.x > windwidth + width)
		{
			return true;
		}
		if (actorPosition.y < -height)
		{
			return true;
		}
		if (actorPosition.y > windowHeight + height)
		{
			return true;
		}
		return false;
	}
	sf::FloatRect Actor::GetActorGlobalBounds()const
	{
		return mSprite.getGlobalBounds();
	}
	void ly::Actor::SetEnablePhysics(bool enable)
	{
		mEnablePhysics = true;
		if (mEnablePhysics)
		{
			InitiallizePhysics();
		}
		else
		{
			UnInitializePhysics();
		}
	}
	void Actor::OnActorBeginOverlap(Actor* actor)
	{
		LOG("over lap begin");
	}
	void Actor::OnActorEndOverlap(Actor* actor)
	{
		LOG("over lap finished");
	}
	void Actor::Destroy()
	{
		UnInitializePhysics();
		Object::Destroy();
	}
}

