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
    // Random device and engine for shuffle
    random_device rd;
    mt19937 generator(rd());
    shuffle(shuffled.begin(), shuffled.end(), generator);
    return shuffled;
}

// Main game function
void playGame(const vector<string>& wordList) {
    // Select a random word from the list
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, wordList.size() - 1);
    string selectedWord = wordList[distribution(generator)];

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

    while (attempts > 0) {
        cout << "You have " << attempts << " chance(s) left. Enter your guess: ";
        cin >> userGuess;

        if (userGuess == selectedWord) {
            // Stop tracking time
            auto endTime = steady_clock::now();
            auto duration = duration_cast<seconds>(endTime - startTime).count();

            cout << "Congratulations! You guessed the word correctly!" << endl;
            cout << "It took you " << duration << " second(s) to guess correctly." << endl;
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
}

int main() {
    // Word list
   vector<string> wordList = {
    "apple", "banana", "cherry", "orange", "grapes", "kiwi", "mango", "pineapple", "pear", "peach",
    "apricot", "plum", "strawberry", "blueberry", "blackberry", "watermelon", "lemon", "lime", "fig", "date",
    "tomato", "potato", "carrot", "cucumber", "lettuce", "spinach", "broccoli", "onion", "garlic", "pepper",
    "carrot", "peas", "radish", "pumpkin", "cabbage", "avocado", "zucchini", "eggplant", "chili", "squash",
    "beetroot", "ginger", "celery", "asparagus", "artichoke", "parsley", "rosemary", "thyme", "oregano", "basil",
    "mint", "cilantro", "dill", "tarragon", "savory", "chives", "bayleaf", "clove", "cumin", "turmeric",
    "cardamom", "cinnamon", "nutmeg", "peppermint", "vanilla", "garlic", "ginger", "saffron", "paprika", "chocolate",
    "cookie", "cake", "pie", "biscuit", "donut", "brownie", "croissant", "tart", "pudding", "candy",
    "coconut", "honey", "sugar", "vanilla", "caramel", "marzipan", "fudge", "wafer", "cheese", "butter",
    "milk", "cream", "yogurt", "creamcheese", "custard", "cheesecake", "pancake", "waffle", "pudding", "smoothie",
    "coffee", "tea", "juice", "soda", "water", "lemonade", "icedtea", "fruitjuice", "cocoa", "latte",
    "espresso", "mocha", "americano", "cappuccino", "macchiato", "smoothie", "shake", "soup", "salad", "sandwich"
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
