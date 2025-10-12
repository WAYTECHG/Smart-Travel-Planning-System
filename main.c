#include <stdio.h>
#include "hotel_func.h"
#include "Algorithm.h"
#include "Extension.h"

#define MAX_HOTELS 100                              //define CONSTANT numbers
#define MAX_DESTINATIONS 100

int get_ValidInt(int, int);
double get_ValidBudget(float, float);

int main(){
    int user;                                       //define variables to get user input
    double budget;
    do{
        Display_System();                           //display system PAGE
        user = get_ValidInt(1,11);                  //get user input with error handling

        switch(user){                               //switch statement
            case 1: Add_Hotel(); break;             //call Add_Hotel() function
            case 2: View_ALLHotels(); break;        //call View_ALLHotel() function
            case 3: Bubble_Sort(); break;           //call Bubble_Sort() function
            case 4: Merge_Sort(); break;            //call Merge_Sort() function
            case 5: Binary_Search();break;          //call Binary_Search() function
            case 6: budget = get_ValidBudget(0,1000);     //get user input of their budget
                    Knapsack(budget); break;        //call Knapsack() function
            case 7: Add_Destination();break;        //call Add_Destination() function
            case 8: Add_Path();break;               //call Add_Patht() function
            case 9: Dijkstra(); break;              //call Dijkstra() function
            case 11: Extension();                   //call Extension()
                    break;
            default: printf("SYSTEM EXIT!! Thank You"); //System EXIT when user input=9
        }
    }while(user!=10);
}

int get_ValidInt(int min, int max) {
    int input;
    char buffer[10];
    while (1) {
        printf("Enter your choice [%d~%d]: ", min, max);
        if (fgets(buffer, sizeof(buffer), stdin)) {                     //get input
            char *endptr;
            input = strtol(buffer, &endptr, 10);
            if (endptr == buffer || *endptr != '\n') {                  //check is it an integar
                printf("Invalid input. Please enter a number.\n");
                continue;
            }
            if (input < min || input > max) {                           //check whether in suitable range
                printf("Number out of range. Please try again.\n");
                continue;
            }
            return input;
        } else {
            printf("Input error. Try again.\n");
        }
    }
}

double get_ValidBudget(float min, float max) {
    double input;
    char buffer[1000];
    while (1) {
        printf("Enter your budget(0->1000): RM");
        if (fgets(buffer, sizeof(buffer), stdin)) {                     // get input
            char *endptr;
            input = strtof(buffer, &endptr);
            if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {              //check is it an number
                printf("Invalid input. Please enter a number.\n");
                continue;
            }
            if (input < min || input > max) {                           // check whether is in suitable range
                printf("Number out of range. Please try again.\n");
                continue;
            }
            return input;
        } else {
            printf("Input error. Try again.\n");
        }
    }
}
