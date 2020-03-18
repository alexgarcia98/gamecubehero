//
//  Score.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 3/30/19.
//  Copyright © 2019 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__Score__
#define __GamecubeHero__Score__

#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Config.hpp>

class Score {
    const float hitScore=25.f;
    const int maxMult=4;
    float getMult() const {
        if(streak<(maxMult-1)*10) {
            return streak/10+1;
        }
        return maxMult;
    }
    void checkStreak() {
        if(streak>longestStreak) {
            longestStreak=streak;
        }
    }

    double scoref=0;
    sf::Uint64 streak=0;
    sf::Uint64 longestStreak=0;
    sf::Uint64 misses=0;
    sf::Uint64 hits=0;
    double total=0;
    struct chord {
        int t_sig;
        int hit_count;
        int miss_count;
    };
    std::vector<chord> chords;
    void add(int t_sig, bool hit) {
        for(int i=0;i<chords.size();i++) {
            if(chords[i].t_sig==t_sig) {
                if(hit) {
                    chords[i].hit_count++;
                }
                else {
                    chords[i].miss_count++;
                }
                return;
            }
        }
        chords.push_back({t_sig, hit, !hit});
    }
public:
    Score() {
        streak=0;
    }
    int getCurrentMultiplier() const {
        return getMult();
    }
    double getScore() const {
        return scoref;
    }
    sf::Uint64 getMisses() const {
        return misses;
    }
    sf::Uint64 getLongestStreak() const {
        return longestStreak;
    }
    sf::Uint64 getCurrentStreak() const {
        return streak;
    }
    int getHitAccuracy() const {
        if(total != 0)
            return (hits / total) * 100;
        else
            return 100;
    }
    int getEffectiveAccuracy() const {
        if(total != 0) {
            int value = ((total - misses) / total) * 100;
            if(value < 0)
                return 0;
            else
                return value;
        }
        else
            return 100;
    }

    void hit(int t_sig) {
        add(t_sig, true);
        hits++;
        total++;
    }
    void miss(int t_sig) {
        add(t_sig, false);
        misses++;
    }
    void updateTotal() {
        total++;
    }
    void update() {
        std::sort(chords.begin(), chords.end(), [](chord& lhs, chord& rhs) {
            return lhs.t_sig<rhs.t_sig;
        });
        for(int i=0;i<chords.size();i++) {
            //current mult * hits
            for(int j=0;j<chords[i].hit_count;j++) {
                //hit a single note!
                streak++;
                checkStreak();
                //score += current mult * one hit score
                scoref+=getMult()*hitScore;
            }

            //if any misses, set streak to 0 and mult to 1
            if(chords[i].miss_count>0) {
                streak=0;
            }
        }
        chords.clear();
    }
};

#endif /* defined(__GamecubeHero__Score__) */
