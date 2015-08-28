//
//  CurrentShape.cpp
//  Tetris
//
//  Created by Lavery, Chris on 8/25/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#include "CurrentShape.h"

CurrentShape::CurrentShape()
{
    color = sf::Color::Blue;
    blockPositions.push_back(sf::Vector2u(5,0));
    blockPositions.push_back(sf::Vector2u(6,0));
    blockPositions.push_back(sf::Vector2u(5,1));
    blockPositions.push_back(sf::Vector2u(6,1));
}