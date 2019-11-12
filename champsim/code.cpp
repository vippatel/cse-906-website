#include <bits/stdc++.h>
using namespace std;

int main (void) 
{
	std::fstream trace_file, procc_file;

	trace_file.open("trace_list_multicore", std::fstream::in);
	procc_file.open("processor_list_file", std::fstream::in);

	std::string trace, procc;
	std::vector<std::string> processors, traces;
	
	while(std::getline(procc_file, procc)) {
		processors.emplace_back(procc);					
	}
	
	while(std::getline(trace_file, trace)) {
		traces.emplace_back(trace);	
	}

	for(const auto trace : traces) {
		for(const auto processor : processors) {
			std::cout << "./run_4core.sh " << processor << " " << trace << "\n";					
		}	
	}

	return 0;
}

