#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAX_HOTELS 100                  // Define maximum number of hotels
#define MAX_BUDGET 1000                 // Define maximum budget
#define INF 999999.0f                   // Define infinite value for unreachable paths

typedef struct {                        // Define structure for hotel objects
    int id;                             // Hotel ID
    char name[50];                      // Hotel name
    float price;                        // Hotel price
    float rating;                       // Hotel rating
    float distance;                     // Distance from city centre
} eObject;

eObject eobjects[MAX_HOTELS];           // Array to store hotel objects
int eobjectCount = 0;                   // Counter for number of hotels loaded

void eLoad_file();                      // Function to load hotel data
void eLoad_Desfile();                   // Function to load destination data
int input_ValidInt(int, int);           // Validate integer input
double input_ValidDoub(char s[], float, float); // Validate double input
void eMerge_Sort(int,int);              // Sort hotels by rating using merge sort
void eBubble_Sort(int,int);             // Sort hotels by price using bubble sort
void eKnapsack(float, float);           // Knapsack function for budget optimization
void FloydWarshall();                   // Floyd-Warshall algorithm for shortest paths
int User_DEFINE(char a[]);              // Convert user input into selection ID
int User_SortOrder();                   // Allow user to choose the sort order they prefer

float distanceMatrix[MAX_HOTELS][MAX_HOTELS]; // Distance matrix between hotels
int next[MAX_HOTELS][MAX_HOTELS];      // Path reconstruction matrix for Floyd-Warshall

const char *field_names[] = {          // Array of field names for display
    "",                                 // Index 0 (unused)
    "ID",
    "name",
    "price",
    "rating",
    "distance from the city centre."
};
const char *sort_Order[] = {          // Array of field names for display
    "",                                 // Index 0 (unused)
    "in Ascending Order",
    "in Descending Order"
};

// _________________________________________Extension PAGE________________________________________________
int Extension(){
    int user;
    double Budget, Rating;
    printf("\n===== Smart Travel Planner Extension System =====\n");            //Function to display system
    printf("1. Sort Hotels by User-Defined fields (Bubble Sort)\n");
    printf("2. Sort Hotels by User-Defined fields (Merge Sort)\n");
    printf("3. Select Optimal Hotels Within Budget (Knapsack)\n");
    printf("4. Find Shorest Path Between Destinations (Floyd-Warshall)\n");
    user = input_ValidInt(1,4);                                                 //get user input

    switch (user){                                                              //statement based on user choice
        case 1: eBubble_Sort(User_SortOrder(),User_DEFINE("Bubble Sort"));break;
        case 2: eMerge_Sort(User_SortOrder(),User_DEFINE("Merge Sort"));break;
        case 3: Budget = input_ValidDoub("your Budget RM", 0,1000);            //get Hotel's Price
                Rating = input_ValidDoub("Minimum Rating for the Hotel", 0,5);  //get Hotel's Minimum Rating;
                eKnapsack(Budget, Rating); break;
        case 4: FloydWarshall();break;
        default: break;
    }
    return 0;
}

// _________________________________________GET USER INPUT________________________________________________
int User_SortOrder(){
    int sort;
    printf("Sorting Order:\n");
    printf("1. Ascending Order\n");
    printf("2. Descending Order\n");
    sort = input_ValidInt(1,2);                                     //get user input for sorting order
    return sort;
}
int User_DEFINE(char a[]){
    int user;
    printf("\n=====================%s========================\n",a);
    printf("Your can choose to sort Hotels with the fields include:\n");
    printf("1. Hotel's ID\n");
    printf("2. Hotel's Name\n");
    printf("3. Hotel's Price\n");
    printf("4. Hotel's Rating\n");
    printf("5. Hotel's distance from the city centre.\n");
    user = input_ValidInt(1,5);                                     //get user input
    return user;
}
// ___________________________________Extension ALgorithm functions_______________________________________________

