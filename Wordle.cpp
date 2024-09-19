#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[93m"
#define GREY "\033[90m"
#define RED "\033[31m"
using namespace std;

// Group Activity #6 Contributors: Daiwei, Alberto, Kenzai, Mikel, Andrew



//Alberto
// Display Function
void displayFeedback (const string& wordGuess, const string& targetWord){
    // sets all letters in the target word to false becuase they have not been mathced yet this is used in case the user types duplicate letters
    // This will track if a letter in the target word has already been matched to another letter from the guessed word
    vector<bool> matchedTarget(targetWord.length(), false);

    // This will track the letters in the user guess that was already marked. 
    vector<bool> matchedGuess(wordGuess.length(), false);
    vector <string> coloredGuess(wordGuess.length()); // This is where the colored letters will go for every guess and then displayed after the loops are finished
    
    // WordGuess Check + Color

    //First Loop: Checks and marks all correct posistions with green
    for (int i = 0; i < wordGuess.length(); i++) {
 
        if (wordGuess.at(i) == targetWord.at(i)) {
            // Gives green if the letter is in the correct position
            //This will take where the charcter is found it and store it in another vectore in order to be outputted later
            // It sets the string to green then will create a string with the lenth 1 which will store the letter found at this index
            coloredGuess.at(i) =  GREEN + string(1, wordGuess.at(i)) + ' ' + RESET;
            // Changes the value of the letter in the target word to true since it has been matched
            matchedTarget.at(i) = true; 
            // changes the value of the guess word to true since it has been mathced
            matchedGuess.at(i) = true;
        }
    } 
    //Second loop to check if the letter is in the word but inccorect position
    for (int i = 0;i < targetWord.length(); i++) {
        if(!matchedGuess.at(i)){ // Only will check the letters that HAVEN'T been matched so if we already matched a letter and the user has types that same letter again but it is not in the word this will not execute because that letter has already been matched previously and found will remain false
            bool found = false; // This will track if the letter is found in the target word but it is assigned false because its not in the correct position
            // Nested loop to check the the current guessed letter to each letter in the target word
            for (int j = 0; j < targetWord.length(); j++){
                if (!matchedTarget.at(j) && wordGuess.at(i) == targetWord.at(j)){ // This will output a yellow letter if the letter hasnt been matched already in the target word and is found within the user Guess  
                    // Gives yellow if the letter is in the word but not in the correct position
                    coloredGuess.at(i) = YELLOW + string(1, wordGuess.at(i)) + ' ' + RESET;                    // sets the the matched letter that we found in the word put not in the correct position to true in otder to not track it again unless there is actually a duplicate letter in the wordGuess
                    matchedTarget.at(j) = true; // Marks this inccorect position letter as true within its matched list
                    found = true; // This marks the found variable as true since we found something at an incorrect position which is a match to the target word
                    break; // This will then stop searching because the letter has been found
                }
            }
            if(!found){ // if the letter wasnt found in the previous loop the found variable will still be false which will execute this statement
            // Give grey if the letter is not in the target word at all
            coloredGuess.at(i) =  GREY + string(1, wordGuess.at(i)) + ' ' + RESET;
            }    
        }
    }
    for (int i = 0; i < wordGuess.length(); i++){
        cout << coloredGuess.at(i);
    }
         
}
// Start Function
// Alberto
void startNewGame(const vector<string>& wordList, int playerCount, vector<int>& playerHighScores, vector<string> playerList) {
    int randomIndex;
    char answer;
    string wordGuess;
    vector <string> coloredGuess(wordGuess.length());
 
    int numberGuess = 5;
 
    //Alberto
    //Creates empty index for each player
    playerHighScores.assign(playerCount, 0);

    do {
        for (int i = 0; i < playerCount; i++) {
            // Creates Player Turns 
            cout << playerList.at(i) << "'s " << "Turn" << endl;
            randomIndex = rand() % wordList.size();
            //cout << wordList.at(randomIndex) << endl; //This will show the word (Used for testing)
            cout << "Guess the word: ";
            numberGuess = 5;
        
    //Alberto
            do {
            bool validInput = true;
                do { //Checks valid Input
                    // Reset before getting the new guess from the player
                    cin >> wordGuess;
                    validInput = true;

                    if (wordGuess.length() != 5){
                        validInput = false;
                    }
                    else{
                        // Makes sure they actually typed a word
                        for (int i = 0; i < wordGuess.length(); i++){
                            if(!isalpha(wordGuess.at(i))){
                                validInput = false;
                                break;
                            }
                        }
                    }

                    if (!validInput){
                        cout << RED << "Please enter a valid 5-letter word: " << RESET;
                        cin.clear();
                        cin.ignore(100, '\n');
                    }
                } while(!validInput);

                for(int i = 0; i < wordGuess.length(); i++){
                    wordGuess.at(i) = toupper(wordGuess.at(i));
                }
                //Color codes the guess
                
                displayFeedback(wordGuess, wordList.at(randomIndex));
                cout << endl;

                // Places "_" for each letter in the word
                for (int i = 0; i < wordGuess.size(); i++) {
                    cout << "_ ";
                }
                cout << endl;
            
                if (wordGuess == wordList.at(randomIndex)) {
                    cout << GREEN << "Correct!" << endl << RESET << "Your word is: " << GREEN << wordList.at(randomIndex) + "." << RESET << endl;
                    //Alberto + Daiwei
                    playerHighScores.at(i) += numberGuess;
                }
        
                else if (wordGuess != wordList.at(randomIndex)){
                    numberGuess--; // Decreases number of guesses possible
                    cout << "Try again: "; 
                }
                else if (numberGuess == 0){
                    cout << RED << "You have ran out of tries your word was: " << GREEN << wordList.at(randomIndex) << RESET << endl;

                }
    
                } while (wordGuess != wordList.at(randomIndex) && numberGuess != 0);
            
                if (wordGuess != wordList.at(randomIndex) && numberGuess == 0) {
                cout << RED << "You have run out of tries! Your word was: " << GREEN << wordList.at(randomIndex) << RESET << endl;
            }
        // Resets the wordGuess to nothing
         wordGuess.clear();
         

        } 
        // If typed 'y' the game will restart 
        cout << "Would you like to play again?" << endl;
        cout << "Yes(y) or No(Type Anything)" << endl;
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');
}
// Instructions Function
void howToPlay() {
    cout << "\nHow to Play!" << endl;
    cout << setfill('-') << setw(60) << "" << endl;
    cout << "Player Turns: Player 1 goes first, then Player 2 and so on..." << endl;
    cout << "1. Type a five letter word." << endl;
    
    cout << "2. Depending on your guess the color of your letters will change to show how close you are to the word." << endl;
    
    cout << " - " << GREEN << "Green"
    << " means the letter is in the correct position." << RESET << endl;
 
    cout << " - " << YELLOW << "Yellow"
    << " means the letter is correct but in the wrong position." << RESET << endl;
 
    cout << " - " << GREY << "Grey"
    << " means the letter isn't correct." << RESET << endl;
    
    cout << "Scoring System: Only gain points if the player guessed the correct word (Point +1 per leftover guesses)" << endl;
    
    cout << "3. The goal is to guess the correct word within a specific number of trys.\n";
    
    cout << "4. Finally, have fun!\n";
    
    cout << setfill('-') << setw(60) << "" << endl;
}
// Scores Function
//Alberto
void highScores(int playerCount, vector<int> playerHighScores, vector<string>playerList) {
    for (int i = 0; i < playerCount; i++){
        cout << playerList.at(i) << ": " << playerHighScores.at(i) << endl; 
    }
}
// Andrew
// Program Starts
int main() {
    int playerCount = 0, menuChoice = 0;
    string playerName;
    vector <string> playerList;
    vector <int> playerHighScores;
    vector <string> coloredGuess; // This is where the colored letters will go for every guess and then displayed after the loops are finished

    srand(time(nullptr));

    vector<string> wordList = 
        {"HELLO", "NINJA", "DEBUT", "CANDY", "BRAIN",
        "BREAD", "LUCKY", "BROWN", "VOZHD", "ELITE",
        "TIGER", "APPLE", "CHAOS", "LEMON", "PANDA",
        "QUICK", "VIOLA", "ZEBRA", "FROST", "JUMBO"};

    //Daiwei, Mikel, Andrew, Alberto, Kenzai
    cout << "Welcome to Word Guesser!" << endl;
    do {
        cout << "How many players are participating (1-5): "; 
        cin >> playerCount;

        if (cin.fail() || playerCount < 1 || playerCount > 5) {
            cin.clear(); 
            cin.ignore(100, '\n');
            cout << "Error, enter a valid input " << endl;
        }
    } while (playerCount < 1 || playerCount > 5);
    
    
    
    cout << "Create a username for each Player" << endl;
    

    for(int i = 0; i < playerCount; i++){
        cout << "Player " << i+1 << ": ";
        cin >> playerName;
        playerList.push_back(playerName);
        }
    
    // Andrew 
    // Do While Loop to pick 4 choices
    do {
 
        do {
            cout << "Pick a menu (Start New Game (1), How to Play (2), High Scores (3), and Quit(4)): ";
            cin >> menuChoice;
 
            if (menuChoice == 1) {
                startNewGame(wordList, playerCount, playerHighScores, playerList);
            }    
            else if (menuChoice == 2) {
                howToPlay();
            } 
            else if (menuChoice == 3) {
                highScores(playerCount, playerHighScores, playerList);
            } 
            else if (menuChoice == 4) {
                cout << "Thank you for playing!" << endl;
                exit(0);
            } 
            else {
                cout << "Invalid input try again!" << endl;
                cin.clear();
                cin.ignore(100, '\n');
            }
 
        } while (cin.fail() || menuChoice < 1 || menuChoice > 4);
    } while (menuChoice != 4);
    return 0;
}
