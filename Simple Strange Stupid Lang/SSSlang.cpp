#include "SSSlang.h"

void SSSlang::open(std::string path) {
	std::ifstream input;
	input.open(path, std::ios::in);
	std::string buffer = "";

	code.clear();

	while (std::getline(input, buffer)) {
		interpretLine(buffer);
	}
	input.close();
}

void SSSlang::run() {
	init();
	for(int at = 0; at < code.size(); at++) {
		if (code.at(at).cmd == "home") {
			setHome(code.at(at).num.at(0), at);
		}
	}

	while (runAt < code.size()) {
		runLine(code.at(runAt));
		runAt++;
	}
}

void SSSlang::runLine(const CodeData& data) {
	if (data.cmd == "set") {
		setMemory(data.num.at(0), data.num.at(1));
	}
	else if (data.cmd == "get") {
		setMemory(data.num.at(1), getMemory(getMemory(data.num.at(0))));
	}
	else if (data.cmd == "print") {
		int start = data.num.at(0);

		for (int at = 0; at < INT_MAX; at++) {
			int& tempMem = getMemory(start + at);
			if (tempMem == 0) {
				break;
			}

			std::cout << static_cast<char>(tempMem);
		}
	}
	else if (data.cmd == "out") {
		std::cout << static_cast<char>(getMemory(data.num.at(0)));
	}
	else if (data.cmd == "add") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));
		setMemory(data.num.at(2), a + b);
	}
	else if (data.cmd == "mul") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));
		setMemory(data.num.at(2), a * b);
	}
	else if (data.cmd == "div") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));
		setMemory(data.num.at(2), a / b);
	}
	else if (data.cmd == "sub") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));
		setMemory(data.num.at(2), a - b);
	}
	else if (data.cmd == "goto") {
		runAt = getHome(data.num.at(0));
	}
	else if (data.cmd == "equal") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));
		
		if (a != b) {
			runAt += 1;
		}
	}
	else if (data.cmd == "abig") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));

		if (a <= b) {
			runAt += 1;
		}
	}
	else if (data.cmd == "bbig") {
		int& a = getMemory(data.num.at(0));
		int& b = getMemory(data.num.at(1));

		if (a >= b) {
			runAt += 1;
		}
	}
}

void SSSlang::init() {
	memory.clear();
	runAt = 0;
}

void SSSlang::checkMem(int memAt) {
	while (memory.size() < memAt + 1) {
		memory.push_back(0);
	}
}

void SSSlang::setMemory(int at, int data) {
	checkMem(at);
	memory.at(at) = data;
}

int& SSSlang::getMemory(int at) {
	checkMem(at);
	return memory.at(at);
}

void SSSlang::checkHome(int at) {
	while (home.size() < at + 1) {
		home.push_back(0);
	}
}

void SSSlang::setHome(int at, int line) {
	checkHome(at);
	home.at(at) = line;
}

int SSSlang::getHome(int at) {
	checkHome(at);
	return home.at(at);
}

void SSSlang::addToData(CodeData& data, std::string& buffer, int& dataAt) {
	if (buffer.size() != 0) {
		if (dataAt == 0) {
			data.cmd = buffer;
		}
		else {
			data.num.push_back(std::stoi(buffer));
		}
		buffer = "";
		dataAt++;
	}
}

void SSSlang::interpretLine(std::string line) {
	int dataAt = 0;
	std::string buffer = "";
	CodeData temp;

	for (int at = 0; at < line.size(); at++) {
		if (line.at(at) == ' ') {
			addToData(temp, buffer, dataAt);
		}
		else {
			if (line.at(at) == '/') {
				break;
			}

			if (line.at(at) != '\t') {
				buffer += line.at(at);
			}
		}
	}

	addToData(temp, buffer, dataAt);

	if (dataAt != 0) {
		code.push_back(temp);
	}
}
