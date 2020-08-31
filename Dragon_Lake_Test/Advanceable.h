#pragma once

struct LinearTrajectoryGenerator;
struct Point;

class Advanceable
{
public:

	virtual void setTrajectory(LinearTrajectoryGenerator* trajectory) = 0;
	virtual LinearTrajectoryGenerator* trajectory() const = 0;
	virtual void advance() = 0;
	virtual Point next() = 0;

protected:
};

