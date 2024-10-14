// This program is to create a randomised player creator for Dungeons and Dragons tabletop game.
/* While this program does contradict the fantasy genre of DND, often times new players may find it 
difficult to come up with a character, especially if they lack the imagination. Thus, I created this
program to ease your burden. You're Welcome. */  

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <unistd.h>
#include <stdlib.h> 
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <ctype.h>

std::string nameGenerator(){
    std::srand(std::time(0));
    int incrementerNum = 1 + std::rand() % 2;
    const std::string vowels = "aeiou";
    const std::string consonants = "bcdfghjklmnpqrstvwxyz";
    std::string name = "";
    int nameLength = 4 + std::rand() % 4;
    for (int i = 0; i <= nameLength; i++){
        int charType = std::rand()%2;
        if (charType == 0){
            for (int j = 0; j < incrementerNum; j++){
                name += vowels[std::rand()%5];
            }
        } else if (charType == 1) {
            for (int j = 0; j < incrementerNum; j++){
                name += consonants[std::rand()%consonants.size()];
            }
        } else {
            continue;
        }

        if (islower(name[0])){
            name[0] = std::toupper(name[0]);
        }
    }

    std::string title[8] = {"The Slayer", "The Warrior", "The Nimble", "The Lightweight", "The Wise", "The Cunning", "The Guardian", "The Restless"};
    name += (' ' + title[std::rand()%8]);
    return name;
}

int main(){
    bool viewState = true;  // Properly initialize bool
    int mainMenuChoice;

    // Starting screen
    std::cout << "Welcome to Dungeons and Dragons (DND) Player Creator!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "1. New Character" << std::endl;
    std::cout << "2. Randomiser Settings" << std::endl;
    std::cout << "3. Abort Program" << std::endl;
    std::cout << "Please enter a choice: ";
    std::cin >> mainMenuChoice;

    switch (mainMenuChoice){
        case 1:
            std::cout << "Player chose option \"1\", proceeding to New Character screen" << std::endl;
            sleep(3);
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #else 
                system("clear");
            #endif
            char answer;  // Declare the variable
            std::cout << "Your Character Details:" << std::endl;
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "Name: " << nameGenerator() << std::endl;
            while (viewState) {
                std::cout << "Stop viewing? [Y/N]" << std::endl;
                std::cin >> answer;
                answer = toupper(answer);
                if (answer == 'Y') {
                    viewState = false;
                } else {
                    sleep(10);  // If not, wait for 10 seconds
                }
            }
            break;
        case 2:
            std::cout << "Player chose option \"2\", proceeding to Settings screen." << std::endl;
            break;
        case 3:
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #else 
                system("clear");
            #endif
            std::cout << "Player chose option \"3\", awaiting program abortion..." << std::endl;
            sleep(1);
            std::cout << "Aborting in 3..." << std::endl;
            sleep(1);
            std::cout << "Aborting in 2..." << std::endl;
            sleep(1);
            std::cout << "Aborting in 1..." << std::endl;
            sleep(1);
            std::cout << "Program aborted!";
            sleep(2);
            break;
        default:
            std::cout << "Please enter a valid answer!";
            break;
    }

    return 0;
}