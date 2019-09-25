 
#include <bits/stdc++.h>
using namespace std;

std::unordered_map<int, std::set<unsigned long long int> > thread_to_block;
std::unordered_map<unsigned long long int, std::set<unsigned long long int> > block_to_thread;
std::vector<unsigned long long int> block_counts;

template <typename T>
void print_vec (std::vector<T> vec) {
	int counter = 0;
    for (const auto &item  : vec) {
		std::cout << "[Threads count : " << counter << "] Block counts : " << item  << std::endl;
		counter++;
    }
}

int main (int argc, char *argv[], char *envp[]) {

    // input -> thread_id addr_trace 
    
	std::fstream fs(argv[1], std::fstream::in);
	
	int thread_id = 0;
    unsigned long long int block_addr = 0, counter = 0, addr_access = 0;
    std::string str, buffer;
	
	while(std::getline(fs, str)) {

		std::stringstream ss(str);
        
		ss >> buffer;
        thread_id = std::stoi(buffer.c_str(), nullptr, 10);
		buffer = "";
		ss >> buffer;
		addr_access = std::strtoull(buffer.c_str(), nullptr, 10);
		
		// Block Offset. 6
		block_addr = addr_access >> 6;
		thread_to_block[thread_id].insert(block_addr);
        block_to_thread[block_addr].insert(thread_id);
	}

	for(auto i = 0; i < 9; i++) block_counts.push_back(0); // initialize counters. 

    for(const auto &vecs : block_to_thread) {
    	// std::cout << "Block ID " << vecs.first << ", #thread_count " << vecs.second.size() << std::endl;
		block_counts[vecs.second.size()]++;
	}

	print_vec(block_counts);

	return 0;
}
