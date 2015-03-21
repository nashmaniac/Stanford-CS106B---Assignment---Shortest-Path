/*
* File : pqueue.h
* ----------------
* Defines the interface for the Priority Queue(PQueue) class 
* The priority queue class is implemented by the Heap Binary tree
* The name choice here is important as though the implementation
* is done using a binary heap tree we abstract the ugly ans show
* the priority queue as a priority queue
*/

#ifndef PQUEUE_H
#define PQUEUE_H
#include "realvector.h"
#include <iostream> 
#include "cmpfn.h"
	
template <typename ElemType>
class PQueue{
public:
	/*
	* Function : PQueue()
	* Usage    : Automatically Invoked
	* -----------------------------------------------------
	* Sets apart space for the input of integers	
	* The constructor takes in a function to compare the defined 
	* ElemType elements, the working of the comparison function must 
	* be as described following 
	* If the two passed in elements are the same the function should return 0
	* If the first element is less than the second then it should return a -1
	* If the first element is greater than the second one then it should return a 1
	* If no comparison function is passed then the constructor uses the default 
	* function which uses the > and = to order the elements
	*/
	PQueue(int (cmpFn)(ElemType, ElemType) = OperatorCmp);
	/*
	* Function : ~PQueue
	* Usage    : Automatically Invoked
	* -----------------------------------------------------
	*/
	~PQueue();

	/*
	* Function : void enqueue(int value)
	* -----------------------------------------------------
	* Adds in the value passed as parameter to the queue
	* for later retreival.
	*/
	void enqueue(ElemType value);

	/*
	* Function : size()
	* -----------------------------------------------------
	* Returns the number of elements or integers present in
	* the queue.
	*/
	int size();

	bool isEmpty();

	/*
	* Function : int dequeueMin()
	* -----------------------------------------------------
	* Returns the smallest value present in the queue.
	*/
	ElemType dequeueMin();
private:
	RealVector<ElemType> rv;
	int numElements;
	int (*cmpFn)(ElemType, ElemType);

	void rearrangeAfterInsertion();
	void recInsertRearrange(int endIndex);
	void rearrangeAfterRemoval();
	void recRemovalRearrange(int begIndex);
	int smallestChild(int parentIndex);
	bool hasNoMoreChildren(int index);

};

/*
* File : pqueue.cpp
* ------------------
* Defines the internal mechanisms and working of 
* the Priority queue class
*/
template <typename ElemType>
PQueue<ElemType>::PQueue(int (cmp)(ElemType, ElemType)){
	cmpFn = cmp;
}

template <typename ElemType>
PQueue<ElemType>::~PQueue(){
	//destructor function
}

/*
* Implementation notes : 
* -----------------------
* Adds the value to the queue making sure that the 
* largest of the values stay at top of the heap tree
* or in other words the tree always remains arranged in 
* decreasing order.
* The maintainance of arrangement is carried out by the 
* rearrangeAfterInsertion() function;
*/
template <typename ElemType>
void PQueue<ElemType>::enqueue(ElemType value){
	rv.add(value);
	if(size() >= 2) rearrangeAfterInsertion();
}

	
//wrapper function FOR RecInsertRearrange() recursive function
template <typename ElemType>
void PQueue<ElemType>::rearrangeAfterInsertion(){
	recInsertRearrange(size());
}

template <typename ElemType>
void PQueue<ElemType>::recInsertRearrange(int endIndex){
	if(endIndex <= 1) return;
	int parentIndex = endIndex/2;
	if(cmpFn(rv.getAt(parentIndex), rv.getAt(endIndex)) == -1 || cmpFn(rv.getAt(parentIndex), rv.getAt(endIndex)) == 0 ) return;
	rv.swap(parentIndex, endIndex);
	recInsertRearrange(parentIndex);
}


/* Implementation notes: 
* ----------------------
* Removes the largest integer from the array ,which is the 
* one at the very begenning and returns it. After removal of 
* the element the heap is rearranged to make sure that 
* the arrangement of values is maintained in descending order.
* The maintainance of order of queue is managed by rearrangeAfterRemoval() 
* function.
* The algorithms says to remove the top most element from the queue
* and replace it with the last element/integer
* once done then trickle down the least value element placed at the top to
* the correct position.
*/
template <typename ElemType>

ElemType PQueue<ElemType>::dequeueMin(){
	if(size() == 1) return (rv.removeAt(1));
	ElemType min = rv.getAt(1);
	rv.swap(1,size());
	rv.removeAt(size());
	rearrangeAfterRemoval(); 
	return min;
}

//wrapper function for rearrangeAfterRemoval
template <typename ElemType>
void PQueue<ElemType>::rearrangeAfterRemoval(){
	recRemovalRearrange(1);
}

/*
* Implementation notes
* -----------------------
* Rearranges the whole heap to maintain it in order
* after an element is removed from the heap.
*/
template <typename ElemType>
void PQueue<ElemType>::recRemovalRearrange(int begIndex){
	if(hasNoMoreChildren(begIndex)) return;
	int smallestChildIndex = smallestChild(begIndex);
	if(cmpFn(rv.getAt(smallestChildIndex), rv.getAt(begIndex)) == 1) return;
	else{
		rv.swap(smallestChildIndex, begIndex);
		recRemovalRearrange(smallestChildIndex);
	}
}

//Private helper functions for recRemovalRearrange
template <typename ElemType>
bool PQueue<ElemType>::hasNoMoreChildren(int index){
	return((index * 2) > size() || index < 1);
}

template <typename ElemType>
int PQueue<ElemType>::smallestChild(int index){
	//if an index has children then there are going to be atleast one 
	int firstChildIndex = index * 2;
	int secondChildIndex = ((firstChildIndex + 1) < size() ? firstChildIndex + 1 : -1);
	if(secondChildIndex == -1){
		return firstChildIndex;
	}else{
		return((cmpFn(rv.getAt(firstChildIndex), rv.getAt(secondChildIndex)) == -1) ? firstChildIndex : secondChildIndex);
	}
}

template <typename ElemType>
int PQueue<ElemType>::size(){
	return rv.size();
}

template <typename ElemType>
bool PQueue<ElemType>::isEmpty(){
	return size() == 0;
}


#endif
