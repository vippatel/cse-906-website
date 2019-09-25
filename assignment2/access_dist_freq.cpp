#include <bits/stdc++.h>
using namespace std;

std::unordered_map<unsigned long long int, std::vector<unsigned long long int> > total_addr_mapping; 
std::map<unsigned long long int, std::vector<unsigned long long int> > freq_map;

template <typename T>
void print_vec (std::vector<T> vec) {
    for (const auto &item  : vec) {
        std::cout << item  << ", ";
    }
}

int main (int argc, char *argv[], char *envp[]) {
	std::fstream fs("addr_trace.txt", std::fstream::in);
	unsigned long long int block_addr = 0, counter = 0, addr_access = 0;
	
	while(!fs.eof()) {
		std::string str;
		std::getline(fs, str);
		addr_access = std::strtoll(str.c_str(), nullptr, 10);
		
		// Block Offset.
		block_addr = addr_access >> 6;
		total_addr_mapping[block_addr].emplace_back(counter);
		counter++;
	}

	for(const auto &vecs : total_addr_mapping) {
		// std::cout << "\nBlock Id : " << vecs.first << std::endl;
		// print_vec(vecs.second);
		std::vector<unsigned long long int> trace_map = vecs.second;
		for (auto i = 1; i < trace_map.size(); i++) {
			unsigned long long int access_dist = trace_map[i] - trace_map[i - 1];
			freq_map[access_dist].emplace_back(vecs.first);
		} 
	}
	
	for(const auto &freqs : freq_map) {
		std::cout << freqs.first << " " << freqs.second.size() << std::endl;
	}

	return 0;
}






























