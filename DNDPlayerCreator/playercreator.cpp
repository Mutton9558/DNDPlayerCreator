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
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <ctype.h>
#include <conio.h>
#include <cctype> // for isalpha function
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

// Name generation function.
std::string nameGenerator()
{
    std::srand(std::time(0));
    int incrementerNum = 1 + std::rand() % 2;
    const std::string vowels = "aeiou";
    const std::string consonants = "bcdfghjklmnpqrstvwxyz";
    std::string name = "";
    int nameLength = 4 + std::rand() % 4;
    for (int i = 0; i <= nameLength; i++)
    {
        int charType = std::rand() % 2;
        if (charType == 0)
        {
            for (int j = 0; j < incrementerNum; j++)
            {
                name += vowels[std::rand() % 5];
            }
        }
        else if (charType == 1)
        {
            for (int j = 0; j < incrementerNum; j++)
            {
                name += consonants[std::rand() % consonants.size()];
            }
        }
        else
        {
            continue;
        }

        if (islower(name[0]))
        {
            name[0] = std::toupper(name[0]);
        }
    }

    std::string title[8] = {"The Slayer", "The Warrior", "The Nimble", "The Lightweight", "The Wise", "The Cunning", "The Guardian", "The Restless"};
    name += (' ' + title[std::rand() % 8]);
    return name;
}

// Race Generation Function
std::string raceGenerator()
{

    int traitAnswer;
    int dwarfChance = 0;
    int elfChance = 0;
    int halflingChance = 0;
    int humanChance = 0;
    std::string raceSelection[4] = {"Dwarf", "Elf", "Halfling", "Human"};

    std::cout << "Do you prefer a short, medium or tall character? [1 for Short, 2 for Medium and 3 for Tall]" << std::endl;
    std::cin >> traitAnswer;
    if (traitAnswer == 1)
    {
        dwarfChance += 1;
        halflingChance += 1;
    }
    else if (traitAnswer == 2)
    {
        humanChance += 1;
    }
    else if (traitAnswer == 3)
    {
        elfChance += 1;
    }
    else
    {
        std::cout << "Invalid answer!" << std::endl;
        return "Idiot";
    }

    std::cout << "What is a more desirable trait? Resilience, Speed or a mix of both? [1 for Resilience, 2 for Speed and 3 for both]" << std::endl;
    std::cin >> traitAnswer;
    if (traitAnswer == 1)
    {
        dwarfChance += 1;
    }
    else if (traitAnswer == 2)
    {
        halflingChance += 1;
    }
    else if (traitAnswer == 3)
    {
        humanChance += 1;
        elfChance += 1;
    }
    else
    {
        std::cout << "Invalid answer!" << std::endl;
        return "Idiot";
    }

    std::cout << "In the face of danger, would you: " << std::endl;
    std::cout << "1. Charge head on!" << std::endl;
    std::cout << "2. Devise a strategy." << std::endl;
    std::cout << "3. Sneak past danger." << std::endl;
    std::cout << "4. Run away." << std::endl;
    std::cout << "Choose an option [1-4]: ";
    std::cin >> traitAnswer;
    if (traitAnswer == 1)
    {
        dwarfChance += 1;
    }
    else if (traitAnswer == 2)
    {
        elfChance += 1;
    }
    else if (traitAnswer == 3)
    {
        halflingChance += 1;
    }
    else if (traitAnswer == 4)
    {
        humanChance += 1;
    }
    else
    {
        std::cout << "Invalid answer!" << std::endl;
        return "Idiot";
    }

    std::cout << "You see a dying sheep down the road, do you let it die or do you help it?" << std::endl;
    std::cout << "1. Let it die" << std::endl;
    std::cout << "2. Save it" << std::endl;
    std::cout << "Choose an option: " << std::endl;
    std::cin >> traitAnswer;

    if (traitAnswer == 1)
    {
        dwarfChance += 1;
        humanChance += 1;
    }
    else if (traitAnswer == 2)
    {
        elfChance += 1;
        halflingChance += 1;
    }
    else
    {
        std::cout << "Invalid answer!" << std::endl;
        return "Idiot";
    }

    int temp = 0;
    int arrOfChances[4] = {dwarfChance, elfChance, halflingChance, humanChance};

    for (int i = 0; i < 4; i++)
    {
        if (i == 3)
        {
            break;
        }
        else if (arrOfChances[temp] < arrOfChances[i + 1])
        {
            temp = i + 1;
        }
        else
        {
            continue;
        }
    }
    return raceSelection[temp];
}

