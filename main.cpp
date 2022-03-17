#include <iostream>

void head();
void quit(short games_played, short player_bal);

int main() {
  head();

  unsigned short player_bal = 500;
  unsigned short player_points = 0;
  unsigned short pc_points = 0;
  unsigned short games_played = 1;

  char interested;
  std::cin >> interested;
  while (interested != 'n' || interested != 'N') {
    // game
  }
  quit(games_played, player_bal);
  
  return 0;
}

// print heading information on user console
void head() {
  std::cout << " _     _            _     _            _" << std::endl;
  std::cout << "| |__ | | __ _  ___| | __(_) __ _  ___| | __" << std::endl;
  std::cout << "| '_ \\| |/ _` |/ __| |/ /| |/ _` |/ __| |/ /" << std::endl;
  std::cout << "| |_) | | (_| | (__|   < | | (_| | (__|   <" << std::endl;
  std::cout << R"(|_.__/|_|\__,_|\___|_|\__/ |\__,_|\___|_|\_\)" << std::endl;
  std::cout << "                       |__/" << std::endl;

  std::cout << "How to play:" << std::endl;

}

void quit(short games_played, short player_bal) {
  std::cout << "Thank you for playing blackjack." << std::endl;
  std::cout << "You played total of [" << games_played << "] games" << std::endl;
  std::cout << "And you're leaving the game with $" << player_bal << ".00 ." << std::endl;
}