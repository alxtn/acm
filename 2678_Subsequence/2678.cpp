#include <iostream>

using namespace std;

int calcMinSeq(int N, int S, int *seq){
	int sum;
	for(int len = 1; len <= N; len++){
		for(int i = 0; i < N - len + 1; i++){
			sum = 0;
			for(int j = 0; j < len; j++){
				sum += seq[i+j];
			}
			if( sum >= S )
				return len;
		}
	}
	return N;
}


int main(){

	int N,S,min, *seq;
	cin >> N >> S;
	while(!cin.eof()){
		seq = (int*) malloc(sizeof(int) * N);
		for( int i = 0; i < N; i++)
			cin >> seq[i];
		min = calcMinSeq(N, S, seq);
		cout << min << endl;
		free(seq);
		cin >> N >> S;
	}
}
