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

enum Controller{
    JUMP = 1,
    RIGHT = 2,
    LEFT = 3,
    DOWN = 4,
    FIRE = 5
    
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
    //some 'get input function' in here - depends upon controller type, obviously!
};
#endif /* defined(__Platformer2__Controller__) */
