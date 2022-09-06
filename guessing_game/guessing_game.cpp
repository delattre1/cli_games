#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

int main() {
  
  srand(time(NULL));
  const int SECRET_N = rand() % 100; // generate a pseudo random number in range 1 - 99
  const int maxAttempts = 3;
  double score = 100.0;
  int guess;
  int attempts = 1;
  bool isGreater, isRight, exceeded;

  std::cout << "******************************" << std::endl; 
  std::cout << "** welcome to guessing game **"  << std::endl; 
  std::cout << "******************************" << std::endl; 
  std::cout << std::fixed << std::setprecision(2);

  while (guess != SECRET_N) {
    std::cout << "\nInsert your guess:\n    >> ";
    std::cin  >> guess;
    //std::cout << "Your guess is: " << guess << std::endl;
    isGreater = guess >  SECRET_N;
    isRight   = guess == SECRET_N;
    exceeded  = attempts == maxAttempts;
    score -= (abs(SECRET_N - guess))/2.0;
  
    if (isRight or exceeded) { break; }

    else if (isGreater) {
      std::cout << "Boo! You are wrong, try again. (try a smaller n)" << std::endl;
    }
    else if (not isGreater) {
      std::cout << "Boo! You are wrong, try again. (try a bigger n)" << std::endl;
    }
    attempts++;
    std::cout << "Score: " << score << std::endl;
  }
  
  if (isRight) {
    std::cout << "\n****************************************" << std::endl; 
    std::cout << " Congratulations, your guess is right!!\n You won the game with only " << attempts << " attempts!" << std::endl;
    std::cout << " Your final score is: " << score << std::endl;
    std::cout << "****************************************" << std::endl; 
  }
  else {
    score = 0.0;
    
    std::cout << "\n#############################################" << std::endl; 
    std::cout << " BOO!! You lost with the maximum of " << attempts << " attempts." << std::endl;
    std::cout << " Your final score is: " << score << std::endl;
    std::cout << " The secret number was: " << SECRET_N << std::endl;
    std::cout << "#############################################" << std::endl; 
  }
}
