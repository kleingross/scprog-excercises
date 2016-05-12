#include "LZW.h"
#include "InputBitStream.h"
#include "OutputBitStream.h"
#include <fstream>

using namespace std;

int main( void ){
  unsigned code_length = 8;

  //Encode
  fstream original, encoded;
  original.open('original.txt');
  encoded.open('encoded.dat');

  InputBitStream input_enc;
  OutPutBitStream output_enc;


  Encode(input_enc, output_enc, code_length);

  original.close();
  encoded.close();


  //Decode
  fstream encoded, decoded;
  encoded.open('encoded.dat');
  decoded.open('decoded.txt');

  InputBitStream input_dec;
  OutputBitStream output_dec;


  Decode(input_dec, output_dec, code_length);

  encoded.close();
  decoded.close();

  return 0;
}
