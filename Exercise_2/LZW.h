#ifndef LZW_H_
#define LZW_H_


class InputBitStream;
class OutputBitStream;


void Encode( InputBitStream* input, OutputBitStream* output, unsigned code_length );
void Decode( InputBitStream* input, OutputBitStream* output, unsigned code_length );


#endif /*LZW_H_*/
