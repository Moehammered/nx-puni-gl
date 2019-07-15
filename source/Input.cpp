#include "Input.h"
#include <stdio.h>
//#include <switch\services\hid.h>
#include <switch.h>

puni::Input* puni::Input::_instance = nullptr;

void puni::Input::Initialise()
{
    //init code goes here for touch stuff later/player config
}

puni::Input* const puni::Input::Instance()
{
    if(!_instance)
        _instance = new Input();
    
    return _instance;
}

void puni::Input::RecordState() ///might be redundent if hid already has the polling functionality
{
    hidScanInput();
    // Instance()->lastKeyState = Instance()->currKeyState;
    // Instance()->currKeyState = hidKeysDown(CONTROLLER_P1_AUTO);
}

bool puni::Input::IsKeyHeld(unsigned int key)
{
    return key & hidKeysHeld(CONTROLLER_P1_AUTO);
}

bool puni::Input::IsKeyPressed(unsigned int key)
{
    return (key & hidKeysDown(CONTROLLER_P1_AUTO)) /*& !(key & Instance()->lastKeyState)*/;
}

bool puni::Input::IsKeyReleased(unsigned int key)
{
    return key & hidKeysUp(CONTROLLER_P1_AUTO);
}

puni::Input::Input() {printf("Creating Input Instance.\n\n");}

puni::Input::~Input() {printf("Destroying Input Instance.\n\n");}