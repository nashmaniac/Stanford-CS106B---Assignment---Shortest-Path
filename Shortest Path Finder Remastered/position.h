/*
* File : position.h
* --------------------------------
* A Position is an entity that is an elementary 
* part of the chart, that makes it up a position on 
* the chart has a name and a unique location on the chart.
* A Position object holds the name of the position, it's position
* that is to say its cartesian coordinates on the chart. 
*/

#ifndef POSITION_H
#define POSITION_H

#include "vector.h"
#include "set.h"

/*
* A simple structure that holds the x and y coordinates
* of the position
*/

struct coordT{
	double x, y;
};

class Position{
public:
	/*
	* Function : Constructor function for the Position calss
	* Usage    : Position samplePos(name of the position, coordinates of the position)
	* ---------------------------------------------------------------------------------
	*/
	Position(string posName, coordT posCoordinates);

	/*
	* Function : getCoordinates
	* Usage    : coordT samplePosCoords = smaplePos.getCoordinates();
	* ---------------------------------------------------------------
	*/
	coordT getCoordinates();

	/*
	* Function : addOriginatingLink
	* Usage    : samplePos.addOriginatingLink(a pointer to Link object)
	* ------------------------------------------------------------------
	* A Position object holds a collection of links that start or end 
	* at the position, the function is used to add a link to a collection of 
	* such links of the position.
	*/
	void addOriginatingLink(Link* origLink);

	/*
	* Function : getName
	* Usage    : string samplePosName = samplePos.getName();
	* ------------------------------------------------------
	*/
	string getName();

	/*
	* Function : getOriginatingLinks
	* Usage    : Vector<Link*> * neighboringLinks = samplePos.getOriginatingLinks();
	* -------------------------------------------------------------------------------
	*/
	Vector<Link*> * getOriginatingLinks();

private :
	string name;
	coordT coordinates;
	Vector<Link*> originatingLinks; // Links that originate from the current Position
};

#endif

Position::Position(string posName, coordT posCoordinates){
	name = posName;
	coordinates = posCoordinates;
}

void Position::addOriginatingLink(Link* origLink){
	originatingLinks.add(origLink);
}

coordT Position::getCoordinates(){
	return coordinates;
}

string Position::getName(){
	return name;
}

Vector<Link *> * Position::getOriginatingLinks(){
	return &originatingLinks;
}
