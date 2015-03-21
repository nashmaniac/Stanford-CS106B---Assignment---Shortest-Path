/*
* File : chart.h
* -----------------------------------------
* A chart as in real world is a chart that
* holds a collection of positions and links 
* that link the location. Chart described in 
* the Chart class is exactly that a collection
* of positions and links linking those positions
*/

#ifndef CHART_H
#define CHART_H

#include <cmath>
#include <fstream>
#include "map.h"
#include "path.h"
#include "position.h"
#include "extgraph.h"
#include "pqueuemin.h"
#include "set.h"

/*
* Type definitions 
* -------------------
* Some typedefs to increase readability of the code 
*/
typedef Set<Position*> Branch;
typedef Vector<Branch> Tree;

/* Constants
 * ----------
 * A few program-wide constants concerning the graphical display.
 */
const double CircleRadius =.05;       // The radius of a node
const int LabelFontSize = 9;          // for node name labels
const int NOT_FOUND = -1;

const string MAP_COLOR = "Gray";
const string FINAL_PATH_COLOR = "Black";
const string MST_COLOR = "Black";

class Chart{
public : 
	/*
	* Function : Constructor function for the Chart class 
	* Usage    : Chart myChart("DataFile.txt");
	* ----------------------------------------------------
	* Constructor function for the Chart class, takes in the name 
	* of data file that holds the data for nodes(Position(s)) and 
	* connections between the positions (Link(s)) along with respective 
	* cost. 
	* ****************Data File Format******************
	* Name of the image file with extension e.g. USA.bmp
	* NODES(Marks the begenning of nodes)
	* sampleNode 2.3(X coordinate) 4.2(Y coordinate)
	* ...
	* ARCS(Marks the begenning of connection between nodes)
	* sampleNodeOne sampleNodeTwo 2000(cost of the connection)
	* ...
	*/
	Chart(string dataFileName);

	/*
	* Function : Destructor function for the Chart class
	* ---------------------------------------------------
	*/
	~Chart();
	
	/*
	* Function : getPositionNameAt
	* Usage    : string samplePosName = getPositionNameAt(coords);
	* -------------------------------------------------------------
	* Checks if a position exists at the supplied coordinates, if does
	* then returns the name of the position else returns an empty string
	*/
	string getPositionNameAt(coordT posCoords);

	/*
	* Function : findShortestPathBetween
	* Usage    : findShortesPathBetween(startPositionName, endPositionName)
	* ---------------------------------------------------------------------
	* Takes in the names of the starting and the ending positions on the 
	* chart and finds the shortest path between the positions marked by 
	* highlighting the path on the chart in the display window
	*/
	void findShortestPathBetween(string startPosName, string endPosName);
	
	/*
	* Function : findMinimalSpanningTree
	* Usage    : myChart.findMinimalTree();
	* -------------------------------------------
	* Finds the minimal spanning tree in the current graph
	* by using kruskal's algorithm.
	*/
	void findMinimalSpanningTree();

private :
	Map<Position* > positions;
	Vector<Link* > links;
	ifstream infile;

	void addPositionsFromData(ifstream &infile);
	void addLinksFromData(ifstream &infile);
	void addPosition(string posName, double x, double y);
	void addLink(string startPosName, string endPosName, double cost);

	Position * getPosition(string posName);
	
	void drawFilledCircleWithLabel(coordT center, string color, string label = "");
	void drawLineBetween(coordT start, coordT end, string color = "Black");
	bool withinDistance(coordT pt1, coordT pt2, double maxDistance = CircleRadius*2);
	void colorPath(Path &path, string color);

	static int cmpPaths(Path p1, Path p2);
	static int cmpLinks(Link* l1, Link* l2);
	void recFindShortestPath(Path &currentPath, PQueue<Path> &paths, Set<string> &visited, Position * end);
	
	int getContainingBranch(Position * pos, Tree &tree);
	bool includeInTree(Position * start, Position * end,Tree &tree );
};

#endif

