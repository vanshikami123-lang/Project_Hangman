
# HANGMAN – The Ultimate Challenge

## FOCP-I C Programming Mini Project

**Project Name:** Hangman  
**Language:** C  
**University:** The NorthCap University

## About the Project

Hangman is a console-based word guessing game developed using the C programming language. The player has to guess a randomly selected secret word by entering one letter at a time before running out of attempts.

The game provides different categories and difficulty levels to make the experience more interactive and challenging.

## Features

- Four word categories:
  - Technology
  - Animals
  - Sports
  - General Knowledge
- Three difficulty levels: Easy, Medium and Hard.
- Random word selection.
- Interactive Hangman drawing.
- Letter-by-letter guessing.
- Hint system.
- Score calculation.
- Winning streak bonus.
- Duplicate letter detection.
- Input validation.
- Replay through the main menu.

## How to Play

1. Run the program.
2. Select PLAY GAME.
3. Choose a category.
4. Select a difficulty level.
5. Guess the secret word one letter at a time.
6. Type `?` to use your hint.
7. Guess the complete word before your attempts run out.

## Scoring System

| Action | Points |
|---|---:|
| Correct letter | +10 |
| Winning the game | +50 |
| Each remaining chance | +5 |
| Winning streak bonus | +20 |
| Using a hint | -5 |

## Technologies Used

- C Programming Language
- Standard C Libraries
- GCC Compiler

## How to Compile and Run

Compile using:

```bash
gcc -Wall -std=c11 main.c -o hangman
```

Run on Windows:

```bash
hangman.exe
```

Run on Linux:

```bash
./hangman
```

## Project Team

- Vanshika – Team Leader
- Charika – Team Member
- Hansika – Team Member

## Academic Details

**Course:** B.Tech Computer Science and Engineering  
**Subject:** Fundamentals of Computer Programming – I  
**University:** The NorthCap University

---

Developed as an academic mini-project for FOCP-I.
