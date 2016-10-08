//
//  main.cpp
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 29/08/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include "LevelLoader.h"
#include "Camera.h"
#include <iostream>

void addChain(ChunkChain &chunkChain){
    std::string level2String = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,10,0,0,0,0,0,10,0,0,0,0,10,0,0,0,0n1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0n1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,10n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n";
    
    chunkChain.appendChunk(Chunk(level2String,sf::Vector2f(chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.x + chunkChain.chunkChain[chunkChain.chunkChain.size()-1].size.x,chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.y), sf::Vector2f(20*32,20*32), sf::Vector2f(32,32)));
}

int main(int, char const**)
{
    
    std::string level2String = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,10,0,0,0,0,0,10,0,0,0,0,10,0,0,0,0n1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0n1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0n";
    std::vector<Spike*> spikeVector;
    std::vector<sf::RectangleShape*> tileVector;
    ChunkChain chunkChain;
    //Chunk chunk(level2String,sf::Vector2f(0,0), sf::Vector2f(20*32,20*32), sf::Vector2f(32,32));
    //chunkChain.appendChunk(chunk);
    chunkChain.appendChunk(Chunk("",sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(32,32)));
    auto levelVector = loadLevelFromChunkChain(chunkChain, sf::Vector2f(32,32), spikeVector, tileVector);
    //std::vector<std::vector<int>> levelVector;
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
    
    
    
    Player player(std::vector<AnimationController> {},25,10,23, sf::Vector2f(5,9),sf::Vector2f(-5,-9),sf::Vector2f(10,20),13000/20);
    Enemy enemy(std::vector<AnimationController> {},20,10,23,sf::Vector2f(5,9),sf::Vector2f(5,9),sf::Vector2f(10,20),13000/20);
    
    AnimationController run(std::vector<float> (10,0.5),std::vector<sf::Texture*> {&runNinja1,&runNinja2,&runNinja3,&runNinja4,&runNinja5,&runNinja6,&runNinja7,&runNinja8,&runNinja9,&runNinja10},&player.sprite);
    AnimationController redRun(std::vector<float> (10,0.5),std::vector<sf::Texture*> {&runEnemy1,&runEnemy2,&runEnemy3,&runEnemy4,&runEnemy5,&runEnemy6,&runEnemy7,&runEnemy8,&runEnemy9,&runEnemy10},&enemy.sprite);
    run.active = 1;
    player.animationControllerVector.push_back(run);
    enemy.animationControllerVector.push_back(redRun);
    
    /*sf::Texture standNinja1;
    standNinja1.loadFromFile(resourcePath() + "Ninja with Wind.png", sf::IntRect(0,0,32,32*2));
    sf::Texture standNinja2;
    standNinja2.loadFromFile(resourcePath() + "Ninja with Wind.png", sf::IntRect(32,0,32,32*2));
    sf::Texture standNinja3;
    standNinja3.loadFromFile(resourcePath() + "Ninja with Wind.png", sf::IntRect(32,0,32*2,32*2));
    sf::Texture standNinja4;
    standNinja4.loadFromFile(resourcePath() + "Ninja with Wind.png", sf::IntRect(32*2,0,32*3,32*2));
    AnimationController stand(std::vector<float> {0,0.5,1.0,1.5,2},std::vector<sf::Texture*> {&standNinja1,&standNinja2,&standNinja3,&standNinja4},&player.sprite);
    stand.active = 0;
    player.animationControllerVector.push_back(stand);
     */
    
    player.sprite.setOrigin(5,8);
    player.sprite.setScale(2, 2);
    player.sprite.setPosition(200, 100);
    enemy.sprite.setPosition(300, 300);
    enemy.sprite.setOrigin(5, 8);
    enemy.sprite.setScale(2,2);
    enemy.sprite.setTexture(runEnemy1,true);
    enemy.animationControllerVector[0].active = 1;
    
    sf::Clock jumpClock;
    player.sprite.setTexture(runNinja1,true);
    player.animationControllerVector[0].setAnimationSpeed(4);

    sf::RenderWindow window(sf::VideoMode(1400, 851), "SFML window");
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
    sf::Clock frameTime;
    double storedFrameTime;
    
    sf::Clock cameraClock;
    double cameraTime;
    double cameraAccumulator = 0;
    
    sf::Texture floorTexture;
    floorTexture.loadFromFile(resourcePath() + "FloorTexture.png");
    sf::Texture floorTextureRotated;
    floorTextureRotated.loadFromFile(resourcePath() + "FloorTextureRotated.png");
    
    sf::View playerView(sf::FloatRect(0, 0, 1400, 851));
    window.setView(playerView);
    sf::Vector2f playerViewScrollVector;
    bool mostRecentlyPressed = 1;
    double accumulator = 0;
    const double dt = 1/60.f;
    sf::Vector2f previousPosition = player.sprite.getPosition();
    sf::Vector2f currentPosition = player.sprite.getPosition();
    sf::Vector2f previousAcceleration = sf::Vector2f(0,0);
    sf::Vector2f currentAcceleration = sf::Vector2f(0,0);
    sf::Vector2f previousVelocity = sf::Vector2f(0,0);
    sf::Vector2f currentVelocity = sf::Vector2f(0,0);
    
    sf::CircleShape circle(10);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(100, 100);
    bool storedSouthContact;
    int storedDirection = player.direction;
    bool jumpCutoff = 0;
    sf::RectangleShape rectangle;
    rectangle.setPosition(300,300);
    rectangle.setSize(sf::Vector2f(300,300));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setOrigin(-150,-150);
   
    while (window.isOpen())
    
    {
        // Process events
       
        //fixing my timestep results in poor performance on my macbook. Cutting out this line will fix the physics timestep:
        storedFrameTime = 1/60.f;
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                if(mostRecentlyPressed == 0){
                   // player.physicsController.xVelocity *= pow(0.0,(1/60)/(storedFrameTime));
                    player.physicsController.xVelocity *= 0.15;
                    player.sprite.setScale(2, 2);
                }
                //player.animationControllerVector[0].setCurrentFrame(5);
                mostRecentlyPressed = 1;
            }
            
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
                if(jumpCutoff && player.isJumping){
                    if(player.physicsController.yVelocity < 0){
                        player.physicsController.yVelocity = 0;
                        jumpCutoff = 0;
                    }
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                if(mostRecentlyPressed == 1){
                   player.physicsController.xVelocity *= 0.15 /*pow(0.0,(1/60)/(storedFrameTime))*/;
                    
                }
                
                mostRecentlyPressed = 0;
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W){
                if((player.physicsController.tileCollisionController.southContact || jumpClock.getElapsedTime().asSeconds() < 0.1) && player.isJumping == 0){
                    player.isJumping = 1;
                    player.animationControllerVector[0].active = 0;
                    player.animationControllerVector[0].setCurrentFrame(0);
                    jumpCutoff = 1;
                    player.physicsController.yForce = -450000;
                }
            }else{
                if(!player.physicsController.tileCollisionController.southContact){
                    player.isJumping = 0;
                    
                }
                
            }
        }
        
        
        if(!player.isJumping){
            player.animationControllerVector[0].active = 1;
        }
        if(player.physicsController.tileCollisionController.southContact != storedSouthContact){
            if(player.physicsController.tileCollisionController.southContact == 0){
                jumpClock.restart();
                //player.animationControllerVector[0].setCurrentFrame(5);
            }else{
                player.isJumping = 0;
                //player.animationControllerVector[0].active = 1;
                //player.animationControllerVector[0].setCurrentFrame(5);
            }
        }
        while(chunkChain.chunkChain.size() != 0 && (player.sprite.getPosition().x + playerView.getCenter().x + playerView.getSize().x/2 > chunkChain.chunkChain[chunkChain.chunkChain.size()-1].position.x + chunkChain.chunkChain[chunkChain.chunkChain.size()-1].size.x)){
            addChain(chunkChain);
            levelVector = loadLevelFromChunkChain(chunkChain, sf::Vector2f(32,32), spikeVector, tileVector);
        }
        
        player.animationControllerVector[0].setAnimationSpeed(std::abs(player.physicsController.xVelocity)/50);
        storedSouthContact = player.physicsController.tileCollisionController.southContact;
        window.clear();
        accumulator += storedFrameTime;
            while (accumulator >= dt) {
                sf::Clock physicsTime;
            player.testTileCollisions(tileVector);
            if(mostRecentlyPressed == 1){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    player.direction = 1;
                    player.animationControllerVector[0].update();
                    player.sprite.setScale(2, 2);
                    
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player.direction = -1;
                    player.animationControllerVector[0].update();
                   // player.physicsController.xVelocity *= 0.15;
                    player.sprite.setScale(-2, 2);
                    
                    
                }else
                {
                    player.direction  = 0;
                    player.physicsController.xVelocity *= 0.15;
                    //player.animationControllerVector[0].setCurrentFrame(3);
                }
            }else
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player.direction = -1;
                    player.animationControllerVector[0].update();
                    player.sprite.setScale(-2, 2);
                    
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    
                    player.direction = 1;
                    player.animationControllerVector[0].update();
                    player.sprite.setScale(2, 2);
                    
                    
                }else
                {
                    player.direction  = 0;
                    player.physicsController.xVelocity *= 0.15;

                }
                
            }
            if(storedDirection != player.direction){
                player.physicsController.xVelocity *= 0.40;
            }
                storedDirection = player.direction;
            
            if(player.physicsController.tileCollisionController.southContact){
                player.physicsController.xForce += 10000 * player.direction;
            }else{
                player.physicsController.xForce += 7000 * player.direction;
                
            }
            if(player.physicsController.xVelocity > 600){
                player.physicsController.xVelocity = 600;
            }
            if(player.physicsController.xVelocity < -600){
                player.physicsController.xVelocity = -600;
            }
            if(player.physicsController.yVelocity > 500){
                player.physicsController.yVelocity = 500;
            }
            if(player.physicsController.yVelocity < -500){
                player.physicsController.yVelocity = -500;
            }
            
            if(player.physicsController.tileCollisionController.southContact == 0){
                player.physicsController.yForce += player.physicsController.mass * player.gravity;
                
                
            }else{
                if(std::abs(player.physicsController.xVelocity) < 0.1){
                    player.animationControllerVector[0].setCurrentFrame(3);
                    
                }else{
                    //player.animationControllerVector[0].active = 1;
                    
                }
            }
                if(std::abs(player.physicsController.xVelocity) < 0.1){
                    player.animationControllerVector[0].setCurrentFrame(3);
                    
                }
            player.update(dt,tileVector,mostRecentlyPressed);
            previousAcceleration = currentAcceleration;
            previousVelocity = currentVelocity;
            currentAcceleration.x = player.physicsController.xAcceleration;
            currentAcceleration.y = player.physicsController.yAcceleration;
            currentVelocity.x = player.physicsController.xVelocity;
            currentVelocity.y = player.physicsController.yVelocity;
                previousPosition = currentPosition;
                 circle.move(10,0);
                currentPosition = circle.getPosition();
             
                
            accumulator -= dt;
        }
        for(int x = 0; x < spikeVector.size(); x++){
            if(player.boundingBox.intersects(spikeVector[x]->collisionBox)){
                window.close();
            }
        }
        
        const double alpha = accumulator/dt;
        circle.setPosition(lerp(currentPosition.x,previousPosition.x,alpha), lerp(currentPosition.y,previousPosition.y,alpha));
       
       
        cameraTime = storedFrameTime;
        
        positionView(playerView, player.sprite.getPosition(), cameraTime);
        //still problems with corners!!
        enemy.update(tileVector);
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Red);
        window.setView(playerView);
        for(int i = 0; i < tileVector.size(); i++){
            //window.draw(*tileVector[i]);
           // tileVector[i]->move(-1, 0);
        }
        //take spikes into account!
        drawFloorSpriteFromLevelVector(levelVector, floorTexture, floorTextureRotated, window);
        
        
        
        enemy.animationControllerVector[0].update();
        for (int x = 0; x < spikeVector.size(); x++){
            spikeVector[x]->spikeSprite.setTexture(spikeTexture);
            window.draw(spikeVector[x]->spikeSprite);
        }
        window.draw(player.sprite);
        window.display();
        storedFrameTime =  frameTime.restart().asSeconds();
    }
    
    return EXIT_SUCCESS;
}
