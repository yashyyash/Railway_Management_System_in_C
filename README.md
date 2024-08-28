# Railway Management System in C

## Overview

The Railway Management System is a simple console-based C program designed to handle basic railway booking and management functionalities. It includes features such as saving ticket data, user login, ticket retrieval, and admin functions.

## Features

- **Ticket Booking**: 
  - Allows users to book train tickets with details like passenger name, age, gender, seat number, and class.
  
- **Save Ticket Data**: 
  - Automatically saves ticket information in a text file (`tickets.txt`) after booking.
  
- **User Login and Registration**: 
  - Users can log in or register with a username and password.
  - User credentials are stored in a text file (`logins.txt`).
  
- **Ticket Retrieval**: 
  - Users can retrieve their booked tickets by providing their username.
  
- **Admin Functionality**: 
  - Admins can log in with special credentials to view all tickets or search for tickets by username.
  - Default admin credentials:
    - **Username**: `Admin`
    - **Password**: `Admin@1234`

## Files

- **`railway_management.c`**: 
  - The main C source file containing the entire program code.
  
- **`tickets.txt`**: 
  - The text file where all ticket data is saved. This file is automatically created and updated by the program.
  
- **`logins.txt`**: 
  - The text file where user login credentials are stored. This file is also automatically created and updated by the program.

## How to Run

1. **Clone the Repository**:
   git clone https://github.com/YOUR_GITHUB_USERNAME/Railway-Management-System-in-C.git

2. **Navigate to the Project Directory**:
cd Railway-Management-System-in-C

3. **Compile the Program**:
gcc railway_management.c -o railway_management

4. **Run the Program**:
./railway_management

## Usage
- **Booking a Ticket**:
    - Follow the on-screen prompts to book a ticket. Ticket details will be saved in tickets.txt.
- **Login/Registration**:
    - If you are a new user, the program will automatically register you. Existing users can log in using their credentials.
- **Retrieve Ticket**:
    - Use the retrieval option to fetch your booked ticket information.
- **Admin**:
    - Admins can log in using the provided credentials to view all tickets or search for specific tickets by username.

## Contributing
- **Contributions are welcome! Feel free to submit a pull request or open an issue to suggest improvements**.