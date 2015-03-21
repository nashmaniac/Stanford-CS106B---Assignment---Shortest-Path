#include <iostream>
#include "simpio.h"
#include "chart.h"

/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
	coordT where;
	WaitForMouseDown();
	WaitForMouseUp();
	where.x = GetMouseX();
	where.y = GetMouseY();
	return where;
}

string GetPositionName(Chart &ch){
	while(true){
		coordT coords = GetMouseClick();
		string posName = ch.getPositionNameAt(coords);
		if(posName != "") return posName;
		cout<<"Nothing here, click on a name of location"<<endl;
	}
}


int main(){
	InitGraphics();
	Chart myChart("USA.txt");

	cout<<"Choose a starting position by clicking on the map"<<endl;
	string startPosName = GetPositionName(myChart);
	cout<<startPosName<<" chosen."<<endl;
	cout<<"Choose an ending location"<<endl;
	string endPosName = GetPositionName(myChart);
	cout<<endPosName<<" chosen."<<endl;
	myChart.findShortestPathBetween(startPosName, endPosName);

	return 0;
}