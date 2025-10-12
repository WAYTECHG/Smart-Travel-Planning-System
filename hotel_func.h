#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_HOTELS 100                         // Maximum number of hotels
#define MAX_DESTINATIONS 100                   // Maximum number of destinations
#define INF 999999.0f                          // Representation of infinity for distances

typedef struct {                               // Hotel structure definition
    int id;                                    // Hotel ID
    char name[50];                             // Hotel name
    float price;                               // Hotel price
    float rating;                              // Hotel rating
    float distance;                            // Distance from city centre
} Hotel;

Hotel hotels[MAX_HOTELS];                      // Array to store hotel objects
float distanceMatrix[MAX_HOTELS][MAX_HOTELS];  // Matrix to store distances between hotels
int hotelCount;                                // Counter for the number of hotels

void Save_Hotels(Hotel *hotel);                // Function to save a hotel
void Save_DESs(Hotel *destination);            // Function to save a Destination
void Load_Hotelfile();                         // Function to load hotels from file
void Load_DESfile();                           // Function to load destinations from file
void clear_input_buffer();                     // Clears input buffer
double input_ValidDouble(char s[], float, float);  // Validates double input
void toLowerCase(char *str);                   // Converts string to lowercase
int isDuplicateName(const char *name);         // Checks for duplicate hotel names
void Load_DistanceMatrix(int newCount);        // Loads distance matrix from file
void Update_DistanceFile_With_INF(int newCount); // Updates file with INF where needed


// __________________________________SYSTEM Interface POAGE_________________________________________
int Display_System(){
    printf("===== Smart Travel Planner System =====\n");    //display the system page content
    printf("1. Add Hotel\n");
    printf("2. View All Hotels\n");
    printf("3. Sort Hotels by Price (Bubble Sort)\n");
    printf("4. Sort Hotels by Rating (Merge Sort)\n");
    printf("5. Search Hotel by Name (Binary Search)\n");
    printf("6. Select Optimal Hotels Within Budget (Knapsack)\n");
    printf("7. Add New Destinations\n");
    printf("8. Add Path between Destinations\n");
    printf("9. Find Shorest Path Between Destinations (Dijkstra)\n");
    printf("10. Exit\n");
    printf("11. Extension Function\n");
    return 0;
}

//___________________________________Hotel Adding Function___________________________________________
void Add_Hotel(){
    Load_Hotelfile();                                       //load the file data
    Hotel h;
    h.id = hotelCount + 1;                                  //define Hotel's ID
    while (1) {
        printf("Enter hotel name: ");                       //get Hotel's Name
        scanf("%s", h.name);
        if (isDuplicateName(h.name)) {                      //check whether name is existed
            printf("Hotel name already exists! Please enter a different name.\n");
            clear_input_buffer();
        } else {
            break;}
    }
    clear_input_buffer();
    h.price = input_ValidDouble("price", 0.0f, 1000.0f);           //get Hotel's Price
    h.rating = input_ValidDouble("rating", 0.0f, 5.0f);            //get Hotel's Rating
    h.distance = input_ValidDouble("distance from city center", 0.0f, 1000.0f);   //get the distance
    hotels[hotelCount++] = h;
    Save_Hotels(&h);                                        //save into hotels.txt file
    printf("Hotel added successfully!\n\n");
}
void Add_Destination(){
    Load_DESfile();                                       //load the file data
    Hotel h;
    h.id = hotelCount + 1;                                  //define Destination's ID
    while (1) {
        printf("Enter destination name: ");                       //get Destination's Name
        scanf("%s", h.name);
        if (isDuplicateName(h.name)) {                      //check whether name is existed
            printf("This destination name already exists! Please enter a different name.\n");
            clear_input_buffer();
        } else {
            break;}
    }
    clear_input_buffer();
    hotels[hotelCount++] = h;
    Save_DESs(&h);                                        //save into destination.txt file
    Update_DistanceFile_With_INF(hotelCount);
    printf("Destination added successfully!\n\n");
}

