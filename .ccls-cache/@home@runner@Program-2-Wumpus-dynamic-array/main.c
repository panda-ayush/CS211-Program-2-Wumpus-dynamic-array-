/* ---------------------------------------------
Prog 2: Wumpus (dynamically sized array)

Course: CS 211, Fall 2022. Thursday 10am lab
System: Mac using Replit
Author: Ayush Panda
---------------------------------------------
*/
/*
Late Essay:
The biggest difference between my code and the solution code was the lack of functions that I used. For example there was a function in the solution code that would check for adjacent rooms, what I did instead of creating a function that checks for adjacent rooms is I would check for the adjacent rooms in the main function itself. I think this made my code longer and I would be repeating code more often whereas in the solution code you could simply reuse the function to check for adjacent rooms so that you don’t have to repeat code. I think for this reason using a function to check for adjacent rooms is the better choice. Another difference I saw was the use of a struct in the solution code. In the solution code they used a struct in order to set the variables like the wumpus position, player position, etc. However, in my code I would simply have a variable that would hold the wumpus position, player position, etc. I think both options are fine its more a preference and there really isn’t a better choice. However, argumentatively you could say that using a struct can be better since you can hold values within the struct where as by creating variables that hold all the values it can get confusing and messy while creating the code however, it can be less lines of code by not using a struct which would be a reason why not using a struct may be a better option. Another difference that I recognized was creating functions for each of the testing scenarios. For example, there was a function that strictly checked for the bats and changed the bats position based on the output of the program. What I did instead of creating a function was to check for everything in the main function. I think creating a function that checks for everything is a better option since it can make the code harder to read and understand. If the code is harder to read and understand it also makes it harder to debug the program which can be troublesome when checking trying to complete the test cases. Another difference was checking for hazards, in my code I would check for hazards in the main function by checking for the wumpus first then the pits and then the bats. The solution code did the same thing but there was a function that was called that would check for all the hazards. I think creating a function is a better option since you can re-use the function every time you want to check for hazards. However, if you want to check for hazards again within my code I would have to rewrite the code that checks for hazards. I think the biggest difference between my code and the solution code was the use of functions. I should have implemented more functions within my program since it would make it easier to debug. It would also make reading and understanding the code easier since you would be able to reference the function to understand what is going on.
*/
#include <stdio.h>
#include <stdlib.h>		// for srand
#include <stdbool.h> // for boolean
#include <ctype.h> // for to upper

