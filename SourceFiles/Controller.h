//
//  Controller.h
//  StealthPlatformer
//
//  Created by James Vaughan Craster on 13/10/2016.
//  Copyright (c) 2016 James Vaughan Craster. All rights reserved.
//

#ifndef __Platformer2__Controller__
#define __Platformer2__Controller__

#include <stdio.h>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum Controller{
    JUMP = 0,
    FIRE = 1
    
};

class ControllerController{
private:
    std::vector<bool> isPressed{0,0,0,0,0};
    std::vector<bool> wasPressedOneFrameAgo{0,0,0,0,0};
public:
    bool isButtonHeld(int index){
        return isPressed[index];
    }
    bool wasReleased(int index){
        return (!isPressed[index] && wasPressedOneFrameAgo[index]);
    }
    bool wasPressed(int index){
        return (isPressed[index] && !wasPressedOneFrameAgo[index]);
    }
    void getInput(){
        wasPressedOneFrameAgo = isPressed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            isPressed[Controller::JUMP] = 1;
        }else{
            isPressed[Controller::JUMP] = 0;
        }
    }
};
#endif /* defined(__Platformer2__Controller__) */
