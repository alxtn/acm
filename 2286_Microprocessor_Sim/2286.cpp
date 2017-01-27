#include <iostream>

#define MEM_SIZE 256
#define WORD_LEN 4
#define WORD_MASK 0xF
enum instructions{ LD, ST, SWP, ADD, INC, DEC, BZ, BR, STP };

using namespace std;

void convertMem(char *memory);
void dumpMem(char *memory);
class Word{
public:
	Word() : data(0) {}
	char read() {return data & WORD_MASK;}
	void write(char val){ data = val & WORD_MASK; }
	void clear() { data = 0; }
	Word& operator++(){++data; return *this;}
	Word& operator--(){--data; return *this;}
	Word& operator+=(char val){data += val; return *this; }
private:
	char data;
};

class CPU{
public:
	CPU(char *memory) : memory(memory), pc(0){}
	void reset(){ A.clear(); B.clear(); pc = 0;}
	void run();
private:
	Word A,B;
	char *memory, pc;
};

int main(){
	char *memory = (char*)malloc((MEM_SIZE + 1) * sizeof(char));
	CPU cpu(memory);
	cin.getline(memory, MEM_SIZE + 1);
	convertMem(memory);
	while(memory[0] != STP){
		cpu.reset();
		cpu.run();
		dumpMem(memory);
		cin.getline(memory, MEM_SIZE + 1);
		convertMem(memory);
	}
}

void convertMem(char *memory){

	for( int i = 0; i < MEM_SIZE; i++){
		if(memory[i] <= '9' && memory[i] >= '0'){
			memory[i] -= '0';
		}
		else if(memory[i] >= 'A' && memory[i] <= 'F'){
			memory[i] -= 'A' - 10;
		} else {
			cout << "MEMORY ERROR" << endl;
			exit(1);
		}
	}
}

void dumpMem(char *memory){

	for( int i = 0; i < MEM_SIZE; i++){
		if(memory[i] >= 0 && memory[i] <= 9)
			memory[i] += '0';
		else if(memory[i] >= 10 && memory[i] <= 15)
			memory[i] += 'A' - 10;
		else{
			cout << "BAD MEMORY VALUE: " << (int)memory[i] << endl;
			exit(1);
		}
		cout << memory[i];
	}
	cout << endl;
}

unsigned char buildAddr(char *memory, char loc){
	char low, high;
	high = memory[loc];
	low = memory[++loc];
	return ((high & WORD_MASK) << WORD_LEN) | (low & WORD_MASK);
}




void CPU::run(){
	char ins, sum;
	unsigned char addr;
	Word tmp;
	while(1){
		ins = memory[pc];
		++pc;
		
		switch(ins){
			
		case(LD):
			addr = buildAddr(memory, pc);
			pc += 2;
			A.write(memory[addr]);
			break;
		case(ST):
			addr = buildAddr(memory, pc);
			pc += 2;
			memory[addr] = A.read();
			break;
		case(SWP):
			tmp = A;
			A = B;
			B = tmp;
			break;
		case(ADD):
			sum = A.read() + B.read();
			A.write(sum & WORD_MASK);
			B.write((sum >> WORD_LEN ) & WORD_MASK);
			break;
		case(INC):
			++A;
			break;
		case(DEC):
			--A;
			break;
		case(BZ):
			if(!A.read()){
				addr = buildAddr(memory, pc);
				pc = addr;
			} else {
				pc += 2;
			}
			break;
		case(BR):
			addr = buildAddr(memory, pc);
			pc = addr;
			break;
		case(STP):
			return;
		default:
			cout << "INSTRUCTION ERROR" << endl;
			exit(1);
		}
	}
}
