//
//  Note.cpp
//  GamecubeHero
//
//  Created by Hitch Chriscock and Alex and Aaron :) on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#include "Note.h"
#include <cmath>
#include <SFML/Window/Keyboard.hpp>

std::array<std::string, NoteTypes::COUNT> Note::noteTexPaths={
    "twoButton.png",
    "oneButton.png",
    "leftButton.png",
    "upButton.png",
    "downButton.png",
    "rightButton.png",
    "squareButton.png",
    "triangleButton.png",
    "xButton.png",
    "circleButton.png",
    "oneButton.png",
    "twoButton.png"
};

std::array<std::string, NoteTypes::COUNT> LongNote::noteTrailTexPaths={
    "numberLongNote.png",
    "numberLongNote.png",
    "dpadLongNote.png",
    "dpadLongNote.png",
    "dpadLongNote.png",
    "dpadLongNote.png",
    "squareLongNote.png",
    "triangleLongNote.png",
    "xLongNote.png",
    "circleLongNote.png",
    "numberLongNote.png",
    "numberLongNote.png"
};

Note::Note(NoteTypes type, int tickSig, sf::Vector2f pos, float songSpeed):type(type), pos(pos), speed(songSpeed), missed(false) {
    //std::cout<<"Note "<<type<<"="<<NamedNotes::toString(type)<<", noteTexPaths[type]="<<noteTexPaths[type]<<std::endl;
    std::string mainPath="C:/Users/alexgarcia98/midihero-master/GamecubeHero/GamecubeHero/";
    spr.setTexture(ResourceManager::getTexture(mainPath+noteTexPaths[type]));
    spr.setScale(0.3f, 0.3f);
    spr.setOrigin(spr.getTexture()->getSize().x/2,
                  spr.getTexture()->getSize().y/2);
}
float Note::smack(float distance) {
    //if touching at all, kill the note
    //if not touching, lose points, note stays there
    float noteSize=SMACKSIZE;
    //std::cout<<"distance="<<distance<<", smacksize: "<<SMACKSIZE<<std::endl;
    if(std::fabs(distance)<noteSize) {
        //HIT!
        return std::fabs(distance)/noteSize;
    }
    else {
        //MISS
        return -1.f;
    }
}
void Note::release(float distance) {
    
}
void Note::update(sf::Time delta) {
    pos.y+=delta.asSeconds()*speed;
}
void Note::draw(sf::RenderTarget& window) {
    spr.setPosition(pos);
    window.draw(spr);
}

LongNote::LongNote(NoteTypes type, int tickSig, sf::Vector2f pos, float songSpeed, sf::Time duration):Note(type, tickSig, pos, songSpeed), duration(duration) {
    std::string mainPath="C:/Users/alexgarcia98/midihero-master/GamecubeHero/GamecubeHero/";
    longspr.setTexture(ResourceManager::getTexture(mainPath+noteTrailTexPaths[type]));
    
    longspr.setScale(duration.asSeconds()*100.f, 0.3f); //should feel backwards because of rotation
    
    longspr.setOrigin(0.f, longspr.getTexture()->getSize().y/2.f);//+x goes down (equals +y*scale screen)
    longspr.setRotation(-90.f);
    longNote=true;
    
    /*rect.setFillColor(sf::Color::Red);
    rect.setSize(sf::Vector2f(SMACKSIZE, SMACKSIZE));
    rect.setOrigin(rect.getSize()/2.f);*/
}
float LongNote::smack(float distance) {
    float s=Note::smack(distance);
    if(s!=-1.f) {
        //hit
        smacked=true;
    }
    return s;
}
void LongNote::release(float distance) {
    
}
void LongNote::update(sf::Time delta) {
    Note::update(delta);
}
void LongNote::draw(sf::RenderTarget& window) {
    /*rect.setPosition(getPos());
    window.draw(rect);*/
    longspr.setPosition(getPos());
    window.draw(longspr);
    Note::draw(window);
}