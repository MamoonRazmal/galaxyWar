#pragma once
#include <sfml/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public :
		 Application();
		 void Run();
		 template<typename WorldType>
		 weak<WorldType> LoadWorld();
		 
	private :
		sf::RenderWindow mWindow;
		float mTargetFrameRate;
		sf::Clock mTickClock;
		void TickInternal(float deltatime);
		void RenderInternal();
		virtual void Render();
		virtual void Tick(float deltatime);
		shared<World> currentWorld;
	};


	template <typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternel();
		return newWorld;
	
	}
}
