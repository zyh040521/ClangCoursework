//
// Created by 赵永豪 on 2023/10/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UNTITLED1_FITNESSDATASTRUCT_H
#define UNTITLED1_FITNESSDATASTRUCT_H

#endif //UNTITLED1_FITNESSDATASTRUCT_H

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