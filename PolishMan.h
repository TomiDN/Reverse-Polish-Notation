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
#ifndef __POLISHMAN_HEADER_INCLUDED_
#define __POLISHMAN_HEADER_INCLUDED_

#include <iostream>
#include <fstream>
#include "sTack.h"

class PolishMan
{
public:
	PolishMan();
	~PolishMan();
	void Algorhytm(char*);
	char ValidateOp(char);
	double OperationResult(double, double, char);
	void FillTable(char*);
	void PostBuild(char*);
private:
	sTack<double> nums;
	sTack<char> ops;
	char table[64][3];
	char post[128];
	std::ifstream infile;
	bool Error;
	int i;
	int j;
	int c;
};

PolishMan::PolishMan()
{
	i = 0;
	j = 0;
	c = 0; 
	Error = false; 
	if (infile.is_open())
		infile.close();
}

PolishMan::~PolishMan()
{
	i = 0;
	j = 0;
	c = 0;
	Error = false;
	if (infile.is_open())
		infile.close();
}

void PolishMan::Algorhytm(char * input)
{
	if (infile.is_open())
		infile.close();
	infile.open(input);
	if (!infile.is_open())
	{
		std::cout << "Error!" << std::endl;
		return;
	}
	double num = 0.0;
	char s;
	int newops = 0;
	int opcnt = 0;
	int numcnt = 0;
	bool processed = false;
	char buff[16];
	while (!infile.eof())
	{
		infile >> s;
		if ('0' <= s&&s <= '9')
		{
			infile.seekg(-1, std::ios::cur);
			infile >> num;
			nums.Push(num);
			newops++;
			numcnt++;
		}
		else if (ValidateOp(s) != '0')
		{
			if (newops == 1)
			{
				if (!processed)
				{
					double n1 = nums.Top();
					sprintf_s(buff, "%g ", n1);
					PostBuild(buff);
					newops = 0;
				}
				else
				{
					double n2 = nums.Top();
					nums.Pop();
					double n1 = nums.Top();
					nums.Pop();
					char op = ops.Top();
					ops.Pop();
					sprintf_s(buff, "%g %c ", n2, op);
					PostBuild(buff);
					nums.Push(OperationResult(n1, n2, op));
					if (Error)
						return;
					newops = 0;
					i = 0;
				}
			}
			ops.Push(s);
			opcnt++; 
			processed = false;
		}
		if (newops == 2)
		{
			double n2 = nums.Top();
			nums.Pop();
			double n1 = nums.Top();
			nums.Pop();
			char op = ops.Top();
			ops.Pop();
			sprintf_s(buff, "%g %g %c ", n1, n2, op);
			PostBuild(buff);
			nums.Push(OperationResult(n1, n2, op));
			if (Error)
				return;
			newops = 0;
			i = 0;
			processed = true;
		}
	}
	infile.close();
	if (newops == 1)
	{
		sprintf_s(buff, "%g ", nums.Top());
		PostBuild(buff);
	}
	if (nums.Size() != ops.Size() + 1)
	{
		std::cout << "Error!" << std::endl;
		return;
	}
	while (!ops.Empty())
	{
		double n2 = nums.Top();
		nums.Pop();
		double n1 = nums.Top();
		nums.Pop();
		char op = ops.Top();
		ops.Pop();
		sprintf_s(buff, "%c ", op);
		PostBuild(buff);
		nums.Push(OperationResult(n1, n2, op));
		if (Error)
			return;
		i = 0;
	}
	if (opcnt >= numcnt)
	{
		std::cout << "Error!" << std::endl;
		return;
	}
	std::cout << post << std::endl << nums.Top() << std::endl;
	nums.Pop();

}

char PolishMan::ValidateOp(char op)
{
	for (i = 0; i < c; i++)
	{
		if (table[i][0] == op)
			return table[i][1];
	}
	return '0';
}

/*The cases where the calculation is differed 
by the associativity of the operator are commented
so you can see that I've managed to realize it*/
double PolishMan::OperationResult(double m, double n, char op)
{
	switch (ValidateOp(op))
	{
	case '+':
		m += n;
		break;
	case '-':
		/*if (table[i][2])
			m -= n;
		else
			n -= m;*/
		m -= n;
		break;
	case '*':
		m *= n;
		break;
	case '/':
		if (m != 0 && n != 0)
		{
			/*if (table[i][2])
				m /= n;
			else
				n /= m;*/
			m /= n;
		}
		else
		{
			std::cout << "Error!" << std::endl;
			Error = true;
		}
		break;
	}
	return m;
}

void PolishMan::FillTable(char* input)
{
	if (infile.is_open())
		infile.close();
	infile.open(input);
	if (!infile.is_open())
	{
		std::cout << "Error!" << std::endl;
		Error = true;
	}
	while (!infile.eof())
	{
		infile >> table[c][0];
		if (table[c][0] == '\0')            //I added this check because I was having problems with an additional spin of 
			break;							//the cycle while reading from my file like it's end was detected a bit later
		infile >> table[c][1];
		infile >> table[c][2];
		c++;
	}
	infile.close();
}

void PolishMan::PostBuild(char* buff)
{
	for (int k = 0; buff[k] != '\0'; k++)
		post[j++] = buff[k];
}

#endif
