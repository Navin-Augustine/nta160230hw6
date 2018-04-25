// Navin Augustine nta160230@utdallas.edu CS3377.501

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  

  const char 		*rowTitles[] = {"0 " ,"a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0","a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  class BinaryFileHeader
  {
  public:

    uint32_t magicNumber;
    uint32_t versionNumber;
    uint64_t numRecords;
  };

  const int maxRecordStringLength = 25;
  
  class BinaryFileRecord
  {
  public:

    uint8_t strLength;
    char   stringBuffer[maxRecordStringLength];
    };

  //Initialize the Cdk screen.
  window = initscr();
  cdkscreen = initCDKScreen(window);

  // Start CDK Colors
  initCDKColor();

  //Create the matrix
   myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //Display Matrix
  drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *myInfo = new BinaryFileHeader();

  ifstream binInfile("cs3377.bin", ios::in | ios::binary);
  binInfile.read((char *) myInfo, sizeof(BinaryFileHeader));
  // Display information
  setCDKMatrixCell(myMatrix, 1, 1, myInfo->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 2, myInfo->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 3, myInfo->numRecords);
  int counter = 2;
  while(!binInfile.eof())
  {
    BinaryFileRecord *myRecord = new BinaryFileRecord();
    binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
    setCDKMatrixCell(myMatrix, counter, 1, myInfo->strLength);
    setCDKMatrixCell(myMatrix, counter, 2, myInfo->stringBuffer);
    counter++;
  }
  drawCDKMatrix(myMatrix, true);

  binInfile.close();

  /* So we can see results*/
  unsigned char x;
  cin >> x;
  // Cleanup screen
  endCDK();
}
