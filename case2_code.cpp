#include <bits/stdc++.h>
using namespace std;

#define MIN_RANGE 0
#define MAX_RANGE 18456932511

struct tag {
	unsigned long long int tag_value, counter; // LRU Counter.
	bool valid, dirty, last_access; 
};

struct cache {
	unsigned long long int cache_size; // In Bytes.
	int cache_assoc, cache_line_size, cache_lines, cache_sets, set_index_size, block_offset;
	std::vector< std::vector <tag> > cache_matrix; // 2D Array of tags.
	std::unordered_map<unsigned long long int, unsigned long long int> tag_addr_mapping; // Tag to PA-address mapping.
};

template <class T>
void vector_print (std::vector<T> vec) {
	for(const auto& item : vec) {
		std::cout << item << ", ";
	}
	std::cout << std::endl;
}

// For random index choosing in free ways of a set during LRU.
int random_num(unsigned long long int min, unsigned long long int max)
{
	std::random_device rd;
    	std::default_random_engine seed(rd());
    	std::uniform_int_distribution<unsigned long long int> random_engine_block(min, max);
    	auto random = std::bind(random_engine_block, seed); 
	return random();
}

void initialize_cache (cache *L2, cache *L3, char *config_txt) {

	// Read a CSV File and process it.
	std::fstream config;
	config.open(config_txt, std::ios::in);
	std::string str = "";
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
		t.tag_value = -999;
		t.counter = -1;
		t.valid = false;
		t.dirty = false;
		t.last_access = false;
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
		t.tag_value = -999;
		t.counter = -1;
		t.valid = false;
		t.dirty = false;
		t.last_access = false;
		temp1.emplace_back(t);
	}

	for(auto i = 0; i < L3->cache_sets; i++) {
                L3->cache_matrix.emplace_back(temp1);
     }

	//done.
	config.close();
}

// Run LRU Algorithm on LRU Counters for a CACHE SET in below function. We add the tag in L3 Cache.
unsigned long long int get_lru_cache_vic (cache *X, unsigned long long int index, unsigned long long int val) {

	int assoc = X->cache_assoc;
	for(auto j = 0; j < assoc; j++) {
	// Check who is the LRU victim in the set in terms of j.
	// Return the tag_bits of the victim and replace with value and address in tag_addr_mapping.
	
	
	
	}
	return 0xffffff;
}

