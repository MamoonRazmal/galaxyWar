#include <iostream>
#include "framework/Application.h"
#include <stdio.h>
#include <framework/Core.h>
#include "framework/World.h"
namespace ly
{

    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, uint32_t style) :mWindow{ sf::VideoMode({ windowWidth,windowHeight }), title,style}, mTargetFrameRate{ 60.f }, mTickClock{}, currentWorld{ nullptr }
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
        mWindow.setVerticalSyncEnabled(false); // Add after window creation
        Render();
        mWindow.display();
      

    }

    void Application::Render()
    {
        if (currentWorld)
        {
            currentWorld->Render(mWindow);
      }
    }

    void Application::Tick(float deltatime)
    {

    }

    

}
