// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RPS.h"

int main()
{
	RPS rps;
	rps.Parser(0);
	rps.Parser(1);
	rps.PrintBoard();
	return 0;
}

