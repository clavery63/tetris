//
//  Game.h
//  Tetris
//
//  Created by Lavery, Chris on 8/24/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#ifndef __Tetris__Game__
#define __Tetris__Game__

#include <math.h>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "ResourcePath.hpp"

class Game: private sf::NonCopyable
{
public:
    Game();
    void run();
    
private:
    void processEvents();
    void update();
    void render();
    void handleInput(sf::Keyboard::Key key);
    void incrementScore(int numLines);
    void prepareText(sf::Text &text, int height);
    
private:
    static const float BlockSpeed;
    static const sf::Time TimePerFrame;
    static const int windowHeight;
    static const int windowWidth;
    static const int characterSize;
    
    int framesSinceBlocksMoved;
    int linesScored = 50;
    int score;
    int level = 1;
    bool pressedDown;
    bool isPaused = false;
    
    sf::RenderWindow mWindow;
    sf::Font font;
    sf::Text linesScoredText;
    sf::Text scoreText;
    sf::Text levelText;
    sf::Music silkworm;
    
    Grid grid;
};

#endif /* defined(__Tetris__Game__) */
