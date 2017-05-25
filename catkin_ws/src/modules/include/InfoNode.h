#include <octomap/math/Vector3.h>
#include <octomap/octomap.h>

using namespace octomap;
using namespace std;

class InfoNode
{
public:
	InfoNode();
	InfoNode(float, float, point3d, float, float);
	
	float infoGain;
	float cost;
	float quality;
	point3d coords;
	float yaw;
	float pitch;

	bool operator <(const InfoNode& rhs)
	{
		return this->infoGain < rhs.infoGain;
	}
};