//____________________________PASTE ALL EXISTING HOTELS________________________________________
void View_ALLHotels(){
    Load_Hotelfile();                                       //load the file data
    if (hotelCount == 0) {
        printf("No hotel records found.\n");
        return;
    }
    printf("=============================================================\n");
    printf("| %-4s | %-20s | %-7s | %-6s | %-8s |\n",       //Display all the hotels to user
           "ID", "HOTEL NAME", "Price", "Rating", "Distance");
    printf("=============================================================\n");
    for (int i = 0; i < hotelCount; i++) {                  //Display all the details of Hotels
        printf("| %-4d | %-20s | %-7.2f | %-6.1f | %-8.2f |\n",
               hotels[i].id, hotels[i].name, hotels[i].price, hotels[i].rating, hotels[i].distance);}
    printf("=============================================================\n");
    printf("\n");
}

//________________________________ Display Distence Matrix ____________________________________________
void displayDistanceMatrix() {
    Load_DESfile();                                           // Load hotel names into hotels[]
    // Load distance matrix from file
    FILE *fp = fopen("distances.txt", "r");                     // Open the distances file for reading
    if (!fp) {
        perror("Failed to open distances.txt");                 // Print error if file not found
        return;
    }
    for (int i = 0; i < hotelCount; i++) {
        for (int j = 0; j < hotelCount; j++) {
            char buffer[20];
            fscanf(fp, "%s", buffer);                           // Read each distance value or "INF"
            if (strcmp(buffer, "INF") == 0)
                distanceMatrix[i][j] = INF;                     // Convert "INF" to constant value
            else
                distanceMatrix[i][j] = atof(buffer); }}         // Convert string to float
    fclose(fp);                                                 // Close the file after loading
    // Determine max hotel name length for formatting
    int maxNameLen = 0;
    for (int i = 0; i < hotelCount; i++) {
        int len = strlen(hotels[i].name);
        if (len > maxNameLen) maxNameLen = len;}                 // Find longest name
    int colWidth = (maxNameLen > 7) ? maxNameLen + 2 : 10;      // Minimum column width is 10
    // Compute total width for the entire table
    int totalWidth = (hotelCount + 1) * (colWidth + 2) + 1;     // +2 for padding, +1 for final '|'

    //print Distance Matrix
    printf("\nDistance Matrix (in km):\n\n");
    for (int i = 0; i < totalWidth; i++) printf("=");           // Print dynamic top border
    printf("\n");
    printf("| %-*s", colWidth, " ");                            // Top-left corner cell (blank)
    for (int i = 0; i < hotelCount; i++) {
        printf("| %-*s", colWidth, hotels[i].name);             // Hotel names as column headers
    }
    printf("|\n");
    for (int i = 0; i < totalWidth; i++) printf("=");           // Print header separator
    printf("\n");
    for (int i = 0; i < hotelCount; i++) {
        printf("| %-*s", colWidth, hotels[i].name);             // Row header (hotel name)
        for (int j = 0; j < hotelCount; j++) {
            if (distanceMatrix[i][j] == INF)
                printf("| %-*s", colWidth, "INF");              // Show "INF" for unreachable paths
            else
                printf("| %-*.2f", colWidth, distanceMatrix[i][j]);} // Show distance with 2 decimals
        printf("|\n");}
    for (int i = 0; i < totalWidth; i++) printf("=");           // Print bottom border
    printf("\n\n");
}

