#pragma once
#include <vector>

class SensorCell
{
public:
	SensorCell();
	SensorCell(int index);
	~SensorCell();

	bool operator <(const SensorCell& rhs)
	{
		return this->index < rhs.index;
	}

	std::vector<int> ray;
	float index;
};

