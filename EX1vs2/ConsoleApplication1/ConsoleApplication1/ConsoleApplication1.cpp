// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RPS.h"

int main()
{
	RPS rps;
	rps.Parser(1);
	rps.Parser(2);
	rps.PrintBoard();
	return 0;
}

