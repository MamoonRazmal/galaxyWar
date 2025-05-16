#include <iostream>
#include "framework/Application.h"
#include <stdio.h>
#include <framework/Core.h>
#include "framework/World.h"
namespace ly
{
	Application::Application():mWindow{ sf::VideoMode({ 1024,900 }), "Light Years" },mTargetFrameRate{60.f},mTickClock{},currentWorld{nullptr}
	{
	}
	void Application::Run()
	{
	
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;
        
        while (mWindow.isOpen())
        {
            while (const std::optional event = mWindow.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    mWindow.close();
            }

          
            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
               
                TickInternal(targetDeltaTime);
                RenderInternal();
              //  LOG("ticking at framerate : %f\n", 1.f / frameDeltaTime);
            }
        }
      

	
	}

    void Application::TickInternal(float deltatime)
    {
        Tick(deltatime);
        if (currentWorld)
        {
           
            currentWorld->TickInternal(deltatime);
        }
       
    }

    void Application::RenderInternal()
    {
 
        mWindow.clear();
        Render();
        mWindow.display();
      

    }

    void Application::Render()
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(100, 50));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setOrigin({ 50,50 });
        //  rectangle.setPosition({10, 20});
        rectangle.setPosition({ mWindow.getSize().x / 2.f,mWindow.getSize().y / 2.f });
        mWindow.draw(rectangle);
    }

    void Application::Tick(float deltatime)
    {

    }

    

}
