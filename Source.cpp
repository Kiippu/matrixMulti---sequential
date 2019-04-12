#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
/// user classes
#include "GlobalTimer.h"
#include "Matrix.h"

// global man and min value for auto fill matrix 
ULONG MAX_VALUE = 100;
ULONG MIN_VALUE = 1;
// global row and col length
ULONG ROW_LENGTH = 100;
ULONG COL_LENGTH = 100;

int main() 
{
	// timer for matrix measurements
	GlobalTimer masterDelta;
	masterDelta.addStartTime(std::string("Program runTime"), TIME_MEASURMENT::Second);
	
	// matrcies for multiplication
	Matrix matrix_0;
	Matrix matrix_1;
	Matrix matrix_final;

	// get row and col counts
	do
	{
		matrix_0.askForRowCol();
		matrix_1.askForRowCol();

		if (matrix_0.getColCount() != matrix_1.getRowCount())
			std::cout << "\n<<ERROR>> matrix_0 row count does not equal matrix_1 column count <<ERROR>>\n  Please reenter valid values again.\n" << std::endl;

	} while (matrix_0.getColCount() != matrix_1.getRowCount());

	// set matrix values automatically or manuelly
	char userAnswers;
	// auto fill matricies
	do
	{
		std::cout << "\nWould you like to auto fill matricies with random values? (y/n)" << std::endl;
		std::cin >> userAnswers;
	} while (userAnswers != 'y' && userAnswers != 'n');
	// auto fill == true
	if (userAnswers == 'y')
	{
		ULONG max;
		std::cout << "\nEnter maximum value: ";
		std::cin >> max;
		ULONG min;
		std::cout << "\nEnter minimum value: ";
		std::cin >> min;

		// time managment enum will need to be nano if smalled then 100x100 with max vals of 100.
		masterDelta.addStartTime("Populating both matricies", TIME_MEASURMENT::Milli);
		masterDelta.addStartTime("Populating matrix_0", TIME_MEASURMENT::Milli);
		matrix_0.autoFillMatrix(min, max);
		masterDelta.addFinishTime("Populating matrix_0");

		masterDelta.addStartTime("Populating matrix_1", TIME_MEASURMENT::Milli);
		matrix_1.autoFillMatrix(min, max);
		masterDelta.addFinishTime("Populating matrix_1");
		masterDelta.addFinishTime("Populating both matricies");
	}
	// auto fill == false
	else if(userAnswers == 'n')
	{
		// manuelly add each value to matrix..
		/// matrix 0
		for (size_t x = 0; x < matrix_0.getRowCount(); x++)
		{
			for (size_t y = 0; y < matrix_0.getColCount(); y++)
			{
				ULONG a;
				std::cout << "\nMatrix_0 - Enter value for index : [" << std::to_string(x) << ", " << std::to_string(y) << "]" << std::endl;
				std::cin >> a;
				matrix_0.addValue(x,y,a);
			}
		}
		/// matrix 1
		for (size_t x = 0; x < matrix_1.getRowCount(); x++)
		{
			for (size_t y = 0; y < matrix_1.getColCount(); y++)
			{
				ULONG a;
				std::cout << "\nMatrix_1 - Enter value for index : [" << std::to_string(x) << ", " << std::to_string(y) << "]" << std::endl;
				std::cin >> a;
				matrix_1.addValue(x, y, a);
			}
		}
		// last pause until multiplication occurs
		char temp;
		std::cout << "Press \"ENTER\" key to begin" << std::endl;
		std::cin >> temp;
	}
	// populate final matrix with value 0
	for (size_t i = 0; i < matrix_0.getRowCount(); i++)
	{
		matrix_final.getValue().push_back(std::vector<ULONG>());
		auto count = matrix_1.getColCount();
		for (size_t k = 0; k < matrix_1.getColCount(); k++)
		{
			matrix_final.getValue()[i].push_back(0);
		}
	}
	// register Timer
	masterDelta.addStartTime("Matrix multiplication", TIME_MEASURMENT::Milli);
	matrix_final.setMatrixMulti(matrix_0, matrix_1);

	// print final matrix
	printf("\n\n\n");
	for (size_t i = 0; i < matrix_0.getRowCount(); i++)
	{
		matrix_final.getValue().push_back(std::vector<ULONG>());
		for (size_t k = 0; k < matrix_0.getColCount(); k++)
		{
			printf("%d ,", matrix_final.getValue()[i][k]);
		}
		printf("\n");
	}

	// register finihsed timer
	masterDelta.addFinishTime("Matrix multiplication");
	masterDelta.addFinishTime(std::string("Program runTime"));
	// print results
	masterDelta.printFinalTimeSheet();

	// pause at the end of the application
	int pausePlease;
	std::cin >> pausePlease;

	return 0;
}