//--------------------------------------------------------------------------------
void displayCave()
{
    printf( "\n"
			"       ______18______             \n"
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
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}//end displayInstructions()
void initializeRooms(int **gameBoard) { //function to initialize the rooms for the game
  gameBoard[0][0] = 2;//1
  gameBoard[0][1] = 5;
  gameBoard[0][2] = 8;
  
  gameBoard[1][0] = 1;//2
  gameBoard[1][1] = 3;
  gameBoard[1][2] = 10;

  gameBoard[2][0] = 2;//3
  gameBoard[2][1] = 4;
  gameBoard[2][2] = 12;

  gameBoard[3][0] = 3;//4
  gameBoard[3][1] = 5;
  gameBoard[3][2] = 14;
  
  gameBoard[4][0] = 2;//5
  gameBoard[4][1] = 5;
  gameBoard[4][2] = 8;

  gameBoard[5][0] = 5;//6
  gameBoard[5][1] = 7;
  gameBoard[5][2] = 15;

  gameBoard[6][0] = 6;//7
  gameBoard[6][1] = 8;
  gameBoard[6][2] = 17;
  
  gameBoard[7][0] = 1;//8
  gameBoard[7][1] = 7;
  gameBoard[7][2] = 9;

  gameBoard[8][0] = 8;//9
  gameBoard[8][1] = 10;
  gameBoard[8][2] = 18;

  gameBoard[9][0] = 2;//10
  gameBoard[9][1] = 9;
  gameBoard[9][2] = 11;

  gameBoard[10][0] = 10;//11
  gameBoard[10][1] = 12;
  gameBoard[10][2] = 19;

  gameBoard[11][0] = 3;//12
  gameBoard[11][1] = 11;
  gameBoard[11][2] = 13;

  gameBoard[12][0] = 12;//13
  gameBoard[12][1] = 14;
  gameBoard[12][2] = 20;

  gameBoard[13][0] = 4;//14
  gameBoard[13][1] = 13;
  gameBoard[13][2] = 15;

  gameBoard[14][0] = 6;//15
  gameBoard[14][1] = 14;
  gameBoard[14][2] = 16;

  gameBoard[15][0] = 15;//16
  gameBoard[15][1] = 17;
  gameBoard[15][2] = 20;

  gameBoard[16][0] = 7;//17
  gameBoard[16][1] = 16;
  gameBoard[16][2] = 18;

  gameBoard[17][0] = 9;//18
  gameBoard[17][1] = 17;
  gameBoard[17][2] = 19;

  gameBoard[18][0] = 11;//19
  gameBoard[18][1] = 18;
  gameBoard[18][2] = 20;

  gameBoard[19][0] = 13;//20
  gameBoard[19][1] = 16;
  gameBoard[19][2] = 19;
}
//--------------------------------------------------------------------------------
void initializeRand (int *playerPosition, int *wumpusPosition, int *pit1Position, int *pit2Position, int *bat1Position, int *bat2Position, int *arrow) {
  
  int counter = 0;
  int randomNumber[7]; //array for random placement of game items 
  while(counter < 7) { //while loop checks for random values making sure they are all different values for game item placement
    int randomValue = rand() % 20 + 1; // Using +1 gives random number 1..20 rather than 0..19
    bool numberCheck = false;
     for (int i = 0; i < 7; i++) {
      if (randomValue == randomNumber[i]) {
        numberCheck = true;
        }
      }
    if (numberCheck == false) {
      randomNumber[counter] = randomValue; //if numbers are different they are placed into array
      counter++;
    }
  }

  *playerPosition = randomNumber[0];//sets the random values to the specific game variables
  *wumpusPosition = randomNumber[1];
  *pit1Position = randomNumber[2];
  *pit2Position = randomNumber[3];
  *bat1Position = randomNumber[4];
  *bat2Position = randomNumber[5];
  *arrow = randomNumber[6];
}
//--------------------------------------------------------------------------------
int main(void) {
  
  int **gameBoard = (int **)malloc(sizeof(int*) * 20);//creates the dynamically allocated array
  for (int i = 0; i < 20; i++) {
    gameBoard[i] = (int*)malloc(sizeof(int) * 3);
  }
  
  initializeRooms(gameBoard);
  
  char playerChoice; //character for menu options
  bool gameValue = true; //boolean for while loop
  int moveChoice; //int for player's room move decision
  int playerPosition; //int for player's position
  int wumpusPosition; //int for wumpus position
  int pit1Position; //int for pit1 position
  int pit2Position; //int for pit2 position
  int bat1Position;//int to hold bat1 position
  int bat2Position;//int to hold bat2 position
  int arrow;//int to hold arrow position
  int wumpusGuess; //int for player's guess for wumpus room
  int counter = 0; //counter for random placement of game items
  int menuOptionCounter = 1; //counter for number of moves

  srand(1);// How to get a random number

  initializeRand (&playerPosition,  &wumpusPosition, &pit1Position, &pit2Position, &bat1Position,  &bat2Position, &arrow);//sets all game variables to its designated random values
  
printf("%s %d%s", "You are in room", playerPosition, ". ");
  //outputs player room when game begins
  while(gameValue) {
    bool senser = true; //boollean for whether wumpus and player are in the same room
    
    for (int j = 0; j < 3; j++) {//checks if the wumpus is in an adjacent room
      if (wumpusPosition == gameBoard[playerPosition-1][j]){
        printf("You smell a stench. ");
      }
     }
      
    for (int j = 0; j < 3; j++) {
      if (pit1Position == gameBoard[playerPosition-1][j] || pit2Position == gameBoard[playerPosition-1][j]){ //checks if player is in an adjacent room to pit
        printf("You feel a draft. ");
      }
      }
      
    for (int j = 0; j < 3; j++) { //checks if player is in an adjacent room to bat
      if (bat1Position == gameBoard[playerPosition-1][j] || bat2Position == gameBoard[playerPosition-1][j]){
        printf("You hear rustling of bat wings. ");
      }
     }

    //outputs menuoption
    printf("%s%d%s","\n\n", menuOptionCounter, ". Enter your move (or 'D' for directions): ");
    // prompt for user to enter their move
    scanf (" %c", &playerChoice);
    playerChoice = toupper(playerChoice);//changes all menuoptions to uppercase

    
    if (playerChoice == 'D') {//if player selects menu option D it will output the cave then instructions and then the room number player is in
      displayCave();
      displayInstructions();
      printf("%s %d%s", "You are in room", playerPosition, ". ");
      }
      
    else if (playerChoice == 'R') {//prompts user to enter room locations for all items and resets all item locations and then outputs player room
	    printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n\n");
      scanf("%d %d %d %d %d %d %d", &playerPosition, &wumpusPosition, &pit1Position, &pit2Position, &bat1Position, &bat2Position, &arrow);
      printf("%s %d%s", "You are in room", playerPosition, ". ");
      }
      
    else if (playerChoice == 'C') {
    // Message for menu option C (cheating). Note that the printf() statement below always prints 1 2 3 4
  	// for the player room, wumpus room, pit 1 room, and pit 2 room
    printf( "Cheating! Game elements are in the following rooms: \n"
    		"Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
    		"  %d     %d     %d     %d     %d     %d     %d\n\n", 
			playerPosition,
			wumpusPosition,
			pit1Position,
			pit2Position, 
      bat1Position,
      bat2Position,
      arrow
		);
      printf("%s %d%s", "You are in room", playerPosition, ". ");
      }
      
      else if (playerChoice == 'G') {//prompts user to guess what room wumpus is in if they guess correctly they win if they guess incorrectly they lose.
        // Prompt for guess of where Wumpus room is
        printf("Enter room (1..20) you think Wumpus is in: ");
        scanf("%d", &wumpusGuess);
        if (wumpusGuess == wumpusPosition) {
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
      printf("%s %d%s", "You are in room", playerPosition, ". ");
      }

      else if (playerChoice == 'S') { //if user selects option s
        int numberRooms; //holds the number of rooms player would like to send arrow through
        int * roomsTravel; //holds the rooms the player wants to send the arrow to
        bool condition = true;//exits while loop
        menuOptionCounter++; //increases menu option counter
        if (arrow != -1) { //if player doesn't have arrow then outputs this
          	printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
        }
        else if (arrow == -1) {// if player does have arrow it asks the user to say how many rooms they would like to send the arrow through and which specific rooms to send the arrow through
          	printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
          scanf("%d", &numberRooms);
          if (numberRooms > 3) { // User enters more than 3 rooms to shoot arrow through
            printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
            numberRooms = 3;
          }

	  roomsTravel = malloc(sizeof(int) *numberRooms); //dynamically allocated arrow to hold the room numbers the user would like to send the arrow through to

	// Store room numbers into the array
    for( int i=0; i<numberRooms; i++) {
        scanf("%d", &roomsTravel[i]);
    }
    
    // Move the arrow through those rooms, ensuring they are adjacent
    arrow = playerPosition;  // arrow starts in player room
    for( int i = 0; i < numberRooms; i++) {
        // Ensure room is adjacent before traveling through it
        if( gameBoard[arrow-1][0] == roomsTravel[i] || gameBoard[arrow-1][1] == roomsTravel[i] || gameBoard[arrow-1][2] == roomsTravel[i]) {
            // Room was adjacent, so move arrow there
            arrow = roomsTravel[i];
            // Kill Wumpus if it is there
            if( arrow == wumpusPosition) {
                printf( "Wumpus has just been pierced by your deadly arrow! \n"
                		"Congratulations on your victory, you awesome hunter you.\n");
                condition = false;
                break;
            }
            // Kill player if path went to a second room and then came right back
            if( arrow == playerPosition) {
                printf( "You just shot yourself.  \n"
                		"Maybe Darwin was right.  You're dead.\n");
                condition = false;
                break;
            }
        }
        else {
            // Error in user input, as indicated room is not adjacent.
			printf("Room %d is not adjacent.  Arrow ricochets...\n", roomsTravel[i]);
            // Move arrow to lowest numbered adjacent rooms
            arrow = gameBoard[arrow-1][0];

            if( arrow == playerPosition) {//if arrow ricochets and kills player
                printf( "You just shot yourself, and are dying.\n"
                		"It didn't take long, you're dead.\n");
                condition = false;
                break;
            }
            
            // If it ricochets into room where Wumpus is, Wumpus dies
            if( arrow == wumpusPosition) {
                printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                		"Accidental victory, but still you win!\n");
                condition = false;
                break;
            }
          }//end else
        
    }//end for( int i = 0; i < howManyRoomsForArrow
    
    wumpusPosition = gameBoard[wumpusPosition-1][ 0];//sets wumpus position to lowest adjacent room

	// Free up the space for roomsForArrowTravel
	free(roomsTravel);
         if (condition == false) {//if player or wumpus is killed ends game
          printf("\nExiting Program ...\n");
          break;
        } 
        }
      printf("%s %d%s", "You are in room", playerPosition, ". ");
      }

    else if (playerChoice == 'M') {//if player choses menu option m
      scanf ("%d", &moveChoice);//inputs room number player would like to move to
      
    for (int i = 0; i < 20; i++) {//checks to see if inputted room is connected to players current room
      if (playerPosition == (i+1)) {
        for (int j = 0; j < 3; j++) {
          if(moveChoice == gameBoard[i][j]){
          playerPosition = moveChoice;
          menuOptionCounter++;
        }
    }
      break;
    }
  }
      if (playerPosition != moveChoice) {
        printf("Invalid move.  Please retry. \n");
        // message for invalid move
        }
      if (playerPosition == arrow) {//if player gets the arrow then it will output this message
        arrow = -1;
	      printf("Congratulations, you found the arrow and can once again shoot.\n");        
      }
      while (true) { //if player moves to even number room with wumpus they lose and end the game if the player moves to an odd numbered room with wumpus the game continues
        if (wumpusPosition == playerPosition) {
          if ((wumpusPosition%2) == 0) {
          printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \nIt is over.\n");
          printf("\nExiting Program ...\n");
            gameValue = false;
          }
          else if ((wumpusPosition%2) == 1) {
	          printf( "You hear a slithering sound, as the Wumpus slips away. \nWhew, that was close! \n");
            senser = false;
          }
        }
        else if (pit1Position == playerPosition || pit1Position == playerPosition) {//checks to see if player fell into a pit if they have fallen into a pit the game ends
          printf("Aaaaaaaaahhhhhh....   \n");
          printf("    You fall into a pit and die. \n");
          printf("\nExiting Program ...\n");
            gameValue = false;
        }
        break;
      }
      int temp;
      while (true) {
        if (bat1Position == playerPosition){//if player comes in contact with the bats then it will fly them to a room then get randomly assigned to another room
          printf("Woah... you're flying! \n");
          playerPosition = rand() % 20 + 1;//sets player to random room
          printf("You've just been transported by bats to room %d.\n", playerPosition);
          while (1) {
            if (temp != bat2Position && temp != bat1Position) {//sets bat to random room that is different from bat1 bat2 and player
              bat1Position = temp;
              break;
            }
            else {
              temp = rand() % 20 + 1;
            }
          }
        } 
        else if (bat2Position == playerPosition){
          printf("Woah... you're flying! \n");
          playerPosition = rand() % 20 + 1;
          printf("You've just been transported by bats to room %d.\n", playerPosition);
          while (1) {
            if (temp != bat2Position && temp != bat1Position) {//sets bat to random room that is different from bat1 bat2 and player
              bat1Position = temp;
              break;
            }
            else {
              temp = rand() % 20 + 1;
            }
          }
          }
        break;
      }
      if (gameValue == false) {
        break;
    }
      if (senser == false) {//if player and wumpus are in the same odd numbered room it outputs room number for player and says that it smells
        printf("%s %d%s", "You are in room", playerPosition, ". ");
        printf("You smell a stench. ");
      }
      else {//outputs room number for player
        printf("%s %d%s", "You are in room", playerPosition, ". ");
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