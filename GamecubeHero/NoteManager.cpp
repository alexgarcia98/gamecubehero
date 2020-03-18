//
//  NoteManager.cpp
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#include "NoteManager.h"

void NoteManager::update(sf::Time delta) {
    //check for notes off the screen and missed notes
    //if it's past smack bar, and it hasn't been counted, it is now a missed note
    for(int i=0;i<notes.size();i++) {
        notes[i]->update(delta);
        if(notes[i]->getPos().y>smackCenter+SMACKSIZE) {
            //missed note
            if(!notes[i]->wasMissed()) {
                //count this missed note
                score.miss(notes[i]->getTickSig());
                score.updateTotal();
                notes[i]->setMissNote();
            }
        }
        if(!notes[i]->isLong()&&notes[i]->getPos().y>700.f) {
            notes.erase(notes.begin()+i);
            i--;
        }
    }
    score.update();
}

void NoteManager::onInputDown(NoteTypes button) {
    //find bottom most one that isn't dead in button's lane
    Note* bottom=nullptr;
    int saved=-1;
    for(int i=0;i<notes.size();i++) {
        if(notes[i]->getType()==button) {
            //check if not dead
            if(notes[i]->getPos().y<smackCenter+SMACKSIZE) {
                if(bottom==nullptr||notes[i]->getPos().y>bottom->getPos().y) {
                    bottom=notes[i];
                    saved=i;
                }
            }
        }
    }
    if(bottom!=nullptr) {
        //std::cout<<"smackCenter: "<<smackCenter<<", bottom.y: "<<bottom->getPos().y<<std::endl;
        float s=bottom->smack(smackCenter-bottom->getPos().y);
        if(s==-1.f) {
            //MISS
            //std::cout<<"MISS"<<std::endl;
            //instant score demult
            //update all prior notes
            score.update();
            //set streak to 0
            score.miss(0);//anywhere
            score.update();
        }
        else {
            //HIT
            //remove it from list
            score.hit(bottom->getTickSig());
            notes.erase(notes.begin()+saved);
            //std::cout<<"HIT: ";
            //std::cout<<bottom->getPos().y-smackCenter;
            //std::cout<<", s="<<s<<std::endl;
            delete bottom;
        }
    }
}
void NoteManager::onInputUp(NoteTypes button) {
    //find bottom most one that isn't dead in button's lane

}
