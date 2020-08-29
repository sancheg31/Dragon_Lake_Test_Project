#pragma once


#include <Framework.h>

#include "Utility.h"
#include "PlayerObject.h"

class MyFramework : public Framework 
{
public:

	MyFramework(Size wsize, Size msize, int enemy, int ammo);

	virtual void PreInit(int& width, int& height, bool& fullscreen);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);
private:

	PlayerObject* player{ nullptr };

	Size windowSize;
	Size mapSize;
	int enemyCount;
	int ammoAmount;
};



