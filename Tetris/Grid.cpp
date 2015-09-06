//
//  Grid.cpp
//  Tetris
//
//  Created by Lavery, Chris on 8/25/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#include "Grid.h"
#include <iostream>

Grid::Grid(sf::Vector2u windowSize)
{
    blockSize = windowSize.y / 22;
    gridHeight = blockSize * 20 - 2;
    gridWidth = blockSize * 10 - 2;
    gridTop = blockSize;
    gridLeft = blockSize;
    
    outline.setSize(sf::Vector2f(gridWidth, gridHeight));
    outline.setOutlineColor(sf::Color::Black);
    outline.setFillColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(gridLeft, gridTop);
    
    linesScored = 0;
}

void Grid::setBlock(sf::Vector2i position, sf::Color color, std::vector<sf::RectangleShape> &target)
{
    int blockLeft = gridLeft + position.x * blockSize;
    int blockTop = gridTop + position.y * blockSize;
    
    sf::RectangleShape block = sf::RectangleShape();
    block.setSize(sf::Vector2f(blockSize - 2, blockSize - 2));
    block.setOutlineColor(sf::Color::Black);
    block.setFillColor(color);
    block.setOutlineThickness(2);
    block.setPosition(blockLeft, blockTop);
    
    target.push_back(block);
}

void Grid::setCurrentShapeBlocks()
{
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        setBlock(currentShapeBlockPositions[i], currentShape.getColor(), currentShapeBlocks);
    }
}

void Grid::clearCurrentShapeBlocks()
{
    currentShapeBlocks = {};
}

void Grid::tryMovingDown()
{
    currentShape.moveDown();
    if (collisionDown() || blockCollision())
    {
        currentShape.moveUp();
        addShapeToGrid();
        currentShape = Shape();
    }
}

void Grid::tryMovingLeft()
{
    currentShape.moveLeft();
    if (collisionLeft() || blockCollision())
    {
        currentShape.moveRight();
    }
}

void Grid::tryMovingRight()
{
    currentShape.moveRight();
    if (collisionRight() || blockCollision())
    {
        currentShape.moveLeft();
    }
}

void Grid::tryRotatingClockwise()
{
    currentShape.rotateClockwise();
    if (anyCollision())
    {
        currentShape.rotateCounterClockwise();
    }
}

void Grid::tryRotatingCounterClockwise()
{
    currentShape.rotateCounterClockwise();
    if (anyCollision())
    {
        currentShape.rotateClockwise();
    }
}

bool Grid::blockCollision()
{
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        for (int j = 0; j < filledSpaces.size(); j++)
        {
            if (currentShapeBlockPositions[i] == filledSpaces[j])
                return true;
        }
    }
    return false;
}

bool Grid::collisionLeft()
{
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        if (currentShapeBlockPositions[i].x < 0)
            return true;
    }
    return false;
}

bool Grid::collisionRight()
{
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        if (currentShapeBlockPositions[i].x > 9)
            return true;
    }
    return false;
}

bool Grid::collisionDown()
{
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        if (currentShapeBlockPositions[i].y > 19)
            return true;
    }
    return false;
}

bool Grid::anyCollision()
{
    return collisionLeft() || collisionRight() || collisionDown() || blockCollision();
}

void Grid::addShapeToGrid()
{
    std::set<int> yVals;
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        setBlock(currentShapeBlockPositions[i], currentShape.getColor(), gridBlocks);
        filledSpaces.push_back(currentShapeBlockPositions[i]);
        yVals.insert(currentShapeBlockPositions[i].y);
    }
    int numLines = 0;
    for (int yVal : yVals)
    {
        if (checkLine(yVal))
            numLines++;
    }
    addLinesScored(numLines);
}

bool Grid::checkLine(int yVal)
{
    int hits = 0;
    for (int i = 0; i < filledSpaces.size(); i++)
    {
        if (filledSpaces[i].y == yVal)
            hits++;
    }
    if (hits == 10)
    {
        nukeRow(yVal);
        return true;
    }
    return false;
}

void Grid::nukeRow(int yVal)
{
    for (int i = 0; i < filledSpaces.size(); i++)
    {
        if (filledSpaces[i].y == yVal)
        {
            filledSpaces.erase(filledSpaces.begin() + i);
            i--; // Retry that index after resizing the vector
        }
    }
    
    int heightToErase = gridTop + yVal * blockSize;
    for (int i = 0; i < gridBlocks.size(); i++)
    {
        if (gridBlocks[i].getPosition().y == heightToErase)
        {
            gridBlocks.erase(gridBlocks.begin() + i);
            i--;
        }
    }
    
    for (int i = 0; i < filledSpaces.size(); i++)
    {
        if (filledSpaces[i].y < yVal)
            filledSpaces[i].y++;
    }
    
    for (int i = 0; i < gridBlocks.size(); i++)
    {
        if (gridBlocks[i].getPosition().y < heightToErase)
            gridBlocks[i].setPosition(gridBlocks[i].getPosition().x, gridBlocks[i].getPosition().y + blockSize);
    }
}





