//_______________________________________ Add Path ____________________________________________
void Add_Path() {                                                   // Function to add paths between hotels
    Load_DESfile();                                               // Load hotel data from file
    if (hotelCount < 2) {                                           // Check if there are at least 2 hotels
        printf("Error: Need at least 2 destinations to add paths.\n");
        return;}
    Load_DistanceMatrix(hotelCount);                                // Load current distance matrix
    printf("\n=== Add Missing Paths Between destinations ===\n");         // Display section header
    bool anyAdded = false;                                          // Flag to track if any path was added
    char inputBuffer[100];                                          // Buffer for user input
    for (int i = 0; i < hotelCount; i++) {                          // Loop through all hotels (rows)
        for (int j = i + 1; j < hotelCount; j++) {                  // Loop through remaining hotels (columns)
            if (distanceMatrix[i][j] == INF) {                      // Check if path needs to be added
                printf("\nAdding path between:\n");                 // Display connection being added
                printf("%s --> %s\n", hotels[i].name, hotels[j].name);

                float dist;                                         // Variable to store distance input
                int validInput = 0;                                 // Flag for input validation
                while (!validInput) {                               // Loop until valid input is received
                    printf("Enter distance (km, 0 < distance <= 1000): ");
                    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
                        printf("Error reading input. Please try again.\n");
                        continue;}
                    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';  // Remove newline character
                    if (strcasecmp(inputBuffer, "INF") == 0) {       // Prevent "INF" input
                        printf("Error: You cannot manually set INF. Please enter a valid distance.\n");
                        continue;
                    }
                    char *endptr;                                   // Pointer for number conversion
                    dist = strtof(inputBuffer, &endptr);            // Convert string to float
                    if (endptr == inputBuffer) {                    // Check if conversion failed
                        printf("Error: No numeric input detected. Please enter a number.\n");
                    } else if (*endptr != '\0') {                   // Check for trailing characters
                        printf("Error: Invalid characters detected. Please enter only numbers.\n");
                    } else if (dist <= 0) {                         // Check for positive distance
                        printf("Error: Distance must be greater than 0.\n");
                    } else if (dist > 1000) {                       // Check maximum distance limit
                        printf("Error: Distance cannot exceed 1000 km.\n");
                    } else {                                        // Input is valid
                        validInput = 1;                             // Exit validation loop
                    }}
                distanceMatrix[i][j] = dist;                        // Set distance from i to j
                distanceMatrix[j][i] = dist;                        // Set distance from j to i (symmetric)
                anyAdded = true;                                    // Mark that a path was added
                printf("Success: Added path (%.2f km) between %s and %s\n",
                       dist, hotels[i].name, hotels[j].name);}}}
    if (anyAdded) {                                                 // Check if any paths were added
        Update_DistanceFile_With_INF(hotelCount);                   // Save updated matrix to file
        printf("\n=== Distance matrix updated successfully ===\n");
    } else {                                                        // No paths needed to be added
        printf("\nAll possible paths are already defined.\n");}
    displayDistanceMatrix();                                        // Display the updated matrix
}

//__________________________________ File function ____________________________________________

//_______________________________Load form hotels.txt__________________________________________
void Load_Hotelfile() {
    FILE *file = fopen("hotels.txt", "r");                  // Open hotel data file for reading
    if (file == NULL) {                                     // Check if file failed to open
        printf("Failed to open hotels.txt.\n");
        return;
    }
    hotelCount = 0;                                         // Initialize hotel counter
    while (fscanf(file, "%d %s %f %f %f",                   // Read hotel data from file
                 &hotels[hotelCount].id,
                 hotels[hotelCount].name,
                 &hotels[hotelCount].price,
                 &hotels[hotelCount].rating,
                 &hotels[hotelCount].distance) == 5) {
        hotelCount++;                                       // Increment hotel count
        if (hotelCount >= MAX_HOTELS) break;                // Stop if max limit reached
    }
    fclose(file);                                           // Close the hotel file
}

//__________________________________Save into hotels.txt__________________________________________
void Save_Hotels(Hotel *hotel) {
    FILE *file = fopen("hotels.txt", "a");                  // Open file in append mode
    if (file == NULL) {                                     // Check for file open error
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s %.2f %.1f %.1f\n",                 // Write hotel data to file
            hotel->id, hotel->name,
            hotel->price, hotel->rating, hotel->distance);
    fclose(file);                                           // Close the file
}

//_______________________________Load form destination.txt__________________________________________
void Load_DESfile() {
    FILE *file = fopen("destination.txt", "r");             // Open destination data file for reading
    if (file == NULL) {                                     // Check if file failed to open
        printf("Failed to open destination.txt.\n");
        return;
    }
    hotelCount = 0;                                         // Initialize hotel counter
    while (fscanf(file, "%d %s",                            // Read destination name and id from file
                 &hotels[hotelCount].id,
                 hotels[hotelCount].name) == 2) {
        hotelCount++;                                       // Increment hotel count
        if (hotelCount >= MAX_HOTELS) break;                // Stop if max limit reached
    }
    fclose(file);                                           // Close the destination file
    Load_DistanceMatrix(hotelCount);                        // Load corresponding distance matrix
}
//_______________________________Save into destination.txt__________________________________________
void Save_DESs(Hotel *hotel){
    FILE *file = fopen("destination.txt", "a");             // Open file in append mode
    if (file == NULL) {                                     // Check for file open error
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s\n",                                // Write destination data to file
            hotel->id, hotel->name);
    fclose(file);                                           // Close the file
    for (int i = 0; i < hotelCount; i++) {                  // Update distance matrix for new destination
        distanceMatrix[hotelCount-1][i] = INF;              // Set INF for new paths (row)
        distanceMatrix[i][hotelCount-1] = INF;              // Set INF for new paths (column)
    }
    distanceMatrix[hotelCount-1][hotelCount-1] = 0.0f;      // Distance to itself is 0
    Update_DistanceFile_With_INF(hotelCount);               // Save updated distance matrix
}

