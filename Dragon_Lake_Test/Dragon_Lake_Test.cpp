﻿

#include <iostream>
#include <regex>
#include <string>
#include <cstring>

#include "GameEngine.h"

#include "MapArea.h"
#include "ScreenArea.h"
#include "GameObject.h"
#include "CSpriteFactory.h"
#include "GameObjectFactory.h"

#include "DirectionState.h"

#include "Utility.h"

struct CommandLineArgs
{
	Size windowDim = Size{ 600, 600 };
	Size mapDim = Size{ 1000, 1000 };

	int enemies = 10;
	int ammo = 3;
	int ticks = 10;
};

CommandLineArgs parse(int argc, char* argv[]) {

	CommandLineArgs args;
	std::regex dimensions{ "R(([1-9][0-9])*x([1-9][0-9]*))" };

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-window") == 0) {
			++i;
			if (std::cmatch results;  std::regex_match(argv[i], results, dimensions)) {
				Size mapDim = Size{ std::stoi(results[1]), std::stoi(results[2]) };
				if (mapDim.width > 0 && mapDim.height > 0)
					args.mapDim = mapDim;
			}
		}
		else if (strcmp(argv[i], "-map") == 0) {
			++i;
			if (std::cmatch results;  std::regex_match(argv[i], results, dimensions)) {
				Size windowDim = Size{ std::stoi(results[1]), std::stoi(results[2]) };
				if (windowDim.width > 0 && windowDim.height > 0)
					args.windowDim = windowDim;
			}
		}
		else if (strcmp(argv[i], "-num_enemies") == 0) {
			++i;
			int enemies = std::stoi(argv[i]);
			if (enemies > 0 && enemies < 100)
				args.enemies = enemies;
		}
		else if (strcmp(argv[i], "-num_ammo") == 0) {
			++i;
			int ammo = std::stoi(argv[i]);
			if (ammo > 0)
				args.ammo = ammo;
			args.ammo = std::stoi(argv[i]);
		}
		else if (strcmp(argv[i], "-ticks") == 0) {
			++i;
			int ticks = std::stoi(argv[i]);
			if (ticks >= 0)
				args.ticks = ticks;
		}
	}
	return args;
}


int main(int argc, char* argv[]) {

	auto args = parse(argc, argv);

	GameObject::setSpriteCreator(new CSpriteFactory());
	std::shared_ptr<MapArea> map = std::make_shared<MapArea>(args.mapDim);
	std::shared_ptr<ScreenArea> screen = std::make_shared<ScreenArea>(args.windowDim);
	std::shared_ptr<GameObjectFactory> factory = std::make_shared<GameObjectFactory>(map, screen);
	
	return run(new GameEngine(factory, map, screen, args.enemies, args.ammo, args.ticks));
}
