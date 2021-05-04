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
	BoardPosition pos;

	if (m_cells[row][col].isEmpty() && row < 15 && col < 15)
	{
		m_cells[row][col].setEmpty(false);
		m_cells[row][col].setTileLetter(tile.getLetter());
		m_cells[row][col].setTileScore(tile.getScore());
		pos.setCol(col);
		pos.setRow(row);
		currentWord.push_back(pos);
		return PositionResult(VALID_POSITION);
	}
	else if (m_cells[row][col].isEmpty() && (row > 14 || col > 14)) 
		return PositionResult(1);
	else
		return PositionResult(2);
}
bool Board::checkDictionary()
{
	string paraula;
	int sizeVector = currentWord.size();
	bool trobat = false;
		
	paraula.resize(sizeVector);

	for (int i = 0; i < sizeVector; i++)
	{
		int row = currentWord[i].getRow();
		int col = currentWord[i].getCol();

		char c = m_cells[row][col].getTileLetter();

		paraula.append(i, c);
	}

	return m_dictionary.check(paraula);
}


CurrentWordResult Board::checkCurrentWord(int& points)
{
	int alineacio = 0;

	if(m_cells[(BOARD_COLS_AND_ROWS - 1) / 2][(BOARD_COLS_AND_ROWS - 1) / 2].isEmpty() == true)
	{
		return CurrentWordResult(3);
	}
	alineacio = comprovaAlineacio();

	if (alineacio==0)
	{
		return CurrentWordResult(1);
	}
	bool consecutives = false;
	consecutives = Consecutivas(alineacio);
	if (!consecutives)
	{
		return CurrentWordResult(1);
	}
}

int Board::comprovaAlineacio(){
	bool alineatH = true;
	bool alineatV = true;
	int i = 1;
	int x = 0;
	int y = 0;
	y = currentWord[0].getCol();
	x = currentWord[0].getRow();
	while ( i < (currentWord.size()) && (alineatH != false || alineatV != false) ){

		if (y != currentWord[i].getCol())
		{
			alineatV = false;

		}
		if (x != currentWord[i].getRow())
		{
			alineatH = false;

		}
		i++;

	}
	if (alineatH = true)
	{
		return HORITZONTAL; //Significa alineació Horitzontal
	}
	else if (alineatV = true)
	{
		return VERTICAL; //Significa alineació Vertical
	} else {
		return NO_ALINEADES; //Significa que no estan alineades
	}
}

bool Board::Consecutivas(const int& alineacio){
	vector<int> p;
	bool consecutiu = true;
	switch (alineacio)
	{
	case HORITZONTAL:
		int y = 0;
		p.resize(currentWord.size());
		for (int i = 0; i < currentWord.size(); i++)
		{
			p[i] = currentWord[i].getCol();
		}
		sort(p.begin(), p.end());

		for (int i = 0; i < currentWord.size(); i++)
		{
			currentWord[i].setCol(p[i]);
		}
		int j = 1;
		int y=0;
		y=currentWord[currentWord.size()-1].getCol() - currentWord[0].getCol();
		while (j >= y && !consecutiu)
		{
			if (m_cells[currentWord[0].getRow()][currentWord[j].getCol()].isEmpty() != false)
			{
				consecutiu = false;
			}

			y = currentWord[j].getCol();
			j++;
		}
		break;
	case VERTICAL:
		int x = 0;
		p.resize(currentWord.size());
		for (int i = 0; i < currentWord.size(); i++)
		{
			p[i] = currentWord[i].getRow();
		}
		sort(p.begin(), p.end());

		for (int i = 0; i < currentWord.size(); i++)
		{
			currentWord[i].setRow(p[i]);
		}
		int j = 1;
		int y=0;
		y=currentWord[currentWord.size()-1].getCol() - currentWord[0].getCol();
		while (j >= y && !consecutiu)
		{
			if (m_cells[currentWord[0].getRow()][currentWord[j].getCol()].isEmpty() != false)
			{
				consecutiu = false;
			}

			y = currentWord[j].getCol();
			j++;
		}

		break;
	}		
	return consecutiu;
}


void Board::sendCurrentWordToBoard()
{
	int vectorSize = currentWord.size();
	for (int i = 0; i < vectorSize; i++)
	{
		int col = currentWord[i].getCol();
		int row = currentWord[i].getRow();

		m_cells[row][col].setTilePlayed(true);
	}
	currentWord.resize(0);
}

void Board::removeCurrentWord()
{
	int vectorSize = currentWord.size();
	for (int i = 0; i < vectorSize; i++)
	{
		int col = currentWord[i].getCol();
		int row = currentWord[i].getRow();

		m_cells[row][col].setEmpty(true);
		m_cells[row][col].setTilePlayed(false);
		m_cells[row][col].setTileLetter(' ');
		m_cells[row][col].setTileScore(0);
	}
	currentWord.resize(0);
}

void Board::llegeixEffects()
{
	ifstream fitxer;
	fitxer.open("data/Configuration/board.txt");

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

		m_cells[f][c].setScoreEffect(ScoreEffect(effect));
	}

	fitxer.close();
}




