#include "MinHeap.h"
#include <iostream>

MinHeap::MinHeap(vector<GridNode*> aVector, int aLength) : theVector(aVector), length(aLength)
{

}

MinHeap::MinHeap()
{
	length = 0;
}

void MinHeap::Push(GridNode* nodePtr)
{
	this->theVector.push_back(nodePtr);
	nodePtr->heapIdx = length++;
	BubbleUp(length - 1);
	nodePtr->state = 1;
}

void MinHeap::BubbleDown(int i)
{
	if (i < 0) return;

	while (i < this->length)
	{
		if (2 * i + 1 >= this->length) break;

		if (this->theVector[i]->cost > this->theVector[2 * i + 1]->cost || (2 * i + 2 < this->length && this->theVector[i]->cost > this->theVector[2 * i + 2]->cost))
		{
			GridNode* temp = this->theVector[i];

			if (2 * i + 2 < this->length && this->theVector[2 * i + 1]->cost > this->theVector[2 * i + 2]->cost)
			{
				this->theVector[i] = this->theVector[2 * i + 2];
				this->theVector[i]->heapIdx = 2 * i + 2;
				this->theVector[2 * i + 2] = temp;
				this->theVector[2 *i + 2]->heapIdx = i;
				i = 2 * i + 2;
			}
			else
			{
				this->theVector[i] = this->theVector[2 * i + 1];
				this->theVector[2 * i + 1] = temp;
				i = 2 * i + 1;
			}
		}
		else
		{
			break;
		}
	}
}

void MinHeap::BubbleUp(int i)
{
	if (i >= this->length) return;

	while (i > 0)
	{
		int parent = (int)((i - 1) / 2);

		if (this->theVector[i]->cost < this->theVector[parent]->cost)
		{
			GridNode* temp = this->theVector[i];
			this->theVector[i] = this->theVector[parent];
			this->theVector[i]->heapIdx = i;
			this->theVector[parent] = temp;
			this->theVector[parent]->heapIdx = parent;
			i = parent;
		}
		else
		{
			break;
		}
	}
}

void MinHeap::Heapify()
{
	for (int i = this->length - 1; i > 0; i--)
	{
		BubbleUp(i);
	}
}

GridNode* MinHeap::Get()
{
	return this->theVector[0];
}

GridNode* MinHeap::Pop()
{
	GridNode* min = this->theVector[0];
	min->heapIdx = -1;
	min->state = 2;
	this->theVector[0] = this->theVector.back();
	this->theVector[0]->heapIdx = 0;
	this->theVector.pop_back();
	this->length--;
	BubbleDown(0);

	return min;
}

void MinHeap::Update(int i, double value)
{
	if (value > this->theVector[i]->cost)
	{
		this->theVector[i]->cost = value;
		BubbleDown(i);
	}
	else
	{
		this->theVector[i]->cost = value;
		BubbleUp(i);
	}
}

vector<GridNode*> MinHeap::GetHeap()
{
	return this->theVector;
}

int MinHeap::GetLength()
{
	return this->length;
}