
#include <framework/Object.h>
#include <framework/Core.h>

namespace ly
{
	Object::Object():mIsPendingDestroy{false}{}
	Object::~Object()
	{
		LOG("Destroy");
	}
}

void ly::Object::Destroy()
{
	mIsPendingDestroy = true;

}
