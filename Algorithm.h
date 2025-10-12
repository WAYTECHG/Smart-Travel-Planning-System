#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_HOTELS 100              //define CONSTANT numbers
#define MAX_BUDGET 1000
#define MAX_DESTINATIONS 100
#define INF 999999.0f

typedef struct {                    // build a object structure for hotels
    int id;                         //contain name, price, rating, and distance from city cetre
    char name[50];
    float price;
    float rating;
    float distance;
} Object;

Object objects[MAX_HOTELS];         //Empty list to store all the hotel objects
float distanceMatrix[MAX_HOTELS][MAX_HOTELS];
int objectCount=0;                  //variable for count the number of existed Hotels
void Load_file();                   // Function to load hotel data
void Load_Desfile();                // Function to load destination data
void toLower(char *str);            // lowercase function
int get_ValidInt(int min, int max); // Handle user input
// _____________________________ALgorithm functions_________________________________________

//____________________________ Bubble Sort by price _________________________________________
void Bubble_Sort() {
    Load_file();                                            //load the file data
    bool swapped;                                           //check whether is completely sorted
    for (int i = 0; i < objectCount-1; i++) {
        swapped = false;
        for (int j = 0; j < objectCount - i-1; j++) {
            if (objects[j].price > objects[j+1].price) {    //if current is bigger than next element
                Object temp = objects[j];                   // Swap them
                objects[j] = objects[j+1];
                objects[j+1] = temp;
                swapped = true;}
        }
        if(!swapped){break;}                                //if completely sorted, then end program
    }
    printf("\nHotels sorted by price (from lowest to highest):\n");
    printf("===================================================================\n");
    printf("| %-3s | %-4s | %-20s | %-7s | %-6s | %-8s |\n", //Display the sorted result to user
           "No", "ID", "HOTEL NAME", "Price", "Rating", "Distance");
    printf("===================================================================\n");
    for (int i = 0; i < objectCount; i++) {                 //Display all the details of Hotels
        printf("| %-3d | %-4d | %-20s | %-7.2f | %-6.1f | %-8.2f |\n",
            i+1, objects[i].id, objects[i].name, objects[i].price, objects[i].rating, objects[i].distance);}
    printf("===================================================================\n\n");
}

//______________________ Merge Sort by rating in descending order _________________________________________
void merge(Object arr[], int p, int q, int r);
void Merge_Sorting(Object arr[], int l, int h);

//calling for Merge sort function
void Merge_Sort() {
    Load_file();                                            //load the file data
    if (objectCount > 1) {                                  //check whether have data inside file
        Merge_Sorting(objects, 0, objectCount-1);           //call Merge sort recursion function
        printf("\nHotels sorted by rating (from highest to lowest):\n");
        printf("===================================================================\n");
        printf("| %-3s | %-4s | %-20s | %-7s | %-6s | %-8s |\n", //Display the sorted result to user
               "No", "ID", "HOTEL NAME", "Price", "Rating", "Distance");
        printf("===================================================================\n");
        for (int i = 0; i < objectCount; i++) {             //Display all the details of Hotels
            printf("| %-3d | %-4d | %-20s | %-7.2f | %-6.1f | %-8.2f |\n",
                i+1, objects[i].id, objects[i].name, objects[i].price, objects[i].rating, objects[i].distance);
        }printf("===================================================================\n\n");
    }else{
        printf("Not enough hotels to sort.\n");             //if not data then display error message
    }
}
void Merge_Sorting(Object arr[], int l, int h) {
    if (l < h) {
        int m = (l+ h)/ 2;
        Merge_Sorting(objects, l, m);                       //divide array into two subarray recursively
        Merge_Sorting(objects, m+1, h);
        merge(objects, l, m, h);                            //merge subarrays to obtain the desired sorted array
    }
}
void merge(Object arr[], int p, int q, int r) {
    int s = p, t=q+1, k=p;
    Object B[MAX_HOTELS];                                   //Build an empty array B
    while(s<=q && t<=r){
        if(arr[s].rating>= arr[t].rating){                  //compare element between two subarray
            B[k++] = arr[s++];                                  //put the bigger element into array B
        }else{
            B[k++] = arr[t++];}}
    while(s<=q) {                                           //append the remaining elements arr[s...p] to array B
        B[k++] = arr[s++];
    }
    while(t<=r){                                            //append the remaining elements arr[t...r] to array B
        B[k++] = arr[t++];
    }
    for (int i=p; i<=r;i++){                                //Copy back to original array
        arr[i] = B[i];}
}

//_____________________________________ Binary Search__________________________________________
int binarySearchHotel(Object hotels[], int, int, int);          // Prototype for ID-based binary search

