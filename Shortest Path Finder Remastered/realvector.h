/*
* File : realvector.h
* ---------------------
* Provides the interface for the Real Vector class 
* which sits on top of the standard stanford Vector class
* exported by the vector.h header.
* 
* Implementation notes (Difference between 'actualindex' and 'realindex')
* -----------------------------------------------------------------------
* Since the realvector is a helper class for the PQueue class whose implementation
* requires a vector class in which the counting of elements starts from 1 rather than 0
* here "0 is the actualindex" and "1 is the realindex". In more simple words
* actualindex = realindex-1;
*/

#ifndef REAL_VECTOR_H
#define REAL_VECTOR_H
#include "vector.h"
#include "genlib.h"

template <typename ElemType>
class RealVector{
public :
	/*
	* Method : RealVector();
				 ~RealVector();
	* ------------------------------
	* Constructor and destructor function 
	* for RealVector class, they do nothing 
	*/
	RealVector();
	~RealVector();
	/* 
	* Method : add(ElemType)
	* Usage  : rv.add(ElemType)
	* ---------------------------
	* Inserts the passed in value to 
	* the RealVector at appropriate position
	*/
	void add(ElemType value);
	/*
	* Method : size();
	* Usage  : int size = rv.size();
	* --------------------------------
	* Returns the size of the current vector
	* i.e the number of elements present in 
	* the vector
	*/
	int size();
	/*
	* Method : swap(realindex, realindex) 
	* Usage  : rv.swap(realindex1 , realindex2);
	* --------------------------------------------
	* Swaps the elements present at the respective positions 
	* as passed in the parameter. 
	* The passed in position to the function are real indices 
	* rather than actual
	*/
	void swap(int realindex1, int realindex2);
	/*
	* Method : getAt(int realIndex)
	* Usage  : rv.getAt(2)
	* ---------------------------------
	* Returns the element present at the real index of 
	* 'realindex' that is passed as the function 
	* parameter.
	*/
	ElemType getAt(int realindex);
	/* 
	* Method : removeAt(int realindex)
	* Usage  : rv.removeAt(3);
	* -----------------------------------
	* Removes the element from the vector at the real postion 
	* of realindex . The elements are shifted accordingly to take up
	* the space of the removed element
	*/
	ElemType removeAt(int realindex);


private:
	Vector<ElemType> v;
	int ActualIndex(int realindex);
};

template <typename ElemType>
RealVector<ElemType>::RealVector(){
}

template <typename ElemType>
RealVector<ElemType>::~RealVector(){
}

template <typename ElemType>
void RealVector<ElemType>::add(ElemType value){
	v.add(value);
}

template <typename ElemType>
int RealVector<ElemType>::size(){
	return (v.size());
}

template <typename ElemType>
void RealVector<ElemType>::swap(int realindex1, int realindex2){
	ElemType temp = v[ActualIndex(realindex1)];
	v[ActualIndex(realindex1)] = v[ActualIndex(realindex2)];
	v[ActualIndex(realindex2)] = temp;
}

template <typename ElemType>
ElemType RealVector<ElemType>::getAt(int realindex){
	return(v[ActualIndex(realindex)]);
}

template <typename ElemType>
ElemType RealVector<ElemType>::removeAt(int realindex){
	ElemType value = v[ActualIndex(realindex)];
	v.removeAt(ActualIndex(realindex));
	return value;
}

template <typename ElemType>
int RealVector<ElemType>::ActualIndex(int realindex){
	return(realindex-1);
}
#endif