# Blackjack

# LC-3-Five-Exam-Averaging-ASM-Program
## Table of contents
* [General Info](#General-info)
* [Author](#Author)
* [Techologies](#Technologies)
* [Setup](#Setup)
* [Usage](#Usage)
* [Minimum hardware requirements](#Minimum-hardware-requirements)
* [Features](#Features)
* [Screenshots](#Screenshots)
* [Project status](#Project-status)
* [Room for improvement](#Room-for-improvement)
* [Release date](#Release-date)
* [Acknowledgements](#Acknowledgements)
* [Sources](#Sources)
* [Contact](#Contact)

## General info
JasonAshCIS7DiscreteStructuresCourseProjectBlackjack.cpp is a program that I wrote in C++ for the course project in CIS-7: Discrete structures, taught at Moreno Valley College by Prof. Kasey Nguyen, PhD. It is a text-based C++ Blackjack game that demonstrates discrete structures concepts through algorithms that accomplish the game's logic according to its rules, and it continually updates the probability of obtaining 21 or going bust before and after each hit.

## Author
- Jason Ash, Computer Science Major

## Technologies:
I wrote the source code in Notepad, and edited syntax errors (and a few logic errors) using Code::Blocks IDE. I compiled it using Code::Blocks' default GNU GCC compiler.

## Setup
To make an executable file, compile the source code using your favorite C++ compiler or IDE. Then, run the resulting executable.

## Usage
After running the program, the program's purpose is displayed, and it deals the player and dealer two cards each, which are shown as text. Only the dealer's up card (second card) is shown until the dealer's turn. The program totals the player's hand and asks the player whether or not they want to hit by entering 'h' or 'H'. The probability of obtaining 21 or going bust (calculated as the number of possible next hands that result in that outcome divided by the total number of outcomes) is displayed, informing the player so that he/she can strategize accordingly. Note: on hands with a value of 11 or less, the probability of going bust will be zero, and the likelihood of obtaining 21 on a hand of 10 or less is zero. During the dealer's turn, the up card is revealed, and the program likewise displays the probability of the dealer obtaining 21 or going bust on the next hit. The dealer's turn is automated according to casino rules, which are that the dealer must hit on 16 or less and stand on 17 or more. At the end of the game, the player is prompted to enter 'y' or 'Y' to play again.

Scoring is also done according to casino rules:
- If the player obtains a Blackjack, the player automatically wins.
- If both the player and dealer are dealt Blackjacks, then the player also wins.
- If the dealer has a Blackjack, but the player does not, the player automatically loses.
- If the player busts, then he/she loses even if the dealer also busts.
- If the player and dealer have the same hand, that is called a push, and the game outcome is considered a tie.
- If none of the above scenarios apply, then the player wins if their hand is closer to 21 without going over, and the dealer wins if the dealer's hand is closer to 21 without going over.

## Minimum hardware requirements
Although I developed this on a fairly recent Windows 11 PC, this program should run comfortably on any working computer with sufficient processing power, RAM, a monitor manufactured within the past 15-20 years, and an Internet connection to download the .cpp source file. 

## Features
- One player in addition to the dealer.
- Implements a standard 52-card deck without Jokers.
- The player will be allowed to hit until 21 is reached or they go bust.
- Aces count as 11 on any hand with a value of 10 or below. In hands with a value of more than 10, aces count as one.
- The AI strategy of the dealer follows casino rules in that the dealer must hit on a hand with a value of 16 or less and stand on 17 or more.
- Scoring is done according to the casino rules explained above.
- The dealer's hole card is not revealed until after the player's turn is complete.

## Screenshots
![A screen capture of the Blackjack game that I developed for my Discrete Structures course project showing the probabilities and various combinations of hands as cards are dealt and the game progresses.](ScreenShotOfDiscreteStructuresBlackjackRunningInTerminalWindow.png)

## Project status
Completed according to the requirements of the project and released here on GitHub.

## Room for improvement
- Combining the three multiplication and two division subroutines into one subroutine for each that is called by the respective part of the program that needs their return values.
- Rounding the average score according to math rounding rules instead of either rounding up all fractional scores, truncating average scores, or being off-by-one on the average score.
- Handling fractional scores with decimal values since the LC-3 has no floating point support and only processes integers.
- Asking the user how many test scores they want to enter to average or averaging test scores for an entire class (both of which are beyond the scope of this project).

## Release date
24 November, 2025

## Acknowledgements
Prof. Kasey Nguyen is the project advisor.

## Sources
- Computer architecture and organization, and LC-3 assembly language programming are explained in the textbook:
Patt, Yale, and Patel, Sanjay. Ise Introduction to Computing Systems: From Bits & Gates to C. 3rd ed., 	McGraw-Hill, 	2020.
- “What Is a Swimlane Diagram?” Lucidchart, 8 May 2025, www.lucidchart.com/pages/tutorial/swimlane-diagram#:~:text=A%20swimlane%20diagram%20is%20a,employee%2C%20work%20group%20or%20department 
