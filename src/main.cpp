#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

const char *PATH = getenv("PATH");

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

string checkPATH(string command) {
  stringstream ss(PATH);
  string dir;
  char delimiter = (fs::path::preferred_separator == '/') ? ':' : ';';  // assigns delimiter based on OS

  while (getline(ss, dir, delimiter)) {
    fs::path full_path = fs::path(dir) / command;

    if constexpr (fs::path::preferred_separator == '\\') {         // checks for .exe files in Windows OS
      if (fs::exists(full_path) || fs::exists(full_path.string() + ".exe")) {
        return full_path.string();
      }
    } else {
      if (fs::exists(full_path) && fs::is_regular_file(full_path)) {
        return full_path.string();
      }
    }
  }

  return "";
}

void commandType(string input) {
  vector<string> input_split = split(input);
  vector<string> command_list = {"type", "echo", "exit"};

  bool shell_builtin = false;

  string command = input_split[1];
  for (string it : command_list) {
    if (command == it) {
		shell_builtin = true;
    }
  }

  if (!shell_builtin) {
    string file_path = checkPATH(command);
	if(!file_path.empty()){
		cout << command << " is " << file_path << endl;
		return;
	}
  }

  if (shell_builtin) {
    cout << command << " is a shell builtin" << endl;
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
