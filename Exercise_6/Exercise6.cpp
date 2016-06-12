//#include "SkipList.h"
#include "Hash.h"
#include "SkipList.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

struct hash_compare
{
	bool operator() (const uint32_t hash1, const uint32_t hash2) const
	{
		return hash1 < hash2;
	}
};


typedef SkipList<uint32_t, std::string, hash_compare> dict;
typedef SkipList<uint32_t, int, hash_compare> count;
//typedef std::map < uint32_t, std::string > dict;
//typedef std::map<uint32_t, int> count;



std::string get_word(std::ifstream& input)
{
	char c = 0;
	std::string word;
	while (input.good())
	{
		input.get(c);
		if (c < -1 || c >= 255) break; //exclude non ASCII
		if (isalpha(c) || c == 39 && !(word.length() == 0)) word = word + c;
		else break;
	}
	if (word.length() == 0) word = get_word(input);
	std::transform(word.begin(), word.end(), word.begin(), ::tolower); //transform to lower case only
	return word;
}

int
main( int argc, char** argv )
{
	//set up filenames
	std::string input_filename, output_filename;

	if (argc == 3)
	{
		input_filename = argv[1];
		output_filename = argv[2];
	}
	else std::cout << "invalid number of arguments" << std::endl;

	//take input
	std::ifstream input;
	std::ofstream output;

	input.open(input_filename);

	//set up variables
	std::string str;
	uint32_t hash = 0;
	dict dictionary;
	count hash_counter;


	//process words
	if (input.is_open())
	{
		while (input.good())
		{
			if (input.eof()) break;
			std::string word = get_word(input);
			hash = Hash(word.c_str());

			if(hash_counter.find(hash)) //with SkipList
			//if(hash_counter.find(hash) != hash_counter.end()) //with map
			{
				//increase counter by one
				hash_counter.find(hash)->second += 1;
			}
			else
			{
				//create object and set counter to 1
				std::pair<uint32_t, std::string> hash_word_pair;
				hash_word_pair.first = hash;
				hash_word_pair.second = word;
				dictionary.insert(hash_word_pair);

				std::pair<uint32_t, int> hash_counter_pair;
				hash_counter_pair.first = hash;
				hash_counter_pair.second = 1;
				hash_counter.insert(hash_counter_pair);
			}
		}
	}
	input.close();

	//write output
	output.open(output_filename);
	if (output.is_open())
	{
		//process data 100x
		for (int i = 0; i < 100; ++i)
		{
			uint32_t current_highest_hash;
			int current_highest_counter = 0;
			//iterate through hash_counter if hash_counter not empty
			if (hash_counter.begin() == hash_counter.end()) break;
			for (count::iterator it = hash_counter.begin(); it != hash_counter.end(); ++it)
			{
				//extract highest count
				if (it->second > current_highest_counter)
				{
					current_highest_hash = it->first;
					current_highest_counter = it->second;
				}
				else if (it->second == current_highest_counter)
				{
					//check for lexigraphic order and if necessary update current highest
					uint32_t new_hash = it->first;
					std::string new_word = dictionary.find(new_hash)->second;
					std::string current_word = dictionary.find(current_highest_hash)->second;
					int new_word_size = new_word.length();
					int current_word_size = current_word.length();
					const char* new_word_cstring = new_word.c_str();
					const char* current_word_cstring = current_word.c_str();
					if (std::lexicographical_compare(new_word_cstring, new_word_cstring + new_word_size,
						current_word_cstring, current_word_cstring + current_word_size))
					{
						current_highest_hash = it->first;
						current_highest_counter = it->second;
					}
				}
			}

			//write line to file
			std::string output_string;
			output_string.clear();
			output_string.append(std::to_string(current_highest_counter) + " ");
			output_string.append(dictionary.find(current_highest_hash)->second);
			output << output_string << std::endl;
			hash_counter.erase(current_highest_hash);
		}

		//write line to file
		std::string output_string;
	}
	output.close();
    
	std::cout << "done" << std::endl;

    return 0;
}
