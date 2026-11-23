
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct
{
    const char *word;
    const char *hint;
} Word;

// Function declarations
void welcomeScreen(void);
void mainMenu(void);
void showInstructions(void);
int readNumber(const char *message, int min, int max);
int selectCategory(void);
int selectDifficulty(void);
const char *getCategoryName(int category);
void displayHangman(int wrong, int maxAttempts);
void displayWord(const char *word, const int guessed[]);
int isWordComplete(const char *word, const int guessed[]);
void playGame(int category, int difficulty, int *highScore, int *streak);

// Word banks
const Word technology[] =
{
    {"computer", "An electronic device used for processing data."},
    {"keyboard", "Used to type letters and numbers."},
    {"internet", "A worldwide network of connected computers."},
    {"robot", "A machine that can perform tasks automatically."},
    {"software", "Programs used by a computer."},
    {"database", "An organised collection of information."}
};

const Word animals[] =
{
    {"elephant", "The largest land animal."},
    {"penguin", "A bird that cannot fly but can swim."},
    {"giraffe", "An animal with a very long neck."},
    {"dolphin", "An intelligent sea mammal."},
    {"kangaroo", "An Australian animal that hops."},
    {"cheetah", "The fastest land animal."}
};

const Word sports[] =
{
    {"cricket", "A sport played with a bat and ball."},
    {"football", "A sport played with a round ball and two teams."},
    {"tennis", "A racket sport played over a net."},
    {"badminton", "A sport played using a shuttlecock."},
    {"hockey", "A sport played using sticks."},
    {"basketball", "A sport where players score in a hoop."}
};

const Word generalKnowledge[] =
{
    {"jupiter", "The largest planet in our solar system."},
    {"everest", "The highest mountain in the world."},
    {"oxygen", "A gas essential for human breathing."},
    {"amazon", "A famous rainforest in South America."},
    {"diamond", "A very hard and precious gemstone."},
    {"pacific", "The largest ocean on Earth."}
};

int main(void)
{
    int choice;
    int category;
    int difficulty;
    int highScore = 0;
    int streak = 0;

    srand((unsigned int)time(NULL));

    welcomeScreen();

    do
    {
        mainMenu();

        choice = readNumber("Enter your choice: ", 1, 3);

        switch(choice)
        {
            case 1:
                category = selectCategory();

                if(category == 0)
                    break;

                difficulty = selectDifficulty();

                if(difficulty == 0)
                    break;

                playGame(category, difficulty, &highScore, &streak);
                break;

            case 2:
                showInstructions();
                break;

            case 3:
                printf("\n================================\n");
                printf("       THANK YOU FOR PLAYING!\n");
                printf("================================\n");
                printf("Your session high score: %d\n", highScore);
                printf("See you again!\n");
                break;
        }

    } while(choice != 3);

    return 0;
}

// Welcome screen
void welcomeScreen(void)
{
    printf("\n");
    printf("====================================\n");
    printf("          H A N G M A N\n");
    printf("       THE ULTIMATE CHALLENGE\n");
    printf("====================================\n");
    printf("       Guess it before time runs out!\n");
    printf("====================================\n");
}

// Main menu
void mainMenu(void)
{
    printf("\n\n------------ MAIN MENU ------------\n");
    printf("1. PLAY GAME\n");
    printf("2. HOW TO PLAY\n");
    printf("3. EXIT\n");
    printf("-----------------------------------\n");
}

// Instructions
void showInstructions(void)
{
    printf("\n------------ HOW TO PLAY ------------\n");
    printf("1. Select a category.\n");
    printf("2. Select a difficulty level.\n");
    printf("3. A secret word will be selected randomly.\n");
    printf("4. Guess one letter at a time.\n");
    printf("5. Type ? to use your hint.\n");
    printf("6. Avoid too many wrong guesses.\n");
    printf("7. Guess the complete word to WIN!\n");
    printf("-------------------------------------\n");
    printf("SCORING:\n");
    printf("+10 points for each correct letter.\n");
    printf("+50 points for winning.\n");
    printf("+5 points for each remaining chance.\n");
    printf("+20 bonus points for a winning streak.\n");
    printf("A hint costs 5 points.\n");
}

