#pragma once
#include <vector>
#include "Critter.h"

class ObjectPool {
public:
	ObjectPool(int size);
	~ObjectPool();


	std::vector<Critter> GetActive() { return active; }
	std::vector<Critter> GetInactive() { return inactive; }

	void spawn();
	void despawn(Critter& mover);


private:
	std::vector<Critter> inactive;
	std::vector<Critter> active;
	int m_size;
	Critter* critterPool = nullptr;

};
