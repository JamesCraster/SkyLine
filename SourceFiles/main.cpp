//
//  main.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 29/08/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//


#include "ResourcePath.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include "LevelLoader.h"
#include "Camera.h"
#include <iostream>
#include "LevelGenerator.h"
#include "Controller.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
class smartClock:public sf::Clock{
public:
    bool active = 0;
};

std::vector<std::vector<int>> generatePlatform(sf::Vector2f Size, int width, bool spikes){
    std::vector<std::vector<int>> levelVector;
    int counter = 0;
    for(int x = 0; x < Size.x; x++){
        levelVector.push_back(std::vector<int>{});
        for(int y = 27; y >= 0; y--){
            if(y == Size.y){
                levelVector[x].push_back(99);
                counter ++;
            }
            if(y > Size.y || y <= width){
                levelVector[x].push_back(0);
            }else{
                levelVector[x].push_back(1);
                
            }
        }
    }
    if(Size.x > 8 && spikes){
    generator(levelVector, 99, std::vector<int>{0,10}, std::vector<float>{0.9,0.1}, std::vector<bool>{0,1}, std::vector<int>{0,2},std::vector<int>{0,0});
    }
    return levelVector;
}
std::vector<std::vector<int>> generateNarrowPassage(sf::Vector2f BottomSize, sf::Vector2f UpperSize){
    std::vector<std::vector<int>> levelVector;
    for(int x = 0; x < BottomSize.x; x++){
        levelVector.push_back(std::vector<int>{});
        for(int y = 27; y >= 0; y--){
            if(y < BottomSize.y){
                levelVector[x].push_back(1);
            }
            else if(y >= UpperSize.y){
                levelVector[x].push_back(1);
                
            }else{
                levelVector[x].push_back(0);
                
            }
        }
    }
    return levelVector;
}
std::vector<std::vector<int>> generateGap(float width){
    std::vector<std::vector<int>> levelVector;
    for(int x = 0; x < width; x++){
        levelVector.push_back(std::vector<int>{});
        for(int y = 27; y > 0; y--){
           levelVector[x].push_back(0);        }
    }
    return levelVector;
}

int addChain(ChunkChain &chunkChain, float previousHeight, float distance){
    //make difficulty a function of distance
    
    srand(time(0));
    int height = rand()%8 - 3 + previousHeight;
    if(height >= 23){
        height = 23 - rand() % 7;
    }
    if(height <= 3){
        height = 2 + rand()%3;
    }
    int width;
    if(previousHeight > height){
        width =  rand()%9 + 0;
    }else{
        width = rand()%9 + 4;
        
    }
    
    chunkChain.appendChunk(Chunk(generateGap(width),sf::Vector2f(chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.x + chunkChain.chunkChain[chunkChain.chunkChain.size()-1].size.x,chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.y)));
    

    width = rand()%16 + 3;

    if(previousHeight < height && rand()%2){
    int narrow = rand()%2 + 3;
    chunkChain.appendChunk(Chunk(generateNarrowPassage(sf::Vector2f(width, height),sf::Vector2f(width, height + narrow)),sf::Vector2f(chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.x + chunkChain.chunkChain[chunkChain.chunkChain.size()-1].size.x,chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.y)));
    
    }else{
        chunkChain.appendChunk(Chunk(generatePlatform(sf::Vector2f(width, height),0,1),sf::Vector2f(chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.x + chunkChain.chunkChain[chunkChain.chunkChain.size()-1].size.x,chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.y)));
    }
    return height;
}

