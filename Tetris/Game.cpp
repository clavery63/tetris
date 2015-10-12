//
//  Game.cpp
//  Tetris
//
//  Created by Lavery, Chris on 8/24/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#include "Game.h"

const float Game::BlockSpeed = 300.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const int Game::windowHeight = 800;
const int Game::windowWidth = 800;
const int Game::characterSize = Game::windowHeight / 16;

Game::Game()
: mWindow(sf::VideoMode(windowWidth, windowHeight), "Silkworm's Tetris", sf::Style::Close)
, grid(mWindow.getSize())
, silkworm()
{
    framesSinceBlocksMoved = 0;
    font.loadFromFile(resourcePath() + "sansation.ttf");
    prepareText(linesScoredText, 20);
    prepareText(scoreText, 20 + 1.1 * Game::characterSize);
    prepareText(levelText, 20 + 2 * 1.1 * Game::characterSize);
    
    theBoys.loadFromFile("/Users/clavery/Desktop/chown_laudie/jounce_with-my_friends.png");
    theMusicians.setTexture(theBoys);
    theMusicians.setPosition(450.f, 500.f);
    
    if (!silkworm.openFromFile(resourcePath() + "slow_hands.ogg"))
    {
        std::cout << "THE FUCKIN' MUSIC ISN'T PLAYING!";
    }
    silkworm.setLoop(true);
    silkworm.play();
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
    if (isPaused) { return; }
    framesSinceBlocksMoved++;
    grid.clearCurrentShapeBlocks();
    grid.setCurrentShapeBlocks();
    
    int oldLevel = level;
    int oldLinesScored = linesScored;
    linesScored = grid.getLinesScored();
    int combo = linesScored - oldLinesScored;
    if (combo) { incrementScore(combo); }
    level = linesScored / 2;
    
    if (oldLevel != level)
    {
        silkworm.stop();
        silkworm.setPitch(1 - (float)level / 10);
        silkworm.play();
    }
    
    linesScoredText.setString("Lines: " + std::to_string(linesScored));
    scoreText.setString("Score: " + std::to_string(score));
    levelText.setString("Level: " + std::to_string(level));
    
    if (framesSinceBlocksMoved > 30 / (level + 1) || pressedDown)
    {
        grid.tryMovingDown();
        pressedDown = false;
        framesSinceBlocksMoved = 0;
        if (grid.didILose()) { mWindow.close(); }
    }
}

void Game::render()
{
    mWindow.clear(sf::Color(50, 50, 50, 255));
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
    mWindow.draw(linesScoredText);
    mWindow.draw(scoreText);
    mWindow.draw(levelText);
    mWindow.draw(theMusicians);
    
    mWindow.display();
}

void Game::handleInput(sf::Keyboard::Key key)
{
    if (isPaused && key == sf::Keyboard::Space)
        isPaused = false;
    else if (isPaused)
        return;
    else if (key == sf::Keyboard::Down)
        pressedDown = true;
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
    else if (key == sf::Keyboard::Space)
        isPaused = true;
}

void Game::incrementScore(int numLines)
{
    score += 10 * (level + 1) * exp2(numLines - 1);
}

void Game::prepareText(sf::Text &text, int height)
{
    text.setFont(font);
    text.setCharacterSize(Game::characterSize);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(420, height);
}





















