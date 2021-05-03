//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>



PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos)
{
	int col = boardPos.getCol();
	int row = boardPos.getRow();
	CellPosition cell;

	if (m_cells[row][col].isEmpty() && row < 15 && col < 15)
	{
		m_cells[row][col].setEmpty(false);
		m_cells[row][col].setTileLetter(tile.getLetter());
		m_cells[row][col].setTileScore(tile.getScore());
		cell.col = col;
		cell.row = row;
		paraulaMuntada.push_back(cell);
		lletresDeParaula.push_back(tile);
		return PositionResult(0);
	}
	else if (m_cells[row][col].isEmpty() && (row > 14 || col > 14)) 
		return PositionResult(1);
	else
		return PositionResult(2);
}


CurrentWordResult Board::checkCurrentWord(int& points)
{
	if(m_cells[7][7].isEmpty() == true)
	{

	}

	return CurrentWordResult();
}

void Board::sendCurrentWordToBoard()
{
	
}


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
			effect = TW;
		else if (x == "NO_EFFECT")
			effect = NO_EFFECT;

		m_cells[f][c].setScoreEffect(effect);
	}

	fitxer.close();
}