int startLevel(sf::RenderWindow & window, int & score, int mode){
    ControllerController controllerController;
    std::vector<Spike*> spikeVector;
    std::vector<sf::RectangleShape*> tileVector;
    ChunkChain chunkChain;
    chunkChain.appendChunk(Chunk(generatePlatform(sf::Vector2f(20,10),0,0),sf::Vector2f(0,0)));
    chunkChain.appendChunk(Chunk(generateGap(3),sf::Vector2f(20 + 20*32,0)));
    auto levelVector = loadLevelFromChunkChain(chunkChain, sf::Vector2f(32,32), spikeVector, tileVector);
    
    //load images
    sf::Texture runNinja1;
    runNinja1.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(0,0,10,20));
    sf::Texture runNinja2;
    runNinja2.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10,0,10*2,20));
    sf::Texture runNinja3;
    runNinja3.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*2,0,10*3,20));
    sf::Texture runNinja4;
    runNinja4.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*3,0,10*4,20));
    sf::Texture runNinja5;
    runNinja5.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*4,0,10*5,20));
    sf::Texture runNinja6;
    runNinja6.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*5,0,10*6,20));
    sf::Texture runNinja7;
    runNinja7.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*6,0,10*7,20));
    sf::Texture runNinja8;
    runNinja8.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*7,0,10*8,20));
    sf::Texture runNinja9;
    runNinja9.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*8,0,10*9,20));
    sf::Texture runNinja10;
    runNinja10.loadFromFile(resourcePath() + "BlueRun.png", sf::IntRect(10*9,0,10*10,20));
    
    sf::Texture runEnemy1;
    runEnemy1.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(0,0,10,20));
    sf::Texture runEnemy2;
    runEnemy2.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10,0,10*2,20));
    sf::Texture runEnemy3;
    runEnemy3.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*2,0,10*3,20));
    sf::Texture runEnemy4;
    runEnemy4.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*3,0,10*4,20));
    sf::Texture runEnemy5;
    runEnemy5.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*4,0,10*5,20));
    sf::Texture runEnemy6;
    runEnemy6.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*5,0,10*6,20));
    sf::Texture runEnemy7;
    runEnemy7.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*6,0,10*7,20));
    sf::Texture runEnemy8;
    runEnemy8.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*7,0,10*8,20));
    sf::Texture runEnemy9;
    runEnemy9.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*8,0,10*9,20));
    sf::Texture runEnemy10;
    runEnemy10.loadFromFile(resourcePath() + "RedRun.png", sf::IntRect(10*9,0,10*10,20));
    
    sf::Texture spikeTexture;
    spikeTexture.loadFromFile(resourcePath() + "Spikes.png");
    for (int x = 0; x < spikeVector.size(); x++){
        spikeVector[x]->spikeSprite.setTexture(spikeTexture);
    }
    
    smartClock deathClock;
    
    Player player(std::vector<AnimationController> {},25,10,23, sf::Vector2f(5,9),sf::Vector2f(-5,-9),sf::Vector2f(10,20),46000/20,3);
    Enemy enemy(std::vector<AnimationController> {},20,10,23,sf::Vector2f(5,9),sf::Vector2f(5,9),sf::Vector2f(10,20),16000/20);
    
    AnimationController run(std::vector<float> (10,0.5),std::vector<sf::Texture*> {&runNinja1,&runNinja2,&runNinja3,&runNinja4,&runNinja5,&runNinja6,&runNinja7,&runNinja8,&runNinja9,&runNinja10},&player.sprite);
    AnimationController redRun(std::vector<float> (10,0.5),std::vector<sf::Texture*> {&runEnemy1,&runEnemy2,&runEnemy3,&runEnemy4,&runEnemy5,&runEnemy6,&runEnemy7,&runEnemy8,&runEnemy9,&runEnemy10},&enemy.sprite);
    run.active = 1;
    player.animationControllerVector.push_back(run);
    enemy.animationControllerVector.push_back(redRun);
    
    player.sprite.setOrigin(5,8);
    player.sprite.setScale(2, 2);
    player.sprite.setPosition(sf::Vector2f(100,300));
    player.physicsController.displacement = sf::Vector2f(100,300);
    enemy.sprite.setPosition(300, 600);
    enemy.sprite.setOrigin(5, 8);
    enemy.sprite.setScale(2,2);
    enemy.sprite.setTexture(runEnemy1,true);
    enemy.animationControllerVector[0].active = 1;
    
    sf::Clock jumpClock;
    player.sprite.setTexture(runNinja1,true);
    player.animationControllerVector[0].setAnimationSpeed(4);
    
    
    sf::Clock frameTime;
    double storedFrameTime;
    
    sf::Clock cameraClock;
    double cameraTime;
    double cameraAccumulator = 0;
    
    sf::Texture floorTexture;
    floorTexture.loadFromFile(resourcePath() + "FloorTexture.png");
    sf::Texture floorTextureRotated;
    floorTextureRotated.loadFromFile(resourcePath() + "FloorTextureRotated.png");
    
    sf::View playerView(sf::FloatRect(0, 0, int(1400), int(851)));
    window.setView(playerView);
    sf::Vector2f playerViewScrollVector;
    bool mostRecentlyPressed = 1;
    double accumulator = 0;
    const double dt = 1/360.f;
    
    sf::CircleShape circle(10);
    circle.setFillColor(sf::Color::Black);
    
    bool storedSouthContact;
    int storedDirection = player.direction;
    bool jumpCutoff = 0;

    sf::Vector2f cameraMovement = sf::Vector2f(window.sf::Window::getSize().x/2.f,window.sf::Window::getSize().y/2.f);
    sf::Sprite healthSprite;
    sf::Texture healthTexture;
    healthTexture.loadFromFile(resourcePath() + "HealthBar.png");
    healthSprite.setTexture(healthTexture);
    sf::Joystick ps3Cont;
    player.isJumping = 1;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "arcadeclassic.regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setPosition(700, 50);
    float previousHeight = 10;
    
    int highScore = 0;
    
    std::ifstream inf(resourcePath() + "Sample.dat");
    if(inf){
        std::string string;
        getline(inf,string);
        highScore = std::stoi(string);
        inf.close();
    }if(!inf){
        inf.close();
        std::ofstream ioutf(resourcePath() + "Sample.dat");
        ioutf << "0";
        ioutf.close();
        inf.open(resourcePath() + "Sample.dat");
        std::string string;
        getline(inf,string);
        
        highScore = std::stoi(string);
        inf.close();
        
        
    }
    float t = 0;
    

    frameTime.restart();
    storedFrameTime = 1/60.f;
    while (window.isOpen())
    {
        // Process events
        // std::cout << 1/storedFrameTime << "," << std::endl;
       // std::cout << player.sprite.getPosition().x << "," << std::endl;
        //fixing my timestep results in poor performance on my macbook. Cutting out this line will fix the physics timestep:
        
        if(mode){
           storedFrameTime = 1/60.f;
        }
        controllerController.getInput();
        if(storedFrameTime > 1/5.f){
            storedFrameTime = 1/60.f;
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
                return 1;
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
                return 1;
            }
           /* if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                
                if(mostRecentlyPressed == 0){
                    
                    // player.physicsController.xVelocity *= pow(0.0,(1/60)/(storedFrameTime));
                    if(player.physicsController.tileCollisionController.southContact == 1){
                    player.physicsController.velocity.x *= 0.15;
                    }
                    
                    player.sprite.setScale(2, 2);
                    
                }
                
                //player.animationControllerVector[0].setCurrentFrame(5);
                
                mostRecentlyPressed = 1;
                
            }*/
            //if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
             
             //if(jumpCutoff && player.isJumping){
             
            // if(player.physicsController.velocity.y < 0){
             
            // player.physicsController.velocity.y = 0;
             
            // jumpCutoff = 0;
             
            // }
             
            // }
             
            // }
            
           /* if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
             
             if(mostRecentlyPressed == 1){
                 if(player.physicsController.tileCollisionController.southContact == 1){

                     player.physicsController.velocity.y *= 0.15 /*pow(0.0,(1/60)/(storedFrameTime))*//*;
                 }
            
             }
             
             
             
             mostRecentlyPressed = 0;
             
             }*/
            /*if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) ||  ps3Cont.isButtonPressed(0,11)){
             
             if((player.physicsController.tileCollisionController.southContact || jumpClock.getElapsedTime().asSeconds() < 0.1) && player.isJumping == 0){
             
             player.isJumping = 1;
             
             player.animationControllerVector[0].active = 0;
             
             player.animationControllerVector[0].setCurrentFrame(0);
             
             jumpCutoff = 1;
             
             player.physicsController.force.y = -450000;
             
             }
             
             }else{
             
             if(!player.physicsController.tileCollisionController.southContact){
             
             // player.isJumping = 0;
             
             player.animationControllerVector[0].active = 1;
             
             
             
             }*/
             
             
             
             
        }
        if(controllerController.wasPressed(Controller::JUMP)){
            if((player.physicsController.tileCollisionController.southContact || jumpClock.getElapsedTime().asSeconds() < 0.1) && player.isJumping == 0)
            {
                player.isJumping = 1;
                player.animationControllerVector[0].active = 0;
                player.animationControllerVector[0].setCurrentFrame(0);
                jumpCutoff = 1;
                player.physicsController.force.y = -10970000;
            }
        }else
        {
            if(!player.physicsController.tileCollisionController.southContact)
            {
                
                    player.animationControllerVector[0].active = 1;
                    
            }
                
        }
        
        if (controllerController.wasReleased(Controller::JUMP)) {
            if(jumpCutoff && player.isJumping){
                if(player.physicsController.velocity.y < 0){
                    player.physicsController.velocity.y = 0;
                    jumpCutoff = 0;
                }
            }
        }
        
        if(!player.isJumping){
            player.animationControllerVector[0].active = 1;
        }
        if(player.physicsController.tileCollisionController.southContact != storedSouthContact){
            if(player.physicsController.tileCollisionController.southContact == 0){
                jumpClock.restart();
            }else{
                player.isJumping = 0;
            }
        }
        while(chunkChain.chunkChain.size() != 0 && (playerView.getCenter().x + playerView.getSize().x/2 > chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.x + chunkChain.chunkChain[chunkChain.chunkChain.size()-1].size.x - 3 - 20 )){
            previousHeight = addChain(chunkChain, previousHeight,int(player.sprite.getPosition().x/32));
            levelVector = loadLevelFromChunkChain(chunkChain, sf::Vector2f(32,32), spikeVector, tileVector);
        }
        
        player.animationControllerVector[0].setAnimationSpeed(std::abs(player.physicsController.velocity.x)/50);
        storedSouthContact = player.physicsController.tileCollisionController.southContact;
        window.clear();
        accumulator += storedFrameTime;
        sf::Vector2f originalPos = player.sprite.getPosition();
        
        while (accumulator >= dt) {
            sf::Clock physicsTime;
            player.testTileCollisions(tileVector);
          
            
            if(player.physicsController.tileCollisionController.southContact == 0){
                player.physicsController.force.y += player.physicsController.mass * player.gravity;
            }else{
                if(std::abs(player.physicsController.velocity.x) < 0.1){
                    player.animationControllerVector[0].setCurrentFrame(3);
                    
                }else{
                    
                }
            }
            
            if(std::abs(player.physicsController.velocity.x) < 0.1){
                player.animationControllerVector[0].setCurrentFrame(3);
                
            }
            if(player.alive == 0){
                player.sprite.setOrigin(5,18);
                player.physicsController.velocity.x *= 0.3;
                player.animationControllerVector[0].active = 0;
                if(player.sprite.getRotation() < 90){
                    player.sprite.rotate(4);
                }
            }
            /*if(mostRecentlyPressed == 1){
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||  ps3Cont.getAxisPosition(0, sf::Joystick::Axis::X) > 10)
                    
                {
                    
                    player.direction = 1;
                    
                    player.animationControllerVector.setActiveAnimation(0);
                    
                    player.sprite.setScale(2, 2);
                    
                    
                    
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||  ps3Cont.getAxisPosition(0, sf::Joystick::Axis::X) < -10)
                    
                {
                    
                    player.direction = -1;
                    
                    player.animationControllerVector.setActiveAnimation(0);
                    
                    // player.physicsController.xVelocity *= 0.15;
                    
                    player.sprite.setScale(-2, 2);
                    
                    
                    
                    
                    
                }else
                    
                {
                    
                    player.direction  = 0;
                    if(player.physicsController.tileCollisionController.southContact == 1){
                        player.physicsController.velocity.x *= 0.15;
                    }if(player.physicsController.tileCollisionController.southContact == 0){
                        player.physicsController.velocity.x *= 0.95;
                    }
                    
                    //player.animationControllerVector[0].setCurrentFrame(3);
                    
                }
                
            }else
                
            {
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||  ps3Cont.getAxisPosition(0, sf::Joystick::Axis::X) > 10)
                    
                {
                    
                    player.direction = -1;
                    
                    player.animationControllerVector.setActiveAnimation(0);
                    
                    player.sprite.setScale(-2, 2);
                    
                    
                    
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    
                {
                    
                    
                    
                    player.direction = 1;
                    
                    player.animationControllerVector.setActiveAnimation(0);
                    
                    player.sprite.setScale(2, 2);
                    
                    
                    
                    
                    
                }else
                    
                {
                    
                    player.direction  = 0;
                    if(player.physicsController.tileCollisionController.southContact == 1){
                        player.physicsController.velocity.x *= 0.15;
                    }
                    
                    
                    
                }
                
                
                
            }
            
            
            
            if(storedDirection != player.direction){
                if(player.physicsController.tileCollisionController.southContact == 1){
                    player.physicsController.velocity.x *= 0.40;
                }
                
            }*/
            
            player.direction = 1;
            if(player.physicsController.tileCollisionController.southContact){
                player.physicsController.force.x += 90000 * player.direction;
            }else{
                
               // player.physicsController.force.x += 90000 * player.direction;
                
            }
            
            
            player.update(t,dt,accumulator,tileVector,mostRecentlyPressed);
            

            

            accumulator -= dt;
            t += dt;
        }
        
        player.physicsController.renderUpdate(accumulator/dt);
        if(player.alive == 1){
            player.sprite.setPosition(player.physicsController.displacement);
        }else{
            player.sprite.setPosition(player.physicsController.displacement.x, player.physicsController.displacement.y + 10);
            
        }
        for(int x = 0; x < spikeVector.size(); x++){
            if(player.boundingBox.intersects(spikeVector[x]->collisionBox)){
                player.damage(1);
            }
        }
        
        sf::VertexArray line(sf::LinesStrip);
        line.append(sf::Vertex(sf::Vector2f(playerView.getCenter().x - playerView.getSize().x/2, (27-previousHeight)*32),sf::Color::White));
        line.append(sf::Vertex(sf::Vector2f(playerView.getCenter().x + playerView.getSize().x/2, (27-previousHeight)*32),sf::Color::White));
        for(int i = 0; i < chunkChain.chunkChain.size(); i++){
            if(i == chunkChain.readPosition){
            }else{
            }
             circle.setPosition(chunkChain.chunkChain[i].position.x + chunkChain.chunkChain[i].size.x, 27 * 32 - previousHeight *32);
             window.draw(circle);
        }
        
        if(chunkChain.chunkChain.size() > 0){
            while(playerView.getCenter().x - playerView.getSize().x/2 > chunkChain.chunkChain[chunkChain.readPosition].position.x + /*chunkChain.chunkChain[1].size.x*/ + chunkChain.chunkChain[chunkChain.readPosition].size.x){
                chunkChain.removeChunk();
                levelVector.clear();
                levelVector = loadLevelFromChunkChain(chunkChain, sf::Vector2f(32,32), spikeVector, tileVector);
            }
        }
        
        sf::RectangleShape skyScraper;
        skyScraper.setPosition(100, 200);
        skyScraper.setSize(sf::Vector2f(300, 1000));
        skyScraper.setOutlineColor(sf::Color(24/3,118/3,118/3));
        skyScraper.setOutlineThickness(5);
        skyScraper.setFillColor(sf::Color(24,118,118,0));
        skyScraper.move(-(cameraMovement.x - playerView.getCenter().x)/1.1,0);
        window.draw(skyScraper);
         circle.setPosition(playerView.getCenter().x - playerView.getSize().x/2, 300);
        cameraTime = storedFrameTime;
        positionView(playerView, sf::Vector2f(player.sprite.getPosition().x+600,player.sprite.getPosition().y-200), cameraTime);
        enemy.update(tileVector);
        
        window.setView(playerView);
        for(int i = 0; i < tileVector.size(); i++){
            tileVector[i]->setFillColor(sf::Color::Black);
            tileVector[i]->setOutlineColor(sf::Color(0,0,0,0));
            tileVector[i]->setSize(sf::Vector2f(tileVector[i]->getSize().x+1, tileVector[i]->getSize().y+1));
            window.draw(*tileVector[i]);
            tileVector[i]->setSize(sf::Vector2f(tileVector[i]->getSize().x-1, tileVector[i]->getSize().y-1));
            
        }
        
        drawFloorSpriteFromLevelVector(levelVector, floorTexture, floorTextureRotated, window);
        for(int i = 0; i < player.health; i++){
            healthSprite.setPosition(playerView.getCenter().x - playerView.getSize().x/2 + 21 + 49 * i,playerView.getCenter().y  - playerView.getSize().y/2 + 20);
            window.draw(healthSprite);
        }
       
        if(player.sprite.getPosition().y > 851){
            player.health = 0;
            player.die();
            for(int i = 0; i < tileVector.size(); i++){
                delete tileVector[i];
            }
            
            score = int(player.sprite.getPosition().x/32);
            if(score > highScore){
                std::ofstream outf(resourcePath() + "Sample.dat");
                outf << std::to_string(score);
                
                outf.close();
            }
            spikeVector.clear();
            tileVector.clear();
            levelVector.clear();
            return 0;
        }
        
        player.draw(window);
        
        player.animationControllerVector.setActiveAnimation(0);
        for (int x = 0; x < spikeVector.size(); x++){
            spikeVector[x]->spikeSprite.setTexture(spikeTexture);
            window.draw(spikeVector[x]->spikeSprite);
        }
        if(player.alive == 0 && !deathClock.active){
            deathClock.restart();
            deathClock.active = 1;
        }
        if(player.alive == 0 && deathClock.active && deathClock.getElapsedTime().asSeconds() > 0.5){
            for(int i = 0; i < tileVector.size(); i++){
                delete tileVector[i];
            }

            score = int(player.sprite.getPosition().x/32);
            if(score > highScore){
                std::ofstream outf(resourcePath() + "Sample.dat");
                outf << std::to_string(score);
                
                outf.close();
            }
            spikeVector.clear();
            tileVector.clear();
            levelVector.clear();
            return 0;
            
        }
        
        
        storedDirection = player.direction;
    
        text.setString("Score\n" + std::to_string(int(player.sprite.getPosition().x/32)) + "M");
        text.setPosition(playerView.getCenter().x - playerView.getSize().x/2 + 1000,playerView.getCenter().y - playerView.getSize().y/2 + 30);
        
        text.setScale(sf::Vector2f(1.2,1.2));
        
        sf::Text text2;
        text2.setFont(font);
        text2.setString("High\n" + std::to_string(highScore)+ "M");
        text2.setPosition(playerView.getCenter().x - playerView.getSize().x/2 + 1200,playerView.getCenter().y - playerView.getSize().y/2 + 30);
        text2.setScale(sf::Vector2f(1.2,1.2));
        
        sf::Text highscoreText;
        highscoreText.setPosition(playerView.getCenter().x - playerView.getSize().x/2 + 920,playerView.getCenter().y - playerView.getSize().y/2 + 30);
        highscoreText.setFont(font);
        window.draw(highscoreText);
        window.draw(text2);
        
        window.draw(text);
        
        window.display();
        storedFrameTime =  frameTime.restart().asSeconds();
    }
    
    
    return EXIT_SUCCESS;
}
int showTitle(sf::RenderWindow & window){
    sf::View titleView;
    titleView.setCenter(0 + window.getSize().x/2, 0 + window.getSize().y/2);
    titleView.setSize(window.getSize().x, window.getSize().y);
    window.setView(titleView);
    
    sf::Texture selectorTexture;
    selectorTexture.loadFromFile(resourcePath() + "Selector.png");
    sf::Sprite selectorSprite;
    selectorSprite.setTexture(selectorTexture);
    sf::Texture nextLevelTexture;
    nextLevelTexture.loadFromFile(resourcePath() + "NewGame.png");
    sf::Texture skylineTexture;
    skylineTexture.loadFromFile(resourcePath() + "Skyline.png");
   
    sf::Sprite skyline;
    skyline.setScale(15, 15);
    skyline.setTexture(skylineTexture);
    skyline.setPosition(700 - 350, 200);
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "arcadeclassic.regular.ttf");
    sf::Text newGameText;
    
    
    selectorSprite.setPosition(600, 706);
    
    while (window.isOpen())
    {
        sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return){
            return 1;
        }
        
        }
        
        window.clear(sf::Color::Black);
        
        newGameText.setPosition(620, 690);
        newGameText.setFont(font);
        newGameText.setString("New Game");
        
        window.draw(newGameText);
        window.draw(newGameText);

        
        window.draw(skyline);
        
        window.draw(selectorSprite);
        
        
        window.display();

    }
    
    
}
int showEndScreen(sf::RenderWindow &window, int score){
    sf::View titleView;
    titleView.setCenter(0 + window.getSize().x/2, 0 + window.getSize().y/2);
    titleView.setSize(window.getSize().x, window.getSize().y);
    window.setView(titleView);
    
    sf::Texture selectorTexture;
    selectorTexture.loadFromFile(resourcePath() + "Selector.png");
    sf::Sprite selectorSprite;
    selectorSprite.setTexture(selectorTexture);
    sf::Texture nextLevelTexture;
    nextLevelTexture.loadFromFile(resourcePath() + "NewGame.png");

    
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "arcadeclassic.regular.ttf");
    sf::Text newGameText;
   
    std::ifstream inf(resourcePath() + "Sample.dat");
    std::string string;
    getline(inf,string);
    sf::Text record;
    record.setFont(font);
    if(inf){
        record.setString("High Score  " + string + "\n" + "Score  " + std::to_string(score));
    }else{
        record.setString("High Score  0 \nScore  " + std::to_string(score));
    }
    record.setPosition(600, 400);

    inf.close();

    
    selectorSprite.setPosition(600, 603);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)) {
                window.close();
                return 0;
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return){
                return 1;
            }
            
        }
        
        window.clear(sf::Color::Black);
        
        newGameText.setPosition(620, 590);
        newGameText.setFont(font);
        newGameText.setString("New Game");
        window.draw(record);
        window.draw(newGameText);
        window.draw(selectorSprite);
        srand(time(0));
        window.display();
        
    }
    
}

int main(int, char const**)
{
    
    sf::RenderWindow window(sf::VideoMode(1400, 851), "SkyLines", sf::Style::Default);
    window.setKeyRepeatEnabled(false);
    int mode = 1;
    if(mode){
        window.setVerticalSyncEnabled(true);
    }else{
        window.setVerticalSyncEnabled(true);
    }
    if(!showTitle(window)){
        return EXIT_SUCCESS;
    }
    
    bool gameClosed = 0;
    while (gameClosed != 1){
        int score = 0;
        gameClosed = startLevel(window, score,mode);
        if(!showEndScreen(window, score)){
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
    

}


