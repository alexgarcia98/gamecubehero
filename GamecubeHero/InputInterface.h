//
//  InputInterface.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 4/1/19.
//  Copyright © 2019 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__InputInterface__
#define __GamecubeHero__InputInterface__

#include <iostream>
#include "NoteTypes.h"

class InputInterface {
public:
    virtual void onInputDown(NoteTypes button)=0;
    virtual void onInputUp(NoteTypes button)=0;
    virtual ~InputInterface() { }
};


#endif /* defined(__GamecubeHero__InputInterface__) */
