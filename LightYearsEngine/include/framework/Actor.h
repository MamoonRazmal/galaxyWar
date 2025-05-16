#pragma once
namespace ly
{
	class World;
	class Actor
	{
	public :
		Actor(World* ownworld);
		void BeginPlayInteral();
		virtual void BeginPlay();
		virtual void Tick(float deltatyme);
		virtual ~Actor();
	private:
		World* mOwningWorld;
		bool mHasBeganPlay;
	};
}