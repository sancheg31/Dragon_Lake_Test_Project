

#include "MyFramework.h"
#include "Rectangle.h"
#include "ScreenArea.h"

#include <iostream>

void rectangleTest() {
	Rectangle first{ Point{0, 0}, Size{20, 20}, VertexPosition::UP_LEFT };
	Rectangle second{ Point{10, 10}, Size{20, 20}, VertexPosition::UP_LEFT };
	std::cout << std::boolalpha << first.isCollide(second) << "\n" <<
		first.isContained(Point{ 10, 10 }) << " " << first.isContained(Point{ 0, 0 }) << " " << first.isContained(Point{ 20, 20 })
		<< " " << first.isContained(Point{ 0, 20 }) << " " << first.isContained(Point{ 20, 0 }) << " " << !first.isContained(Point{ 20, 21 }) << '\n';

	first = Rectangle{ Point{20, 40}, Size{15, 8}, VertexPosition::UP_LEFT };
	second = Rectangle{ Point{17, 28}, Size{5, 13}, VertexPosition::UP_LEFT };
	std::cout << std::boolalpha << second.isCollide(first) << " " << first.isCollide(second) << " " << second.isCollide(second) << '\n';

	std::cout << (first.upLeft() == Point{ 20, 40 }) << " " << (first.upRight() == Point{ 35, 40 })
		<< " " << (first.downLeft() == Point{ 20, 48 }) << " " << (first.downRight() == Point{ 35, 48 }) << '\n';
}

int main(int argc, char* argv[]) {

	rectangleTest();
	return run(new MyFramework({ 600, 600 }, { 400, 400 }, 10, 3));
}
