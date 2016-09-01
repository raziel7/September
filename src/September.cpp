#include "Lists.h"
#include "Trees.h"
#include "Templates.h"
#include <string>

using namespace Listing;
using namespace Treeing;
using namespace Templating;

int main()
{
	int size = 16;

//	int* array = makeArray(size);
	int* array = new int[size];
	array[0] = 5;
	array[1] = 2;
	array[2] = 16;
	array[3] = 3;
	array[4] = 4;
	array[5] = 5;
	array[6] = 6;
	array[7] = 7;
	array[8] = 15;
	array[9] = 25;
	array[10] = 1;
	array[11] = 35;
	array[12] = 7;
	array[13] = 13;
	array[14] = 14;
	array[15] = 11;

	for(int i=0;i<size;i++)
		cout << array[i] << " ";

	mergeSort(array, size);
	cout << "\n--------------------\n";

	for(int i=0;i<size;i++)
		cout << array[i] << " ";

	return 0;
}
