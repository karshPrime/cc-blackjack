#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>

void head();
void quit(unsigned short games_played, unsigned short player_bal);
bool is_lost(unsigned short &points, unsigned short balance);
void generate_deck(std::array<int, 52> &deck);
void print_cards(std::vector<int> &picked);

int main() {
  unsigned short player_bal = 500;
  unsigned short player_points = 0;
  unsigned short pc_points = 0;
  unsigned short games_played = 0;
  unsigned short move_counter = 0;
  unsigned short on_stake = 0;
  bool pc_stand = false;
  bool player_stand = false;
  char user_move;
  char interested;

  head();
  std::cin >> interested;

  while (interested != 'n' || interested != 'N') {
    system("clear");
    std::array<int, 52> deck{};
    generate_deck(deck);

    std::vector<int> player_picked{};
    std::vector<int> pc_picked{};

    while (not is_lost(player_points, player_bal)) {
      if (pc_points < 15) {
        pc_picked.push_back(deck[move_counter]);
        move_counter += 1;
      } else {
        pc_stand = true;
      }

      std::cout << "PC  : [" << pc_points << "] ";
      print_cards(pc_picked);

      std::cout << "You : [" << player_points << "] ";
      print_cards(player_picked);

      //checks if pc went over 21
      if (is_lost(pc_points, 1)) {
        std::cout << "Congrats! you won!" << std::endl;
        std::cout << "Added $" << on_stake*2 << " in your account" << std::endl;
        break;
      }

      std::cout << ">> $" << on_stake << " << on stake" << std::endl << std::endl;
      std::cout << "hit[h] or stand[S] : ";
      std::cin >> user_move;

      if (user_move != 'h' or user_move != 'H') {
        pc_stand = true;
      } else {
        player_picked.push_back(deck[move_counter]);
        on_stake += 50;
        player_bal -= 50;
        move_counter += 1;
      }

      if (player_stand & pc_stand) {
        system("clear");
        if (player_points > pc_points) {
          std::cout << "Congrats! you won!" << std::endl;
          std::cout << "Added $" << on_stake * 2 << " in your account" << std::endl;
        } else if (player_points == pc_points) {
          std::cout << "There's a draw!" << std::endl;
          std::cout << "Refunded $" << on_stake << std::endl;
        } else {
          std::cout << "You lost! Better try next time :)" << std::endl;
          std::cout << "Deducted $" << on_stake << " from your account" << std::endl;
        }
        break;
      }
    }

    std::cout << "Continue? [Y/n]";
    std::cin >> interested;
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
  std::cout << "- you start the game with $500.00" << std::endl;
  std::cout << "- on every turn you can either [h]hit or [s]stay" << std::endl;
  std::cout << "- objective of the game is to get closer to 21 without going over it." << std::endl;
  std::cout << "- with every hit you would be gambling some money which should be over some said limit" << std::endl;
  std::cout << "- player to go over 21 loses" << std::endl;
  std::cout << "- first player to go out of all funds loses" << std::endl;

  std::cout << std::endl;
  std::cout << "Continue? [Y/n]: ";
}

// print end-game stats
void quit(unsigned short games_played, unsigned short player_bal) {
  system("clear");
  std::cout << "Thank you for playing blackjack." << std::endl;
  std::cout << "You played total of [" << games_played << "] games" << std::endl;
  std::cout << "And you're leaving the game with $" << player_bal << ".00 ." << std::endl;
}

// print picked up cards
void print_cards(std::vector<int> &picked) {
  for (auto i = 0; i < picked.size(); i++) {
    int card_type = picked[i] / 100;
    switch (card_type) {
      case 1: // heart
        std::cout << "H";
        break;
      case 2: // diamond
        std::cout << "D";
        break;
      case 3: // spade
        std::cout << "S";
        break;
      case 4: // clover
        std::cout << "C";
        break;
    }
    std::cout << picked[i] % 100 << "\t" << std::endl;
  }
}

// Will check for if the player lost
bool is_lost(unsigned short &points, unsigned short balance) {
  if (balance <= 0 ||  points > 21) {
    return true;
  }
  return false; // game can continue
}

// will check if a number already exists in the array
bool is_present(std::array<int, 52> &deck, int filled_upto, int &value_tocheck) {
  for (auto i = 0; i < filled_upto; i++) {
    if (deck[i] == value_tocheck) {
      return true;
    }
  }
  return false;
}

// generating random deck
void generate_deck(std::array<int, 52> &deck) {
  // elements in deck array would be 3 digits numbers
  // first number would represent the card type: 1 heart, 2 diamond, 3 spade, 4 clover
  for (auto i = 0; i != 52; i++) {
    int card = (100 * (rand() % 4 + 1)) + (100 * (rand() % 12 + 1));
    while (is_present(deck, i, card)) {
      card = (100 * (rand() % 4 + 1)) + (100 * (rand() % 12 + 1));
    }
    deck[i] = card;
  }
}
