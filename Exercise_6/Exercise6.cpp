//#include "SkipList.h"
#include "Hash.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>


std::string get_word(std::string chars)
{
	return chars;
}

int
main( int argc, char** argv )
{
	//set up filenames
	std::string input_filename, output_filename;
	if (argc == 2)
	{
		input_filename = argv[1];
		output_filename = argv[2];
	}
	else std::cout << "invalid number of arguments" << std::endl;

	//take input
	std::fstream input, output;
	input.open(input_filename);

	std::string str;
	uint32_t hash;
	std::map<uint32_t, std::string> dictionary;
	std::map<uint32_t, int> hash_counter;

	while (input >> str)
	{
		const std::string word = get_word(str);
		hash = Hash(word.c_str());
		if (hash_counter.find(hash) != hash_counter.end())
		{
			//increase counter by one
			hash_counter.find(hash)->second += 1;
		}
		else
		{
			//create object and set counter to one
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



	input.close();

	//write output
	output.open(output_filename);




	output.close();
    
    return 0;
}
