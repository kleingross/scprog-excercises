#ifndef OUTPUTBITSTREAM_H_
#define OUTPUTBITSTREAM_H_


class OutputBitStream
{
public:
    virtual             ~OutputBitStream() {}
    
    // Write 'bit_count' least significant bits of 'data' to the stream.
    virtual void        write( unsigned data, unsigned bit_count ) = 0;
};


#endif /*OUTPUTBITSTREAM_H_*/
