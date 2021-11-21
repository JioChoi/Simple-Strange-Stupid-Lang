#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class SSSlang {
public:
	void open(std::string path);
	void run();
private:
	struct CodeData {
		std::string cmd;
		std::vector<int> num;
	};

	void interpretLine(std::string line);
	void runLine(const CodeData& data);
	void init();
	void checkMem(int memAt);
	void setMemory(int at, int data);
	int& getMemory(int at);
	void checkHome(int at);
	void setHome(int at, int line);
	int getHome(int at);

	void addToData(CodeData& data, std::string& buffer, int& dataAt);

	std::vector<CodeData> code;
	std::vector<int> memory;
	std::vector<int> home;

	int runAt;
};