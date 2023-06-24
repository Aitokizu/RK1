#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MAX_SENTENCE_LENGTH 100
#define GAME_DURATION 10
#define CORRECT_SCORE 2
#define MAX_ERRORS 5
#define WINNING_SCORE 10

void generateSentence(char* sentence) {
    FILE* file = fopen("C:\\Users\\reeds\\CLionProjects\\RK1\\sentences.txt", "r");
    if (file == NULL) {
        printf("Can't open file.\n");
        exit(1);
    }

    char line[MAX_SENTENCE_LENGTH];
    int numSentences = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        numSentences++;
    }

    rewind(file);

    int randomIndex = rand() % numSentences;
    int currentIndex = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentIndex == randomIndex) {
            line[strcspn(line, "\n")] = 0;  // Remove newline character
            strcpy(sentence, line);
            break;
        }

        currentIndex++;
    }

    fclose(file);
}

int main() {
    srand(time(NULL));

    printf("Welcome to the text typing speed game!\n");
    printf("You need to type sentences as quickly and accurately as possible.\n");
    printf("Ready? The game will start in 5 seconds!\n");
    printf("------------------------------------\n");
    Sleep(5000);

    char sentence[MAX_SENTENCE_LENGTH];
    generateSentence(sentence);

    printf("Type the following sentence: %s\n", sentence);

    time_t startTime = time(NULL);
    time_t currentTime;
    int timeElapsed = 0;
    int errors = 0;
    int score = 0;

    while (1) {
        currentTime = time(NULL);
        timeElapsed = currentTime - startTime;
        if (timeElapsed >= GAME_DURATION) {
            printf("------------------------------------\n");
            printf("Time's up! Game Over.\n");
            printf("Errors: %d\n", errors);
            printf("Score: %d\n", score);
            Sleep(1000);  // Delay for 1 second before exiting
            exit(0);
        }

        if (_kbhit()) {
            char input[MAX_SENTENCE_LENGTH];
            fgets(input, sizeof(input), stdin);

            // Remove the newline character from the input string
            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, sentence) == 0) {
                score += CORRECT_SCORE;
                if (score >= WINNING_SCORE) {
                    printf("------------------------------------\n");
                    printf("Congratulations! You won the game!\n");
                    printf("Score: %d\n", score);
                    Sleep(1000);  // Delay for 1 second before exiting
                    exit(0);
                }
                generateSentence(sentence);
                printf("Correct! Type the next sentence: %s\n", sentence);
            } else {
                errors++;
                if (errors >= MAX_ERRORS) {
                    printf("------------------------------------\n");
                    printf("Game Over! You made too many errors.\n");
                    printf("Errors: %d\n", errors);
                    printf("Score: %d\n", score);
                    Sleep(1000);  // Delay for 1 second before exiting
                    exit(0);
                }
                generateSentence(sentence);
                printf("Incorrect! Type the next sentence:\n%s\n", sentence);
            }
        }
    }

    return 0;
}

