/*
* File : path.h
* -------------------------------------------------------------------------------------
* A path is a collection of links,and two pointers to Position that mark the begenning 
* and the end of the path. Initially the end and the start of a path is the same position
*/


class Position;

#ifndef PATH_H
#define PATH_H

#include "link.h"


class Path{
public :
	Path();
	/*
	* Function : Constructor function for the Position class
	* ------------------------------------------------------
	* Constructor function for the position calss takes in the pointer
	* to the starting position of the Path.
	*/
	Path(Position * startingPos);

	~Path();

	/* 
	* Function : addLinkTopath
	* Usage    : samplePath.addLinkToPath(pointer to a link)
	* ------------------------------------------------------
	* Path being a simple collection of links this function 
	* adds a new link to the path.
	*/
	void addLinkToPath(Link* linkToAdd);
	
	/*
	* Function : popLinkFromPath
	* Usage    : samplePath.popLinkFromPath();
	* ----------------------------------------
	* Removes the last added link from the path
	* (Following the stack ananlogy of pop
	*/
	void popLinkFromPath();

	/*
	* Function : getTotalPathCost
	*/
	double getTotalPathCost();

	/*
	* Function : getEndPosition
	* Usage    : Position * samplePos = samplePath.getEndPosition()
	* -------------------------------------------------------------
	* Returns the extreme end of the path that marks its end.
	*/
	Position * getEndPosition();

	/*
	* Function : getLinks
	* Usage    : Vector<Link*> * linksThatMakethePathUp = smaplePath.getLinks();
	* --------------------------------------------------------------------------
	* Returns a pointer to the vector of links that make the path up.
	*/
	Vector<Link*> * getLinks();

	/*
	* Function : lengthInLinks
	* Usage    : int numLinksInPath = samplePath.lengthInLinks();
	* ----------------------------------------------------------
	* Returns the number of links that make the path up
	*/
	int lengthInLinks();

	/*
	* Forget about it this function simply breaks the abstraction of the whole class
	* if only I had access to the drawing class I could've had avoided that.
	* I could've avoided this whole color path method in the chart class as that should've been 
	* the intrinsic function of this clas rather than there 
	*/
	Link * getAt(int index);
private:
	Vector<Link*> links;
	Position * start;
	Position * end;
};

#endif

Path::Path(){};

Path::Path(Position * startingPos){
	start = startingPos;
	end = startingPos;
};
Path::~Path(){};

void Path::addLinkToPath(Link* linkToAdd){
	links.add(linkToAdd);
	end = linkToAdd->getOtherEnd(end);
}

double Path::getTotalPathCost(){
	double totalPathCost = 0;
	for(int i = 0 ;i < links.size(); i++){
		totalPathCost += links[i]->getCost();
	}
	return totalPathCost;
}

void Path::popLinkFromPath(){
	// We also need to rewire the end 
	Link* toRemove = links[links.size() - 1];
	end = toRemove->getOtherEnd(end);
	links.removeAt(links.size() - 1);
}

Position * Path::getEndPosition(){
	return end;
}

Vector<Link*> * Path::getLinks(){
	return &links;
}

int Path::lengthInLinks(){
	return links.size();
}

Link* Path::getAt(int index){
	return links[index];
}