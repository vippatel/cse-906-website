#include <bits/stdc++.h>
using namespace std;

#define MIN_RANGE 0
#define MAX_RANGE 18456932511
#define INVALID_TAG -99999999

std::unordered_map <unsigned long long, unsigned long long> l2tag_l3tag_mapping;
unsigned long long int block_level_lru_counter;

struct tag {
	unsigned long long int tag_value, counter; // LRU Counter.
	bool valid, dirty; 
};

struct cache {
	unsigned long long int cache_size, hits, miss; // In Bytes.
	std::string name;
	int cache_assoc, cache_line_size, cache_lines, cache_sets, set_index_size, block_offset;
	std::vector< std::vector <tag> > cache_matrix; // 2D Array of tags.
	std::unordered_map<unsigned long long int, unsigned long long int> tag_addr_mapping; // Tag to PA-address mapping.
	std::vector<unsigned long long int> lru_set_counters;
};

template <class T>
void vector_print (std::vector<T> vec) {
	for(const auto& item : vec) {
		std::cout << item << ", ";
	}
	std::cout << std::endl;
}

// For random index choosing in free ways of a set during LRU.
int random_num(int min, int max) {
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

	//done.
	config.close();

	// L2 Cache.
	L2->cache_size = cache_config[0][0] << 10;
	L2->cache_assoc = cache_config[0][1];
	L2->cache_line_size = cache_config[0][2];
	L2->name = "L2 Cache";
	L2->block_offset = (int)log2(L2->cache_line_size);
	L2->cache_lines = L2->cache_size >> L2->block_offset;
	L2->cache_sets = L2->cache_lines >> (int)log2(L2->cache_assoc);
	L2->set_index_size = (int)log2(L2->cache_sets);
	L2->hits = 0;
	L2->miss = 0;
	std::vector<tag> temp0;

	for(auto ways = 0; ways < L2->cache_assoc; ways++) {
		tag t;
		t.tag_value = INVALID_TAG;
		t.counter = INT_MIN;
		t.valid = false;
		t.dirty = false;
		temp0.emplace_back(t);	
	}

	for(auto i = 0; i < L2->cache_sets; i++) {
		L2->cache_matrix.emplace_back(temp0);
		L2->lru_set_counters.push_back(INT_MIN);
	}

	// L3 Cache.
    L3->cache_size = cache_config[1][0] << 10;
    L3->cache_assoc = cache_config[1][1];
    L3->cache_line_size = cache_config[1][2];
	L3->name = "L3 Cache";
	L3->block_offset = (int)log2(L3->cache_line_size);
    L3->cache_lines = L3->cache_size >> L3->block_offset;
    L3->cache_sets = L3->cache_lines >> (int)log2(L3->cache_assoc);
	L3->set_index_size = (int)log2(L3->cache_sets);
	L3->hits = 0;
	L3->miss = 0;
	std::vector<tag> temp1;

	for(auto ways = 0; ways < L3->cache_assoc; ways++) {
		tag t;
		t.tag_value = INVALID_TAG;
		t.counter = INT_MIN;
		t.valid = false;
		t.dirty = false;
		temp1.emplace_back(t);
	}

	for(auto i = 0; i < L3->cache_sets; i++) {
        L3->cache_matrix.emplace_back(temp1);
		L3->lru_set_counters.push_back(INT_MIN);
    }
}

// Run LRU Algorithm on LRU Counters for a CACHE SET in below function. We add the tag in L3 Cache.
unsigned long long int get_lru_cache_vic (cache *X, 
								unsigned long long int index, 
								unsigned long long int val // tag bits 
								) {

	int assoc = X->cache_assoc, min_counter = -1, pos = 0;
	for(auto j = 0; j < assoc; j++) {
		// Check who is the LRU victim in the set in terms of j.
		// Return the tag_bits of the victim and replace with value and address in tag_addr_mapping.
		// Find minimum counter and replace it. 
	if(min_counter > X->cache_matrix[index][j].counter) {
			min_counter = X->cache_matrix[index][j].counter;
			pos = j;
		}
	}
	
	unsigned long long int prev_tag_bits = X->cache_matrix[index][pos].tag_value;
	X->cache_matrix[index][pos].tag_value = val;
	X->cache_matrix[index][pos].counter = ++(X->lru_set_counters[index]);
	X->cache_matrix[index][pos].valid = true;
	X->cache_matrix[index][pos].dirty = false;
	return prev_tag_bits;
}

