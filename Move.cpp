/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Ojochilemi Okoka, Zan Huang
 * okokaojo, zanh
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if(commandString == ""){
        isPass = true;
    } else if(commandString.at(0) == 'S' || commandString.at(0) == 's'){
        isSave = true;
    } else if(commandString.at(0) == 'Q' || commandString.at(0) == 'q'){
        isQuit = true;
    } else if (commandString.at(0) == 'e'){
        elevatorId = static_cast<int>(commandString.at(1)) - 48;
        if(commandString.at(2) == 'p'){
            isPickup = true;
        } else if(commandString.at(2) == 'f'){
            targetFloor = static_cast<int>(commandString.at(3)) - 48;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    //TODO: Implement isValidMove
    if(isPass || isSave || isQuit){
        return true;
    } else if(isPickup){
        if(elevatorId >= 0 && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()){
            return true;
        }
    } else {
        if(elevatorId >= 0 && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()){
            if(targetFloor >= 0 && targetFloor < NUM_FLOORS){
                if(targetFloor != elevators[elevatorId].getCurrentFloor()){
                    return true;
                }
            }
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    //TODO: Implement setPeopleToPickup
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int anger_level = 0;
    int insert = 0;
    int satisfaction = 0;
    int difference;
    for(int i = 0; i < pickupList.size(); i++){
        insert = static_cast<int>(pickupList.at(i)) - 48;
        peopleToPickup[i] = insert;
        numPeopleToPickup++;
    }
    
    for(int i = 0; i < numPeopleToPickup; i++){
        anger_level = pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        satisfaction = MAX_ANGER - anger_level;
        totalSatisfaction += satisfaction;
    }
    
    difference = abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[0]).getTargetFloor());
    targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[0]).getTargetFloor();
    for(int i = 1; i < numPeopleToPickup; i++){
        if(abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor()) > difference){
                targetFloor =  pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
            difference = abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor());
        }
    }
    
    
    
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