// Extract the set index from the 64 bit address given.
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
	
	for(const auto& trace_item : miss_trace) {
		
		bool l2_hit = false, l3_hit = false; int hit_way = -1;	
		unsigned long long int l3_tag_bits = 0, l2_tag_bits = 0, l2_set_index = 0, l3_set_index = 0;
		std::vector<int> l2_valid_ways, l3_valid_ways;
		
		l2_tag_bits = trace_item >> (L2->set_index_size + L2->block_offset);
		l2_set_index = get_set_index_bits(trace_item, L2->set_index_size, L2->block_offset);
	
		l3_tag_bits = trace_item >> (L3->set_index_size + L3->block_offset);
		l3_set_index = get_set_index_bits(trace_item, L3->set_index_size, L3->block_offset);		
		
		L3->tag_addr_mapping[l3_tag_bits] = trace_item;
		L2->tag_addr_mapping[l2_tag_bits] = trace_item;
		
		for(auto ways = 0; ways < L2->cache_assoc; ways++) {
			auto exist_tag = L2->cache_matrix[l2_set_index][ways].tag_value;
			if(l2_tag_bits == exist_tag) {
				l2_hit = true;
				hit_way = ways;
				L2->cache_matrix[l2_set_index][ways].counter = 0;
				L2->cache_matrix[l2_set_index][ways].last_access = true; 
				
				// L2 SET LRU Counter Updation on target SET. It will run only once, when a hit occurs.		
				for(auto ways = 0; ways < L2->cache_assoc; ways++) {
					if(ways != hit_way && L2->cache_matrix[l2_set_index][ways].tag_value != -999) 
					L2->cache_matrix[l2_set_index][ways].counter++;
				}
				std::cout << "L2 HIT : " << l2_set_index << ", " << hit_way << ", " << l2_tag_bits << std::endl;
				break;		
			}	
		} 
			
		if(l2_hit == false) {
			
			std::cout << "L2 MISS -> SET : " << l2_set_index << ", TAG : " << l2_tag_bits << std::endl;
			
			// Check in L3 Cache;
			for(auto ways = 0; ways < L3->cache_assoc; ways++) {
			auto exist_tag = L3->cache_matrix[l3_set_index][ways].tag_value;
				if(l3_tag_bits == exist_tag) {
					l3_hit = true;
					hit_way = ways;
					L3->cache_matrix[l3_set_index][ways].counter++;
					L3->cache_matrix[l3_set_index][ways].last_access = true;                  					
					
					// L3 SET LRU Counter Updation on target SET. It will run only once, when a hit occurs.		
					for(auto ways = 0; ways < L3->cache_assoc; ways++) {
						if(ways != hit_way && L3->cache_matrix[l3_set_index][ways].tag_value != -999) 
						L3->cache_matrix[l3_set_index][ways].counter++;
					}
					std::cout << "L3 HIT : " << l3_set_index << ", " << hit_way << ", " << l3_tag_bits << std::endl;
					// TO-DO : LRU Replacement in L2 Cache.
					break;		
				}	
			}	
			
			if(l2_hit == false && l3_hit == false) {
				
			std::cout << "L3 MISS -> SET : " << l3_set_index << ", TAG : " << l3_tag_bits << std::endl;
			
			// L3 is non-inclusive-non-exclusive (NINE) of L2: An L3 miss fills into L3 and L2.
			// An L3 eviction does not invalidate the corresponding block in L2.

			// Find a empty/invalid way to fill first. If no way such found, use LRU replace on L3 Set. 
			// On finding a LRU candidate, replace the candidate in L2 also. 
			
			// If an invalid way is found in L3, fill it and then find the corresponding way in L2 and repeat 
			// the same at L2. 
			
				for(auto ways = 0; ways < L3->cache_assoc; ways++) {
					if(L3->cache_matrix[l3_set_index][ways].tag_value == -999) {
						L3->cache_matrix[l3_set_index][ways].valid = false; // invalid.
						l3_valid_ways.push_back(ways);
					} else 
						L3->cache_matrix[l3_set_index][ways].valid = true; // Valid tag exists.
				}
				
				for(auto ways = 0; ways < L2->cache_assoc; ways++) {
					if(L2->cache_matrix[l2_set_index][ways].tag_value == -999) {
						L2->cache_matrix[l2_set_index][ways].valid = false; // invalid.
						l2_valid_ways.push_back(ways);
					} else 
						L2->cache_matrix[l2_set_index][ways].valid = true; // Valid tag exists.
				}

				// vector_print<int> (l2_valid_ways); // Print the free ways we got.
				// vector_print<int> (l3_valid_ways); // Print the free ways we got.
				
				// Now block comming from memory. Fill L3 first and then L2.
				if(!l3_valid_ways.empty()) {
					
					int index = random_num(0, l3_valid_ways.size() - 1); // Choose a free way randomly.
					int free_way = l3_valid_ways[index];
					L3->cache_matrix[l3_set_index][free_way].tag_value = l3_tag_bits; // Fill L3 Set.
					L3->cache_matrix[l3_set_index][free_way].counter = 0;
					L3->cache_matrix[l3_set_index][free_way].valid = true;
					L3->cache_matrix[l3_set_index][free_way].dirty = false;
					L3->cache_matrix[l3_set_index][free_way].last_access = true; // A write-access is a hit.
				
				} else {
				
					// LRU Cache replacement [Cache Eviction] @L3 Set. TO DO.
					unsigned long long int l3_vic_tag_bits = get_lru_cache_vic(L3, l3_set_index, l3_tag_bits);
					// No invalidation needed here.
				}
				
				if(!l2_valid_ways.empty()) {
				
					int index = random_num(0, l2_valid_ways.size() - 1); // Choose a free way randomly.
					int free_way = l2_valid_ways[index];
					L2->cache_matrix[l2_set_index][free_way].tag_value = l2_tag_bits; // Fill L2 Set.
					L2->cache_matrix[l2_set_index][free_way].counter = 0;
					L2->cache_matrix[l2_set_index][free_way].valid = true;
					L2->cache_matrix[l2_set_index][free_way].dirty = true;
					L2->cache_matrix[l2_set_index][free_way].last_access = true; // A write-access is a hit.
					L2->tag_addr_mapping[l2_tag_bits] = trace_item;
				
				} else {
				
					// LRU Cache replacement @L2 Set. Pick an L2 Cache Victim. TO DO. 
					// What do we do to L3 in this case ?? 
				
				}
			}
		}
	}
}

void print_cache(cache *L2) {
	for(auto set = 0; set < L2->cache_sets; set++) {
		for(auto ways = 0; ways < L2->cache_assoc; ways++) {
			std::cout << L2->cache_matrix[set][ways].tag_value << ", ";
		}
		std::cout << std::endl;
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
	
	// print_cache(L2);
	// print_cache(L3);
	
	return 0;
}
