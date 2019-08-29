#include <bits/stdc++.h>
using namespace std;

struct tag {
	unsigned long long int tag_value;
	bool valid, dirty, last_access;
	int counter; 
};

struct cache {
	unsigned long long int cache_size, params;
	int tag_bits, cache_assoc, cache_line_size, cache_lines, cache_sets, set_index_size, block_offset;
	std::vector< std::vector <tag> > cache_matrix;
};

#define MIN_RANGE 0
#define MAX_RANGE 7

int random_num()
{
	std::random_device rd;
    	std::default_random_engine seed(rd());
    	std::uniform_int_distribution<int> random_engine_block(MIN_RANGE, MAX_RANGE);
    	auto random = std::bind(random_engine_block, seed); 
	return random();
}

void initialize_cache (cache *L2, cache *L3, char *name) {
	std::fstream config;
	config.open(name, std::ios::in);

	std::string str;
	std::vector< std::vector<int> > cache_config;

	while(std::getline(config, str)) {

		std::stringstream ss(str);
		std::vector<int> tokens;

		while(ss) {
			std::string token;
			if(!std::getline(ss, token, ','))
				break;
			try {
				tokens.push_back(std::atoi(token.c_str()));
			} catch (const std::invalid_argument error) {
				error.what();
			}
		}

		cache_config.push_back(tokens);
	}

	// L2 Cache.

	L2->cache_size = cache_config[0][0] << 10;
	L2->cache_assoc = cache_config[0][1];
	L2->cache_line_size = cache_config[0][2];

	L2->block_offset = (int)log2(L2->cache_line_size);
	L2->cache_lines = L2->cache_size >> L2->block_offset;
	L2->cache_sets = L2->cache_lines >> (int)log2(L2->cache_assoc);
	L2->set_index_size = (int)log2(L2->cache_sets);
	
	std::vector<tag> temp0;

	for(auto ways = 0; ways < L2->cache_assoc; ways++) {
		tag t;
		temp0.emplace_back(t);	
	}

	for(auto i = 0; i < L2->cache_sets; i++) {
		L2->cache_matrix.emplace_back(temp0);
	}

	// L3 Cache.

        L3->cache_size = cache_config[1][0] << 10;
        L3->cache_assoc = cache_config[1][1];
        L3->cache_line_size = cache_config[1][2];

	L3->block_offset = (int)log2(L3->cache_line_size);
        L3->cache_lines = L3->cache_size >> L3->block_offset;
        L3->cache_sets = L3->cache_lines >> (int)log2(L3->cache_assoc);
	L3->set_index_size = (int)log2(L3->cache_sets);

	std::vector<tag> temp1;

	for(auto ways = 0; ways < L3->cache_assoc; ways++) {
		tag t;
		temp1.emplace_back(t);
	}

	for(auto i = 0; i < L3->cache_sets; i++) {
                L3->cache_matrix.emplace_back(temp1);
        }

	//done.
	config.close();
}

unsigned long long int get_set_index_bits(unsigned long long int x, int set_index_size, int offset) {
	int mask = 0;
	for(auto i = 0; i < set_index_size; i++) {
		mask = mask << 1;
		mask = mask ^ 1;
	}
	mask = mask << offset;
	x = x & mask;
	x = x >> offset;	
	return x;
}


void process_trace (cache *L2, cache *L3, std::vector<unsigned long long int> miss_trace) {
	
	unsigned long long int l3_tag_bits = 0, l2_tag_bits = 0, l2_set_index = 0, l3_set_index = 0;
	for(const auto& trace_item : miss_trace) {
		l2_tag_bits = trace_item >> (L2->set_index_size + L2->block_offset);
		l2_set_index = get_set_index_bits(trace_item, L2->set_index_size, L2->block_offset);
	
		l3_tag_bits = trace_item >> (L3->set_index_size + L3->block_offset);
		l3_set_index = get_set_index_bits(trace_item, L3->set_index_size, L3->block_offset);	

		bool l2_hit = false, l3_hit = false;		
		
		std::cout << l2_tag_bits << ", " << l3_tag_bits << std::endl;
		
		for(auto ways = 0; ways < L2->cache_assoc; ways++) {
			auto exist_tag = L2->cache_matrix[l2_set_index][ways].tag_value;
			if(l2_tag_bits == exist_tag) {
				l2_hit = true;
				L2->cache_matrix[l2_set_index][ways].counter++;
				L2->cache_matrix[l2_set_index][ways].last_access= true;				
				// std::cout << "L2 Cache_hit." << std::endl;
				break;		
			}	
		} 
		
		if(l2_hit == false) {
			
			// std::cout << "L2 Cache_miss." << std::endl;
 			
			// Check in L3 Cache;
			for(auto ways = 0; ways < L3->cache_assoc; ways++) {
			auto exist_tag = L3->cache_matrix[l3_set_index][ways].tag_value;
				if(l3_tag_bits == exist_tag) {
					l3_hit = true;
					L3->cache_matrix[l3_set_index][ways].counter++;
					L3->cache_matrix[l3_set_index][ways].last_access= true;					
					// std::cout << "L3 Cache_hit." << std::endl;
					break;		
				}	
			}	
			
			if(l2_hit == false && l3_hit == false) {
				
			// Need to write logic here.	






			}
		}
		// std::cout << std::endl;		
	}
}

int main (int argc, char* argv[], char* envp[]) {

	int iord = 0, type = 0;
	unsigned long long int addr = 0;
	unsigned pc = 0;
	char trace_name[30];
	std::vector<unsigned long long int> miss_trace;

	FILE* trace_reader = fopen(argv[1], "rb");

	long long int traces = std::atoi(argv[3]);
	for (auto k = 0; k < traces; k++) {
		sprintf(trace_name, "%s_%d", argv[1], k);
		FILE* trace_reader = fopen(trace_name, "rb");
		assert(trace_reader != NULL);
		while (!feof(trace_reader)) {
			fread(&iord, sizeof(int), 1, trace_reader);
    	   		fread(&type, sizeof(int), 1, trace_reader);
        		fread(&addr, sizeof(unsigned long long int), 1, trace_reader);
        		fread(&pc, sizeof(unsigned), 1, trace_reader);
        		if(type != 0) miss_trace.emplace_back(addr);
		}
		fclose(trace_reader);
		printf("Done reading the binary file %s, %d\n", trace_name, k + 1);
	}

	cache *L2 = new cache();
	cache *L3 = new cache();

	initialize_cache(L2, L3, argv[2]);
	
	process_trace(L2, L3, miss_trace);

	return 0;
}
