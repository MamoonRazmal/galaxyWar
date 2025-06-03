
#include <framework/Object.h>


#include <framework/Actor.h>


namespace ly
{
	Object::Object():mIsPendingDestroy{false}{}
	Object::~Object()
	{
		LOG("Destroy");
	}


	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
		LOG("your ship should be destroyed");

	}

	weak<Object> Object::GetSelfWeakRef()
	{
		return weak_from_this();
	}
	weak<const Object> Object::GetSelfWeakRef() const
	{
		return weak_from_this();
	}
}