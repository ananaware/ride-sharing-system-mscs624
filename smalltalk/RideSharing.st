"RideSharing System - Smalltalk version
 Classes:
   - Ride (abstract)
   - StandardRide
   - PremiumRide
   - Driver
   - Rider
 This code demonstrates encapsulation, inheritance,
 and polymorphism for MSCS 624 assignment."

" Base class: Ride "

Object subclass: #Ride
    instanceVariableNames: 'rideId pickupLocation dropoffLocation distanceMiles fareTotal'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.


"Initialization"

Ride >> initializeWithId: anId
       pickup: pickup
       dropoff: dropoff
       distance: dist
    rideId := anId.
    pickupLocation := pickup.
    dropoffLocation := dropoff.
    distanceMiles := dist.
    fareTotal := 0.0.


"Abstract protocol - subclasses must override these"

Ride >> computeFare
    "Abstract method - subclasses provide implementation."
    self subclassResponsibility.

Ride >> printRideDetails
    "Abstract method - subclasses provide implementation."
    self subclassResponsibility.


"Encapsulated getters and setter"

Ride >> rideId
    ^ rideId.

Ride >> distanceMiles
    ^ distanceMiles.

Ride >> fareTotal
    ^ fareTotal.

Ride >> fareTotal: aNumber
    fareTotal := aNumber.



"StandardRide class"

Ride subclass: #StandardRide
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.


StandardRide >> computeFare
    "Simple fare formula for standard rides."
    | baseFare perMile total |
    baseFare := 1.5.
    perMile := 1.8.
    total := baseFare + (perMile * distanceMiles).
    self fareTotal: total.
    ^ total.


StandardRide >> printRideDetails
    Transcript
        show: '[Standard] Ride ID: ', rideId printString;
        show: ' | From: ', pickupLocation;
        show: ' | To: ', dropoffLocation;
        show: ' | Distance: ', distanceMiles printString, ' miles';
        show: ' | Fare: $', fareTotal printString;
        cr.



"PremiumRide class"

Ride subclass: #PremiumRide
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.


PremiumRide >> computeFare
    "Premium ride has higher rate and a luxury fee."
    | baseFare perMile luxuryFee total |
    baseFare := 4.0.
    perMile := 3.2.
    luxuryFee := 1.5.
    total := baseFare + (perMile * distanceMiles) + luxuryFee.
    self fareTotal: total.
    ^ total.


PremiumRide >> printRideDetails
    Transcript
        show: '[Premium]  Ride ID: ', rideId printString;
        show: ' | From: ', pickupLocation;
        show: ' | To: ', dropoffLocation;
        show: ' | Distance: ', distanceMiles printString, ' miles';
        show: ' | Fare: $', fareTotal printString;
        cr.



"Driver class "

Object subclass: #Driver
    instanceVariableNames: 'driverId driverName driverRating completedRides'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.


Driver >> initializeWithId: anId
          name: aName
          rating: aRating
    driverId := anId.
    driverName := aName.
    driverRating := aRating.
    completedRides := OrderedCollection new.


Driver >> addCompletedRide: aRide
    "Encapsulated modification of completedRides list."
    completedRides add: aRide.


Driver >> printDriverInfo
    Transcript
        show: 'Driver ID: ', driverId printString;
        show: ' | Name: ', driverName;
        show: ' | Rating: ', driverRating printString;
        show: ' | Total rides: ', completedRides size printString;
        cr.


Driver >> totalEarnings
    | sum |
    sum := 0.0.
    completedRides do: [:ride |
        sum := sum + ride fareTotal].
    ^ sum.



" Rider class"

Object subclass: #Rider
    instanceVariableNames: 'riderId riderName rideHistory'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'RideSharing'.


Rider >> initializeWithId: anId name: aName
    riderId := anId.
    riderName := aName.
    rideHistory := OrderedCollection new.


Rider >> requestRide: aRide
    "Encapsulated modification of rideHistory list."
    rideHistory add: aRide.


Rider >> printRideHistory
    Transcript
        show: 'Rider ID: ', riderId printString;
        show: ' | Name: ', riderName;
        cr.
    Transcript show: 'Ride history:'; cr.
    rideHistory do: [:ride |
        ride printRideDetails].


Rider >> averageFare
    rideHistory isEmpty ifTrue: [ ^ 0.0 ].
    | sum |
    sum := 0.0.
    rideHistory do: [:ride |
        sum := sum + ride fareTotal ].
    ^ sum / rideHistory size.