// Input validation
int readNumber(const char *message, int min, int max)
{
    char input[100];
    char *end;
    long number;

    while(1)
    {
        printf("%s", message);

        if(fgets(input, sizeof(input), stdin) == NULL)
            return min;

        number = strtol(input, &end, 10);

        while(isspace((unsigned char)*end))
            end++;

        if(end == input || *end != '\0')
        {
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        if(number < min || number > max)
        {
            printf("Please enter a number between %d and %d.\n",
                   min, max);
            continue;
        }

        return (int)number;
    }
}

// Category selection
int selectCategory(void)
{
    int choice;

    printf("\n----------- SELECT CATEGORY -----------\n");
    printf("1. Technology\n");
    printf("2. Animals\n");
    printf("3. Sports\n");
    printf("4. General Knowledge\n");
    printf("5. Back to Main Menu\n");
    printf("---------------------------------------\n");

    choice = readNumber("Enter category: ", 1, 5);

    if(choice == 5)
        return 0;

    return choice;
}

// Difficulty selection
int selectDifficulty(void)
{
    int choice;

    printf("\n---------- SELECT DIFFICULTY ----------\n");
    printf("1. EASY   - 10 chances\n");
    printf("2. MEDIUM - 7 chances\n");
    printf("3. HARD   - 5 chances\n");
    printf("4. Back to Main Menu\n");
    printf("---------------------------------------\n");

    choice = readNumber("Enter difficulty: ", 1, 4);

    if(choice == 4)
        return 0;

    return choice;
}

// Get category name
const char *getCategoryName(int category)
{
    switch(category)
    {
        case 1: return "Technology";
        case 2: return "Animals";
        case 3: return "Sports";
        case 4: return "General Knowledge";
        default: return "Unknown";
    }
}

// Hangman drawing
void displayHangman(int wrong, int maxAttempts)
{
    int stage = (wrong * 6) / maxAttempts;

    printf("\n");

    printf(" +---+\n");
    printf(" |   |\n");

    if(stage >= 1)
        printf(" O   |\n");
    else
        printf("     |\n");

    if(stage == 2)
        printf(" |   |\n");
    else if(stage == 3)
        printf("/|   |\n");
    else if(stage >= 4)
        printf("/|\\  |\n");
    else
        printf("     |\n");

    if(stage == 5)
        printf("/    |\n");
    else if(stage >= 6)
        printf("/ \\  |\n");
    else
        printf("     |\n");

    printf("     |\n");
    printf("=========\n");
}

// Display the secret word
void displayWord(const char *word, const int guessed[])
{
    int i;

    printf("\nSecret Word: ");

    for(i = 0; word[i] != '\0'; i++)
    {
        if(guessed[word[i] - 'a'])
            printf("%c ", word[i]);
        else
            printf("_ ");
    }

    printf("\n");
}

// Check whether the word is complete
int isWordComplete(const char *word, const int guessed[])
{
    int i;

    for(i = 0; word[i] != '\0'; i++)
    {
        if(!guessed[word[i] - 'a'])
            return 0;
    }

    return 1;
}

// Main gameplay
void playGame(int category, int difficulty,
              int *highScore, int *streak)
{
    const Word *wordList;
    const char *secretWord;
    const char *hint;

    int maxAttempts;
    int wrong = 0;
    int score = 0;
    int guessed[26] = {0};
    int hintUsed = 0;
    int i;
    int found;
    int letterValue;

    char input[100];
    char guess;

    // Select word bank
    switch(category)
    {
        case 1:
            wordList = technology;
            break;

        case 2:
            wordList = animals;
            break;

        case 3:
            wordList = sports;
            break;

        default:
            wordList = generalKnowledge;
            break;
    }

    // Set difficulty
    if(difficulty == 1)
        maxAttempts = 10;
    else if(difficulty == 2)
        maxAttempts = 7;
    else
        maxAttempts = 5;

    // Random word selection
    i = rand() % 6;
    secretWord = wordList[i].word;
    hint = wordList[i].hint;

    printf("\n====================================\n");
    printf("          GAME STARTED!\n");
    printf("====================================\n");

    printf("Category: %s\n", getCategoryName(category));

    if(difficulty == 1)
        printf("Difficulty: EASY\n");
    else if(difficulty == 2)
        printf("Difficulty: MEDIUM\n");
    else
        printf("Difficulty: HARD\n");

    printf("You have %d chances.\n", maxAttempts);

    // Game loop
    while(wrong < maxAttempts &&
          !isWordComplete(secretWord, guessed))
    {
        displayHangman(wrong, maxAttempts);
        displayWord(secretWord, guessed);

        printf("\nScore: %d\n", score);
        printf("Remaining chances: %d\n", maxAttempts - wrong);

        printf("\nEnter a letter (or ? for hint): ");

        if(fgets(input, sizeof(input), stdin) == NULL)
            return;

        input[strcspn(input, "\n")] = '\0';

        if(strlen(input) != 1)
        {
            printf("Please enter only one character.\n");
            continue;
        }

        guess = (char)tolower((unsigned char)input[0]);

        // Hint system
        if(guess == '?')
        {
            if(hintUsed)
            {
                printf("You have already used your hint!\n");
            }
            else
            {
                printf("\nHINT: %s\n", hint);
                score -= 5;

                if(score < 0)
                    score = 0;

                hintUsed = 1;
            }

            continue;
        }

        if(!isalpha((unsigned char)guess))
        {
            printf("Please enter a valid alphabet letter.\n");
            continue;
        }

        letterValue = guess - 'a';

        if(guessed[letterValue])
        {
            printf("You already guessed that letter!\n");
            continue;
        }

        guessed[letterValue] = 1;
        found = 0;

        for(i = 0; secretWord[i] != '\0'; i++)
        {
            if(secretWord[i] == guess)
            {
                found = 1;
                score += 10;
            }
        }

        if(found)
        {
            printf("\nCORRECT GUESS! Great job!\n");
        }
        else
        {
            wrong++;
            printf("\nWRONG GUESS! Be careful!\n");
        }
    }

    // Final display
    displayHangman(wrong, maxAttempts);
    displayWord(secretWord, guessed);

    // Win or lose
    if(isWordComplete(secretWord, guessed))
    {
        printf("\n====================================\n");
        printf("          CONGRATULATIONS!\n");
        printf("             YOU WON!\n");
        printf("====================================\n");

        score += 50;
        score += (maxAttempts - wrong) * 5;

        (*streak)++;

        if(*streak > 1)
        {
            score += 20;
            printf("Winning streak bonus: +20 points!\n");
        }
    }
    else
    {
        printf("\n====================================\n");
        printf("             GAME OVER!\n");
        printf("====================================\n");
        printf("The correct word was: %s\n", secretWord);

        *streak = 0;
    }

    printf("\nYour final score: %d\n", score);

    if(score > *highScore)
    {
        *highScore = score;
        printf("NEW SESSION HIGH SCORE!\n");
    }

    printf("Session high score: %d\n", *highScore);
    printf("Winning streak: %d\n", *streak);

    printf("\nReturning to Main Menu...\n");
}
