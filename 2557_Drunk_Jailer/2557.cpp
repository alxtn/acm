#include <iostream>
#include <algorithm>

using namespace std;

int drunkJailer(int numCells){

	bool cells[numCells];
	for( int i = 0; i < numCells; i++)
		cells[i] = true; // Unlock all cells

	for( int i = 2; i < numCells + 1; i++){ // Each pass
		for( int j = 1; j < numCells + 1; j++){ // Check each cell
			if( !(j % i) )
				cells[j-1] = !cells[j-1]; // toggle if chosen
		}
	}
	// return the number of open cells
	return count(cells, cells + numCells, true);
}



int main(){

	int numInputs;
	cin >> numInputs;

	// Process each input
	for( int i = 0; i < numInputs; i++){
		int numCells;
		cin >> numCells;
		cout << drunkJailer(numCells) << endl;
	}

}
