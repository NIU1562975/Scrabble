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
    Cell() { }
    ScoreEffect getScoreEffect() { return m_scoreEffect; }
    void setScoreEffect(ScoreEffect x) { m_scoreEffect = x; }
    bool isEmpty() { return m_empty; }
    void setEmpty(bool x) { m_empty = x; }
    bool isTilePlayed() { return m_tilePlayed; }
    void setTilePlayed(int x) { m_tilePlayed = x; }

private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