void Binary_Search() {
    Object *hotels = objects;                                   // Pointer to global hotel array
    Load_file();                                                // Load hotel data from file
    if (objectCount < 0) return;                                // Exit if no objects loaded
    char nameToSearch[100];                                     // Variable to store user input
    printf("Enter hotel name to search: ");
    scanf(" %[^\n]", nameToSearch);                             // Read full line with spaces
    while (getchar() != '\n');       // Clear the input buffer

    toLower(nameToSearch);                                      // Convert input to lowercase for case-insensitive match
    // Sort hotels alphabetically by name (case-insensitive bubble sort)
    for (int i = 0; i < objectCount - 1; i++) {
        for (int j = i + 1; j < objectCount; j++) {
            char name1[100], name2[100];
            strcpy(name1, hotels[i].name);                      // Copy first hotel name
            strcpy(name2, hotels[j].name);                      // Copy second hotel name
            toLower(name1);                                     // Convert to lowercase
            toLower(name2);                                     // Convert to lowercase
            if (strcmp(name1, name2) > 0) {                     // If out of order, swap
                Object temp = hotels[i];
                hotels[i] = hotels[j];
                hotels[j] = temp;}}
    }
    // Perform binary search on sorted array (case-insensitive)
    int left = 0, right = objectCount - 1;
    int index = -1;
    while (left <= right) {
        int mid = (left + right) / 2;                           // Find middle index
        char midName[100];
        strcpy(midName, hotels[mid].name);                      // Copy middle hotel name
        toLower(midName);                                       // Convert to lowercase
        int cmp = strcmp(nameToSearch, midName);                // Compare input with mid
        if (cmp == 0) {
            index = mid;                                        // Match found
            break;
        } else if (cmp < 0) {
            right = mid - 1;                                    // Search in left half
        } else {
            left = mid + 1;}                                    // Search in right half
    }
    // Display hotel details if found
    if (index != -1) {
        printf("\n================================== HOTEL FOUND ==================================\n");
        printf("| ID   | Name                         | Price (RM) | Rating   | Distance        |\n");
        printf("=================================================================================\n");
        printf("| %-4d | %-28s | %-10.2f | %-8.1f | %-9.1f km    |\n",
            hotels[index].id, hotels[index].name, hotels[index].price, hotels[index].rating, hotels[index].distance);
        printf("=================================================================================\n\n");
    } else {
        printf("\nHotel with name \"%s\" not found.\n\n", nameToSearch); // If no match
    }
}

int binarySearchHotel(Object hotels[], int left, int right, int targetId) {
    while (left <= right) {
        int mid = left + (right - left) / 2;                      // Avoid overflow in midpoint calculation
        if (hotels[mid].id == targetId)
            return mid;                                           // Found by ID
        else if (hotels[mid].id < targetId)
            left = mid + 1;                                       // Search right half
        else
            right = mid - 1; }                                    // Search left half
    return -1;                                                    // Not found
}
// Convert a string to lowercase
void toLower(char *str) {
    for (int i = 0; str[i]; i++)                                  // Loop through each character
        str[i] = tolower((unsigned char)str[i]);                  // Convert to lowercase safely
}

//________________________ 01 Knapsack Dynamic Programming___________________________________
//combination of budget and total rating
void Knapsack(double Budget){
    printf("\nInput Budget: RM %0.2lf\n", Budget);
    int budget = (int)(rint(Budget));                       //budget get from user's input
    Load_file();                                            //load the file data
    if (objectCount == 0) {
        printf("No hotels available.\n");
        return;}
    double Knap_table[MAX_HOTELS+1][MAX_BUDGET+1];
    for(int i=0; i<=objectCount; i++){                      //create an empty table fill by 0
        Knap_table[i][0] = 0.0;}
    for(int i=0; i<=budget; i++){
        Knap_table[0][i] = 0.0;}

    for(int i=1; i<=objectCount; i++){
        for(int j=1; j<=budget; j++){                       //Apply Knapsack Algorithm
            if(j>=objects[i-1].price){                      //if (w-wi)>=0, compare and find maximum value
                Knap_table[i][j] = fmax(Knap_table[i-1][j], Knap_table[i-1][j-(int)(rint(objects[i-1].price))]+objects[i-1].rating);
            }else{
                Knap_table[i][j] = Knap_table[i-1][j];}}}
    int i = objectCount;
    int j = budget;
    bool selected[MAX_HOTELS] = {false};                    //Apply backtrack to find the selected items
    while (i > 0 && j > 0) {
        if (Knap_table[i][j] != Knap_table[i-1][j]) {       // Mark as selected when knapsack table changes
            selected[i-1] = true;
            j -= (int)(rint(objects[i-1].price));}          // Reduce the remaining budget
        i--;                 // Move to the previous hotel
    }
    printf("\nSelected Hotels within Budget:\n");
    printf("===================================================================\n");
    printf("| %-3s | %-4s | %-20s | %-7s | %-6s | %-8s |\n", //Display the selected Hotels
           "No", "ID", "HOTEL NAME", "Price", "Rating", "Distance");
    printf("===================================================================\n");
    int count = 0;
    double total_price = 0.0, total_rating = 0.0;
    for (int i = 0; i < objectCount; i++) {
        if (selected[i]) {
            count++;
            total_price += objects[i].price;
            total_rating += objects[i].rating;              //Display the Hotels' details
            printf("| %-3d | %-4d | %-20s | %-7.2f | %-6.1f | %-8.2f |\n",
                   count, objects[i].id, objects[i].name, objects[i].price, objects[i].rating, objects[i].distance);}
    }
    printf("===================================================================\n");
    printf("|TOTAL PRICE: RM %2.2lf\t\t  TOTAL RATING: %2.2lf stars        |\n",total_price,total_rating);
    printf("===================================================================\n");
    if (count == 0) {
        printf("No suitable hotels found within the budget.\n\n");
    }
}

