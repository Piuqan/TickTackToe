#pragma once
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <string>
using namespace std;
//typy wyliczeniowe
 enum STANGRY { G_NIEWYSTARTOWANA, G_WYSTARTOWANA, G_WYGRANA, G_REMIS };
 enum ZNAK    { Z_KOLKO, Z_KRZYZYK };
 enum POLE   { pole_puste,
			   pole_kółko, 
			   pole_krzyżyk };
 const int WYGRANA[][3][2] =   {{{0,0},{0,1},{0,2}}, //mozliwości na wygraną
							   { {1,0},{1,1},{1,2}},
							   { {2,0},{2,1},{2,2}},
							   { {0,0},{1,0},{2,0}},
							   { {0,1},{1,1},{2,1}},
							   { {0,2},{1,2},{2,2}},
							   { {0,0},{1,1},{2,2}},
							   { {2,0},{1,1},{0,2}} };


POLE plansza[3][3] = {{pole_puste, pole_puste, pole_puste},
					  {pole_puste, pole_puste, pole_puste},
					  {pole_puste, pole_puste, pole_puste}};
STANGRY stangry = G_NIEWYSTARTOWANA;
ZNAK gracz;
//funkcje programu
bool RysPlansze()
{
	system("cls");
	cout << "		Gra w kolko i krzyzyk		" << endl;
	cout << "-----------------------------------" << endl;
	cout << "                       -----             " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "                       |";
		for (int j = 0; j < 3; j++)
		{
			if (plansza[i][j] == pole_puste)
				cout << i * 3 + j + 1;
			else
			{
				enum ZNAK { Z_KOLKO = 'O', Z_KRZYZYK = 'X' };
				cout << static_cast<char>(plansza[i][j]);
			}

		}
		cout << "|" << endl;
	}
	cout << "                       -----" << endl;
	cout << endl;
	switch (stangry)
	{
	case G_WYSTARTOWANA:
		cout << "Podaj numer pola w ktorym chcesz postawic " << (gracz == Z_KOLKO ? "kolko" : "krzyzyk") << ": ";
		break;
	case G_WYGRANA:
		cout << "Wygral gracz stawiajacy " << (gracz == Z_KOLKO ? "kolka" : "krzyzyki") << "!";
		break;
	case G_REMIS:
		cout << "Remis!";
		break;
	}
	return true;
}
bool Ruch(unsigned uNumerPola)
{
	if (!(uNumerPola >= 1 && uNumerPola <= 9)) return false;
	unsigned X = (uNumerPola - 1) / 3;
	unsigned Y = (uNumerPola - 1) % 3;
	if (plansza[X][Y] == pole_puste)
	{
		if (gracz == Z_KOLKO)
		{
			plansza[X][Y] = pole_kółko;
		}
		else
			plansza[X][Y] = pole_krzyżyk;
	}
	//sprawdzenie wygranej
	POLE Pole, ZgodnePole;
	unsigned LiczbaZgodnychPol;
	for (int i = 0; i < 8; i++)
	{
		Pole = ZgodnePole = pole_puste;
		LiczbaZgodnychPol = 0;
		for (int j = 0; j < 3; j++)  //tu jest coś źle
		{
			Pole = plansza[WYGRANA[i][j][0]][WYGRANA[i][j][1]];
			if (Pole != ZgodnePole)
			{
				ZgodnePole = Pole;
				LiczbaZgodnychPol = 1;
			}
			else
			{
				++LiczbaZgodnychPol;
			}
		}
		if (LiczbaZgodnychPol == 3 && ZgodnePole != pole_puste)
		{
			stangry = G_WYGRANA;
			return true;
		}
	}
	unsigned LiczbaZapelnionychPol = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (plansza[i][j] != pole_puste)
				LiczbaZapelnionychPol++;
	if (LiczbaZapelnionychPol == 9)
	{
		stangry = G_REMIS;
		return true;
	}
	gracz = (gracz == Z_KOLKO ? Z_KRZYZYK : Z_KOLKO);
	return true;
}
bool StartGry()
{
	srand((static_cast<unsigned>(time(NULL))));
	unsigned los = rand() % 2 + 0;
	cout << los;
    if (los == 1)
		gracz = Z_KOLKO;
	else
		gracz = Z_KRZYZYK;
	stangry = G_WYSTARTOWANA;
	return true;
}