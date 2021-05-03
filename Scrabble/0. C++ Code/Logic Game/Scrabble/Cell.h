//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include "Tile.h"

typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

class Cell
{
public:
    Cell() : m_empty(1), m_tilePlayed(0) { m_scoreEffect = NO_EFFECT; };
    ScoreEffect getScoreEffect() { return m_scoreEffect; }
    void setScoreEffect(ScoreEffect x) { m_scoreEffect = x; }
    bool isEmpty() { return m_empty; }
    void setEmpty(bool x) { m_empty = x; }
    bool isTilePlayed() { return m_tilePlayed; }
    void setTilePlayed(bool x) { m_tilePlayed = x; }
    void setTileLetter(char x) { m_tile.setLetter(x); }
    void setTileScore(int x) { m_tile.setScore(x); }
    char getTileLetter() { return m_tile.getLetter(); }
    int getTileScore() { return m_tile.getScore(); }


private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
