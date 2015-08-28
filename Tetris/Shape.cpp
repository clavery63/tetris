//
//  Shape.cpp
//  Tetris
//
//  Created by Lavery, Chris on 8/25/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//
#include <stdlib.h>
#include "Shape.h"

Shape::Shape()
{
    transformIndex = 0;
    mainBlock = sf::Vector2i(5,1);
    
    int randomBelowSix = rand() % 6;
    
    switch (randomBelowSix)
    {
        case 0:
            createI();
            break;
        case 1:
            createJ();
            break;
        case 2:
            createS();
            break;
        case 3:
            createO();
            break;
        case 4:
            createZ();
        case 5:
            createL();
            break;
    }
    
    applyTransform(transformIndex);
}

void Shape::moveUp()
{
    mainBlock.y--;
    for (int i = 0; i < blockPositions.size(); i++)
    {
        blockPositions[i].y--;
    }
}

void Shape::moveDown()
{
    mainBlock.y++;
    for (int i = 0; i < blockPositions.size(); i++)
    {
        blockPositions[i].y++;
    }
}

void Shape::moveLeft()
{
    mainBlock.x--;
    for (int i = 0; i < blockPositions.size(); i++)
    {
        blockPositions[i].x--;
    }
}

void Shape::moveRight()
{
    mainBlock.x++;
    for (int i = 0; i < blockPositions.size(); i++)
    {
        blockPositions[i].x++;
    }
}

void Shape::rotateClockwise()
{
    transformIndex++;
    transformIndex = transformIndex % 4;
    applyTransform(transformIndex);
}

void Shape::rotateCounterClockwise()
{
    transformIndex +=3;
    transformIndex = transformIndex % 4;
    applyTransform(transformIndex);
}

void Shape::applyTransform(int tIndex)
{
    blockPositions = {};
    
    blockPositions.push_back(mainBlock);
    blockPositions.push_back(mainBlock + sf::Vector2i(transformSets[tIndex][0],transformSets[tIndex][1]));
    blockPositions.push_back(mainBlock + sf::Vector2i(transformSets[tIndex][2],transformSets[tIndex][3]));
    blockPositions.push_back(mainBlock + sf::Vector2i(transformSets[tIndex][4],transformSets[tIndex][5]));
}

// Friends don't let friends do this by the way :)

void Shape::createL()
{
    color = sf::Color::Blue;
    transformSets.push_back(std::vector<int> { -1, 0, 1, 0, 1, 1 });
    transformSets.push_back(std::vector<int> { 0, 1, 0, -1, -1, 1 });
    transformSets.push_back(std::vector<int> { 1, 0, -1, 0, -1, -1 });
    transformSets.push_back(std::vector<int> { 0, -1, 0, 1, 1, -1 });
}

void Shape::createJ()
{
    color = sf::Color::Red;
    transformSets.push_back(std::vector<int> { -1, 0, 1, 0, -1, 1 });
    transformSets.push_back(std::vector<int> { 0, 1, 0, -1, -1, -1 });
    transformSets.push_back(std::vector<int> { 1, 0, -1, 0, 1, -1 });
    transformSets.push_back(std::vector<int> { 0, -1, 0, 1, 1, 1 });
}

void Shape::createO()
{
    color = sf::Color::Yellow;
    transformSets.push_back(std::vector<int> { 1, 0, 1, 1, 0, 1 });
    transformSets.push_back(std::vector<int> { 1, 0, 1, 1, 0, 1 });
    transformSets.push_back(std::vector<int> { 1, 0, 1, 1, 0, 1 });
    transformSets.push_back(std::vector<int> { 1, 0, 1, 1, 0, 1 });
}

void Shape::createI()
{
    color = sf::Color::Green;
    transformSets.push_back(std::vector<int> { -1, 0, 1, 0, 2, 0 });
    transformSets.push_back(std::vector<int> { 0, -1, 0, 1, 0, 2 });
    transformSets.push_back(std::vector<int> { -1, 0, 1, 0, 2, 0 });
    transformSets.push_back(std::vector<int> { 0, -1, 0, 1, 0, 2 });
}

void Shape::createS()
{
    color = sf::Color::Magenta;
    transformSets.push_back(std::vector<int> { 0, -1, 1, -1, -1, 0 });
    transformSets.push_back(std::vector<int> { 0, 1, -1, 0, -1, -1 });
    transformSets.push_back(std::vector<int> { 0, -1, 1, -1, -1, 0 });
    transformSets.push_back(std::vector<int> { 0, 1, -1, 0, -1, -1 });
}

void Shape::createZ()
{
    color = sf::Color::Black;
    transformSets.push_back(std::vector<int> { 0, -1, -1, -1, 1, 0 });
    transformSets.push_back(std::vector<int> { 0, 1, 1, 0, 1, -1 });
    transformSets.push_back(std::vector<int> { 0, -1, -1, -1, 1, 0 });
    transformSets.push_back(std::vector<int> { 0, 1, 1, 0, 1, -1 });
}









































