

template<class T>
class Heap<T>
{
	T items[];
	int currentItemCount;

public:
	Heap(int maxHeapSize);
	Add(T item);
};