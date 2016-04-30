#ifndef FILEINPUTBITSTREAM_H_
#define FILEINPUTBITSTREAM_H_


#include "InputBitStream.h"


class FileInputBitStream:
    public InputBitStream
{
public:
                        FileInputBitStream( const char* file_name );
                        ~FileInputBitStream();
            
    virtual unsigned    read( unsigned bit_count, unsigned* data );
};


#endif /*FILEINPUTBITSTREAM_H_*/
