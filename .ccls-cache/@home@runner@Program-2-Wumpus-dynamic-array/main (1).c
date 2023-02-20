/* ---------------------------------------------
Prog 1: Wumpus (fixed size array)

Course: CS 211, Fall 2022. Thursday 10am lab
System: Mac using Replit
Author: Ayush Panda
---------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>		// for srand
#include <stdbool.h> // for boolean
#include <ctype.h> // for to upper

//--------------------------------------------------------------------------------
void displayCave() //function to display the cave
{
    printf( "\n       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}

//--------------------------------------------------------------------------------
void displayInstructions() //function for game instructions
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
    		"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
    		"2. The Wumpus is not bothered by the pits, as he has sucker feet. Usually he is \n"
			"   asleep. He will wake up if you enter his room. When you move into the Wumpus'\n"
			"   room, then he wakes and moves if he is in an odd-numbered room, but stays    \n"
			"   still otherwise.  After that, if he is in your room, he snaps your neck and  \n"
			"   you die!                                                                     \n"
    		"                                                                                \n"
    		"Moves:                                                                          \n"
    		"On each move you can do the following, where input can be upper or lower-case:  \n"
    		"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
    		"   then a room number.                                                          \n"
    		"2. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
    		"3. Enter 'C' to cheat and display current board positions.                      \n"
    		"4. Enter 'D' to display this set of instructions.                               \n"
    		"5. Enter 'P' to print the maze room layout.                                     \n"
        "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game!         \n"
    		"7. Enter 'X' to exit the game.                                                  \n"
    		"                                                                                \n"
    		"Good luck!                                                                      \n"
    		" \n\n");
}//end displayInstructions()


//--------------------------------------------------------------------------------
int main(void) {
  int gameBoard [20][3] = { //array containg all rooms
{2, 5, 8}, //1
{1, 3, 10}, //2
{2, 4, 12}, //3
{3, 5, 14}, //4
{1, 4, 6}, //5
{5, 7, 15}, //6
{6, 8, 17}, //7
{1,7,9}, //8
{8, 10 ,18}, //9
{2, 9, 11}, //10
{10, 12, 19}, //11
{3, 11, 13}, //12
{12, 14, 20}, //13
{4, 13, 15}, //14
{6, 14, 16}, //15
{15, 17, 20}, //16
{7, 16, 18}, //17
{9, 17, 19}, //18
{11, 18, 20}, //19
{13, 16, 19} //20
  };
  char playerChoice; //character for menu options
  bool gameValue = true; //boolean for while loop
  int moveChoice; //int for player's room move decision
  int *playerPosition; //int pointer for player's position
  int *wumpusPosition; //int pointer for wumpus position
  int *pit1Position; //int pointer for pit1 position
  int *pit2Position; //int pointer for pit2 position
  int wumpusGuess; //int for player's guess for wumpus room
  int randomNumber[4]; //array for random placement of game items 
  int counter = 0; //counter for random placement of game items
  int menuOptionCounter = 1; //counter for number of moves

  
  srand(time(0));
    // How to get a random number
  

  
  while(counter < 4) { //while loop checks for random values making sure they are all different values for game item placement
    int randomValue = rand() % 20 + 1; // Using +1 gives random number 1..20 rather than 0..19
    bool numberCheck = false;
     for (int i = 0; i < 4; i++) {
      if (randomValue == randomNumber[i]) {
        numberCheck = true;
        }
      }
    if (numberCheck == false) {
      randomNumber[counter] = randomValue; //if numbers are different they are placed into array
      counter++;
    }
  }

  // pit1Position = &randomNumber[0];
  // pit2Position = &randomNumber[1];
  // wumpusPosition = &randomNumber[2];
  // playerPosition = &randomNumber[3];
  int value1 = 16;
  int value2 = 18;
  int value3 = 4;
  int value4 = 7;
  pit1Position = &value3; //assigns pit1 starting room
  pit2Position = &value4; //assigns pit2 starting room
  wumpusPosition = &value2; //assigns wumpus starting room
  playerPosition = &value1; //assigns player's starting room
  
printf("%s %d%s", "You are in room", *playerPosition, ". ");
  //outputs player room when game begins
  while(gameValue) {
    bool senser = true; //bool lean for whether wumpus and player are in the same room
    
    for (int i = 0; i < 20; i++) {//nested for loop to check if wumpus is in a connected room to player
      for (int j = 0; j < 3; j++) {
        if (*wumpusPosition == gameBoard[*playerPosition-1][j]){
          printf("You smell a stench. ");
        }
      }
      	break;
    }
    
    for (int i = 0; i < 20; i++) {//nested loop to check if player is in a connected room to pit
      for (int j = 0; j < 3; j++) {
        if (*pit1Position == gameBoard[*playerPosition-1][j] || *pit2Position == gameBoard[*playerPosition-1][j]){
          printf("You feel a draft. ");
        }
      }
      	break;
    }
    //outputs menuoption
    printf("%s%d%s","\n\n", menuOptionCounter, ". Enter your move (or 'D' for directions): ");
    // prompt for user to enter their move
    scanf (" %c", &playerChoice);
    playerChoice = toupper(playerChoice);//changes all menuoptions to uppercase

    
    if (playerChoice == 'D') {//if player selects menu option D it will output the cave then instructions and then the room number player is in
      displayCave();
      displayInstructions();
      printf("%s %d%s", "You are in room", *playerPosition, ". ");
      }
    else if (playerChoice == 'R') {//prompts user to enter room locations for all items and resets all item locations and then outputs player room
	    printf("Enter the room locations (1..20) for player, wumpus, pit1, and pit2: \n\n");
      scanf("%d %d %d %d", playerPosition, wumpusPosition, pit1Position, pit2Position);
      printf("%s %d%s", "You are in room", *playerPosition, ". ");
      }
    else if (playerChoice == 'C') {
    // Message for menu option C (cheating). Note that the printf() statement below always prints 1 2 3 4
  	// for the player room, wumpus room, pit 1 room, and pit 2 room
    printf( "Cheating! Game elements are in the following rooms: \n"
    		"Player Wumpus Pit1 Pit2  \n"
    		"%4d %7d %5d %5d \n\n", 
			*playerPosition,
			*wumpusPosition,
			*pit1Position,
			*pit2Position
		);
      printf("%s %d%s", "You are in room", *playerPosition, ". ");
      }
      else if (playerChoice == 'G') {//prompts user to guess what room wumpus is in if they guess correctly they win if they guess incorrectly they lose.
        // Prompt for guess of where Wumpus room is
        printf("Enter room (1..20) you think Wumpus is in: ");
        scanf("%d", &wumpusGuess);
        if (wumpusGuess == *wumpusPosition) {
          printf("You won!\n");
          printf("\nExiting Program ...\n");
          break;
        }
        else {
          printf("You lost.\n");
          printf("\nExiting Program ...\n");
          break;
        }
        
      }
    else if (playerChoice == 'P') {//outputs cave then outputs player position
      displayCave();
      printf("%s %d%s", "You are in room", *playerPosition, ". ");
      }

    else if (playerChoice == 'M') {//if player choses menu option m
      scanf ("%d", &moveChoice);//inputs room number player would like to move to
      
    for (int i = 0; i < 20; i++) {//checks to see if inputted room is connected to players current room
      if (*playerPosition == (i+1)) {
        for (int j = 0; j < 3; j++) {
          if(moveChoice == gameBoard[i][j]){
          *playerPosition = moveChoice;
          menuOptionCounter++;
        }
    }
      break;
    }
  }
      if (*playerPosition != moveChoice) {
        printf("Invalid move.  Please retry. \n");
        // message for invalid move
        }
      
        for (int i = 0; i < 20; i++) {//if player moves to even number room with wumpus they lose and end the game if the player moves to an odd numbered room with wumpus the game continues
          for (int j = 0; j < 3; j++) {
        if (*wumpusPosition == *playerPosition) {
          if ((*wumpusPosition%2) == 0) {
          printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \nIt is over.\n");
          printf("\nExiting Program ...\n");
            gameValue = false;
            break;
          }
          else if ((*wumpusPosition%2) == 1) {
	          printf( "You hear a slithering sound, as the Wumpus slips away. \nWhew, that was close! \n");
            senser = false;
            break;
          }
        }
        else if (*pit1Position == *playerPosition || *pit1Position == *playerPosition) {//checks to see if player fell into a pit if they have fallen into a pit the game ends
          printf("Aaaaaaaaahhhhhh....   \n");
          printf("    You fall into a pit and die. \n");
          printf("\nExiting Program ...\n");
            gameValue = false;
            break;
        }
       }
        break;
      }
      if (gameValue == false) {
        break;
    }
      if (senser == false) {//if player and wumpus are in the same odd numbered room it outputs room number for player and says that it smells
        printf("%s %d%s", "You are in room", *playerPosition, ". ");
        printf("You smell a stench. ");
      }
      else {//outputs room number for player
        printf("%s %d%s", "You are in room", *playerPosition, ". ");
      }
      
}

    else if (playerChoice == 'X') {	//if player chooses X game ends
      // Message that prints at the end of the program
	    printf("\nExiting Program ...\n");
      break;
      }
    
    
  }

	return 0;
}