std::string classGenerator(std::string race)
{
    std::string classList[12] = {"Barbarian", "Fighter", "Ranger", "Rogue", "Monk", "Bard", "Paladin", "Sorcerer", "Cleric", "Druid", "Warlock", "Wizard"};
    std::srand(std::time(0));

    if (race == "Dwarf")
    {
        return classList[std::rand() % 3];
    }
    else if (race == "Elf")
    {
        return classList[8 + std::rand() % 4];
    }
    else if (race == "Halfling")
    {
        return classList[2 + std::rand() % 4];
    }
    else
    {
        return classList[std::rand() % 8];
    }
}

int profileSave()
{
    // Open the JSON file
    std::ifstream inFile("profile.json");
    if (!inFile.is_open())
    {
        std::cerr << "Failed to open the JSON file." << std::endl;
        std::cout << "Press enter or enter any key to continue!" << std::endl;
#if defined(_WIN32) || defined(_WIN64)
        _getch();
#else
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores everything until Enter is pressed
#endif
        return 1; // Exit if the file cannot be opened
    }

    json jArray;
    inFile >> jArray; // Assuming the JSON file contains an array of arrays
    inFile.close();

    // Check if the JSON structure is an array
    if (!jArray.is_array())
    {
        std::cerr << "Invalid JSON structure. Expected an array of arrays." << std::endl;
        std::cout << "Press enter or enter any key to continue!" << std::endl;
#if defined(_WIN32) || defined(_WIN64)
        _getch();
#else
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores everything until Enter is pressed
#endif
        return 1; // Exit if the structure is invalid
    }

    // Display the saved profiles
    std::cout << "Saved Profiles:" << std::endl;
    for (size_t i = 0; i < jArray.size(); ++i)
    {
        // Check if each character is an array with exactly three elements
        if (jArray[i].is_array() && jArray[i].size() == 9)
        {
            std::cout << (i + 1) << ". " << jArray[i][0] << std::endl; // Display only the Name
        }
        else
        {
            std::cerr << "Invalid character structure at index " << i << std::endl;
        }
    }

    // Ask the user to choose a character profile to display
    std::cout << "Choose a character profile to display (1-" << jArray.size() << "):" << std::endl;

    int ans = 0; // Initialize ans
    while (true)
    {
        std::cin >> ans;
        // Check for valid input
        if (std::cin.fail() || ans < 1 || ans > jArray.size())
        {
            std::cerr << "Invalid choice! Enter a valid integer corresponding to the profile number." << std::endl;
            std::cin.clear();                                                   // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
        {
            break; // Valid input, exit the loop
        }
    }

    const json &selectedCharacter = jArray[ans - 1]; // Convert to 0-based index
    std::cout << "Character " << ans << " Details:" << std::endl;
    std::cout << "  Name: " << selectedCharacter[0] << std::endl;
    std::cout << "  Race: " << selectedCharacter[1] << std::endl;
    std::cout << "  Class: " << selectedCharacter[2] << std::endl;
    std::cout << "\n"
              << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Stats" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "  Strength: " << selectedCharacter[3] << std::endl;
    std::cout << "  Dexterity: " << selectedCharacter[4] << std::endl;
    std::cout << "  Constitution: " << selectedCharacter[5] << std::endl;
    std::cout << "  Intelligence: " << selectedCharacter[6] << std::endl;
    std::cout << "  Wisdom: " << selectedCharacter[7] << std::endl;
    std::cout << "  Charisma: " << selectedCharacter[8] << std::endl;
    std::cout << "\n";
    std::cout << "Enter any key to return back to setting screen" << std::endl;
#if defined(_WIN32) || defined(_WIN64)
    _getch();
#else
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores everything until Enter is pressed
#endif
    return 0;
}

int menu2()
{
    int choice2;
    bool view = true;

    while (view)
    {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
        std::cout << "Randomiser Settings" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "(Note that this feature is still experimental and is yet to be completed)" << std::endl;
        std::cout << "1. Generation Filter (Unavailable)" << std::endl;
        std::cout << "2. Profile Saves" << std::endl;
        std::cout << "3. Return" << std::endl;
        std::cout << "Choose an option!" << std::endl;
        std::cin >> choice2;
        sleep(2);

        if (choice2 == 1)
        {
            std::cout << "Setting currently unavailable, come back next time." << std::endl;
            continue;
        }
        else if (choice2 == 2)
        {
            std::cout << "Loading saves..." << std::endl;
#if defined(_WIN32) || defined(_WIN64)
            system("cls");
#else
            system("clear");
#endif
            int load = profileSave();
            continue;
        }
        else if (choice2 == 3)
        {
            view = false;
            return 0;
        }
    }
    // For filtration system, save filtered options in a json file. Make the data into a global variable.
    // Allow users to filter out what race they want as well
    return 0;
}

int main()
{
    bool programRun = true;
    int mainMenuChoice;
    json j;

    while (programRun)
    {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
        // Starting screen
        std::cout << "Welcome to Dungeons and Dragons (DND) Player Creator!" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. New Character" << std::endl;
        std::cout << "2. Randomiser Settings" << std::endl;
        std::cout << "3. Abort Program" << std::endl;
        std::cout << "Please enter a choice: " << std::endl;
        std::cin >> mainMenuChoice;

        if (mainMenuChoice == 1)
        {
            bool viewState = true;
            std::cout << "Player chose option \"1\", proceeding to New Character screen" << std::endl;
            sleep(3);
#if defined(_WIN32) || defined(_WIN64)
            system("cls");
#else
            system("clear");
#endif

            char answer; // Declare the variable
            char placeholder;
            char input;
            std::string name = nameGenerator();

            // User's name
            std::cout << "First, let's figure out a name for you..." << std::endl;
            std::cout << "By the blessings of the high one, it is decided that your name shall be..." << (name + ".") << std::endl;
            std::cout << "\n"
                      << std::endl;

            // User's race
            std::cout << "Next, let us determine your race by asking you some questions!" << std::endl;
            std::string race = raceGenerator();
            std::cout << "You are born of the " << (race + " race.") << std::endl;
            std::cout << "\n"
                      << std::endl;

            // User's class
            std::cout << "Next, let us determine your class!" << std::endl;
            std::string classChoice = classGenerator(race);
            std::cout << "The class that the great Mutton has chosen for thee is the " << (classChoice + " class.") << std::endl;
            std::cout << "\n"
                      << std::endl;

            std::cout << "Let's roll for your stats!" << std::endl;
            std::cout << "Rolling for stats..." << std::endl;
            int temp[6];
            std::srand(std::time(0));
            int stat = std::rand() % 21;
            std::cout << "Your strength is: " << stat << std::endl;
            temp[0] = stat;
            sleep(1);
            int stat2 = std::rand() % 21;
            std::cout << "Your dexterity is: " << stat2 << std::endl;
            temp[1] = stat2;
            sleep(1);
            int stat3 = std::rand() % 21;
            std::cout << "Your constitution is: " << stat3 << std::endl;
            temp[2] = stat3;
            sleep(1);
            int stat4 = std::rand() % 21;
            std::cout << "Your intelligence is: " << stat4 << std::endl;
            temp[3] = stat4;
            sleep(1);
            int stat5 = std::rand() % 21;
            std::cout << "Your wisdom is: " << stat5 << std::endl;
            temp[4] = stat5;
            sleep(1);
            int stat6 = std::rand() % 21;
            std::cout << "Your charisma is: " << stat6 << std::endl;
            temp[5] = stat6;
            sleep(1);
            std::cout << "Press enter or enter any key to continue!" << std::endl;

#if defined(_WIN32) || defined(_WIN64)
            _getch();
#else
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores everything until Enter is pressed
#endif // Waits for any key press, works on Windows systems

#if defined(_WIN32) || defined(_WIN64)
            system("cls");
#else
            system("clear");
#endif

            std::cout << "Your Character Details:" << std::endl;
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Race: " << race << std::endl;
            std::cout << "Class: " << classChoice << std::endl;
            std::cout << "\n"
                      << std::endl;
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "Stats" << std::endl;
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "Strength: " << temp[0] << std::endl;
            std::cout << "Dexterity: " << temp[1] << std::endl;
            std::cout << "Constitution: " << temp[2] << std::endl;
            std::cout << "Intelligence: " << temp[3] << std::endl;
            std::cout << "Wisdom: " << temp[4] << std::endl;
            std::cout << "Charisma: " << temp[5] << std::endl;

            std::cout << "Save profile? [Y/N]: " << std::endl;
            try
            {
                std::cin >> input;
                if (!std::isalpha(input))
                {
                    throw "Not char";
                }
            }
            catch (const std::string error)
            {
                std::cout << "Enter a valid input" << std::endl;
            }
            if (toupper(input) == 'Y')
            {
                std::string profile[9] = {name, race, classChoice, std::to_string(temp[0]), std::to_string(temp[1]), std::to_string(temp[2]), std::to_string(temp[3]), std::to_string(temp[4]), std::to_string(temp[5])};
                json newProfile = json::array({profile[0], profile[1], profile[2], profile[3], profile[4], profile[5], profile[6], profile[7], profile[8]});
                std::vector<json> profiles;

                // Read existing profiles from the JSON file
                std::ifstream inFile("profile.json");
                if (inFile.is_open())
                {
                    json existingProfiles;
                    inFile >> existingProfiles; // Read the existing JSON array

                    // Ensure the existing data is an array
                    if (existingProfiles.is_array())
                    {
                        profiles = existingProfiles.get<std::vector<json>>(); // Convert to vector of JSON arrays
                    }
                    inFile.close();
                }
                else
                {
                    // If the file doesn't exist or couldn't be opened, create a new one
                    std::ofstream outFile("profile.json");
                    if (outFile.is_open())
                    {
                        outFile << "[]"; // Initialize with an empty JSON array
                        outFile.close();
                    }
                    else
                    {
                        std::cerr << "Unable to create JSON file." << std::endl;
                        return 1; // Exit if unable to create the file
                    }
                }

                // Append the new profile to the existing profiles
                profiles.push_back(newProfile);

                // Write the updated profiles back to the JSON file
                std::ofstream outFile("profile.json");
                if (outFile.is_open())
                {
                    outFile << json(profiles).dump(4); // Write as a pretty JSON array with indentation
                    outFile.close();
                    std::cout << "Profile saved!" << std::endl;
                }
                else
                {
                    std::cerr << "Unable to save." << std::endl;
                }
            }

            while (viewState)
            {
                std::cout << "Stop viewing? [Y/N]" << std::endl;
                std::cin >> answer;
                answer = toupper(answer);
                if (answer == 'Y')
                {
                    viewState = false;
                }
                else
                {
                    sleep(10); // If not, wait for 10 seconds
                }
            }
        }
        else if (mainMenuChoice == 2)
        {
            std::cout << "Player chose option \"2\", proceeding to Settings screen." << std::endl;
            sleep(1);
            int load = menu2();
        }
        else if (mainMenuChoice == 3)
        {
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
            programRun = false;
            sleep(2);
        }
        else
        {
            std::cout << "Please enter a valid answer!";
        }
    }
    return 0;
}