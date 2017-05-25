#include "InfoNode.h"



InfoNode::InfoNode()
{
	infoGain = 0;
	cost = 0;
	quality = 0;
	coords = point3d(0, 0, 0);
	pitch = 0;
	yaw = 0;
}

InfoNode::InfoNode(float IG, float dist, point3d coord, float yawy, float pit)
{
	infoGain = IG;
	cost = dist;
	quality = 0;
	coords = coord;
	yaw = yawy;
	pitch = pit;
}