//__________________________________Bubble Sort by USER-DEFINE FIELDS_____________________________________________
void eBubble_Sort(int sort, int user_defined) {
    eLoad_file();                                                   //load the file data
    bool swapped;                                                   //check whether is completely sorted
    switch (user_defined){                                          //switch statement based on USER-DEFINE FIELDS
        case 1: for (int i = 0; i < eobjectCount-1; i++) {
                    swapped = false;
                    for (int j = 0; j < eobjectCount - i-1; j++) {
                        if (eobjects[j].id > eobjects[j+1].id) {    //bubble sort based on hotel's ID
                            eObject temp = eobjects[j];
                            eobjects[j] = eobjects[j+1];
                            eobjects[j+1] = temp;
                            swapped = true;}
                    }if(!swapped){break;}                                //if completely sorted, then end program
                }break;
        case 2: for (int i = 0; i < eobjectCount-1; i++) {
                    swapped = false;
                    for (int j = 0; j < eobjectCount - i-1; j++) {  //bubble sort based on hotel's NAME
                        if (strcmp(eobjects[j].name, eobjects[j+1].name)>= 0) {
                            eObject temp = eobjects[j];
                            eobjects[j] = eobjects[j+1];
                            eobjects[j+1] = temp;
                            swapped = true;}
                    }if(!swapped){break;}                                //if completely sorted, then end program
                }break;
        case 3: for (int i = 0; i < eobjectCount-1; i++) {
                    swapped = false;
                    for (int j = 0; j < eobjectCount - i-1; j++) {  //bubble sort based on hotel's price
                        if (eobjects[j].price > eobjects[j+1].price) {
                            eObject temp = eobjects[j];
                            eobjects[j] = eobjects[j+1];
                            eobjects[j+1] = temp;
                            swapped = true;}
                    }if(!swapped){break;}                                //if completely sorted, then end program
                }break;
        case 4: for (int i = 0; i < eobjectCount-1; i++) {
                    swapped = false;
                    for (int j = 0; j < eobjectCount - i-1; j++) {  //bubble sort based on hotel's ratng
                        if (eobjects[j].rating > eobjects[j+1].rating) {
                            eObject temp = eobjects[j];
                            eobjects[j] = eobjects[j+1];
                            eobjects[j+1] = temp;
                            swapped = true;}
                    }if(!swapped){break;}                                //if completely sorted, then end program
                }break;
        case 5: for (int i = 0; i < eobjectCount-1; i++) {
                    swapped = false;
                    for (int j = 0; j < eobjectCount - i-1; j++) {  //bubble sort based on the distance from city centre
                        if (eobjects[j].distance > eobjects[j+1].distance) {
                            eObject temp = eobjects[j];
                            eobjects[j] = eobjects[j+1];
                            eobjects[j+1] = temp;
                            swapped = true;}
                    }if(!swapped){break;}                                //if completely sorted, then end program
                }break;
        default: break;}
    if(sort==2){                                                    //sort in descending order follow user requirement
        for(int i=0; i<eobjectCount/2;i++){
            eObject temp = eobjects[i];
            eobjects[i] = eobjects[eobjectCount-i-1];
            eobjects[eobjectCount-i-1] = temp;}
    }
    printf("===================================================================\n");
    printf("         Hotels sorted by %s (%19s)\n", field_names[user_defined], sort_Order[sort]);
    printf("===================================================================\n");
    printf("| %-3s | %-3s | %-20s | %-7s  | %-6s | %-8s |\n",
        "No","ID", "Name", "Price", "Rating", "Distance");
    printf("===================================================================\n");
    for (int i = 0; i < eobjectCount; i++) {                        //Display the sorted result to user
        printf("| %-3d | %-3d | %-20s | RM%-7.2f| %-6.1f | %-8.2f |\n",  //Display all the details of Hotels
            i+1, eobjects[i].id, eobjects[i].name, eobjects[i].price, eobjects[i].rating,eobjects[i].distance);}
    printf("===================================================================\n\n");
}
//__________________________________ Merge Sort by USER-DEFINE FIELDS_____________________________________________
void emerge(eObject arr[], int p, int q, int r,int user_defined);
void eMerge_Sorting(eObject arr[], int l, int h,int user_defined);

//calling for Merge sort function
void eMerge_Sort(int sort,int user_defined) {
    eLoad_file();                                                   //load the file data
    if (eobjectCount > 1) {                                         //check whether have data inside file
        eMerge_Sorting(eobjects, 0, eobjectCount-1, user_defined);  //call Merge sort recursion function
        if(sort==2){                                                //sort in descending order follow user requirement
            for(int i=0; i<eobjectCount/2;i++){
                eObject temp = eobjects[i];
                eobjects[i] = eobjects[eobjectCount-i-1];
                eobjects[eobjectCount-i-1] = temp;}
        }
        printf("===================================================================\n");
        printf("         Hotels sorted by %s (%19s)\n", field_names[user_defined], sort_Order[sort]);
        printf("===================================================================\n");
        printf("| %-3s | %-3s | %-20s | %-7s  | %-6s | %-8s |\n",
            "No","ID", "Name", "Price", "Rating", "Distance");
        printf("===================================================================\n");
        for (int i = 0; i < eobjectCount; i++) {                    //Display all the details of Hotels
            printf("| %-3d | %-3d | %-20s | RM%-7.2f| %-6.1f | %-8.2f |\n",
                i+1, eobjects[i].id, eobjects[i].name, eobjects[i].price, eobjects[i].rating, eobjects[i].distance);
        }
        printf("===================================================================\n\n");
    } else {
        printf("Not enough hotels to sort.\n");                     //if not data then display error message
    }
}

