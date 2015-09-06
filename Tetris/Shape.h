//
//  Shape.h
//  Tetris
//
//  Created by Lavery, Chris on 8/25/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#ifndef __Tetris__Shape__
#define __Tetris__Shape__

#include <vector>
#include <SFML/Graphics.hpp>

class Shape
{
public:
    Shape();
    std::vector<sf::Vector2i> getBlockPositions() { return blockPositions; }
    sf::Color getColor() { return color; }
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    
    void rotateClockwise();
    void rotateCounterClockwise();
    
    void applyTransform(int transformIndex);
    
    void createL();
    void createJ();
    void createI();
    void createO();
    void createS();
    void createZ();
    void createT();
    
private:
    sf::Vector2i mainBlock;
    std::vector<sf::Vector2i> blockPositions;
    std::vector<std::vector<int>> transformSets;
    sf::Color color;
    
    int transformIndex;
};

#endif /* defined(__Tetris__Shape__) */
