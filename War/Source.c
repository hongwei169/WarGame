/*
    By Ethan Conneely
    G00393941
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#define TotalCards 52
#define PlayersCards 13

int currentRound = 1;
int currentPlayer = 0;
int numberPlaying = 2;
int scorePool = 0;

int cards[TotalCards];
int suits[TotalCards];
int playersScore[4];

int playersChoice[4];

void clearScreen();
void printSuit(int suit);
void shuffleDeck();
int promptCards(int player);
int promptOptions(char* title, char* options[], int optionsSize);
void nextRound();
void loadGame();
void saveGame();
void printStatus();
void newGame();
void exitGame();
void handleWinner();

void main()
{
    char* options[] = { "New Game", "Load Game" };
    int option = promptOptions("Pick an option.", options, 2);

    for (int i = 0; i < 4; i++)
    {
        playersScore[i] = 0;
    }

    // Load a previous Game
    if (option == 1)
    {
        newGame();
    }
    else
    {
        loadGame();
        printStatus();
    }

    while (1)
    {
        // round loop
        for (int i = currentRound; i < 13 + 1; i++)
        {
            for (int j = 0; j < numberPlaying; j++)
            {
                nextRound();
            }

            handleWinner();

            getchar();

            currentPlayer = 0;
            currentRound++;
        }

        clearScreen();

        int winnerScore = 0;
        int winnerIndex = 0;

        for (int i = 0; i < numberPlaying; i++)
        {
            if (playersScore[i] > winnerScore)
            {
                winnerScore = playersScore[i];
                winnerIndex = i;
            }
        }

        printf("The winner is Player %d with %d points\n", winnerIndex + 1, winnerScore);

        printf("Press enter key to close...");
        getchar();

        exitGame();
    }
}

// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
// Used to clear the screen
void clearScreen()
{
    // printf("\n\n");
    system("cls");
}

// Prints the character for each card suit
void printSuit(int suit)
{
    switch (suit)
    {
    case 0:
        printf("S");
        break;

    case 1:
        printf("H");
        break;

    case 2:
        printf("D");
        break;

    case 3:
        printf("C");
        break;
    }
}

// Randomize the order of cards in the deck
void shuffleDeck()
{
    srand((unsigned)time(0));

    for (int i = 0; i < 1000; i++)
    {
        int cardA = rand() % TotalCards;
        int cardB = rand() % TotalCards;

        int tempCard = cards[cardA];
        cards[cardA] = cards[cardB];
        cards[cardB] = tempCard;

        int tempSuit = suits[cardA];
        suits[cardA] = suits[cardB];
        suits[cardB] = tempSuit;
    }
}

// Prints out all the cards to the screen and
// let user pick one
int promptCards(int player)
{
    char answer;

    do
    {
        clearScreen();

        for (int i = PlayersCards * currentPlayer; i < PlayersCards + (PlayersCards * currentPlayer); i++)
        {
            if (cards[i] != -1)
            {
                printf("  ___ ");
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");

        for (int i = PlayersCards * currentPlayer; i < PlayersCards + (PlayersCards * currentPlayer); i++)
        {
            if (cards[i] != -1)
            {
                if (cards[i] == 10)
                {
                    printf(" |%d |", cards[i]);
                }
                else
                {
                    if (cards[i] == 11)
                    {
                        printf(" |J  |");
                    }
                    else if (cards[i] == 12)
                    {
                        printf(" |Q  |");
                    }
                    else if (cards[i] == 13)
                    {
                        printf(" |K  |");
                    }
                    else if (cards[i] == 14)
                    {
                        printf(" |A  |");
                    }
                    else
                    {
                        printf(" |%d  |", cards[i]);
                    }
                }
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");

        for (int i = PlayersCards * currentPlayer; i < PlayersCards + (PlayersCards * currentPlayer); i++)
        {
            if (cards[i] != -1)
            {
                printf(" | ");
                printSuit(suits[i]);
                printf(" |");
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");

        for (int i = PlayersCards * currentPlayer; i < PlayersCards + (PlayersCards * currentPlayer); i++)
        {
            if (cards[i] != -1)
            {
                if (cards[i] == 10)
                {
                    printf(" |_%d|", cards[i]);
                }
                else
                {
                    if (cards[i] == 11)
                    {
                        printf(" |__J|");
                    }
                    else if (cards[i] == 12)
                    {
                        printf(" |__Q|");
                    }
                    else if (cards[i] == 13)
                    {
                        printf(" |__K|");
                    }
                    else if (cards[i] == 14)
                    {
                        printf(" |__A|");
                    }
                    else
                    {
                        printf(" |__%d|", cards[i]);
                    }
                }
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");
        printf("\n");

        for (int i = PlayersCards * currentPlayer; i < PlayersCards + (PlayersCards * currentPlayer); i++)
        {
            if (cards[i] != -1)
            {
                printf("   %c  ", ('a' + i - (PlayersCards * currentPlayer)));
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");
        printf("\n");

        printf("Player %d card selection (a-m): ", player + 1);

        scanf("%c", &answer);

        answer = answer - 'a';
    } while (!(answer >= 0 && answer < 13) || cards[answer + (PlayersCards * currentPlayer)] == -1);

    int t = cards[answer + (PlayersCards * currentPlayer)];
    cards[answer + (PlayersCards * currentPlayer)] = -1;
    return t;
}

int promptOptions(char* title, char* options[], int optionsSize)
{
    int answer;

    do
    {
        clearScreen();
        printf("%s\n", title);

        for (int i = 0; i < optionsSize; i++)
        {
            printf("%d. %s\n", i + 1, options[i]);
        }
        printf("Choose option: ");

        scanf("%d", &answer);

        // Clear the input buffer of invalid data
        fflush(stdin);

    } while (!(answer >= 1 && answer <= optionsSize));

    return answer;
}

// Print in english the choice of the players
void printPlayersChoices()
{
    for (int i = 0; i < numberPlaying; i++)
    {
        printf("Player %d choose the ", i + 1, playersChoice[i]);

        if (playersChoice[i] == 11)
        {
            printf("Joker of ");
        }
        else if (playersChoice[i] == 12)
        {
            printf("Queen of ");
        }
        else if (playersChoice[i] == 13)
        {
            printf("King of ");
        }
        else if (playersChoice[i] == 14)
        {
            printf("Ace of ");
        }
        else
        {
            printf("%d of ", playersChoice[i]);
        }

        switch (suits[i])
        {
        case 0:
            printf("Spades");
            break;

        case 1:
            printf("Hearts");
            break;

        case 2:
            printf("Diamonds");
            break;

        case 3:
            printf("Clubs");
            break;
        }

        printf("\n");
    }
}

// Hand and display the winner of the game
void handleWinner()
{
    clearScreen();

    printPlayersChoices();

    printf("\n");

    int highest = 0;
    int highestPlayer = -1;

    int duplicates[4] = { 0, 0, 0, 0 };

    // get the player with the highjest unique card
    // and the displays it to the screen
    for (int i = 0; i < numberPlaying; i++)
    {
        for (int j = i + 1; j < numberPlaying; j++)
        {
            if (playersChoice[i] == playersChoice[j])
            {
                duplicates[i] = 1;
                duplicates[j] = 1;
            }
        }

        if (duplicates[i] == 1)
        {
            continue;
        }

        if (highest < playersChoice[i])
        {
            highest = playersChoice[i];
            highestPlayer = i;
        }
    }

    int roundTotal = 0;

    for (int i = 0; i < numberPlaying; i++)
    {
        roundTotal += playersChoice[i];
    }

    if (highestPlayer == -1)
    {
        printf("There was a tie the %d points roll over to the next round!", roundTotal);
        scorePool = roundTotal;
    }
    else
    {
        printf("Player %d has won the round ", highestPlayer + 1);
        printf("and was awarded %d points\n", roundTotal + scorePool);
        playersScore[highestPlayer] += roundTotal + scorePool;
    }

    printf("\n");

    printf("Press enter key to close...");
    getchar();
}

// Next round prompt
void nextRound()
{
    char title[60];
    sprintf(title, "Take your turn Player %d", currentPlayer + 1);

    int takenTurn = 0;

    do
    {
        char* options[] = { "Choose Card", "Save and Exit", "Exit without saving", "Ouput Status" };
        int option = promptOptions(title, options, 4);

        switch (option)
        {
        case 1:
            playersChoice[currentPlayer] = promptCards(currentPlayer);
            currentPlayer++;
            takenTurn = 1;
            break;

        case 2:
            saveGame();
            exitGame();
            break;

        case 3:
            exitGame();
            break;

        case 4:
            printStatus();
            break;
        }
    } while (takenTurn == 0);
}

// Load the game
void loadGame()
{
    clearScreen();

    FILE* file = fopen("Save.txt", "r");

    if (file == NULL)
    {
        printf("Save not found exiting!");
        getchar();
        exit(0);
    }

    fscanf(file, "%d", &currentRound);  // current Round
    fscanf(file, "%d", &numberPlaying); // number of players
    fscanf(file, "%d", &currentPlayer); // current player

    for (int i = 0; i < 4; i++)
    {
        for (int j = i * PlayersCards; j < PlayersCards + (PlayersCards * i); j++)
        {
            fscanf(file, "%d,", &cards[j]);
        }

        for (int j = i * PlayersCards; j < PlayersCards + (PlayersCards * i); j++)
        {
            fscanf(file, "%d,", &suits[j]);
        }

        fscanf(file, "%d,", &playersScore[i]);
    }

    fclose(file);
}

// Save the game
void saveGame()
{
    FILE* file = fopen("Save.txt", "w");

    fprintf(file, "%d\n", currentRound);  // current Round
    fprintf(file, "%d\n", numberPlaying); // number of players
    fprintf(file, "%d\n", currentPlayer); // current player

    for (int player = 0; player < 4; player++)
    {
        fprintf(file, "\n");

        for (int j = player * PlayersCards; j < PlayersCards + (PlayersCards * player); j++)
        {
            fprintf(file, "%d,", cards[j]);
        }

        fprintf(file, "\n");

        for (int j = player * PlayersCards; j < PlayersCards + (PlayersCards * player); j++)
        {
            fprintf(file, "%d,", suits[j]);
        }

        fprintf(file, "\n");

        // Player score
        fprintf(file, "%d,", playersScore[player]);

        fprintf(file, "\n");
    }

    fclose(file);
}

// Print the status of the game
void printStatus()
{
    clearScreen();

    printf("Status:\n");
    for (int i = 0; i < numberPlaying; i++)
    {
        printf("Player %d's score %d\n", i + 1, playersScore[i]);
    }
    printf("Score pool for next round %d\n", scorePool);

    printf("Press enter key to close...");
    getchar();
}

// Prompt the new game menu
void newGame()
{
    currentRound = 1;
    currentPlayer = 0;
    numberPlaying = 2;
    scorePool = 0;

    do
    {
        clearScreen();
        printf("Input the number of players playing 2-4\n");
        printf("Choose option: ");
        scanf("%d", &numberPlaying);
    } while (numberPlaying != 2 && numberPlaying != 3 && numberPlaying != 4);

    // Fill with default deck
    for (int i = 0; i < TotalCards; i++)
    {
        cards[i] = 2 + (i % PlayersCards);
        suits[i] = i / PlayersCards;
    }

    shuffleDeck();
}

// Prompt the exit game menu
void exitGame()
{
    char* options[] = { "New Game", "Load Game", "Quit" };
    int option = promptOptions("Menu", options, 3);

    switch (option)
    {
    case 1:
        newGame();
        break;

    case 2:
        loadGame();
        break;

    case 3:
        exit(0);
        break;
    }
}
