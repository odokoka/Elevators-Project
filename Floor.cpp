/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Ojochilemi Okoka, Zan Huang
 * okokaojo, zanh
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int num_people_exploded = 0;
    int j = 0;
    int explosionArr[MAX_PEOPLE_PER_FLOOR];
    
    for (int i = 0; i < numPeople; ++i) {
        if (people[i].tick(currentTime)) {
            explosionArr[j] = i;
            ++num_people_exploded;
            ++j;
        }
    }
    removePeople(explosionArr, num_people_exploded);
    return num_people_exploded;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople != MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        if (request > 0) {
            hasUpRequest = true;
        } else {
            hasDownRequest = true;
        }
        ++numPeople;
    }
    return;
}


void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    int indicesToRemoveCopy[MAX_PEOPLE_PER_FLOOR];
    for(int copy = 0; copy < numPeopleToRemove; copy++){
        indicesToRemoveCopy[copy] = indicesToRemove[copy];
    }
    sort(indicesToRemoveCopy, indicesToRemoveCopy + numPeopleToRemove);
    int k = 0;

    for(int i = 0; i < numPeopleToRemove; i++){
        indicesToRemoveCopy[i] = indicesToRemoveCopy[i] - k;
        for(int j = indicesToRemoveCopy[i]; j < numPeople; j++){
            people[j] = people[j+1];
        }
        numPeople--;
        k++;
    }
    resetRequests();
}


void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;
    
    for (int i = 0; i < numPeople; ++i) {
        if ((people[i].getTargetFloor() - people[i].getCurrentFloor()) > 0) {
            hasUpRequest = true;
        } else {
            hasDownRequest = true;
        }
    }
    return;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