//____________________________________OTHER FUNCTIONS__________________________________________
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);                  //clear input
}
double input_ValidDouble(char s[],float min, float max) {
    double input;
    char buffer[1000];
    while (1) {
        printf("Enter %s (%d -> %d): ", s, (int)min, (int)max);
        if (fgets(buffer, sizeof(buffer), stdin)) {                 //get input
            char *endptr;
            input = strtof(buffer, &endptr);
            if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {              //check is it an number
                printf("Invalid input. Please enter a number.\n");
                continue;
            }
            if (input < min || input > max) {                       // check whether is in suitable range
                printf("Number out of range. Please try again.\n");
                continue;
            }
            return input;                                           //return double
        } else {
            printf("Input error. Try again.\n");
        }
    }
}
// Convert a string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)                                  // Loop through each character
        str[i] = tolower((unsigned char)str[i]);                  // Convert character to lowercase
}

// Check if hotel/destination name already exists (case-insensitive)
int isDuplicateName(const char *name) {
    char inputLower[50], existingLower[50];
    strcpy(inputLower, name);                                     // Copy input name
    toLowerCase(inputLower);                                      // Convert input name to lowercase
    for (int i = 0; i < hotelCount; i++) {
        strcpy(existingLower, hotels[i].name);                    // Copy existing hotel name
        toLowerCase(existingLower);                               // Convert to lowercase
        if (strcmp(inputLower, existingLower) == 0) {
            return 1;                                             // Duplicate found
    }}
    return 0;                                                     // No duplicate
}
void Initialize_DistanceMatrix() {
    for (int i = 0; i < MAX_HOTELS; i++) {                  // Loop through all rows
        for (int j = 0; j < MAX_HOTELS; j++) {              // Loop through all columns
            distanceMatrix[i][j] = (i == j) ? 0.0f : INF;   // 0 if same hotel, INF otherwise
    }}
}

// Dynamically expand the distance matrix to accommodate new hotels
void Load_DistanceMatrix(int count) {
    // Initialize with default values first
    for (int i = 0; i < MAX_HOTELS; i++) {
        for (int j = 0; j < MAX_HOTELS; j++) {
            distanceMatrix[i][j] = (i == j) ? 0.0f : INF;           // 0.0 for same index, INF otherwise
    }}
    // Then load from file
    FILE *file = fopen("distances.txt", "r");
    if (file) {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                char buffer[20];
                if (fscanf(file, "%s", buffer) == 1) {              // Read each distance or "INF"
                    if (strcmp(buffer, "INF") == 0) {
                        distanceMatrix[i][j] = INF;                 // If "INF", set as infinite
                    } else {
                        distanceMatrix[i][j] = atof(buffer);        // Otherwise, convert to float
    }}}}
        fclose(file);                                               // Close the file after reading
}}

// Update distance file with new INF-initialized matrix
void Update_DistanceFile_With_INF(int count) {
    FILE *file = fopen("distances.txt", "w");
    if (!file) {
        printf("Error saving distance matrix!\n");                  // Print error if file can't be opened
        return;
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (distanceMatrix[i][j] == INF) {
                fprintf(file, "INF");                               // Write "INF" if value is infinite
            } else {
                fprintf(file, "%.2f", distanceMatrix[i][j]);        // Otherwise, write float with 2 decimals
            }
            if (j < count - 1) fprintf(file, " ");                  // Add space between values (except last)
        }
        fprintf(file, "\n");                                        // Newline after each row
    }
    fclose(file);                                                   // Close the file after writing
}
