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
    gridHeight = blockSize * 20;
    gridWidth = blockSize * 10;
    gridTop = blockSize;
    gridLeft = blockSize;
    
    outline.setSize(sf::Vector2f(gridWidth, gridHeight));
    outline.setOutlineColor(sf::Color::Black);
    outline.setFillColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(gridLeft, gridTop);
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
    std::vector<sf::Vector2i> currentShapeBlockPositions = currentShape.getBlockPositions();
    for (int i = 0; i < currentShapeBlockPositions.size(); i++)
    {
        setBlock(currentShapeBlockPositions[i], currentShape.getColor(), gridBlocks);
        filledSpaces.push_back(currentShapeBlockPositions[i]);
        checkLine(currentShapeBlockPositions[i].y);
    }
}

void Grid::checkLine(int yVal)
{
    int hits = 0;
    for (int i = 0; i < filledSpaces.size(); i++)
    {
        if (filledSpaces[i].y == yVal)
            hits++;
    }
    if (hits == 10)
        nukeRow(yVal);
}

void Grid::nukeRow(int yVal)
{
    std::cout << "nuking row " << yVal << std::endl;
}



































