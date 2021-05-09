//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>

Board::Board()
{
	ifstream fitxer;
	fitxer.open("./data/Configuration/board.txt");

	if (fitxer.is_open())
	{
		int row, col;
		string effect;
		vector<int> fila;
		vector<int> columna;
		vector<string> efecte;

		fitxer >> row >> col >> effect;

		while (!fitxer.eof())
		{
			fila.push_back(row);
			columna.push_back(col);
			efecte.push_back(effect);
			fitxer >> row >> col >> effect;
		}

		ScoreEffect s;

		for (int i = 0; i < fila.size(); i++)
		{
			if (efecte[i] == "DL")
				s = DL;
			else if (efecte[i] == "TL")
				s = TL;
			else if (efecte[i] == "DW")
				s = DW;
			else if (efecte[i] == "TW")
				s = TW;
			else
				s = NO_EFFECT;

			m_cells[fila[i]][columna[i]].setScoreEffect(s);
		}

		fitxer.close();
	}

}
PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos)
{
	int col = boardPos.getCol();
	int row = boardPos.getRow();
	BoardPosition pos;

	if (m_cells[col][row].isEmpty() && (0 <= row) && (row < BOARD_COLS_AND_ROWS) && (0 <= col) && (col < BOARD_COLS_AND_ROWS))
	{
		m_cells[col][row].setEmpty(false);
		m_cells[col][row].setTileLetter(tile.getLetter());
		m_cells[col][row].setTileScore(tile.getScore());
		pos.setCol(col);
		pos.setRow(row);
		currentWord.push_back(pos);
		return PositionResult(VALID_POSITION);
	}
	else if ((row > BOARD_COLS_AND_ROWS - 1 || row < 0) || (col > BOARD_COLS_AND_ROWS - 1 || col < 0))
		return PositionResult(1);
	else
		return PositionResult(2);
}
bool Board::checkDictionary()
{
	string paraula;
	bool trobat = true;
	int i = 0;
	while (i < newWords.size() && trobat)
	{
		int sizeVector = newWords[i].size();

		for (int j = 0; j < sizeVector; j++)
		{
			int row = newWords[i][j].getRow();
			int col = newWords[i][j].getCol();

			char c = m_cells[col][row].getTileLetter();

			paraula.push_back(c);
		}
		trobat = m_dictionary.check(paraula);
		i++;
	}

	return trobat;
}



CurrentWordResult Board::checkCurrentWord(int& points)
{
	int alineacio = 0;

	
	alineacio = comprovaAlineacio();
	buscarParaulesNoves(alineacio);

	if (alineacio == 0)
	{
		return CurrentWordResult(1);
	}
	if (comprovaConexio(alineacio) == true && Consecutivas(alineacio)==false)
	{
		return CurrentWordResult(2);
	}
	if (m_cells[(BOARD_COLS_AND_ROWS - 1) / 2][(BOARD_COLS_AND_ROWS - 1) / 2].isEmpty() == true)
	{
		return CurrentWordResult(3);
	}
	if (currentWord.size() < 2) {
		return CurrentWordResult(4);
	}
	if (checkDictionary() == false)
	{
	return CurrentWordResult(5);
	}

	puntuacioParaules(points);
	return CurrentWordResult(0);

}

int Board::comprovaAlineacio(){
	bool alineatH = true;
	bool alineatV = true;
	int i = 1;
	int x = 0;
	int y = 0;
	x = currentWord[0].getCol();
	y = currentWord[0].getRow();
	while ( i < (currentWord.size()) && (alineatH != false || alineatV != false) ){

		if (x != currentWord[i].getCol())
		{
			alineatV = false;

		}
		if (y != currentWord[i].getRow())
		{
			alineatH = false;

		}
		i++;

	}
	if (alineatH == true)
	{
		return HORITZONTAL; //Significa alineació Horitzontal
	}
	else if (alineatV == true)
	{
		return VERTICAL; //Significa alineació Vertical
	} else {
		return NO_ALINEADES; //Significa que no estan alineades
	}
}

