//
//  Game.h
//  Tetris
//
//  Created by Lavery, Chris on 8/24/15.
//  Copyright (c) 2015 Chris Lavery. All rights reserved.
//

#ifndef __Tetris__Game__
#define __Tetris__Game__

#include <SFML/Graphics.hpp>
#include "Grid.h"

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
    
private:
    static const float BlockSpeed;
    static const sf::Time TimePerFrame;
    static const int windowHeight;
    static const int windowWidth;
    
    int framesSinceBlocksMoved;
    
    sf::RenderWindow mWindow;
    Grid grid;
};

#endif /* defined(__Tetris__Game__) */
