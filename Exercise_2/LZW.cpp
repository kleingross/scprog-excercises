#include "LZW.h"
#include "InputBitStream.h"
#include "OutputBitStream.h"
#include <map>

using namespace std;

void
Encode( InputBitStream* input, OutputBitStream* output, unsigned code_length )
{
  int dictsize = pow(2, code_length);
  //initialize dictionary with single characters
  map<string, int> dict;
  for  (int i = 0; i < 256; i++) {
    dict[string(1, i)] = i;
  }

  //initialize variables
  int index = 256;
  seq = input.read(); //type of seq unclear
  next = seq;
  seq_next;
  //iterate until end of file
  while ( !next.empty() ){
    next = input.read();
    seq_next = seq + next;
    if( seq_next in dict ) seq = seq_next;
    else if (seq_next not in dict) {
      output dict[seq];
      if ( index <= dictsize ) {
        //dict.insert( pair<string,int>(seq_next, index) );
        dict[seq_next] = index;
        index++;
      }
      seq = next;
    }
  }
}

void
Decode( InputBitStream* input, OutputBitStream* output, unsigned code_length )
{
  int dictsize = pow(2, code_length);
  //initialize dictionaries with single characters
  map<string, int> dict;
  for(int i = 0; i < 256; i++) {
    dict[string(1, i)] = i;
  }

  map<int, string> index_dict;
  for(int i = 0; i < 256; i++) {
    index_dict[i] = string(1, i);
  }

  //initialize variables
  int index = 256;
  seq = index_dict[input.read()];
  next = seq;
  seq_next;

  while( !next.empty() ) {
    next = index_dict[input.read()];
    seq_next = seq + next;
    if( seq_next in dict ) seq = seq_next;
    }
    else if( !seq_next in dict) {
      output seq;
      if( index <= dictsize ) {
        dict[seq_next] = index;
        index_dict[index] = seq_next;
        index++;
      }
      seq = next;
    }
  }

}
