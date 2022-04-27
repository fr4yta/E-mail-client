#include "Files.h"

Files::Files(string fileName) : fileName(fileName) {}

bool Files::ifFileExists() {
	fstream file;
	file.open(this->fileName.c_str(), ios::in | ios::_Nocreate);
	if (file.is_open()) {
		file.close();
		return true;
	}
	else {
		return false;
	}
}

void Files::reWriteContentFile(const string& content) {
	ofstream outfile;
	outfile.open(this->fileName);
	if (outfile.is_open()) {
		outfile << content << endl;
		outfile.close();
	}
}