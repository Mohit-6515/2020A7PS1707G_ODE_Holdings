#include <iostream>
#include <vector>

using namespace std;

// Abstract base class for vehicles
class Vehicle {
public:
    virtual int getSpotsNeeded(const string& spotType) const = 0;
    virtual string getType() const = 0;
};

// Concrete class for Motorcycle
class Motorcycle : public Vehicle {
public:
    int getSpotsNeeded(const string& spotType) const override { return 1; }
    std::string getType() const override { return "Motorcycle"; }
};

// Concrete class for Car
class Car : public Vehicle {
public:
    int getSpotsNeeded(const string& spotType) const override { return 1; }
    std::string getType() const override { return "Car"; }
};

// Concrete class for Van
class Van : public Vehicle {
public:
    int getSpotsNeeded(const string& spotType) const override {
        return (spotType == "Big") ? 1 : 3;
    }
    std::string getType() const override { return "Van"; }
};

// ParkingSpot class
class ParkingSpot {
private:
    bool occupied;
    Vehicle* vehicle;

public:
    ParkingSpot() : occupied(false), vehicle(nullptr) {}

    bool isOccupied() const { return occupied; }

    void parkVehicle(Vehicle* v) {
        if (!occupied) {
            vehicle = v;
            occupied = true;
        }
    }

    void removeVehicle() {
        if (occupied) {
            vehicle = nullptr;
            occupied = false;
        }
    }

    Vehicle* getVehicle() const { return vehicle; }
};

// ParkingLot class
class ParkingLot {
private:
    int totalMotorcycleSpots;
    int totalRegularCarSpots;
    int totalBigSpots;

    int remainingMotorcycleSpots;
    int remainingRegularCarSpots;
    int remainingBigSpots;

    std::vector<ParkingSpot> motorcycleSpots;
    std::vector<ParkingSpot> regularSpots;
    std::vector<ParkingSpot> bigSpots;

public:
    ParkingLot(int motorcycleSpots, int regularCarSpots, int bigSpots)
        : totalMotorcycleSpots(motorcycleSpots),
          totalBigSpots(bigSpots),
          totalRegularCarSpots(regularCarSpots),
          remainingMotorcycleSpots(motorcycleSpots),
          remainingRegularCarSpots(regularCarSpots),
          remainingBigSpots(bigSpots) {

        // Initialize parking spots
        for (int i = 0; i < motorcycleSpots; ++i) {
            this->motorcycleSpots.push_back(ParkingSpot());
        }

        for (int i = 0; i < regularCarSpots; ++i) {
            this->regularSpots.push_back(ParkingSpot());
        }

        for (int i = 0; i < bigSpots; ++i) {
            this->bigSpots.push_back(ParkingSpot());
        }
    }

    int getRemainingSpots(const string& spotType) const {
        if (spotType == "Motorcycle") {
            return remainingMotorcycleSpots;
        } else if (spotType == "Regular") {
            return remainingRegularCarSpots;
        } else if (spotType == "Big") {
            return remainingBigSpots;
        }
        return 0;
    }

    int getTotalSpots(const string& spotType) const {
        if (spotType == "Motorcycle") {
            return totalMotorcycleSpots;
        } else if (spotType == "Regular") {
            return totalRegularCarSpots;
        } else if (spotType == "Big") {
            return totalBigSpots;
        }
        return 0;
    }

    bool isFull(const string& spotType) const {
        if (spotType == "Motorcycle") {
            return remainingMotorcycleSpots == 0;
        } else if (spotType == "Regular") {
            return remainingRegularCarSpots == 0;
        } else if (spotType == "Big") {
            return remainingBigSpots == 0;
        }
        return false;
    }

    bool isEmpty(const string& spotType) const {
        if (spotType == "Motorcycle") {
            return remainingMotorcycleSpots == totalMotorcycleSpots;
        } else if (spotType == "Regular") {
            return remainingRegularCarSpots == totalRegularCarSpots;
        } else if (spotType == "Big") {
            return remainingBigSpots == totalBigSpots;
        }
        return false;
    }

    int getOccupiedVanSpots() const {
        int occupiedRegularSpotsByVan = 0;
        int occupiedBigSpotsByVan = 0;

        for (const auto& spot : regularSpots) {
            if (spot.isOccupied() && spot.getVehicle()->getType() == "Van") {
                occupiedRegularSpotsByVan += 1;
            }
        }

        for (const auto& spot : bigSpots) {
            if (spot.isOccupied() && spot.getVehicle()->getType() == "Van") {
                occupiedBigSpotsByVan += 1;
            }
        }

        cout << "Occupied Regular Spots by Van: " << occupiedRegularSpotsByVan << endl;
        cout << "Occupied Big Spots by Van: " << occupiedBigSpotsByVan << endl;

        return occupiedRegularSpotsByVan + occupiedBigSpotsByVan;
    }

    void parkVehicle(Vehicle* v, const string& spotType) {
        if (spotType == "Motorcycle") {
            parkInMotorcycleSpot(v);
        } else if (spotType == "Regular") {
            parkInRegularSpots(v, v->getSpotsNeeded(spotType));
        } else if (spotType == "Big") {
            parkInBigSpot(v);
        }
    }

    void parkInMotorcycleSpot(Vehicle* v) {
        for (auto& spot : motorcycleSpots) {
            if (!spot.isOccupied() && spot.getVehicle() == nullptr) {
                spot.parkVehicle(v);
                remainingMotorcycleSpots--;
                break;
            }
        }
    }

    void parkInRegularSpots(Vehicle* v, int numSpots) {
        if (getRemainingSpots("Regular")>=numSpots) {
            int reqSpots=numSpots;
            for(auto& spot : regularSpots){
                if (!spot.isOccupied() && spot.getVehicle() == nullptr) {
                    reqSpots--;
                    spot.parkVehicle(v);
                    if (reqSpots == 0) {
                        remainingRegularCarSpots -= numSpots;
                        break;
                    }
                }
            }
        } else cout<<"Number of Available Spots aren't enough to park"<<endl;
    }

    void parkInBigSpot(Vehicle* v) {
        for (auto& spot : bigSpots) {
            if (!spot.isOccupied() && spot.getVehicle() == nullptr) {
                spot.parkVehicle(v);
                remainingBigSpots--;
                break;
            }
        }
    }

    void printParkingLotStatus() const {
        printSpotStatus("Motorcycle");
        printSpotStatus("Regular");
        printSpotStatus("Big");
        cout << "Parking Lot Status: " << (isFull("Motorcycle") && isFull("Regular") && isFull("Big") ? "Full" : "Available") << endl;
        getOccupiedVanSpots();
    }

    void printSpotStatus(const string& spotType) const {
        cout << "Total " << spotType << " Spots: " << getTotalSpots(spotType) << endl;
        cout << "Remaining " << spotType << " Spots: " << getRemainingSpots(spotType) << endl;
        cout << "Status of " << spotType << " Spots: " << (isFull(spotType) ? "Full" : (isEmpty(spotType) ? "Empty" : "Available")) << endl;
    }
};

int main() {
    // Create a parking lot with 10 motorcycle spots, 10 regular car spots, and 3 big spots
    ParkingLot parkingLot(10, 10, 3);

    // Create vehicles
    Motorcycle motorcycle1;
    Car car1;
    Van van1;

    // Park vehicles
    parkingLot.parkVehicle(&motorcycle1, "Motorcycle");
    parkingLot.parkVehicle(&car1, "Regular");
    parkingLot.parkVehicle(&van1, "Big");

    // Print parking lot status
    parkingLot.printParkingLotStatus();

    return 0;
}