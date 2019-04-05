//
//  NoteManager.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__NoteManager__
#define __GamecubeHero__NoteManager__

#include <iostream>
#include <vector>
#include "Note.h"
#include "Score.h"
#include "InputInterface.h"

class NoteManager:public InputInterface {
    std::vector<Note*> notes;
    float smackCenter;
    Score score;
public:
    NoteManager(float smackCenter):smackCenter(smackCenter) { }
    void addNote(Note* note) { notes.push_back(note); }
    void update(sf::Time delta);
    const Score& getScore() {
        return score;
    }
    void draw(sf::RenderTarget& window) {
        for(int i=0;i<notes.size();i++) {
            notes[i]->draw(window);
        }
    }
    
    Note* getFirst() { if(notes.size()>0) { return notes[0]; } else { return nullptr; } }
    
    virtual ~NoteManager() {
        for(int i=0;i<notes.size();i++) {
            delete notes[i];
        }
    }
    virtual void onInputDown(NoteTypes button) override;
    virtual void onInputUp(NoteTypes button) override;
};

#endif /* defined(__GamecubeHero__NoteManager__) */
