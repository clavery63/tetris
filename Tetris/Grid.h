//
//  Grid.h
//  Tetris
//
//  Created by Lavery, Chris on 8/25/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#ifndef __Tetris__Grid__
#define __Tetris__Grid__

#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include "Shape.h"

class Grid: private sf::NonCopyable
{
public:
    Grid(sf::Vector2u windowSize);
    
    sf::RectangleShape getOutline() { return outline; }
    int getBlockSize() { return blockSize; }
    int getLinesScored() { return linesScored; }
    void addLinesScored(int i) { linesScored += i; }
    std::vector<sf::RectangleShape> getGridBlocks() { return gridBlocks; }
    std::vector<sf::RectangleShape> getCurrentShapeBlocks() { return currentShapeBlocks; }
        
    void setBlock(sf::Vector2i position, sf::Color color, std::vector<sf::RectangleShape> &target);
    void setCurrentShapeBlock(sf::Vector2i position, sf::Color color);
    void setCurrentShapeBlocks();
    void addShapeToGrid();
    void clearCurrentShapeBlocks();
    void nukeRow(int yVal);
    
    void tryMovingDown();
    void tryMovingLeft();
    void tryMovingRight();
    void tryRotatingClockwise();
    void tryRotatingCounterClockwise();
    
    bool checkLine(int yVal);
    bool blockCollision();
    bool collisionLeft();
    bool collisionRight();
    bool collisionDown();
    bool anyCollision();
    
    bool didILose() { return ILost; }

private:
    sf::RectangleShape outline;
    int blockSize;
    int gridHeight;
    int gridWidth;
    int gridLeft;
    int gridTop;
    
    int linesScored;
    
    bool ILost;
    
    std::vector<sf::Vector2i> filledSpaces;
    std::vector<sf::RectangleShape> gridBlocks;
    std::vector<sf::RectangleShape> currentShapeBlocks;
    
    Shape currentShape;
};

#endif /* defined(__Tetris__Grid__) */