bool Board::Consecutivas(const int& alineacio){
	vector<int> p;
	bool consecutiu = true;
	int j = 0;
	int y = 0;
	int w = 0;
	int k = 0;
	switch (alineacio)
	{
	case HORITZONTAL:
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
		
		y=currentWord[currentWord.size()-1].getCol() - currentWord[0].getCol();
		while (j <= y && consecutiu != false)
		{
			if (m_cells[currentWord[j].getCol()][currentWord[0].getRow()].isEmpty() != false)
			{
				consecutiu = false;
			}
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
		
		k=currentWord[currentWord.size()-1].getRow() - currentWord[0].getRow();
		while (w >= k && consecutiu != false)
		{
			if (m_cells[currentWord[w].getCol()][currentWord[0].getRow()].isEmpty() != false)
			{
				consecutiu = false;
			}
			w++;
		}

		break;
	}		
	return consecutiu;
}
bool Board::comprovaConexio(const int& alineacio) {

	bool conectada = true;
	int i = 0;
	int j = 0;
	switch (alineacio)
	{
	case HORITZONTAL:	
		
		 while (i < currentWord.size() && conectada != false ) {

			if (m_cells[currentWord[i].getCol()][currentWord[i].getRow() + 1].isEmpty() != false) {

				conectada = false;
			}
			if (m_cells[currentWord[i].getCol()][currentWord[i].getRow() - 1].isEmpty() != false) {

				conectada = false;
			}
			if (m_cells[currentWord[i].getCol() + 1][currentWord[i].getRow()].isEmpty() != false) {

				conectada = false;
			}
			if (m_cells[currentWord[i].getCol() - 1][currentWord[i].getRow()].isEmpty() != false) {

				conectada = false;
			}
		}

		break;
	case VERTICAL:
		

		while (j < currentWord.size() && conectada != false) {

			if (m_cells[currentWord[i].getCol()][currentWord[i].getRow() + 1].isEmpty() != false) {

				conectada = false;
			}
			if (m_cells[currentWord[i].getCol()][currentWord[i].getRow() - 1].isEmpty() != false) {

				conectada = false;
			}
			if (m_cells[currentWord[i].getCol() + 1][currentWord[i].getRow()].isEmpty() != false) {

				conectada = false;
			}
			if (m_cells[currentWord[i].getCol() - 1][currentWord[i].getRow()].isEmpty() != false) {

				conectada = false;
			}
		}
		break;

		return conectada;
	}
}
void Board::buscarParaulesNoves(const int& alineacio) {

	vector<BoardPosition> newWord;
	int j = 0;
	int y = 0;
	int w = 0;
	int k = 0;
	int mida = 0;

	switch (alineacio)
	{
	case HORITZONTAL:
		
		
		while (m_cells[currentWord[0].getCol() + j][currentWord[0].getRow()].isEmpty() == false) {
			j++;
		}
		
		while (m_cells[currentWord[0].getCol() - y][currentWord[0].getRow()].isEmpty() == false) {
			y++;
		}
		newWord.resize((j - y) + 1 + currentWord[0].getCol());
		y = currentWord[0].getCol() - y;
		for (int x = 0; x < newWord.size(); x++)
		{
			y--;
			newWord[x].setRow(currentWord[0].getRow());
			newWord[x].setCol(y);
		}

		newWords.push_back(newWord);

		for (int i = 0; i < currentWord.size(); i++) {
			newWord.resize(0);
			
			int j = 0;
			while (m_cells[currentWord[i].getCol()][currentWord[i].getRow() - j].isEmpty() == false) {
				j++;
			}
			int y = 0;
			while (m_cells[currentWord[i].getCol()][currentWord[i].getRow() + y].isEmpty() == false) {
				y++;
			}
			newWord.resize((j - y) + 1);
			for (int x = 0; x < newWord.size(); x++)
			{
				y--;
				newWord[x].setCol(currentWord[0].getCol());
				newWord[x].setRow(y);
			}

			newWords.push_back(newWord);

			}

		break;
	case VERTICAL:

		
		while (m_cells[currentWord[0].getCol()][currentWord[0].getRow() - w].isEmpty() == false) {
			w++;
		}
		
		while (m_cells[currentWord[0].getCol()][currentWord[0].getRow() + k].isEmpty() == false) {
			k++;
		}
		mida = (w - k) + 1+currentWord[0].getRow();
		newWord.resize(mida);
		for (int x = 0; x < newWord.size(); x++)
		{
			k--;
			newWord[x].setCol(currentWord[0].getCol());
			newWord[x].setRow(k);
		}

		newWords.push_back(newWord);
		
		for (int i = 0; i < currentWord.size(); i++) {
			newWord.resize(0);

			int j = 0;
			while (m_cells[currentWord[i].getCol() + j][currentWord[i].getRow()].isEmpty() == false) {
				j++;
			}
			int y = 0;
			while (m_cells[currentWord[i].getCol() - y][currentWord[i].getRow()].isEmpty() == false) {
				y++;
			}


			newWord.resize((j - y) + 1+currentWord[i].getCol());
			for (int x = 0; x < newWord.size(); x++)
			{
				y--;
				newWord[x].setRow(currentWord[0].getRow());
				newWord[x].setCol(y);
			}

			newWords.push_back(newWord);

		}
		break;
	}
}
void Board::puntuacioParaules(int& points)
{
	
	for (int i = 0; i < newWords.size(); i++)
	{
		int multiplicador = 1;
		for (int j = 0; j = newWords[i].size(); i++)
		{
			int row = newWords[j][i].getRow();
			int col = newWords[j][i].getCol();

			if (m_cells[col][row].isTilePlayed())
			{
				points += m_cells[col][row].getTileScore();
			}
			else
			{
				switch (m_cells[col][row].getScoreEffect())
				{
				case DL:
					points += m_cells[col][row].getTileScore() * 2;
					break;
				case TL:
					points += m_cells[col][row].getTileScore() * 3;
					break;
				case DW:
					multiplicador *= 2;
					break;
				case TW:
					multiplicador *= 3;
					break;
				default:
					break;
				}
			}
			points *= multiplicador;
		}
	}
}

void Board::sendCurrentWordToBoard()
{
	int vectorSize = currentWord.size();
	for (int i = 0; i < vectorSize; i++)
	{
		int col = currentWord[i].getCol();
		int row = currentWord[i].getRow();

		m_cells[col][row].setTilePlayed(true);
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

		m_cells[col][row].setEmpty(true);
		m_cells[col][row].setTilePlayed(false);
		m_cells[col][row].setTileLetter(' ');
		m_cells[col][row].setTileScore(0);
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




