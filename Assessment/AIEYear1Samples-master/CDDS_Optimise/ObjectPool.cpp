#include "ObjectPool.h"
#include "ResourceManager.h"


ObjectPool::ObjectPool(int size)
{
	m_size = size;
	critterPool = new Critter[size];
	for (int i = 0; i < size; ++i)
	{
		inactive.push_back(critterPool[i]);
	}
}
ObjectPool::~ObjectPool()
{
	//destroy[] critterpool;
}


void ObjectPool::spawn()
{
	if (inactive.size() > 0) {
		Critter critter = inactive.back();
		inactive.pop_back();
		active.push_back(critter);
	}
}

void ObjectPool::despawn(Critter &moved)
{
	if (active.size() > 0)
	{
		std::swap(moved, active.back());
		active.pop_back();
		inactive.push_back(moved);
	}

}
