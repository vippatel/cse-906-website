#include <bits/stdc++.h>
using namespace std;

std::unordered_map<long long int, std::vector<long long int> > total_addr_mapping;

int main (int argc, char *argv[], char *envp[]) {
	std::fstream fs("addr_trace.txt", std::fstream::in);
	unsigned long long int block_addr = 0, counter = 0, addr_access = 0;
	
	while(!fs.eof()) {
		std::string str;
		std::getline(fs, str);
		addr_access = std::strtoll(str.c_str(), nullptr, 10);
		
		block_addr = addr_access - (addr_access % 64);
		total_addr_mapping[block_addr].emplace_back(counter);
		counter++;
	}
	
	return 0;
}

// Store the sequence of access points corresponding to each memory block ever accessed. 
