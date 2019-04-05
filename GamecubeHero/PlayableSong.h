//
//  PlayableSong.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/29/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__PlayableSong__
#define __GamecubeHero__PlayableSong__

#include <iostream>
#include <vector>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Time.hpp>
#include "MidiFile.h"
#include "NoteTypes.h"

struct MidiNote {
    //in ticks
    int tick;
    sf::Time tickTime;
    int duration;
    sf::Time durationTime;
    uint8_t note;
    bool isLong = false;
    bool operator==(const MidiNote& rhs) {
        return tick==rhs.tick && duration==rhs.duration && note==rhs.note;
    }
    struct Compare {
        bool operator()(MidiNote& lhs, MidiNote& rhs) {
            if(lhs.tick==rhs.tick) {
                if(lhs.duration==rhs.duration) {
                    return lhs.note<rhs.note;
                }
                return lhs.duration<rhs.duration;
            }
            return lhs.tick<rhs.tick;
        }
    };
};

struct Song {
    int tpq;
    std::vector<MidiNote> notes;
    std::string filename;
    
};

class PlayableSong {
    sf::Music song;
    struct NoteSpawn {
        sf::Time spawnTime;
        sf::Time duration;
        NoteTypes button;
        bool isLong;
        int tickSig;
    };
    std::vector<NoteSpawn> spawns;
    NoteSpawn makeSpawn(MidiNote& note);
    int tpq;
public:
    PlayableSong(smf::MidiFile& midifile, std::string songPath, int track, int endtrack);
    static NoteTypes note_to_type(int note);
    //add spawn delay to times
    std::vector<NoteSpawn> getSpawns(sf::Time curr, sf::Time prev);
    NoteSpawn getFirstSpawn() { return spawns[0]; }
    void playSong() { song.play(); }
    int getTicksPerQuarter() { return tpq; }
};

#endif /* defined(__GamecubeHero__PlayableSong__) */
