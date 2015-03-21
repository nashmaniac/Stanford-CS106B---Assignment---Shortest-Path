/*
* File : link.h
* -------------------------
* A Link defines a link between two positions
* on the chart and stores the cost two traverse 
* from one link to the other link. Though one can 
* see a link with a starting and an ending position
* The link doesn't has a start or an end it just 
* connects two Positions together and choice of start and 
* end is completely arbitrary.
*/

class Position;


#ifndef LINK_H
#define LINK_H

class Link{
public :
	/*
	* Function : Constructor function for the Link Class
	* Usage    : Link sampleLink(start, end)
	* ---------------------------------------------------
	* The constructor of the Link class takes in the pointers
	* to two locations as parameters one which acts like the 
	* begenning and one that acts as end.
	*/
	Link(Position* startPos, Position* endPos, double linkCost);

	/*
	* Function : Destructor function for the Link class
	* --------------------------------------------------
	*/
	~Link();

	/*
	* Function : getCost
	* Usage    : double totalPathCost = sampleLink.getCost();
	* -------------------------------------------------------
	* Returns the cost of the link that is to say the cost of 
	* traversing from the start position to the end position of 
	* the link.
	*/
	double getCost();

	/*
	* Function : getOtherEnd
	* Usage    : Position * samplePos = sampleLink.getOtherEnd(pointer to a position)
	* -------------------------------------------------------------------------------
	* Supplied one end of the link the function returns the other end of the link.
	* e.g. If supplied in start the function would return the end and vice versa
	*/
	Position * getOtherEnd(Position* pos);

	/*
	* Function : getStart
	* Usage    : Position* samplePos = sampleLink.getStart();
	* ------------------------------------------------------
	* As previously said about no distinction between the start 
	* and end of the link the function is used to retrieve the 
	* end (Position) first added to the class, so as to say the position that 
	* is first passed in the constructor function of the class during its initialization 
	*/
	Position * getStart();
	
	/*
	* Function : getEnd
	* Usage    : Position* samplePos = sampleLink.getStart();
	* -------------------------------------------------------
	* Retrieves the end that is added after the start to the Class.
	*/
	Position * getEnd();
private:
	Position* start;
	Position * end;
	double cost;
};


#endif

Link::Link(Position* startPos, Position* endPos, double linkCost){
	start = startPos;
	end = endPos;
	cost = linkCost;
};

Link::~Link(){};

double Link::getCost(){
	return cost;
}

Position * Link::getOtherEnd(Position * pos){
	if(pos == start) return end;
	else return start;
}


Position * Link::getStart(){
	return start;
}

Position * Link::getEnd(){
	return end;
}

