//
//  Game.cpp
//  Tetris
//
//  Created by Lavery, Chris on 8/24/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#include "Game.h"

const float Game::BlockSpeed = 60.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const int Game::windowHeight = 1080;
const int Game::windowWidth = 1080;

Game::Game()
: mWindow(sf::VideoMode(windowWidth, windowHeight), "Tetris", sf::Style::Close)
, grid(mWindow.getSize())
{
    framesSinceBlocksMoved = 0;
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            
            processEvents();
            update();
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handleInput(event.key.code);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    framesSinceBlocksMoved++;
    grid.clearCurrentShapeBlocks();
    grid.setCurrentShapeBlocks();
    
    if (framesSinceBlocksMoved > 30)
    {
        grid.tryMovingDown();
        framesSinceBlocksMoved = 0;
    }
}

void Game::render()
{
    mWindow.clear(sf::Color::Cyan);
    mWindow.draw(grid.getOutline());
    
    std::vector<sf::RectangleShape> gridBlocks = grid.getGridBlocks();
    for (int i = 0; i < gridBlocks.size(); i++)
    {
        mWindow.draw(gridBlocks[i]);
    }
    
    std::vector<sf::RectangleShape> currentShapeBlocks = grid.getCurrentShapeBlocks();
    for (int i = 0; i < currentShapeBlocks.size(); i++)
    {
        mWindow.draw(currentShapeBlocks[i]);
    }
    
    mWindow.display();
}

void Game::handleInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Down)
        grid.tryMovingDown();
    else if (key == sf::Keyboard::Left)
        grid.tryMovingLeft();
    else if (key == sf::Keyboard::Right)
        grid.tryMovingRight();
    else if (key == sf::Keyboard::D)
        grid.tryRotatingClockwise();
    else if (key == sf::Keyboard::A)
        grid.tryRotatingCounterClockwise();
    else if (key == sf::Keyboard::Escape)
        mWindow.close();
}




