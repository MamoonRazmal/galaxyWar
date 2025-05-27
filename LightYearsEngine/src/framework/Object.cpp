
#include <framework/Object.h>


#include <framework/Actor.h>


namespace ly
{
	Object::Object():mIsPendingDestroy{false}{}
	Object::~Object()
	{
		LOG("Destroy");
	}


	void ly::Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;

	}

	weak<Object> ly::Object::GetSelfWeakRef()
	{
		return weak_from_this();
	}
	weak<const Object> ly::Object::GetSelfWeakRef() const
	{
		return weak_from_this();
	}
}