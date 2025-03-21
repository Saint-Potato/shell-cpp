#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string trim(string str) {
  while (!str.empty() && isspace(str.front()))
    str.erase(0, 1); // Remove leading spaces
  while (!str.empty() && isspace(str.back()))
    str.pop_back(); // Remove trailing spaces
  return str;
}

vector<string> split(const string &str) {
  vector<string> words;
  istringstream iss(str);
  string word;

  while (iss >> word) { // Extract words separated by spaces
    words.push_back(word);
  }

  return words;
}

void commandInvalid(string input) {
  cout << input << ": command not found" << std ::endl;
}

void commandEcho(string input) {
  cout << input.substr(5, input.length() - 5) << endl;
}

void commandType(string input) {
  vector<string> input_split = split(input);
  vector<string> command_list = {"type", "echo", "exit"};

  bool valid_command = false;

  for (string command : command_list) {
    if (input_split[1] == command) {
      valid_command = true;
    }
  }

  if (valid_command) {
    cout << input_split[1] << " is a shell builtin" << endl;
  } else {
    cout << input.substr(5, input.length() - 5) << ": not found" << endl;
  }
}

int inputParser(string input) {
  input = trim(input);
  vector<string> input_split = split(input);
  if (input_split[0] == "exit") {
    if (input_split[1] == "0" && input_split.size() == 2) {
      return 0;
    } else {
      return -1;
    }
  } else if (input_split[0] == "echo") {
    return 1;
  } else if (input_split[0] == "type") {
    return 2;
  } else {
    return -1;
  }
}

bool processCommand(int command, string input) {
  switch (command) {
  case -1:
    commandInvalid(input);
    return true;
  case 0:
    return false; // exit command
  case 1:
    commandEcho(input);
    return true;
  case 2:
    commandType(input);
    return true;

  default:
    commandInvalid(input);
    return true;
  }
}

void REPL() {
  while (true) {
    string input;
    cout << "$ ";
    getline(std::cin, input);
    int command = inputParser(input);
    ;
    bool response = processCommand(command, input);
    if (!response) {
      break;
    }
  }
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage

  REPL();

  return 0;
}
