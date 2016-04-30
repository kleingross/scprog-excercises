#ifndef INPUTBITSTREAM_H_
#define INPUTBITSTREAM_H_


class InputBitStream
{
public:
    virtual             ~InputBitStream() {}
    
    // Read 'bit_count' bits from the stream and store them in 'bit_count' least significant bits of 'data'.
    // Returns the number of bits, which have been read.
    // Example:
    // unsigned data = 0;
    // unsigned read_bit_count = stream->read( bit_count, &data );
    virtual unsigned    read( unsigned bit_count, unsigned* data ) = 0;
};


#endif /*INPUTBITSTREAM_H_*/