void eMerge_Sorting(eObject arr[], int l, int h, int user_defined) {
    if (l < h) {
        int m = (l+ h)/ 2;
        eMerge_Sorting(eobjects, l, m, user_defined);               //divide array into two subarray recursively
        eMerge_Sorting(eobjects, m+1, h, user_defined);
        emerge(eobjects, l, m, h, user_defined);                    //merge subarrays to obtain the desired sorted array
    }
}
void emerge(eObject arr[], int p, int q, int r, int user_defined) {
    int s = p, t=q+1, k=p;
    eObject B[MAX_HOTELS];                                          //Build an empty array B
    switch (user_defined){                                          //switch statement based on USER-DEFINE FIELDS
        case 1: while(s<=q && t<=r){
                if(arr[s].id<= arr[t].id){                          //merge sort based on hotel's ID
                    B[k++] = arr[s++];
                }else{
                    B[k++] = arr[t++];}
                }break;
        case 2: while(s<=q && t<=r){                                //merge sort based on hotel's Name
                if(strcmp(arr[s].name, arr[t].name) <= 0){
                    B[k++] = arr[s++];
                }else{
                    B[k++] = arr[t++];}
                }break;
        case 3: while(s<=q && t<=r){                                //merge sort based on hotel's Price
                if(arr[s].price<= arr[t].price){
                    B[k++] = arr[s++];
                }else{
                    B[k++] = arr[t++];}
                }break;
        case 4: while(s<=q && t<=r){                                //merge sort based on hotel's Rating
                if(arr[s].rating<= arr[t].rating){
                    B[k++] = arr[s++];
                }else{
                    B[k++] = arr[t++];}
                }break;
        default: break;
    }
    while(s<=q) {                           //append the remaining elements arr[s...p] to array B
        B[k] = arr[s];
        k++;
        s++;}
    while(t<=r){                            //append the remaining elements arr[t...r] to array B
        B[k] = arr[t];
        k++;
        t++;}
    for (int i=p; i<=r;i++){                //Copy back to original array
        arr[i] = B[i];}
}



//__________________________________ 01 Knapsack Dynamic Programming_____________________________________________
//combination of budget and total rating (include additional constraints: minimum rating)
void eKnapsack(float Budget, float Rating){
    printf("\nInput Budget: %0.2f\n", Budget);
    int ebudget = (int)(rint(Budget));                               //budget get from user's input
    eLoad_file();                                                   //load the file data
    if (eobjectCount == 0) {
        printf("No hotels available.\n");
        return;
    }
    double Knap_table[MAX_HOTELS+1][MAX_BUDGET+1];
    for(int i=0; i<=eobjectCount; i++){                             //create an empty table fill by 0
        Knap_table[i][0] = 0.0;}
    for(int i=0; i<=ebudget; i++){
        Knap_table[0][i] = 0.0;}

    for(int i=1; i<=eobjectCount; i++){                             //Apply Knapsack Algorithm
        for(int j=1; j<=ebudget; j++){                              //Adding condition minimum rating enter by user
            if(j>=eobjects[i-1].price && eobjects[i-1].rating>=Rating){  //if (w-wi)>=0, compare and find maximum value
                Knap_table[i][j] = fmax(Knap_table[i-1][j], Knap_table[i-1][j-(int)(rint(eobjects[i-1].price))]+eobjects[i-1].rating);
            }else{
                Knap_table[i][j] = Knap_table[i-1][j];}}}
    int i = eobjectCount;
    int j = ebudget;
    bool selected[MAX_HOTELS] = {false};                            //Apply backtrack to find the selected items
    while (i > 0 && j > 0) {
        if (Knap_table[i][j] != Knap_table[i-1][j]) {               // Mark as selected when knapsack table changes
            selected[i-1] = true;
            j -= (int)(rint(eobjects[i-1].price));}                 // Reduce the remaining budget
        i--;                 // Move to the previous hotel
    }
    printf("\nSelected Hotels within Budget:\n");
    printf("===================================================================\n");
    printf("| %-3s | %-4s | %-20s | %-7s | %-6s | %-8s |\n",        //Display the selected Hotels
           "No", "ID", "HOTEL NAME", "Price", "Rating", "Distance");
    printf("===================================================================\n");
    int count = 0;
    double total_price = 0.0, total_rating = 0.0;
    for (int i = 0; i < eobjectCount; i++) {
        if (selected[i]) {
            count++;
            total_price += eobjects[i].price;
            total_rating += eobjects[i].rating;                     //Display the Hotels' details
            printf("| %-3d | %-4d | %-20s | %-7.2f | %-6.1f | %-8.2f |\n",
                   count,eobjects[i].id,eobjects[i].name,eobjects[i].price, eobjects[i].rating,eobjects[i].distance);}}
    printf("===================================================================\n");
    printf("|TOTAL PRICE: RM %2.2lf\t\t  TOTAL RATING: %2.2lf stars        |\n",total_price,total_rating);
    printf("===================================================================\n\n");
    if (count == 0) {
        printf("No suitable hotels found within the budget.\n\n");
    }
}

