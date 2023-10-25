#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

//Related structures and fuctions have been written into "FitnessDataStruct.h"

// Complete the main function
int main() {
    FILE *fp;

    char buff[255];
    char stepstr[10];



    char input[0];
    char filename[255];
    printf("A: Specify the filename to be imported . \n"
           "B: Display the total number of records in the file\n"
           "C: Find the date and time of the timeslot with the fewest steps\n"
           "D: Find the data and time of the timeslot with the largest number of steps\n"
           "E: Find the mean step count of all the records in the file\n"
           "F: Find the longest continuous period where the step count is above 500 steps\n"
           "Q: Quit\n");

    do {
        printf("Please enter the command: ");
        scanf("%s",input);


                        //====================Entering A====================
        if (strcmp(input, "A") == 0){
            printf("Input filename: ");
            scanf("%s",filename);

            fp=fopen(filename, "r");
            if (fgets(buff, 255, fp) == NULL){
                printf("Input error!\n");
            }
            fclose(fp);
        }

                         //====================Entering B====================
        else if (strcmp(input, "B") == 0){
            int record = 0;

            fp=fopen(filename, "r");
            // Read and count each line in the file
            while (fgets(buff, 255, fp) != NULL) {
                record++;
            }

            // Close the file

            printf("Total records: %d\n", record);
        }

                        //====================Entering C====================
        else if (strcmp(input, "C") == 0){
            FITNESS_DATA data;
            int minSteps = INT_MAX; // Initialize with the maximum possible value
            char minDate[11];
            char minTime[6];

            fp=fopen(filename, "r");
            // Read and process each line in the file
            while (fgets(buff, 255, fp) != NULL) {
                tokeniseRecord(buff, ",", data.date, data.time, stepstr);

                // Convert the stepstr to an integer and assign it to data.steps
                data.steps = atoi(stepstr);

                // Check if the current steps count is less than the minimum
                if (data.steps < minSteps) {
                    minSteps = data.steps;
                    strcpy(minDate, data.date);
                    strcpy(minTime, data.time);
                }
            }

            // Close the file
            if (minSteps != INT_MAX) {
                printf("Fewest steps:%s %s\n", minDate, minTime);
            } else {
                printf("No data found in the CSV file.\n");
            }
        }

                     //====================Entering D============================
        else if (strcmp(input, "D") == 0){
            FITNESS_DATA data;
            int maxSteps = 0; // Initialize with 0, assuming all steps are positive
            char maxDate[11];
            char maxTime[6];

            fp=fopen(filename, "r");
            // Read and process each line in the file
            while (fgets(buff, 255, fp) != NULL) {
                tokeniseRecord(buff, ",", data.date, data.time, stepstr);

                // Convert the stepstr to an integer and assign it to data.steps
                data.steps = atoi(stepstr);

                // Check if the current steps count is greater than the maximum
                if (data.steps > maxSteps) {
                    maxSteps = data.steps;
                    strcpy(maxDate, data.date);
                    strcpy(maxTime, data.time);
                }
            }

            // Close the file
            fclose(fp);

            if (maxSteps > 0) {
                printf("Largest steps: %s %s\n", maxDate, maxTime);
            } else {
                printf("No data found in the CSV file.\n");
            }
        }

                        //====================Entering E====================
        else if (strcmp(input, "E") == 0){
            FITNESS_DATA data;
            int totalSteps = 0;
            int recordCount = 0;


            fp=fopen(filename, "r");
            // Read and process each line in the file
            while (fgets(buff, 255, fp) != NULL) {
                tokeniseRecord(buff, ",", data.date, data.time, stepstr);

                // Convert the stepstr to an integer and add it to the totalSteps
                data.steps = atoi(stepstr);
                totalSteps += data.steps;
                recordCount++;
            }

            // Close the file
            fclose(fp);

            if (recordCount > 0) {
                double averageSteps = (double)totalSteps / recordCount;
                printf("Mean step count: %.0lf\n", averageSteps);
            } else {
                printf("No data found in the CSV file.\n");
            }
        }

                        //====================Entering F====================
        else if (strcmp(input, "F") == 0){
            FITNESS_DATA data;
            int currentSteps = 0;
            int maxSteps = 0;
            char maxStartDate[11];
            char maxStartTime[6];
            char maxEndDate[11];
            char maxEndTime[6];
            char currentStartDate[11];
            char currentStartTime[6];
            char currentEndDate[11];
            char currentEndTime[6];
            int recording = 0; // ==1 if recording a continuous period


            fp=fopen(filename, "r");
            // Read and process each line in the file
            while (fgets(buff, 255, fp) != NULL) {
                tokeniseRecord(buff, ",", data.date, data.time, stepstr);

                // Convert the stepstr to an integer
                data.steps = atoi(stepstr);

                if (data.steps >= 500) {
                    if (!recording) {
                        // Start recording a continuous period
                        strcpy(currentStartDate, data.date);
                        strcpy(currentStartTime, data.time);
                        recording = 1;
                    }
                    currentSteps += data.steps;
                    // Update the current end date and time
                    strcpy(currentEndDate, data.date);
                    strcpy(currentEndTime, data.time);
                } else {
                    if (recording) {
                        // End of a continuous period
                        if (currentSteps > maxSteps) {
                            maxSteps = currentSteps;
                            strcpy(maxStartDate, currentStartDate);
                            strcpy(maxStartTime, currentStartTime);
                            strcpy(maxEndDate, currentEndDate);
                            strcpy(maxEndTime, currentEndTime);
                        }
                        recording = 0;
                        currentSteps = 0;
                    }
                }
            }

            // Check if the last period was the longest
            if (currentSteps > maxSteps) {
                maxSteps = currentSteps;
                strcpy(maxStartDate, currentStartDate);
                strcpy(maxStartTime, currentStartTime);
                strcpy(maxEndDate, currentEndDate);
                strcpy(maxEndTime, currentEndTime);
            }

            // Close the file
            fclose(fp);

            if (maxSteps > 0) {
                printf("Longest period start: %s %s\n", maxStartDate, maxStartTime);
                printf("Longest period end: %s %s\n",maxEndDate, maxEndTime);
            } else {
                printf("No continuous period found with steps exceeding 500.\n");
            }
        }

    } while (strcmp(input, "Q") != 0);
    printf("Quit");


    return 0;
}