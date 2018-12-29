#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct MidiNote {
   //in ticks
   int tick;
   int duration;
   sf::Uint8 note;
};

class Song {
   int tpq;
   std::vector<MidiNote> notes;
   std::string filename;
public:

};

class PlayableSong {
   sf::Music song;
   struct NoteSpawns {
      sf::Time spawn;
      sf::Time duration;
      NoteTypes button;

   };

public:

};



int main(int argc, char** argv) {
   if(argc < 2) {
      printf("Include Filename\n");
      return 0;
   }
   // Array of line numbers each line being no more than 100 chars
   char thearray[1000][100];
   char finarray[1000][100];
   int counter = 0;
   // Open our file
   std::ifstream inFile(argv[1], std::ifstream::in);
   // If we can read/write great
   if (inFile.good()) {
      // Read throuthe file and load into array
      while (!inFile.eof() && (counter < 1000)) {
         inFile.getline(thearray[counter],100);
         counter++;
      }
      bool flag = false;
      int tick = -1;
      int count = 0;
      std::string::size_type sz;   // alias of size_t
      // Loop through the array which we just put together
      for (int i = 0; i < counter; i++) {
         //printf("Line #%d\n", i);
         std::string s (thearray[i]);
         std::string s1 (thearray[i+1]);
         int s2 = -1;
         std::vector<std::string> result;
         std::istringstream iss(s);
         for(std::string s; iss >> s; ) {
            result.push_back(s);
         }
         std::vector<std::string> result1;
         std::istringstream iss1(s1);
         for(std::string s1; iss1 >> s1; ) {
             result1.push_back(s1);
         }
         if(flag) {
            //printf("_1\n");
            try {
               if(result.size() != 0) {
                  tick = std::stoi(result[0], &sz);
               }
               else {
                  tick = -1;
               }
            }
            catch (const std::invalid_argument& ia) {
               printf("failed\n");
            }
            //printf("_2\n");
            try {
               if(result1.size() != 0) {
                  s2 = std::stoi(result1[0], &sz);
               }
               else {
                  s2 = -1;
               }
            }
            catch (const std::invalid_argument& ia) {
               printf("failed\n");
            }
            //printf("_3\n");
            if(tick != s2) {
               for(int k = 0; k < 100; k++) {
                  finarray[count][k] = thearray[i][k];
               }
               //printf("%s\n", finarray[count]);
               count++;
            }
         }
         if(result.size() != 0) {
            //printf("%s\n", result[0].c_str());
            if(result[0] == "Tick") {
               //printf("changing flag to true\n");
               flag = true;
            }
         }
         else {
            //printf("changing flag to false\n");
            flag = false;
         }
      }
      // Loop through the array which we just put together
      for (int i = 0; i < count; i++) {
         std::cout << finarray[i] << std::endl;
      }
   }
   inFile.close();

   return 0;
}
