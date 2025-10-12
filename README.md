🏨 Hotel & Destination Management System (C Project)
📋 Overview

This project is a menu-driven Hotel & Destination Management System written in C.
It integrates sorting algorithms, searching, knapsack optimization, and graph algorithms (like Dijkstra’s shortest path) to help manage hotel and destination data efficiently.

The system allows users to:

Add and view hotels or destinations

Sort hotels using Bubble Sort or Merge Sort

Search hotels using Binary Search

Find the best hotel combination under a given budget (Knapsack)

Manage paths between destinations

Calculate shortest travel routes using Dijkstra’s algorithm

Access extended analytical features in the “Extension” module

⚙️ Features
Function	Description
Add Hotel	Add a new hotel with name, price, rating, and distance.
View All Hotels	Display the complete list of hotels.
Bubble Sort / Merge Sort	Sort hotels by price, rating, or distance.
Binary Search	Search for a hotel by ID or name.
Knapsack	Recommend hotels that fit within a user’s budget.
Add Destination	Add new travel destinations.
Add Path	Define paths (connections) between destinations.
Dijkstra Algorithm	Find the shortest route between two destinations.
Extension Menu	Access advanced features such as matrix operations or combined sorting/filtering.
🧩 Project Structure
📁 Hotel_Management_System
│
├── main.c                # Entry point for the program
├── hotel_func.c          # Handles hotel/destination operations and file I/O
├── Algorithm.c           # Implements sorting, searching, knapsack, and Dijkstra
├── Extension.c           # Contains extra/advanced algorithmic features
│
├── hotel_func.h          # Header for hotel_func.c
├── Algorithm.h           # Header for Algorithm.c
├── Extension.h           # Header for Extension.c
│
├── hotels.txt            # Stores hotel data
├── destination.txt       # Stores destination data
├── distances.txt         # Stores distance matrix between destinations
│
└── README.md             # Project documentation (this file)

🧠 Key Algorithms Used
Category	Algorithm	Description
Sorting	Bubble Sort, Merge Sort	Organizes hotel data based on selected criteria.
Searching	Binary Search	Finds hotels quickly in sorted data.
Optimization	Knapsack Problem	Selects hotels within a budget for best value.
Graph Theory	Dijkstra’s Algorithm	Computes the shortest path between destinations.
🧮 Input Validation

The program includes robust input validation functions:

get_ValidInt(min, max) → Ensures valid menu choice input

get_ValidBudget(min, max) → Ensures valid numeric budget input
Invalid entries are handled gracefully with informative messages.

👨‍💻 Contributors

Wilbert Yonathan & Chua Kian Hoong – Project Developer

CST209 – Final Project (Hotel & Destination Management System)
