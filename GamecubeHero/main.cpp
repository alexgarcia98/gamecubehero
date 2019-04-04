
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method mainPath from ResourcePath.hpp
//

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MidiFile.h"
#include "Options.h"

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "NoteManager.h"
#include "PlayableSong.h"
#include "Lanes.h"

int main(int argc, char const** argv) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    smf::MidiFile midifile;

    std::string mainPath="C:/Users/alexgarcia98/midihero-master/GamecubeHero/GamecubeHero/";
    int track = 0;
    int endtrack = 1;
    std::string file=
    // Beginner
    "alphabet_songvoice"; track = 1; endtrack = 2;

    // Easy

    // Medium
    // std::string file="LifeWillChange";


    // Hard

    // Expert

    // Master
    //std::string file="FreedomDive";



    //std::string file="passion";
    //std::string file="KHMedley";
    //std::string file="FaceMyFears";
    //std::string file="RiversInTheDesert";
    //std::string file="HesAPirate";
    //std::string file="Mii";
    //std::string file="Disney";
    //std::string file="Melee";
    //std::string file="FountainOfDreams";
    //std::string file="SmashUltimate";
    //std::string file="5PM";
    //std::string file="SadnessAndSorrow";
    //std::string file="lastsurprise"; //track = 1; endtrack = 2;
    //std::string file="MIDIlovania"; track = 3; endtrack = 4;
    //std::string file="CharlieBrown";
    //std::string file="TheEntertainer";
    //std::string file="FurElise";
    //std::string file="RondoAllaTurca";
    //std::string file="BohemianRhapsody";
    //std::string file="GoingToCalifornia";
    //std::string file="MrBlueSky";
    //std::string file="StairwayToHeaven";
    //std::string file="TokyoGhoul";
    //std::string file="BangBangBang";
    //std::string file="GeraltOfRivia";
    //std::string file="ThankUNext";
    //std::string file="WishYouWereGay";
    //std::string file="SeptetteForTheDeadPrincess";
    //std::string file="RenaiCirculation";
    //std::string file="RollingInTheDeep";
    //std::string file="LadyCupid";
    //track = 1; endtrack = 2; // melody
    //track = 3; endtrack = 4; //harmony
    //std::string file="The_Eagles_-_Hotel_California";

    sf::Font font;
    font.loadFromFile(mainPath+"sansation.ttf");

    sf::Text text("", font, 30);

    if(argc==0) {
        midifile.read(std::cin);
    }
    else {
        midifile.read(mainPath+file+".mid");
        //midifile.read(mainPath+"alphabet_songvoice.mid");
    }
    midifile.doTimeAnalysis();
    midifile.linkNotePairs();

    //generate song from midifile
    PlayableSong song(midifile, mainPath+file+".ogg", track, endtrack);
    Lanes lanes;
    float songSpeed=250.f;
    float smackZoneY=500.f;

    srand(unsigned(time(NULL)));

    sf::Texture& backgroundTex=ResourceManager::getTexture(mainPath+"gradient"+std::to_string((int)rand()%6)+".png");
    sf::Sprite background;
    background.setTexture(backgroundTex);
    background.setScale(window.getSize().x/(float)backgroundTex.getSize().x,
                        window.getSize().y/(float)backgroundTex.getSize().y);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(mainPath + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    NoteManager noteManager(smackZoneY-SMACKSIZE);
    for(int i=0;i<10;i++) {
        //Note note = note_to_type(Song.notes[i].note));
        //noteManager.addNote(note);
        //noteManager.addNote(new Note(static_cast<NoteTypes>(rand()%NoteTypes::COUNT), sf::Vector2f(rand()%800, 0), 12));
    }
    //noteManager.addNote(new Note(NoteTypes::X, sf::Vector2f(45, 0), songSpeed));

    sf::RectangleShape smackZone;
    smackZone.setSize(sf::Vector2f(window.getSize().x, SMACKSIZE));
    smackZone.setOrigin(0, smackZone.getSize().y/2.f);
    smackZone.setFillColor(sf::Color(127, 127, 127, 127));
    smackZone.setPosition(0, smackZoneY);

    sf::Clock clock;
    sf::Time prev;
    sf::Time curr=clock.getElapsedTime();

    sf::Time noteSpawnDelay=sf::seconds(5.f);
    sf::Time startTime=curr;
    sf::Time playMusicTime=noteSpawnDelay-sf::seconds(0.25f);//+song.getFirstSpawn().spawnTime;//add songoffset to noteSpawnDelay
    //sf::Time playMusicTime=noteSpawnDelay;//+sf::seconds(1.33f);
    //sf::Time noteSpawnTimer=curr+noteSpawnDelay;
    bool startedPlayingSong=false;
    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;
    // Start the game loop
    while (window.isOpen()) {
        prev=curr;
        curr=clock.getElapsedTime();

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if(event.type==sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                noteManager.onInputDown(X);
            }
            /*
            if(event.type == sf::Event::JoystickButtonPressed) {
                std::cout<<"button: "<<event.joystickButton.button<<std::endl;
                switch(event.joystickButton.button) {
                    case 4:
                        noteManager.onInputDown(UP);
                        break;
                    case 5:
                        noteManager.onInputDown(RIGHT);
                        break;
                    case 6:
                        noteManager.onInputDown(DOWN);
                        break;
                    case 7:
                        noteManager.onInputDown(LEFT);
                        break;
                    case 8:
                        noteManager.onInputDown(L2);
                        break;
                    case 9:
                        noteManager.onInputDown(R2);
                        break;
                    case 10:
                        noteManager.onInputDown(L1);
                        break;
                    case 11:
                        noteManager.onInputDown(R1);
                        break;
                    case 12:
                        noteManager.onInputDown(TRIANGLE);
                        break;
                    case 13:
                        noteManager.onInputDown(CIRCLE);
                        break;
                    case 14:
                        noteManager.onInputDown(X);
                        break;
                    case 15:
                        noteManager.onInputDown(SQUARE);
                        break;
                }
            }
            */

            if(event.type == sf::Event::JoystickButtonPressed) {
                std::cout<<"button: "<<event.joystickButton.button<<std::endl;
                switch(event.joystickButton.button) {
                    case 11:
                        noteManager.onInputDown(UP);
                        break;
                    case 10:
                        noteManager.onInputDown(RIGHT);
                        break;
                    case 9:
                        noteManager.onInputDown(DOWN);
                        break;
                    case 8:
                        noteManager.onInputDown(LEFT);
                        break;
                    case 6:
                        noteManager.onInputDown(L2);
                        break;
                    case 7:
                        noteManager.onInputDown(R2);
                        break;
                    case 4:
                        noteManager.onInputDown(L1);
                        break;
                    case 5:
                        noteManager.onInputDown(R1);
                        break;
                    case 3:
                        noteManager.onInputDown(TRIANGLE);
                        break;
                    case 2:
                        noteManager.onInputDown(CIRCLE);
                        break;
                    case 1:
                        noteManager.onInputDown(X);
                        break;
                    case 0:
                        noteManager.onInputDown(SQUARE);
                        break;
                }
            }


            float xpos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
            float ypos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);

            // right dpad
            if(xpos > 25) {
                if(rightPressed == false) {
                    rightPressed = true;
                    noteManager.onInputDown(RIGHT);
                    std::cout<<"dpad: right"<<std::endl;
                }
            }
            else if (xpos < 25) {
                rightPressed = false;
            }

            // left dpad
            if(xpos < -25) {
                if(leftPressed == false) {
                    leftPressed = true;
                    noteManager.onInputDown(LEFT);
                    std::cout<<"dpad: left"<<std::endl;
                }
            }
            else if (xpos > -25) {
                leftPressed = false;
            }

            // up dpad
            if(ypos > 25) {
                if(upPressed == false) {
                    upPressed = true;
                    noteManager.onInputDown(UP);
                    std::cout<<"dpad: up"<<std::endl;
                }
            }
            else if (ypos < 25) {
                upPressed = false;
            }

            // down dpad
            if(ypos < -25) {
                if(downPressed == false) {
                    downPressed = true;
                    noteManager.onInputDown(DOWN);
                    std::cout<<"dpad: down"<<std::endl;
                }
            }
            else if (ypos > -25) {
                downPressed = false;
            }
        }

        if(curr>=playMusicTime&&!startedPlayingSong) {
            song.playSong();
            startedPlayingSong=true;
        }

        auto spawns=song.getSpawns(curr-startTime, prev-startTime);
        for(int i=0;i<spawns.size();i++) {
            if(spawns[i].isLong) {
                //noteManager.addNote(new LongNote(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed, spawns[i].duration));
                noteManager.addNote(new Note(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed));
            }
            else {
                noteManager.addNote(new Note(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed));
            }
        }

        // Clear screen
        window.clear();

        noteManager.update(curr-prev);
        window.draw(background);
        window.draw(smackZone);

        noteManager.draw(window);
        if(noteManager.getFirst()!=nullptr) {
            text.setString(std::to_string(noteManager.getFirst()->getPos().y));
        }
        window.draw(text);


        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
