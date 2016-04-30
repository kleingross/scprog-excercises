#ifndef FILEOUTPUTBITSTREAM_H_
#define FILEOUTPUTBITSTREAM_H_


#include "OutputBitStream.h"


class FileOutputBitStream:
    public OutputBitStream
{
public:
                        FileOutputBitStream( const char* file_name );
                        ~FileOutputBitStream();
            
    virtual void        write( unsigned data, unsigned bit_count );
};


#endif /*FILEOUTPUTBITSTREAM_H_*/