Chart::Chart(string dataFileName){
	infile.open(dataFileName.c_str());
	// The first line in the data file is the name of the image file 
	string imageFileName;
	infile>>imageFileName;
	SetWindowTitle("Shortest path finder/Nash Vail");
	DrawNamedPicture(imageFileName);
	// Next line says NODES which mark the beginning of the nodes 
	infile>>imageFileName;
	addPositionsFromData(infile);
	addLinksFromData(infile);
	infile.close();

};


Chart::~Chart(){
	
};

void Chart::addPosition(string posName, double x, double y){
	coordT posCoords = {x, y};
	Position* pos = new Position(posName, posCoords);
	positions.add(posName, pos);

	// Draw the position in the graphics window
	drawFilledCircleWithLabel(posCoords, MAP_COLOR, posName);
}

void Chart::addLink(string startPosName, string endPosName, double cost){
	Position * start = getPosition(startPosName);
	Position * end = getPosition(endPosName);
	
	Link* posLink = new Link(start, end, cost);
	links.add(posLink);

	// Draw the link between positions in the graphics window
	drawLineBetween(start->getCoordinates(), end->getCoordinates(), MAP_COLOR);

	start->addOriginatingLink(posLink);
	end->addOriginatingLink(posLink);

}

void Chart::addPositionsFromData(ifstream &infile){
	string posName; 
	double x,y;
	while(true){
		infile>>posName;
		if(posName == "ARCS") break;
		infile>>x;
		infile>>y;
		addPosition(posName, x, y);
	}
}

void Chart::addLinksFromData(ifstream &infile){
	string startPosName, endPosName;
	double cost;
	while(true){
		infile>>startPosName;
		infile>>endPosName;
		infile>>cost;
		if(infile.eof()) break;
		addLink(startPosName, endPosName, cost);
	}
}



Position* Chart::getPosition(string posName){
	if(positions.containsKey(posName)) return positions.getValue(posName);
	else{
		Error("No position with that name found");
		return NULL;
	}
}


string Chart::getPositionNameAt(coordT posCoords){
	Map<Position* >::Iterator posItr = positions.iterator();
	while(posItr.hasNext()){
		string posName = posItr.next();
		Position * pos = getPosition(posName);
		if(withinDistance(posCoords, pos->getCoordinates())) return posName;
	}
	return "";

}

/* Function: DrawFilledCircleWithLabel
 * Usage:  DrawFilledCircleWithLabel(center, "Green", "You are here");
 * -------------------------------------------------------------------
 * Uses facilities from extgraph to draw a circle filled with
 * color specified. The circle is centered at the given coord has the
 * specified radius.  A label is drawn to the right of the circle.
 * You can leave off the last argument if no label is desired.
 */
