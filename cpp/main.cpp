#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Base class: Ride (abstract)
class Ride {
protected:
    int rideId;
    string pickupLocation;
    string dropoffLocation;
    double distanceMiles;
    double fareTotal;

public:
    Ride(int id, const string& pickup, const string& dropoff, double dist)
        : rideId(id),
          pickupLocation(pickup),
          dropoffLocation(dropoff),
          distanceMiles(dist),
          fareTotal(0.0) {}

    virtual ~Ride() {}

    // Polymorphic interface
    virtual double computeFare() = 0;
    virtual void printRideDetails() const = 0;

    // Encapsulated getters
    int getRideId() const {
        return rideId;
    }

    double getDistance() const {
        return distanceMiles;
    }

    double getFareTotal() const {
        return fareTotal;
    }

protected:
    void setFareTotal(double value) {
        fareTotal = value;
    }
};


// StandardRide: inherits from Ride

class StandardRide : public Ride {
public:
    StandardRide(int id, const string& pickup, const string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double computeFare() override {
        // basic formula for standard rides
        double baseFare = 1.5;
        double perMile = 1.8;
        double total = baseFare + perMile * distanceMiles;
        setFareTotal(total);
        return total;
    }

    void printRideDetails() const override {
        cout << "[Standard] Ride ID: " << rideId
             << " | From: " << pickupLocation
             << " | To: " << dropoffLocation
             << " | Distance: " << distanceMiles << " miles"
             << " | Fare: $" << fareTotal << endl;
    }
};


// PremiumRide: inherits from Ride

class PremiumRide : public Ride {
public:
    PremiumRide(int id, const string& pickup, const string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double computeFare() override {
      
        double baseFare = 4.0;
        double perMile = 3.2;
        double luxuryFee = 1.5;
        double total = baseFare + perMile * distanceMiles + luxuryFee;
        setFareTotal(total);
        return total;
    }

    void printRideDetails() const override {
        cout << "[Premium]  Ride ID: " << rideId
             << " | From: " << pickupLocation
             << " | To: " << dropoffLocation
             << " | Distance: " << distanceMiles << " miles"
             << " | Fare: $" << fareTotal << endl;
    }
};


// Driver class

class Driver {
private:
    int driverId;
    string driverName;
    double driverRating;
    vector<Ride*> completedRides;   

public:
    Driver(int id, const string& name, double rating)
        : driverId(id), driverName(name), driverRating(rating) {}

    void addCompletedRide(Ride* ride) {
        completedRides.push_back(ride);
    }

    void printDriverInfo() const {
        cout << "Driver ID: " << driverId
             << " | Name: " << driverName
             << " | Rating: " << driverRating
             << " | Total rides: " << completedRides.size()
             << endl;
    }

    double calculateTotalEarnings() const {
        double sum = 0.0;
        for (auto ride : completedRides) {
            sum += ride->getFareTotal();
        }
        return sum;
    }
};


// Rider class

class Rider {
private:
    int riderId;
    string riderName;
    vector<Ride*> rideHistory;   

public:
    Rider(int id, const string& name)
        : riderId(id), riderName(name) {}

    void requestRide(Ride* ride) {
        rideHistory.push_back(ride);
    }

    void printRideHistory() const {
        cout << "Rider ID: " << riderId
             << " | Name: " << riderName << endl;
        cout << "Ride history:" << endl;

        for (auto ride : rideHistory) {
            ride->printRideDetails();   
        }
    }

    double computeAverageFare() const {
        if (rideHistory.empty()) {
            return 0.0;
        }
        double sum = 0.0;
        for (auto ride : rideHistory) {
            sum += ride->getFareTotal();
        }
        return sum / rideHistory.size();
    }
};


void printSeparator() {
    cout << "----------------------------------------" << endl;
}

-
// main: create rides, driver, rider
//       and demonstrate polymorphism

int main() {
    // Create some rides
    Ride* ride1 = new StandardRide(1, "University", "City Center", 4.3);
    Ride* ride2 = new PremiumRide(2, "International Airport", "Hotel District", 12.0);
    Ride* ride3 = new StandardRide(3, "Tech Park", "Student Housing", 3.1);

    vector<Ride*> rides;
    rides.push_back(ride1);
    rides.push_back(ride2);
    rides.push_back(ride3);

    printSeparator();
    cout << "Calculating fares for all rides (polymorphism demo)" << endl;
    printSeparator();

    for (auto ride : rides) {
        ride->computeFare();       // calls correct subclass version
        ride->printRideDetails();  // dynamic dispatch
    }

    printSeparator();

    // Create driver and rider
    Driver driver(101, "Anushka Driver", 4.8);
    Rider rider(201, "Anushka Rider");

    // Assign rides
    for (auto ride : rides) {
        driver.addCompletedRide(ride);
        rider.requestRide(ride);
    }

    cout << "Driver info:" << endl;
    driver.printDriverInfo();
    cout << "Total driver earnings: $" << driver.calculateTotalEarnings() << endl;

    printSeparator();

    cout << "Rider info and history:" << endl;
    rider.printRideHistory();
    cout << "Average fare paid by rider: $" << rider.computeAverageFare() << endl;

    printSeparator();
    cout << "Program finished." << endl;


    for (auto ride : rides) {
        delete ride;
    }

    return 0;
}