//__________________________________________Djikstra__________________________________________________
void Dijkstra() {
    Load_Desfile();                                     // This loads destination into objects[] array
    Load_DistanceMatrix(objectCount);                   // Use objectCount instead of hotelCount

    if (objectCount < 2) {
        printf("Need at least 2 destinations to find paths.\n");
        return;}
    // Display destination list with proper numbering
    printf("\n=== List of Destinations (Starting Point) ===\n");
    for (int i = 0; i < objectCount; i++) {
        printf("%d. %s \n", i+1, objects[i].name);
    }
    // Get valid starting destination selection
    int start = get_ValidInt(1, objectCount) - 1;       // Convert to 0-based index

    // Dijkstra's algorithm implementation
    float dist[MAX_HOTELS];
    int prev[MAX_HOTELS];
    bool visited[MAX_HOTELS] = {false};                 // Track visited nodes

    // Initialize distances and previous nodes
    for (int i = 0; i < objectCount; i++) {
        dist[i] = INF;                                  // Set all distances to INF initially
        prev[i] = -1;                                   // No previous node yet
    }
    dist[start] = 0;                                    // Distance to start node is 0

    // Main algorithm loop
    for (int count = 0; count < objectCount - 1; count++) {
        // Find the unvisited node with minimum distance
        float min_dist = INF;
        int u = -1;
        for (int v = 0; v < objectCount; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];                     // Update min_dist and index
                u = v;}
        }
        if (u == -1) break;                             // No more reachable nodes
        visited[u] = true;                              // Mark as visited
        // Update distances for adjacent nodes
        for (int v = 0; v < objectCount; v++) {
            if (!visited[v] && distanceMatrix[u][v] != INF) {
                float alt = dist[u] + distanceMatrix[u][v]; // New potential distance
                if (alt < dist[v]) {
                    dist[v] = alt;                      // Update shortest distance
                    prev[v] = u;                        // Track previous node
        }}}
    }

    // Print results
    printf("\nShortest paths from %s:\n", objects[start].name);
    printf("========================================\n");
    for (int i = 0; i < objectCount; i++) {
        if (i == start) continue;                 // Skip path to self
        if (dist[i] == INF) {
            printf("No path to %s\n", objects[i].name);  // Unreachable
        } else {
            // Reconstruct path
            int path[MAX_HOTELS];
            int path_length = 0;
            for (int at = i; at != -1; at = prev[at]) {
                path[path_length++] = at;         // Build path in reverse
            }
            // Print path in correct order
            printf("Path to %s (%.2f km): ", objects[i].name, dist[i]);
            for (int j = path_length - 1; j >= 0; j--) {
                printf("%s", objects[path[j]].name);
                if (j > 0) printf(" -> ");         // Arrow between path nodes
            }
            printf("\n");}
        printf("----------------------------------------\n\n");
    }
}

//__________________________________ File function ____________________________________________

//_______________________________Load form hotels.txt__________________________________________
void Load_file() {
    FILE *file = fopen("hotels.txt", "r");                  //open file
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    objectCount = 0;
    while (fscanf(file, "%d %s %f %f %f",                   //read all the data inside file
                  &objects[objectCount].id,
                  objects[objectCount].name,
                  &objects[objectCount].price,
                  &objects[objectCount].rating,
                  &objects[objectCount].distance) == 5) {
        objectCount++;                                      //count for the number of hotels
        if (objectCount >= MAX_HOTELS) break;               //interupt when exceeding
    }
    fclose(file);                                           //close file
}
void Load_Desfile() {
    FILE *file = fopen("destination.txt", "r");                  // Open hotel data file for reading
    if (file == NULL) {                                     // Check if file failed to open
        printf("Failed to open destination.txt.\n");
        return;
    }
    objectCount = 0;                                         // Initialize hotel counter
    while (fscanf(file, "%d %s",                   // Read hotel data from file
                 &objects[objectCount].id,
                 objects[objectCount].name) == 2) {
        objectCount++;                                       // Increment hotel count
        if (objectCount >= MAX_HOTELS) break;                // Stop if max limit reached
    }
    fclose(file);                                           // Close the hotel file
    Load_DistanceMatrix(objectCount);                        // Load corresponding distance matrix
}