// Insert into Cache X, the tags which missed.
std::pair <unsigned long long int, bool> insert_into_cache (cache *X, 
					unsigned long long int index,
					unsigned long long int tag_bits
					) {

	std::vector<int> list_free_ways;					
	bool lru_flag = false;
	unsigned long long int return_tag = INVALID_TAG, addr = -1;
	
	for(auto ways = 0; ways < X->cache_assoc; ways++) {
		if(X->cache_matrix[index][ways].tag_value == INVALID_TAG) {
			X->cache_matrix[index][ways].valid = false; // invalid.
			list_free_ways.push_back(ways);
		} else 
			X->cache_matrix[index][ways].valid = true; // Valid tag exists.
	}
	
	if(!list_free_ways.empty()) { 
		
		// We got a free way. So we insert here.
		int index = random_num(0, list_free_ways.size() - 1); // Choose a free way randomly.
		int free_way = list_free_ways[index];
		X->cache_matrix[index][free_way].tag_value = tag_bits; // Fill the cache Set.
		X->cache_matrix[index][free_way].counter = ++(X->lru_set_counters[index]);
		X->cache_matrix[index][free_way].valid = true;
		X->cache_matrix[index][free_way].dirty = false;
		lru_flag = false;
		std::cout << "[Free Way] " << X->name << ", " << free_way << std::endl; 
		return std::make_pair(false, 0);
		
	} else {
		
		// LRU Cache replacement [Cache Eviction] in Cache Index Set.
		lru_flag = true;
		return_tag = get_lru_cache_vic(X, index, tag_bits);
		auto pair = std::make_pair(return_tag, lru_flag);
		return pair;
	}
						
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
		
		// Helps in invalidating L2.
		l2tag_l3tag_mapping[l3_tag_bits] = l2_tag_bits;
		
		for(auto ways = 0; ways < L2->cache_assoc; ways++) {
			auto exist_tag = L2->cache_matrix[l2_set_index][ways].tag_value;
			if(l2_tag_bits == exist_tag) {
				l2_hit = true;
				hit_way = ways;
				L2->cache_matrix[l2_set_index][ways].counter = ++(L2->lru_set_counters[l2_set_index]);
				L2->hits++;
				std::cout << "L2 HIT : " << l2_set_index << ", " << hit_way << ", " << l2_tag_bits << std::endl;
				break;		
			}	
		} 
			
		if(l2_hit == false) {
			
			std::cout << "L2 MISS -> SET : " << l2_set_index << ", TAG : " << l2_tag_bits << std::endl;
			L2->miss++;
			// Check in L3 Cache;
			for(auto ways = 0; ways < L3->cache_assoc; ways++) {
			auto exist_tag = L3->cache_matrix[l3_set_index][ways].tag_value;
				if(l3_tag_bits == exist_tag) {
					l3_hit = true;
					hit_way = ways;
					L3->cache_matrix[l3_set_index][ways].counter = ++(L3->lru_set_counters[l3_set_index]);                  					
					L3->hits++;
					std::cout << "L3 HIT : " << l3_set_index << ", " << hit_way << ", " << l3_tag_bits << std::endl;
					
					// Replace Cache-block [LRU] or insert in L2.
					auto dump_pair = insert_into_cache(L2, l2_set_index, l2_tag_bits);
					break;		
				}	
			}	
			
			if(l2_hit == false && l3_hit == false) {
				
				std::cout << "L3 MISS -> SET : " << l3_set_index << ", TAG : " << l3_tag_bits << std::endl;
				L3->miss++;
			
				insert_into_cache(L3, l3_set_index, l3_tag_bits);
				insert_into_cache(L2, l2_set_index, l2_tag_bits);
			}
			// No L2 Invalidation.
		}
	}
}

void print_cache(cache *L2) {
	for(auto set = 0; set < L2->cache_sets; set++) {
		for(auto ways = 0; ways < L2->cache_assoc; ways++) {
			std::cout << L2->cache_matrix[set][ways].counter << ", ";
		}
		std::cout << std::endl;
	}
}

int main (int argc, char* argv[], char* envp[]) {

	unsigned int iord = 0, type = 0, pc = 0;
	unsigned long long int addr = 0;
	char trace_file_name[50];
	std::vector<unsigned long long int> miss_trace;

	long long int traces = std::atoi(argv[3]);
	for (auto file_number = 0; file_number < traces; file_number++) {
		sprintf(trace_file_name, "%s_%d", argv[1], file_number);
		FILE* trace_reader = fopen(trace_file_name, "rb");
		assert(trace_reader != NULL);
		while (!feof(trace_reader)) {
			fread(&iord, sizeof(unsigned int), 1, trace_reader);
    	   		fread(&type, sizeof(unsigned int), 1, trace_reader);
        		fread(&addr, sizeof(unsigned long long int), 1, trace_reader);
        		fread(&pc, sizeof(unsigned int), 1, trace_reader);
        		if(type != 0) miss_trace.emplace_back(addr);
		}
		fclose(trace_reader);
	}

	cache *L2 = new cache();
	cache *L3 = new cache();

	initialize_cache(L2, L3, argv[2]);
	process_trace(L2, L3, miss_trace);

	std::cout << "[INFO Case-2] L2 Hits : " << L2->hits << ", L2 Miss : " << L2->miss  
			<< ", L3 Hits : " << L3->hits << ", L3 Miss : " << L3->miss << std::endl;

	return 0;
}
