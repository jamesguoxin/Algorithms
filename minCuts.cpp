#include <iostream>
#include <vector>
#include <string>

class Tools {
	public:
		std::vector<std::vector<int>> readTxt(std::string path) {
			std::vector<std::vector<int>> result;
			std::vector<int> vline;
			std::fstream file(path);

			while(std::getline(file, str)) {
				vline = parseLine(str);
				result.push_back(vline);
			}
			return result;
		}

		std::vector<int> parseLine(std::string line) {
			std::vector<int> result;
			std::string integer;
			int tmp;
			size_t index;
			for (size_t i = 0; i < line.size(); i++) {
				if (line[i] == ' ' || i == line.size()) {
                                      number = line.substr(index, i - index);
				      index = i + 1;
				      tmp = atoi(number.c_str());
				      result.push_back(tmp);
				}
			}
			return result;
		}
};

int main(int argc, const char * argv[]) {
	return 0;
}