void Chart::drawFilledCircleWithLabel(coordT center, string color, string label){
	MovePen(center.x + CircleRadius, center.y);
	SetPenColor(color);
	StartFilledRegion(1.0);
	DrawArc(CircleRadius, 0, 360);
	EndFilledRegion();
	if (!label.empty()) {
		MovePen(center.x + CircleRadius, center.y);
		SetFont("Helvetica");
		SetPointSize(LabelFontSize);
		DrawTextString(label);
	}
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */
void Chart::drawLineBetween(coordT start, coordT end, string color)
{
	SetPenColor(color);
	MovePen(start.x, start.y);
	DrawLine(end.x - start.x, end.y - start.y);
}

/* Function: WithinDistance
 * Usage:  if (WithinDistance(click, pt))...
 * -----------------------------------------
 * Returns true if the Cartesian distance between the two coordinates
 * is <= the specified distance, false otherwise. If not specified,
 * the distance is assumed to be size of the node diameter on screen.
 */
bool Chart::withinDistance(coordT pt1, coordT pt2, double maxDistance){
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double distance = sqrt(dx*dx + dy*dy);
	return (distance <= maxDistance);
}


// Acts as wrapper function for the recFindShortestPath function
void Chart::findShortestPathBetween(string startPosName, string endPosName){
	Position * start = getPosition(startPosName);
	Path path(start);
	PQueue<Path> paths(cmpPaths);
	paths.enqueue(path);
	Set<string> visitedPosNames;
	Position * end = getPosition(endPosName);

	recFindShortestPath(path, paths, visitedPosNames, end);
}

void Chart::recFindShortestPath(Path &currentPath, PQueue<Path> &paths, Set<string> &visited, Position * end){
	Position * currentPos = currentPath.getEndPosition();
	if(currentPos == end){
		colorPath(currentPath, FINAL_PATH_COLOR);
		return;
	}
	visited.add(currentPos->getName());
	Vector<Link *> * neighborLinks = currentPos->getOriginatingLinks();
	for(int i = 0; i < neighborLinks->size(); i++){
		Position * neighbor = neighborLinks->getAt(i)->getOtherEnd(currentPos);
		if(!visited.contains(neighbor->getName())){
			currentPath.addLinkToPath(neighborLinks->getAt(i));
			paths.enqueue(currentPath);
			currentPath.popLinkFromPath();
		}
	}

	recFindShortestPath(paths.dequeueMin(), paths, visited, end);
	
}

int Chart::cmpPaths(Path p1, Path p2){
	if(p1.getTotalPathCost() < p2.getTotalPathCost()) return -1;
	else if(p1.getTotalPathCost() > p2.getTotalPathCost()) return 1;
	else return 0;
}

int Chart::cmpLinks(Link *l1, Link *l2){
	if(l1->getCost() > l2->getCost()) return 1;
	else if(l1->getCost() < l2->getCost()) return -1;
	else return 0;
}

void Chart::colorPath(Path &path, string color){
	for(int i = 0 ; i < path.lengthInLinks(); i++){
		Position * start = path.getAt(i)->getStart();
		Position * end = path.getAt(i)->getEnd();
		drawLineBetween(start->getCoordinates(), end->getCoordinates(), color);
		drawFilledCircleWithLabel(start->getCoordinates(), color, start->getName());
		drawFilledCircleWithLabel(end->getCoordinates(), color, end->getName());
		Pause(0.15);
	}
}

void Chart::findMinimalSpanningTree(){
	// Refer typedefs defined
	PQueue<Link*> chartLinks(cmpLinks);
	for(int i = 0 ; i < links.size(); i++)
		chartLinks.enqueue(links[i]);
	
	Tree minimalSpanTree;
	while(!chartLinks.isEmpty()){
		Link * currentLink = chartLinks.dequeueMin();
		Position * start = currentLink->getStart();
		Position * end = currentLink->getEnd();
		
		if(includeInTree(start, end, minimalSpanTree)){
			Pause(0.01);
			drawLineBetween(start->getCoordinates(), end->getCoordinates(), MST_COLOR);
			drawFilledCircleWithLabel(start->getCoordinates(), MST_COLOR, start->getName());
			drawFilledCircleWithLabel(end->getCoordinates(), MST_COLOR, end->getName());
		}
	}
}

bool Chart::includeInTree(Position * start, Position * end, Tree &minimalSpanTree){
	int brnchCntngStart = getContainingBranch(start, minimalSpanTree);
	int brnchCntngEnd = getContainingBranch(end, minimalSpanTree);
		
	if(brnchCntngStart != brnchCntngEnd && (brnchCntngStart != NOT_FOUND && brnchCntngEnd != NOT_FOUND)){
		minimalSpanTree[brnchCntngStart].unionWith(minimalSpanTree[brnchCntngEnd]);
		minimalSpanTree.removeAt(brnchCntngEnd);
		return true;
	}else if(brnchCntngStart == NOT_FOUND && brnchCntngEnd == NOT_FOUND){
		Branch newBranch;
		newBranch.add(start);
		newBranch.add(end);
		minimalSpanTree.add(newBranch);
		return true;
	}else if (brnchCntngStart == NOT_FOUND || brnchCntngEnd == NOT_FOUND){
		int validBranch = (brnchCntngStart != NOT_FOUND) ? brnchCntngStart : brnchCntngEnd;
		minimalSpanTree[validBranch].add(start);
		minimalSpanTree[validBranch].add(end);
		return true;
	}

	return false;
}

int Chart::getContainingBranch(Position * pos, Tree &minimalSpanTree ){
	for(int i = 0 ; i < minimalSpanTree.size() ; i++)
		if(minimalSpanTree[i].contains(pos)) return i;
	return NOT_FOUND;
}