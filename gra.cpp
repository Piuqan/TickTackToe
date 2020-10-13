#include "pch.h"
#include <iostream>
#include "Game.h"
#include <conio.h>
#include <stdio.h>


using namespace std;
int main()
{
	StartGry();
	for (;;)
	{
		RysPlansze();
		if (stangry == G_WYSTARTOWANA)
		{
			unsigned NumerPola;
			cin >> NumerPola;
			Ruch(NumerPola);
		}
		else if (stangry == G_WYGRANA || stangry == G_REMIS)
		{
			system("pause");
			break;
		}
	}
}