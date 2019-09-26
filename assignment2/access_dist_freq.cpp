 
#include <bits/stdc++.h>
using namespace std;

std::unordered_map<unsigned long long int, std::vector<unsigned long long int> > total_addr_mapping; 
std::map<unsigned long long int, std::vector<unsigned long long int> > freq_map;
std::map<unsigned long long int, unsigned long long int> cfd_map;

template <typename T>
void print_vec (std::vector<T> vec) {
    for (const auto &item  : vec) {
        std::cout << item  << ", ";
    }
}

int main (int argc, char *argv[], char *envp[]) {

	// input -> thread_id addr_trace 
	
	std::fstream fs(argv[1], std::fstream::in);
	unsigned long long int block_addr = 0, counter = 0, addr_access = 0;
	int thread_id = 0;
	std::string str, buffer;
	unsigned long long int N = 0;
	
	while(std::getline(fs, str)) {

		std::stringstream ss(str);
        
		ss >> buffer;
        thread_id = std::stoi(buffer.c_str(), nullptr, 10);
		buffer = "";
		ss >> buffer;
		addr_access = std::strtoull(buffer.c_str(), nullptr, 10);
		
		// Block Offset. 6
		block_addr = addr_access >> 6;
		total_addr_mapping[block_addr].emplace_back(counter);
		counter++;
	}

	for(const auto &vecs : total_addr_mapping) {
		std::vector<unsigned long long int> trace_map = vecs.second;
		
		auto size = vecs.second.size() - 1; // Excluding first access. 
		N += size; 

		for (auto i = 1; i < trace_map.size(); i++) {
			unsigned long long int access_dist = trace_map[i] - trace_map[i - 1];
			freq_map[access_dist].emplace_back(vecs.first);
		} 

	}
	
	unsigned long long int cummulative_freq = 0;
	for(const auto &freqs : freq_map) {
		cummulative_freq += freqs.second.size();
		cfd_map[freqs.first] = cummulative_freq;
	}

	for(const auto &cfd_values : cfd_map) {
		float _N = N;
		float x = cfd_values.second;
		float F = x / _N;
		std::cout << std::setprecision(10) << cfd_values.first << " " << cfd_values.second  << " " << F << std::endl;
	}

	return 0;
}
