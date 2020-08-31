﻿

#include "MyFramework.h"

#include "MapArea.h"
#include "ScreenArea.h"
#include "GameObject.h"
#include "CSpriteFactory.h"
#include "GameObjectFactory.h"

#include "Utility.h"

#include <iostream>
#include <regex>
#include <string>
#include <cstring>

struct CommandLineArgs
{
	Size windowDim = Size{ 1000, 1000 };
	Size mapDim = Size{ 1000, 1000 };

	int enemies = 10;
	int ammo = 100;
};

CommandLineArgs parse(int argc, char* argv[]) {

	CommandLineArgs args;
	std::regex dimensions{ "R(([1-9][0-9])*x([1-9][0-9]*))" };

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-window") == 0) {
			++i;
			if (std::cmatch results;  std::regex_match(argv[i], results, dimensions)) {
				args.mapDim = Size{ std::stoi(results[1]), std::stoi(results[2]) };
			}
		}
		else if (strcmp(argv[i], "-map") == 0) {
			++i;
			if (std::cmatch results;  std::regex_match(argv[i], results, dimensions)) {
				args.windowDim = Size{ std::stoi(results[1]), std::stoi(results[2]) };
			}
		}
		else if (strcmp(argv[i], "-num_enemies") == 0) {
			++i;
			args.enemies = std::stoi(argv[i]);
		}
		else if (strcmp(argv[i], "-num_ammo") == 0) {
			++i;
			args.enemies = std::stoi(argv[i]);
		}
	}
	return args;
}


int main(int argc, char* argv[]) {

	auto args = parse(argc, argv);

	GameObject::setSpriteCreator(new CSpriteFactory());
	std::shared_ptr<MapArea> map = std::make_shared<MapArea>(args.mapDim);
	std::shared_ptr<ScreenArea> screen = std::make_shared<ScreenArea>(args.windowDim);
	std::cout << screen->size().width << " " << screen->size().height << '\n';
	auto factory = new GameObjectFactory(map, screen);
	return run(new MyFramework(factory, map, screen, args.enemies, args.ammo));
}
