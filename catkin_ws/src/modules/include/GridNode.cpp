#include "GridNode.h"
#include <limits>


GridNode::GridNode()
{
	coords = point3d(0, 0, 0);
	occupied = 0;
	parent = NULL;
	cost = std::numeric_limits<int>::max();
	heapIdx = -1;
	state = 0;
	neighbors = {};
	edges = {};
	object = 0;
}

GridNode::GridNode(point3d coord, bool occ, GridNode* par, double cos, vector<GridNode*> neighbs, vector<float> eggs, bool obj)
{
	coords = coord;
	occupied = occ;
	parent = par;
	cost = cos;
	neighbors = neighbs;
	edges = eggs;
	heapIdx = -1;
	state = 0;
	object = obj;
}