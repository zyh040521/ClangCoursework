#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "FitnessDataStruct.h"

// Define any additional variables here

typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() {
    FILE *fp;
//    =========task1========
    fp=fopen("FitnessData_2023.csv", "r");
    FITNESS_DATA data;
    char buff[255];
    char stepstr[10];

    for (int i = 0; i < 3; ++i) {
        fgets(buff, 255, (FILE*)fp);
        tokeniseRecord(buff,",", data.date, data.time, stepstr);
        data.steps = atoi(stepstr);
        printf("%s/%s/%d\n", data.date, data.time, data.steps);
    }

    fclose(fp);
}
