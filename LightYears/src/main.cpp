#include <iostream>
#include <SFML/Graphics.hpp>
#include "framework/Application.h"
using namespace std;
int main()
{
	
unique_ptr<	ly::Application> App = make_unique< ly::Application>();
	App->Run();
    return 0;
	
	
}