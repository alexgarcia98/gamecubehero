
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
// method resourcePath() from ResourcePath.hpp
//

#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MidiFile.h"
#include "Options.h"

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "NoteManager.h"
#include "PlayableSong.h"
#include "Lanes.h"
#include "ButtonMapping.h"

template <typename T>
std::string to_string(const T x, int precision) {
    std::stringstream s;
    s.precision(precision);
    s<<std::fixed<<x;
    return s.str();
}

sf::Time hertz(float x) {
    return sf::seconds(1.f/x);
}

int main(int argc, char const** argv) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);

    smf::MidiFile midifile;
    std::string mainPath="C:/Users/alexgarcia98/midihero-master/GamecubeHero/GamecubeHero/";
    int track = 0;
    int endtrack = 1;
    int tracklist [10];
    tracklist[0] = 0;
    int tracklength = 1;

    sf::Time extraDelay = sf::milliseconds(0);
    sf::Time reduceDelay = sf::milliseconds(150);
    std::string file=
    // Beginner
    // "alphabet_songvoice"; track = 1; endtrack = 2;

    // Easy
    // "LastSurprise"; // Melody
    // "Mii";
    // "BrambleBlast"; track = 5; endtrack = 7;



    // Medium
    //"LifeWillChange"; // HS: 59175 - Alex
    // "LifeWillChange2"; reduceDelay=sf::milliseconds(700);
    // "LastSurprise"; track = 1; endtrack = 2; // Piano
    // "LastSurprise2"; track = 1; endtrack = 2; reduceDelay=sf::milliseconds(850); // Surprising HS: 30950 - Alex
    // "FurElise";
    // "TheEntertainer";



    // Hard
    // "FountainOfDreams"; track = 0; endtrack = 1;
    // "HesAPirate";
    // "CharlieBrown";
    // "FloweringNight";
    // "FlightOfTheBumblebee";


    // Expert


    // Master
    // "FreedomDive";

    //std::string file="passion";
    //std::string file="KHMedley";
    //"FaceMyFears"; track = 1; endtrack = 2;
    //"RiversInTheDesert";
    //"BigBlue"; track = 1; endtrack = 2;
    //"GladItsOver";
    //"Disney";
    //"PalletTown";
    //"Melee";
    //"CliffsOfDover"; track = 12; endtrack = 13;
    //"SouljaBoy"; track = 0; endtrack = 1;
    //"SongOfStorms"; track = 2; endtrack = 3;
    //"SmashUltimate";
    //"ThroughTheFireAndTheFlames"; track = 1; endtrack = 2;
    //std::string file="5PM";
    //std::string file="SadnessAndSorrow";

    // "MIDIlovania";

    // right
    // tracklist[0] = 2; tracklist[1] = 5; tracklist[2] = 12;
    // tracklength = 3;

    // high right
    // tracklist[0] = 7; tracklist[1] = 10; tracklist[2] = 11;
    // tracklength = 3;

    // right??
    // tracklist[0] = 2; tracklist[1] = 9; tracklist[2] = 16; tracklist[3] = 17;
    // tracklength = 4;

    // ???
    // tracklist[0] = 3; tracklist[1] = 4; tracklist[2] = 8; tracklist[3] = 16;
    // tracklength = 4;

    // left
    // tracklist[0] = 13; tracklist[1] = 14; tracklist[2] = 15; tracklist[3] = 18;
    // tracklength = 4;

    //std::string file="RondoAllaTurca";
    //std::string file="BohemianRhapsody";
    //std::string file="GoingToCalifornia";
    //std::string file="MrBlueSky";
    //std::string file="StairwayToHeaven";
    //std::string file="TokyoGhoul";
    //"BangBangBang"; track = 5; endtrack = 6;
    //std::string file="GeraltOfRivia";
    //std::string file="ThankUNext";
    //std::string file="WishYouWereGay";
    //"SeptetteForTheDeadPrincess";
    //"RenaiCirculation";
    //"RollingInTheDeep";
    //std::string file="LadyCupid";
    //track = 1; endtrack = 2; // melody
    //track = 3; endtrack = 4; //harmony
    //"HotelCalifornia";
    //"NightOfFire"; track = 5; endtrack = 6;
    //"The_Eagles_-_Hotel_California";
    //"RiversInTheDesert2";
    //"MirorBXD";
    //"MirorB2";
    //"PkmnXDGoDMirorB"; track = 9; endtrack = 10; // melody
    //"Junes";
    //"layercake"; track = 1; endtrack = 3; // melody
    //"TheEndInTheWorld";
    "PersonaExams"; track = 2; endtrack = 3; // melody
    tracklist[0] = 2; tracklength = 1;
    //"Passion2"; track = 2; endtrack = 3; // right
    //"Passion2"; track = 3; endtrack = 4; // left
    //"Passion2"; track = 2; endtrack = 4; // both

    // Shokugeki
    //"KibouNoUta"; track = 1; endtrack = 2; // melody
    //"Spice"; track = 2; endtrack = 3; // melody
    //"GodTongue";
    //"Snowdrop"; track = 2; endtrack = 3; // melody
    //"TheSecretIngredientCalledVictory";
    //"Braver";
    //"Symbol"; track = 1; endtrack = 2; // melody
    //"RisingRainbow"; track = 1; endtrack = 2; // melody
    //"Atria1";
    //"Atria2";

    // Persona
    //"Alleycat"; track = 2; endtrack = 3; // melody
    //"LastSurprise3"; track = 2; endtrack = 3; // melody
    //"TheDaysWhenMyMotherWasThere"; track = 2; endtrack = 3; // melody
    //"TheWhimsOfFate"; track = 2; endtrack = 3; // melody
    //"SwearToMyBones"; track = 2; endtrack = 3; // melody
    //"ButterflyKiss"; track = 2; endtrack = 3; // melody
    //"MassDestruction"; track = 2; endtrack = 3; // melody
    //"BarCrossroads"; track = 2; endtrack = 3; // melody
    //"Phantom"; track = 2; endtrack = 3; // melody
    //"KimiNoKioku"; track = 2; endtrack = 3; // melody
    //"BurnMyDread"; track = 2; endtrack = 3; // melody
    //"HeartfulCry"; track = 2; endtrack = 3; // melody
    //"TheBattleForEveryonesSouls"; track = 2; endtrack = 3; // melody
    //"BeneathTheMask"; track = 2; endtrack = 3; // melody
    //"Price"; track = 2; endtrack = 3; // melody

    // Hat
    // "TrainRush";

    // left
    // tracklist[0] = 1; tracklist[1] = 13;
    // tracklist[2] = 15; tracklist[3] = 20;
    // tracklength = 4;

    // right
    // tracklist[0] = 2; tracklist[1] = 5; tracklist[2] = 6; tracklist[3] = 7;
    // tracklist[4] = 8; tracklist[5] = 9; tracklist[6] = 10; tracklength = 7;

    // ???
    // tracklist[0] = 3; tracklist[1] = 4;
    // tracklist[2] = 12; tracklist[3] = 14;
    // tracklist[4] = 16; tracklist[5] = 17;
    // tracklist[6] = 18; tracklist[7] = 19;
    // tracklength = 8;

    //"YourContractHasExpired"; track = 1; endtrack = 2; // melody
    //"TheBattleOfAward42"; track = 1; endtrack = 2; // melody HS: 52325 alex

    sf::Font font;
    font.loadFromFile(mainPath+"sansation.ttf");

    sf::Text text("", font, 24);
    text.setPosition(10, 5);

    if(argc==0) {
        midifile.read(std::cin);
    }
    else {
        midifile.read(mainPath+"music/"+file+".mid");
    }
    midifile.doTimeAnalysis();
    midifile.linkNotePairs();

    //generate song from midifile
    PlayableSong song(midifile, mainPath+"music/"+file+".ogg", track, endtrack, tracklist, tracklength);
    Lanes lanes;
    float songSpeed=250.f;//1.f/song.getTicksPerQuarter()*57600*4;//250.f;
    std::cout<<"song.tpq="<<song.getTicksPerQuarter()<<std::endl;
    float smackZoneY=500.f;

    srand(unsigned(time(NULL)));

    sf::Texture& backgroundTex=ResourceManager::getTexture(mainPath+"gradient"+std::to_string((int)rand()%5)+".png");
    sf::Sprite background;
    background.setTexture(backgroundTex);
    background.setScale(window.getSize().x/(float)backgroundTex.getSize().x,
                        window.getSize().y/(float)backgroundTex.getSize().y);

    // Set the Icon
    sf::Image icon;
    if(!icon.loadFromFile(mainPath + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    NoteManager noteManager(smackZoneY);
    for(int i=0;i<10;i++) {
        //Note note = note_to_type(Song.notes[i].note));
        //noteManager.addNote(note);
        //noteManager.addNote(new Note(static_cast<NoteTypes>(rand()%NoteTypes::COUNT), sf::Vector2f(rand()%800, 0), 12));
    }
    //noteManager.addNote(new Note(NoteTypes::X, sf::Vector2f(45, 0), songSpeed));


    ButtonMapping* buttonMapping=new ButtonMappingPS3(&noteManager);


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
    sf::Time playMusicTime=noteSpawnDelay+song.getFirstSpawn(midifile, mainPath+"music/"+file+".ogg").spawnTime-reduceDelay+extraDelay;//add songoffset to noteSpawnDelay
    //sf::Time playMusicTime=noteSpawnDelay;//+sf::seconds(1.33f);
    //sf::Time noteSpawnTimer=curr+noteSpawnDelay;
    bool startedPlayingSong=false;
    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;

    const sf::Time fpsUpdateDelay=hertz(10);//sf::seconds(1.f/10);

    sf::Time deltaLow=  sf::Time::Zero;
    sf::Time deltaHigh= sf::seconds(1.f);
    sf::Time deltaSum=  sf::Time::Zero;
    int deltaCount=0;
    sf::Time fpsTimer=  fpsUpdateDelay;

    // Start the game loop
    while(window.isOpen()) {
        prev=curr;
        curr=clock.getElapsedTime();
        const sf::Time delta=curr-prev;

        fpsTimer+=delta;
        deltaSum+=delta;
        deltaCount++;
        if(delta>deltaLow) {
            deltaLow=delta;
        }
        if(delta<deltaHigh) {
            deltaHigh=delta;
        }
        if(fpsTimer>=fpsUpdateDelay) {
            fpsTimer%=fpsUpdateDelay;
            //display values
            text.setString("fps: "+to_string(1.f/(deltaSum/(float)deltaCount).asSeconds(), 1)+
                           "\nhi:    "+to_string(1.f/deltaHigh.asSeconds(), 1)+
                           "\nlo:    "+to_string(1.f/deltaLow.asSeconds(), 1));
            //reset highs and lows
            deltaSum=sf::Time::Zero;
            deltaCount=0;
            deltaLow=delta;
            deltaHigh=delta;
        }
        text.setString(std::to_string((sf::Uint64)(noteManager.getScore().getScore()))+" Points\n"
            +std::to_string(noteManager.getScore().getCurrentMultiplier())+".0x Mult\n"
            +"\nNote Accuracy: "+std::to_string(noteManager.getScore().getHitAccuracy())+"%"
            +"\nEffective Accuracy: "+std::to_string(noteManager.getScore().getEffectiveAccuracy())+"%"
            +"\nCurrent Streak: "+std::to_string(noteManager.getScore().getCurrentStreak())
            +"\nLongest Streak: "+std::to_string(noteManager.getScore().getLongestStreak()));

        // Process events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Close window: exit
            if(event.type==sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                noteManager.onInputDown(X);
            }
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
                    //std::cout<<"dpad: right"<<std::endl;
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
                    //std::cout<<"dpad: left"<<std::endl;
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
                    //std::cout<<"dpad: up"<<std::endl;
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
                    //std::cout<<"dpad: down"<<std::endl;
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
                noteManager.addNote(new LongNote(spawns[i].button, spawns[i].tickSig, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed, spawns[i].duration));
                //noteManager.addNote(new Note(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed));
            }
            else {
                noteManager.addNote(new Note(spawns[i].button, spawns[i].tickSig, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed));
            }
        }

        // Clear screen
        window.clear();

        window.draw(background);
        window.draw(smackZone);

        noteManager.draw(window);
        if(noteManager.getFirst()!=nullptr) {
            //text.setString(std::to_string(noteManager.getFirst()->getPos().y));

            //text.setString(std::to_string((int)(1.f/(curr-prev).asSeconds())));
        }
        window.draw(text);
        noteManager.update(curr-prev);

        // Update the window
        window.display();
    }

    delete buttonMapping;

    return EXIT_SUCCESS;
}
