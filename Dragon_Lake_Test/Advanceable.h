#pragma once

class LinearTrajectoryGenerator;
struct Point;

/*
Interface class to distinguish game objects that are able to gradually advance by trajectory.
*/

class Advanceable
{
public:
	virtual ~Advanceable();

	virtual LinearTrajectoryGenerator* setTrajectory(LinearTrajectoryGenerator* trajectory) = 0;
	virtual LinearTrajectoryGenerator* removeTrajectory() = 0;
	virtual void advance() = 0;

	virtual Point next() const = 0;

protected:
};