// _______________________________________________FloydWarshall____________________________________________________
void FloydWarshall() {
    eLoad_Desfile();                                        // Load destination data into eobjects[] array
    if (eobjectCount < 2) {                                 // If less than 2 hotels, we can't compute any paths
        printf("Error: Need at least 2 destinations to find paths.\n");
        return;}
    FILE *fp = fopen("distances.txt", "r");                 // Try to open the distances file
    if (!fp) {                                              // If file can't be opened, show error
        printf("Error: Could not open distances.txt file.\n");
        printf("Please ensure the file exists in the same directory.\n");
        return;}
    // Initialize the distance and next matrices
    for (int i = 0; i < eobjectCount; i++) {
        for (int j = 0; j < eobjectCount; j++) {
            if (i == j) {
                distanceMatrix[i][j] = 0;                   // Distance to itself is 0
                next[i][j] = -1;                            // No next node needed
            } else {
                distanceMatrix[i][j] = INF;                 // Default distance is infinity
                next[i][j] = -1;                            // No path known yet
    }}}
    int expectedEntries = eobjectCount * eobjectCount;      // Total number of expected entries in distance file
    int entriesRead = 0;                                    // Counter for how many entries we have read
    char buffer[20];                                        // Buffer to read each value from file
    // Read all distances from the file
    for (int i = 0; i < eobjectCount; i++) {
        for (int j = 0; j < eobjectCount; j++) {
            if (fscanf(fp, "%19s", buffer) != 1) {          // Read string and check success
                printf("Error: Insufficient data in distances.txt.\n");
                printf("Expected %d entries but only found %d.\n", expectedEntries, entriesRead);
                fclose(fp);
                return;
            }
            entriesRead++;                                  // Successfully read one entry
            if (strcmp(buffer, "INF") == 0) {               // If distance is "INF", set to infinity
                distanceMatrix[i][j] = INF;
            } else {
                char *endptr;
                double value = strtod(buffer, &endptr);     // Try to parse as float
                if (*endptr != '\0') {                      // If parsing fails, invalid value
                    printf("Error: Invalid distance value '%s' at position (%d,%d).\n", buffer, i+1, j+1);
                    printf("Please use numbers or 'INF' for infinite distance.\n");
                    fclose(fp);
                    return;}
                distanceMatrix[i][j] = value;               // Set the parsed distance
                next[i][j] = j;                             // Initially, path goes directly to j
    }}}
    fclose(fp);                                             // Finished reading the file

    // Core of Floyd-Warshall: try every node as intermediate point
    for (int k = 0; k < eobjectCount; k++) {
        for (int i = 0; i < eobjectCount; i++) {
            for (int j = 0; j < eobjectCount; j++) {
                if (distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]) {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j]; // Update to shorter path
                    next[i][j] = next[i][k];                // Update next node to go through k
                }
    }}}
    // Ask user for a starting point for path finding
    char startName[50];                                     // Buffer for user input
    int start = -1;                                         // Index of starting destination
    while (start == -1) {
        printf("\nEnter starting destination name or ID (or 'list' to see available destinations): ");
        if (fgets(startName, sizeof(startName), stdin) == NULL) {  // Read user input
            printf("Error reading input.\n");
            return;}
        startName[strcspn(startName, "\n")] = '\0';         // Remove trailing newline character
        if (strcmp(startName, "list") == 0) {               // If user asks for list of hotels
            printf("\nAvailable Destinations:\n");
            for (int i = 0; i < eobjectCount; i++) {
                printf("%d. %s\n", eobjects[i].id, eobjects[i].name);  // Print each destination's ID and name
            }
            continue;                                       // Ask for input again
        }
        // Try to interpret input as an ID
        char *endptr;
        long inputId = strtol(startName, &endptr, 10);      // Try convert input to number
        if (*endptr == '\0') {                              // If successful, look for matching ID
            for (int i = 0; i < eobjectCount; i++) {
                if (eobjects[i].id == inputId) {
                    start = i;                              // Found matching ID
                    break;
        }}}
        // If not found by ID, try match by name
        if (start == -1) {
            for (int i = 0; i < eobjectCount; i++) {
                if (strcasecmp(startName, eobjects[i].name) == 0) {
                    start = i;                              // Found matching name
                    break;
        }}}
        if (start == -1) {                                  // If still not found, show error
            printf("Destination '%s' not found. Please try again or enter 'list' to see options.\n", startName);
        }
    }

    // Print shortest paths from selected destination
    printf("\nShortest paths from %s:\n", eobjects[start].name);
    printf("--------------------------------------------------\n");
    int destinationsFound = 0;                              // Track how many paths were found
    for (int end = 0; end < eobjectCount; end++) {
        if (start == end) continue;                         // Skip self-paths

        if (distanceMatrix[start][end] == INF) {            // If no path exists
            printf("No path found to %s\n", eobjects[end].name);
            continue;
        }
        // Display path and distance
        printf("To %s (%.2f km):\n  ", eobjects[end].name, distanceMatrix[start][end]);
        int u = start;
        printf("%s", eobjects[u].name);                     // Print starting point
        while (u != end) {                                  // Follow the path using next[][]
            u = next[u][end];
            if (u == -1) {                                  // In case of error
                printf(" -> (path error)");
                break;
            }
            printf(" -> %s", eobjects[u].name);             // Print next destionation in path
        }
        printf("\n\n");                                     // End of one path
        destinationsFound++;                                // Count valid destination
    }
    if (destinationsFound == 0) {                           // If no paths were found at all
        printf("No reachable destinations found from %s.\n", eobjects[start].name);
    }
    printf("--------------------------------------------------\n");  // End output
}

