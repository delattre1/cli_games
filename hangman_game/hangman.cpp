#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

const std::string F0 =  "  +---+  \n"
                        "  |   |  \n"
                        "      |  \n"
                        "      |  \n"
                        "      |  \n"
                        "      |  \n"
                        "=========\n";
  
const std::string F1 = "  +---+  \n"
                       "  |   |  \n"         
                       "  O   |  \n"         
                       "      |  \n"         
                       "      |  \n"         
                       "      |  \n"         
                       "=========\n";
                       
const std::string F2 = "  +---+  \n"         
                       "  |   |  \n"         
                       "  O   |  \n"         
                       "  |   |  \n"         
                       "      |  \n"         
                       "      |  \n"         
                       "=========\n";
                       
const std::string F3 = "  +---+  \n"         
                       "  |   |  \n"         
                       "  O   |  \n"         
                       " /|   |  \n"         
                       "      |  \n"         
                       "      |  \n"         
                       "=========\n";
                       
const std::string F4 = "  +---+  \n"         
                       "  |   |  \n"         
                       "  O   |  \n"         
                       " /|\\  |  \n"         
                       "      |  \n"         
                       "      |  \n"         
                       "=========\n";
                       
const std::string F5 = "  +---+  \n"         
                       "  |   |  \n"         
                       "  O   |  \n"         
                       " /|\\  |  \n"         
                       " /    |  \n"         
                       "      |  \n"         
                       "=========\n";
                       
const std::string F6 = "  +---+  \n"         
                       "  |   |  \n"         
                       "  O   |  \n"         
                       " /|\\  |  \n"         
                       " / \\  |  \n"         
                       "      |  \n"         
                       "=========\n";
             
const std::vector<std::string> HANGMANPICS = {F0, F1, F2, F3, F4, F5, F6};
  
bool letterExists(std::string secretWord, char guess) {
  for (char letter: secretWord) {
    if (guess == letter) return true;
  }
  return false;
}

void displayWrongGuesses(std::vector<char> wrongGuesses, int tries) {
    // Display hangman pic state
    std::cout << std::endl << HANGMANPICS[tries-1];
  
    //Display wrong letters
    std::cout << "\nYour wrong guesses: ";
    for (char letter : wrongGuesses) { std::cout << letter << ' ';}
}

void displayBeginMessage() {
  std::cout << "*******************************" << std::endl;
  std::cout << "*** Welcome to HangMan game ***" << std::endl;
  std::cout << "*******************************" << std::endl;
}

void displayEndGameMessage(bool won, std::string secretWord) {
  if (won) {
    std::cout << "\n*******************************" << std::endl;
    std::cout << "         Nice! You won" << std::endl;
    std::cout << "*******************************" << std::endl;
  }
  else {
    std::cout << "\n###############################" << std::endl;
    std::cout << "         Boo! You lost" << std::endl;
    std::cout << "  The secret word was: "  << secretWord << std::endl;
    std::cout << "###############################" << std::endl;
  }
}

std::vector<std::string> load_words() {
  std::string FNAME = "words.txt";
  std::ifstream file;
  std::vector<std::string> loaded_words;
  std::string current_word;
  int qty_words;

  file.open(FNAME);
  file >> qty_words;

  for (int i=0; i<qty_words; i++) {
    file >> current_word;
    loaded_words.push_back(current_word);
  }

  return loaded_words;
}

std::string select_random_word() {
  std::vector<std::string> loaded_words;
  loaded_words = load_words();
  int qty_words = loaded_words.size();
  
  //initialize random seed;
  srand(time(NULL));
  int random_idx = rand() % qty_words;

  return loaded_words[random_idx];
}


int main() {
  std::map<char, bool> guessed;
  std::vector<char> wrongGuesses;
  std::string secretWord;

  int tries = 0;
  int maxTries = 7;
  bool hang, won = false;
  char guess;

  displayBeginMessage();
  secretWord = select_random_word();

  while (not hang && not won) {
    std::cout << "\nInsert your desired letter:\n    >>";
    std::cin >> guess;
    guessed[guess] = true;

    if (not letterExists(secretWord, guess)) {
      wrongGuesses.push_back(guess);
      tries = wrongGuesses.size();

      if (tries > 0) { displayWrongGuesses(wrongGuesses, tries);}
      if (tries == maxTries) { hang = true; }
    }
  
    won = true;
    std::cout << "\nWord to guess: ";
    for (char letter : secretWord) {
      
      if (guessed[letter]) { 
        std::cout << letter << ' '; 
      }
      else { 
        std::cout << '_' << ' ';
        won = false;
      }
    }
    std::cout << std::endl;
  }
  displayEndGameMessage(won, secretWord);
}
