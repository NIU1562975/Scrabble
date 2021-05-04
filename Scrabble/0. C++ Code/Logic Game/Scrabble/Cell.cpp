//
//  Cell.cpp
//  Scrabble
//


#include "Cell.h"

Cell::Cell()
{
	m_empty = true;
	m_tilePlayed = false;
	m_scoreEffect = ScoreEffect(NO_EFFECT);
	m_tile.setLetter(' ');
	m_tile.setScore(0);
}

