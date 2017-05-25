#include <vector>
#include <octomap/math/Vector3.h>
#include <octomap/octomap.h>

using namespace octomap;
using namespace std;

class GridNode
{
public:
	GridNode();
	GridNode(point3d, bool, GridNode*, double, vector<GridNode*>, vector<float>, bool);

	bool occupied;
	int state;
	GridNode* parent;
	double cost;
	point3d coords;
	vector<GridNode*> neighbors;
	vector<float> edges;
	int heapIdx;
	bool object;

	void Update(int);
};