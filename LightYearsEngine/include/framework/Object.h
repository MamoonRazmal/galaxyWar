#pragma once
#include<memory>
#include "framework/Delegate.h"
#include "Delegate.h"

#include"framework/Core.h"

namespace ly
{
	
	class Object : public std::enable_shared_from_this<Object>
	{
	public :
		Object();
		virtual  ~Object();
		virtual void Destroy();
		bool IsPendingDestroy()const { return mIsPendingDestroy; }
	   weak <Object> GetSelfWeakRef();
	   weak<const Object> GetSelfWeakRef() const;
	   Delegate<Object*> onDestroy;
	private:
		bool mIsPendingDestroy;
	};
}