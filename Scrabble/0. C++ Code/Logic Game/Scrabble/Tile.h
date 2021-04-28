//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp

class Tile
{
public:
    Tile() { }
    char getLetter() { return m_letter; }
    void setLetter(char letter) { m_letter = letter; }
    unsigned int getScore() { return m_score; }
    void setScore(unsigned int score) { m_score = score; }
    
private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */