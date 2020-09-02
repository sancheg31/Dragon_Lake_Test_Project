#pragma once


#include <algorithm>
#include <list>
#include <cmath>

#include "Rectangle.h"
#include "Utility.h"

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "DirectionState.h"

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

	Point objectCenter(GameObject* object);

	Point nextObjectCenter(Advanceable* object, Size size);

	Rectangle twoPixelBoundary(GameObject* object);


	container_type findCollidedObjects(typename container_type::iterator start, Rectangle boundary);


	PlayerObject* player;
	container_type objects;
};

