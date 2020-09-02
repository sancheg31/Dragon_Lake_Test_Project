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
		DirectionState leftState;
		DirectionState rightState;
	};

	using container_type = std::list<ExEnemyObject>;

public:
	EnemyAdvancer(PlayerObject* pl, std::list<EnemyObject*> obj);

	void advance();

private:

	Point objectCenter(GameObject* object);

	Point nextObjectCenter(Advanceable* object, Size size);

	Rectangle twoPixelBoundary(GameObject* object);


	std::pair<container_type, typename container_type::iterator> 
		findCollidedObjects(typename container_type::iterator start, Rectangle boundary);


	PlayerObject* player;
	container_type objects;
};

