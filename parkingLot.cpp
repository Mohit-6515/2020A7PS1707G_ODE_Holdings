#include <bits/stdc++.h>
using namespace std;

// Abstract base class for vehicles
class Vehicle {
protected:
    string plateNumber;

public:
    Vehicle(const string& plate) : plateNumber(plate) {}
    
    virtual int getSpotsNeeded(const string& spotType) const = 0;
    virtual string getType() const = 0;
    string getPlateNumber() const { return plateNumber; }
};

// Concrete class for Motorcycle
class Motorcycle : public Vehicle {
public:
    Motorcycle(const string& plate) : Vehicle(plate) {}
    int getSpotsNeeded(const string& spotType) const override { return 1; }
    string getType() const override { return "Motorcycle"; }
};

// Concrete class for Car
class Car : public Vehicle {
public:
    Car(const string& plate) : Vehicle(plate) {}
    int getSpotsNeeded(const string& spotType) const override { return 1; }
    string getType() const override { return "Car"; }
};

// Concrete class for Van
class Van : public Vehicle {
public:
    Van(const string& plate) : Vehicle(plate) {}
    int getSpotsNeeded(const string& spotType) const override {
        return (spotType == "Big") ? 1 : 3;
    }
    string getType() const override { return "Van"; }
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
    string getPlateNumber() const { return (occupied) ? vehicle->getPlateNumber() : ""; }
};

// ParkingLot class
class ParkingLot {
private:
    map<string,int> totalSpots;
    map<string,int> remainingSpots;

    vector<ParkingSpot> motorcycleSpots;
    vector<ParkingSpot> regularSpots;
    vector<ParkingSpot> bigSpots;

public:
    ParkingLot(int motorcycleSpots, int regularCarSpots, int bigSpots){
        totalSpots["Motorcycle"] = motorcycleSpots;
        totalSpots["Regular"] = regularCarSpots;
        totalSpots["Big"] = bigSpots;

        remainingSpots["Motorcycle"] = motorcycleSpots;
        remainingSpots["Regular"] = regularCarSpots;
        remainingSpots["Big"] = bigSpots;

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
        return remainingSpots.at(spotType);
    }

    int getTotalSpots(const string& spotType) const {
        return totalSpots.at(spotType);
    }

    bool isFull(const string& spotType) const {
        return remainingSpots.at(spotType)==0;
    }

    bool isEmpty(const string& spotType) const {
        return remainingSpots.at(spotType)==totalSpots.at(spotType);
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
                remainingSpots["Motorcycle"]--;
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
                        remainingSpots["Regular"] -= numSpots;
                        break;
                    }
                }
            }
        }
    }

    void parkInBigSpot(Vehicle* v) {
        for (auto& spot : bigSpots) {
            if (!spot.isOccupied() && spot.getVehicle() == nullptr) {
                spot.parkVehicle(v);
                remainingSpots["Big"]--;
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

    string getVehiclePlateNumber(const string& spotType, int spotIndex) const {
        if (spotType == "Motorcycle" && spotIndex >= 0 && spotIndex < motorcycleSpots.size()) {
            return motorcycleSpots[spotIndex].getPlateNumber();
        } else if (spotType == "Regular" && spotIndex >= 0 && spotIndex < regularSpots.size()) {
            return regularSpots[spotIndex].getPlateNumber();
        } else if (spotType == "Big" && spotIndex >= 0 && spotIndex < bigSpots.size()) {
            return bigSpots[spotIndex].getPlateNumber();
        } else {
            return "";
        }
    }
};

int main() {
    // Create a parking lot with 10 motorcycle spots, 10 regular car spots, and 3 big spots
    ParkingLot parkingLot(10, 10, 3);

    // Create vehicles with plate numbers
    Motorcycle motorcycle1("M123");
    Car car1("C456");
    Van van1("V789");

    // Park vehicles
    parkingLot.parkVehicle(&motorcycle1, "Motorcycle");
    parkingLot.parkVehicle(&car1, "Regular");
    parkingLot.parkVehicle(&van1, "Big");

    // Print parking lot status
    parkingLot.printParkingLotStatus();

    return 0;
}
