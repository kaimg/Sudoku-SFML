#pragma once
#include <iostream>
bool isTue = false;
void isTrue()
{
	
	int t = 0;
	/*int o = 0;bool ssf = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(sudoku[i][j] != 0) { o++; }
			if (o == 81) { ssf = true; }
		}
	}*/
	for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (solsudoku[i][j] == sudoku[i][j]) { t++; }
				{if (t == 81) { isTue = true; }}
			}
		}
}
