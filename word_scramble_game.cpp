#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono> // For tracking time
using namespace std;
using namespace std::chrono;

// Function to shuffle the characters in the word
string shuffleWord(const string& word) {
    string shuffled = word;
    random_device rd;
    mt19937 generator(rd());
    shuffle(shuffled.begin(), shuffled.end(), generator);
    return shuffled;
}

// Function to filter words based on difficulty
vector<string> filterWordsByDifficulty(const vector<string>& wordList, const string& difficulty) {
    vector<string> filteredWords;
    for (const string& word : wordList) {
        if ((difficulty == "Easy" && word.length() <= 5) ||
            (difficulty == "Medium" && word.length() > 5 && word.length() <= 8) ||
            (difficulty == "Hard" && word.length() > 8)) {
            filteredWords.push_back(word);
        }
    }
    return filteredWords;
}

// Main game function
void playGame(const vector<string>& wordList) {
    // Ask the user for difficulty level
    string difficulty;
    cout << "Choose a difficulty level (Easy, Medium, Hard): ";
    cin >> difficulty;

    // Filter words based on difficulty
    vector<string> filteredWords = filterWordsByDifficulty(wordList, difficulty);
    if (filteredWords.empty()) {
        cout << "No words available for the selected difficulty level." << endl;
        return;
    }

    // Select a random word from the filtered list
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, filteredWords.size() - 1);
    string selectedWord = filteredWords[distribution(generator)];

    // Shuffle the selected word
    string scrambledWord = shuffleWord(selectedWord);

    // Game instructions
    cout << "Welcome to the Word Scramble Game!" << endl;
    cout << "Unscramble the word: " << scrambledWord << endl;
    

    // Start tracking time
    auto startTime = steady_clock::now();

    // Give the user 3 chances to guess
    int attempts = 3;
    string userGuess;
    int score = 0;

    while (attempts > 0) {
        if(attempts==2)
        {
            cout << "Hint: The first letter is '" << selectedWord[0] << "'" << endl;
        }
       if (attempts == 1) {
            cout << "Hint: The last letter is '" << selectedWord[selectedWord.length() - 1] << "'" << endl;
        }
        cout << "You have " << attempts << " chance(s) left. Enter your guess: ";
        
        cin >> userGuess;

        if (userGuess == selectedWord) {
            // Stop tracking time
            auto endTime = steady_clock::now();
            auto duration = duration_cast<seconds>(endTime - startTime).count();

            // Calculate score
            score = 100 - (10 * (3 - attempts));

            cout << "Congratulations! You guessed the word correctly!" << endl;
            cout << "It took you " << duration << " second(s) to guess correctly." << endl;
            cout << "Your score: " << max(score, 0) << " points" << endl;
            return;
        } else {
            cout << "Incorrect guess. Try again." << endl;
        }
        attempts--;
    }

    // If the user fails all attempts
    auto endTime = steady_clock::now();
    auto duration = duration_cast<seconds>(endTime - startTime).count();

    cout << "Sorry, you've used all your chances. The correct word was: " << selectedWord << endl;
    cout << "You took " << duration << " second(s)." << endl;
    cout << "Your score: " << score << " points" << endl;
}

int main() {
    // Word list
    vector<string> wordList = {
        "apple", "banana", "cherry", "orange", "grapes", "kiwi", "mango", "pineapple", "pear", "peach",
        "apricot", "plum", "strawberry", "blueberry", "blackberry", "watermelon", "lemon", "lime", "fig", "date"
    };

    // Start the game
    char playAgain;
    do {
        playGame(wordList);
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing!" << endl;
    return 0;
}
