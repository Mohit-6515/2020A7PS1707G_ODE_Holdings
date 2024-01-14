# Parking Lot Management System

## Overview

This C++ program implements a parking lot management system, providing efficient tracking and management of parking spots for various vehicle types.

## Code Structure

### Vehicle Class

- Abstract base class for vehicles.
- Defines virtual methods: `getSpotsNeeded` and `getType`.

### Motorcycle Class

- Inherits from `Vehicle`.
- Represents a motorcycle, specifying spots needed and type.

### Car Class

- Inherits from `Vehicle`.
- Represents a car, specifying spots needed and type.

### Van Class

- Inherits from `Vehicle`.
- Represents a van, with dynamic spots needed based on the type.

### ParkingSpot Class

- Represents a parking spot.
- Tracks occupancy status and the parked vehicle.

### ParkingLot Class

- Manages the overall parking lot.
- Uses maps to track total and remaining spots for different types.
- Provides methods for parking and retrieving vehicle information.
- Includes functions to print the status of each spot type and the overall parking lot.

## Development Duration

- Coding Time: Approximately 50 minutes.

## Program Output

- Total Motorcycle Spots: 10
- Remaining Motorcycle Spots: 9
- Status of Motorcycle Spots: Available

- Total Regular Spots: 10
- Remaining Regular Spots: 9
- Status of Regular Spots: Available

- Total Big Spots: 3
- Remaining Big Spots: 2
- Status of Big Spots: Available

- Parking Lot Status: Available
- Occupied Regular Spots by Van: 0
- Occupied Big Spots by Van: 1

## UI Diagram

![WhatsApp Image 2024-01-14 at 16 47 09](https://github.com/Mohit-6515/2020A7PS1707G_ODE_Holdings/assets/77959274/8237b986-8ff4-410b-ab0b-85f74f4960b3)

## Details Of Student:
- Name: Mohit Sharma
- BITS ID: 2020A7PS1707G
- Email Id: f20201707@goa.bits-pilani.ac.in
