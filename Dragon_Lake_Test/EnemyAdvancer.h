#pragma once


#include <list>
#include <cmath>

#include "Utility.h"

#include "DirectionState.h"

class Rectangle;

class Advanceable;
class GameObject;
class PlayerObject;
class EnemyObject;

class EnemyAdvancer
{

	struct ExEnemyObject
	{
		EnemyObject* enemy;
		DirectionState currentState;
	};

	using container_type = std::list<ExEnemyObject>;

public:
	EnemyAdvancer(PlayerObject* pl, std::list<EnemyObject*> obj);

	void advance();

private:

	Point nextObjectCenter(Advanceable* object, Size size);

	Rectangle twoPixelBoundary(GameObject* object);

	container_type findCollidedObjects(typename container_type::iterator start, Rectangle boundary);


	PlayerObject* player;
	container_type objects;
};

