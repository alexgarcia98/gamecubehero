//
//  ButtonMapping.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 4/1/19.
//  Copyright © 2019 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__ButtonMapping__
#define __GamecubeHero__ButtonMapping__

#include <iostream>
#include <array>
#include <SFML/Window/Event.hpp>
#include "InputInterface.h"

class ButtonMapping {
protected:
    InputInterface* inputInterface;
public:
    ButtonMapping(InputInterface* inputInterface):inputInterface(inputInterface) { }
    virtual ~ButtonMapping() { }
    virtual void onEvent(const sf::Event& event) { }
};

typedef std::array<unsigned int, NoteTypes::COUNT> JoystickButtonMappingArray;

class ButtonMappingJoystick:public ButtonMapping {
    int joystickID;
    JoystickButtonMappingArray arr;
public:
    ButtonMappingJoystick(InputInterface* inputInterface, JoystickButtonMappingArray arr, int joystickID=0):
    ButtonMapping(inputInterface), arr(arr), joystickID(joystickID) { }
    virtual ~ButtonMappingJoystick() { }
    virtual void onEvent(const sf::Event& event) {
        if(event.type==sf::Event::JoystickButtonPressed && event.joystickButton.joystickId==joystickID) {
            for(int i=0;i<NoteTypes::COUNT;i++) {
                if(arr[i]==event.joystickButton.button) {
                    inputInterface->onInputDown(static_cast<NoteTypes>(i));
                    break;
                }
            }
        }
        if(event.type==sf::Event::JoystickButtonReleased && event.joystickButton.joystickId==joystickID) {
            for(int i=0;i<NoteTypes::COUNT;i++) {
                if(arr[i]==event.joystickButton.button) {
                    inputInterface->onInputUp(static_cast<NoteTypes>(i));
                    break;
                }
            }
        }
    }
};

class ButtonMappingPS3:public ButtonMappingJoystick {
public:
    ButtonMappingPS3(InputInterface* inputInterface, int joystickID=0):
    ButtonMappingJoystick(inputInterface, {8, 10, 7, 4, 6, 5, 15, 12, 14, 13, 11, 9}, joystickID) { }
    virtual ~ButtonMappingPS3() { }
};

class ButtonMappingPS4:public ButtonMappingJoystick {
public:
    ButtonMappingPS4(InputInterface* inputInterface, int joystickID=0):
    ButtonMappingJoystick(inputInterface, {6, 4, 8, 11, 9, 10, 0, 3, 1, 2, 5, 7}, joystickID) { }
    virtual ~ButtonMappingPS4() { }
};

#endif /* defined(__GamecubeHero__ButtonMapping__) */
