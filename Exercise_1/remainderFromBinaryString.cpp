#include "remainderFromBinaryString.h"

//calculateRemainder from string of binary digits
int remainderFromBinaryString( string binaryString ) {
  int remainder = 0;
  for( std::string::size_type i = 0; i < binaryString.size(); ++i) {
    remainder = updateRemainder( remainder, binaryString[i]);
  }
  return remainder;
}

//update Remainder from previous remainder and next binary number
int updateRemainder( const int oldRemainder, const char c ) {
  //
  int newDigit = 0;
  if( c == '0' ) newDigit = 0;
  else if(c == '1') newDigit = 1;
  else cout << "wrong char" << endl;

  int remainder = (2*oldRemainder) % 3;
  remainder = (remainder + newDigit) % 3;
  return remainder;
}
