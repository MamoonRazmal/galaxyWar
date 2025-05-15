#include "framework/Application.h"
namespace ly
{
	Application::Application():mWindow{ sf::VideoMode({ 1024,1440 }), "Light Years" },mTargetFrameRate{60.f}
	{
	}
	void Application::Run()
	{
	

        while (mWindow.isOpen())
        {
            while (const std::optional event = mWindow.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    mWindow.close();
            }

            mWindow.clear();
            ////window.draw(shape);
            mWindow.display();
        }

	
	}

}
