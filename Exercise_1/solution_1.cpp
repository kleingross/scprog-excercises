#include <fstream>
#include <string>
#include "remainderFromBinaryString.h"

using namespace std;


//write output.txt with remainder of division by 3 from input.txt
int main( void ){
  // open input file
  fstream input;
  input.open( "input.txt", ios::in );
  string line;

  // open output file
  fstream output;
  output.open( "output.txt", ios::out );

  // calculate remainder for each line and write to output.txt
  while( getline( input, line ) ) {
    int remainder = remainderFromBinaryString ( line );
    output << remainder << endl;
  }

  input.close();
  output.close();
  return 0;
}
