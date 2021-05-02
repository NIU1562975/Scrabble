//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>



void Board::llegeixEffects(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);

	int n_lines = 0;
	string line;

	//Contar lineas del txt
	while (getline(fitxer, line))
		n_lines++;

	for (int i = 0; i < n_lines; i++)
	{
		int f, c;
		string x;
		ScoreEffect effect;

		fitxer >> f >> c >> x;
		if (x == "DL")
			effect = DL;
		else if(x == "TL")
			effect = TL;
		else if (x == "DW")
			effect = DW;
		else if (x == "TW")
			effect = DW;
		else if (x == "NO_EFFECT")
			effect = NO_EFFECT;

		m_cells[f][c].setScoreEffect(effect);
	}

	fitxer.close();
}




