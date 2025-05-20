#include "framework/MathUtility.h"

namespace ly
{
    const float PI = 3.1415926535;
    sf::Vector2f ly::RotationToVector(sf::Angle angle)
    {
        float radians = angle.asRadians();
     //   float radians = DegreesToRadians(angle);
        
        return sf::Vector2f(std::cos(radians),std::sin(radians));
    }

    float ly::DegreesToRadians(float degress)
    {
        return degress * (PI / 180.f);
    }

    float ly::RadiansToDegress(float radians)
    {
        return radians * (180.f / PI);
    }

}
