/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Tomislav Nikolov
* @idnumber 45211
* @task 1
* @compiler VC
*
*/
#include <iostream>
#include "sTack.h"
#include "PolishMan.h"

int main(int argc, char* argv[])
{
	PolishMan Frank;
	if (argc < 3)
	{ 
		std::cout << "Error!" << std::endl;
	}
	else
	{
		Frank.FillTable(argv[2]);
		Frank.Algorhytm(argv[1]);
	}
	return 0;
}