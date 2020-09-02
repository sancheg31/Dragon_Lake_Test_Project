#pragma once

#include <vector>
#include <list>

#include "DirectionState.h"

struct Point;
class Rectangle;

class Advanceable;
class GameObject;
class PlayerObject;
class EnemyObject;

class EnemyStorage;

class EnemyAdvancePolicy
{

	struct ExEnemyObject
	{
		EnemyObject* enemy;
		DirectionState currentState;
	};

	using container_type = std::list<ExEnemyObject>;
	using iterator = container_type::iterator;

public:
	EnemyAdvancePolicy(PlayerObject* pl, int ticks);

	void advance(const EnemyStorage& objects);

private:

	Point nextObjectCenter(Advanceable* object, Size size) const;

	Rectangle twoPixelBoundary(GameObject* object) const;

	container_type findCollidedObjects(const container_type& cont, iterator start, Rectangle boundary) const;
	
	std::vector<Rectangle> findCollidedRectangles(const container_type& cont) const;

	DirectionState findDirection(EnemyObject* object, DirectionState state, const std::vector<Rectangle>& constraints);


	PlayerObject* playerObject;
	int ticksCount;
	int ticks{ 0 };
};

