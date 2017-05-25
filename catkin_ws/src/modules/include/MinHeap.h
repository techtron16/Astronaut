using namespace std;
#include <vector>
#include "GridNode.h"

class MinHeap
{
private:
	vector<GridNode*> theVector;
	int length;

public:
	MinHeap();
	MinHeap(vector<GridNode*>, int);

	void Push(GridNode* nodePtr);

	void BubbleDown(int);
	
	void BubbleUp(int);

	void Heapify();

	void Update(int, double);

	int GetLength();

	GridNode* Get();

	GridNode* Pop();

	vector<GridNode*> GetHeap();
};