//__________________________________ File function ____________________________________________

//_______________________________Load form hotels.txt__________________________________________
void eLoad_file() {
    FILE *file = fopen("hotels.txt", "r");                      //open file
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    eobjectCount = 0;
    //read all the data
    while (fscanf(file, "%d %s %f %f %f",                       //read all the data inside file
                  &eobjects[eobjectCount].id,
                  eobjects[eobjectCount].name,
                  &eobjects[eobjectCount].price,
                  &eobjects[eobjectCount].rating,
                  &eobjects[eobjectCount].distance) == 5) {
        eobjectCount++;                                         //count for the number of hotels
        if (eobjectCount >= MAX_HOTELS) break;                  //interupt when exceeding
    }
    fclose(file);                                               //close file
}
void eLoad_Desfile() {
    FILE *file = fopen("destination.txt", "r");                  // Open hotel data file for reading
    if (file == NULL) {                                     // Check if file failed to open
        printf("Failed to open destination.txt.\n");
        return;
    }
    eobjectCount = 0;                                         // Initialize hotel counter
    while (fscanf(file, "%d %s",                   // Read hotel data from file
                 &eobjects[eobjectCount].id,
                 eobjects[eobjectCount].name) == 2) {
        eobjectCount++;                                       // Increment hotel count
        if (eobjectCount >= MAX_HOTELS) break;                // Stop if max limit reached
    }
    fclose(file);                                           // Close the hotel file
    Load_DistanceMatrix(eobjectCount);                        // Load corresponding distance matrix
}

int input_ValidInt(int min, int max) {
    int input;
    char buffer[10];
    while (1) {
        printf("Enter your choice [%d~%d]: ", min, max);
        if (fgets(buffer, sizeof(buffer), stdin)) {                     //get input
            char *endptr;
            input = strtol(buffer, &endptr, 10);
            if (endptr == buffer || *endptr != '\n') {                  //check is it an number
                printf("Invalid input. Please enter a number.\n");
                continue;
            }
            if (input < min || input > max) {                           // check whether is in suitable range
                printf("Number out of range. Please try again.\n");
                continue;
            }
            return input;                                               //return integar
        } else {
            printf("Input error. Try again.\n");
        }
    }
}
double input_ValidDoub(char s[],float min, float max) {
    double input;
    char buffer[1000];
    while (1) {
        printf("Enter %s (%0.2f-> %0.2f): ", s, min, max);
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


