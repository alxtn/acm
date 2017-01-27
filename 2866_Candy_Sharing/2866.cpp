#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

void executeRound( int *students, int size ){
	int curr, next;
	curr = students[0] / 2;
	for( int i = 1; i < size; i++ ){
		next = students[i] / 2;
		students[i] = students[i] / 2 + curr;
		curr = next;
	}
	students[0] = students[0] / 2 + curr;

	for( int i = 0; i < size; i++ ){
		if( students[i] % 2 )
			++(students[i]);
	}
}

pair<int, int> candySim( int *students, int size ){

	int rounds = 0;
	while(count(students, students + size, students[0]) != size){
		executeRound( students, size );
		++rounds;
	}
	return pair<int,int>(rounds, students[0]);
}

int main(){

	int numStudents;
	int *students = nullptr;
	cin >> numStudents;
	while( numStudents ){

		if( students )
			free(students);
		students = (int*)malloc(numStudents * sizeof(int));
		for( int i = 0; i < numStudents; i++){
			cin >> students[i];
		}

		pair<int,int> ans = candySim(students, numStudents);
		cout << ans.first << " " << ans.second << endl;
		cin >> numStudents;
	}
}
