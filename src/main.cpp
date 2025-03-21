#include <iostream>
using namespace std;

void invalidCommand(string input) {
	cout << input << ": command not found" << std ::endl;
}

void REPL(){
	while(true){
		string input;
		cout << "$ ";
		getline(std::cin, input);
		invalidCommand(input);
	}
}

int main() {
  // Flush after every std::cout / std:cerr
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage

	REPL();
}
