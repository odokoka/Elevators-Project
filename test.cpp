/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

void person_tests();
void elevator_tests();
void file_check();
void floor_tests();
void test_move();
void test_game();

void start_tests() {
    test_game();
    return;
}

// write test functions here
void person_tests() {
    cout << "Person Tests" << endl;
    //initialize a person with targetFloor 5, anger 5
    Person p("0f0t5a5");
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    
    //test empty initialization
    Person empty;
    cout << empty.getTargetFloor() << " " << empty.getAngerLevel() << " Expected 0 0" << endl;
    
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    
    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    
    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    
    Person spawn("5f4t6a6");
    cout << spawn.getTargetFloor() << " " << spawn.getAngerLevel() << " Expected 6 6" << endl;
    cout << spawn.getTurn() << " Expected 5" << endl;
    
    cout << spawn.tick(0) << " Expected 0" << endl;
    cout << spawn.tick(5) << " Expected 0" << endl;
    cout << spawn.tick(6) << " Expected 0" << endl;
    cout << spawn.tick(10) << " Expected 0" << endl;
    cout << spawn.tick(50) << " Expected 1" << endl;
    
    Person noanger("5f6t6a0");
    cout << spawn.tick(2) << " Expected 0 " << endl;
    
}

void elevator_tests() {
    cout << "TESTING ELEVATOR" << endl;
    Elevator e1;
    e1.print(cout);
    cout << endl;
    
    Elevator e2;
    e2.setCurrentFloor(6);
    e2.serviceRequest(4);
    e2.tick(1);
    cout << e2.isServicing() << " Expected 1" << endl;
    e2.tick(2);
    cout << e2.isServicing() << " Expected 0" << endl;
    e2.tick(3);
    cout << e2.isServicing() << " Expected 0" << endl;
    
    Elevator e3;
    e3.setCurrentFloor(5);
    e3.serviceRequest(5);
    cout << "e3 print" << endl;
    e3.print(cout);
    cout << endl;
    cout << e3.isServicing() << " Expected 1" << endl;
    
    e3.tick(3);
    cout << endl;
    
    e2.print(cout);
    
    return;
}

void floor_tests(){
    cout << "FLOOR TESTS" << endl;
    Floor one;
    Person person1("0f1t4a9");
    Person person2("0f1t7a7");
    Person person3("0f1t6a6");
    Person person4("0f1t5a9");
    Person person5("0f1t9a0");
    
    one.addPerson(person1, 2);
    one.addPerson(person2, 5);
    one.addPerson(person3, 4);
    one.addPerson(person4, 3);
    one.addPerson(person5, 7);
    
    one.printFloorPickupMenu(cout);
    cout << endl << "--------------------------";
    cout << endl;
    cout << endl;
    
    one.prettyPrintFloorLine1(cout);
    one.prettyPrintFloorLine2(cout);
    
    cout << "NUM PEOPLE: " << one.getNumPeople() << endl;
    int remove_indice[] = {0, 2, 4};
    one.removePeople(remove_indice, 3);
    
    cout << "NUM PEOPLE: " << one.getNumPeople() << endl;
    
    one.prettyPrintFloorLine1(cout);
    one.prettyPrintFloorLine2(cout);
    
    //Tests for remove people
    cout << endl << "two--------------------------";
    cout << endl;
    cout << endl;
    Floor two;
    Person personT1("0f1t4a9");
    Person personT2("0f1t7a7");
    Person personT3("0f1t6a6");
    Person personT4("0f1t5a9");
    Person personT5("0f1t9a0");
   
    two.addPerson(personT1, 2);
    two.addPerson(personT2, 5);
    two.addPerson(personT3, 4);
    two.addPerson(personT4, 3);
    two.addPerson(personT5, 7);
    
    
    
    two.prettyPrintFloorLine1(cout);
    two.prettyPrintFloorLine2(cout);
    
    cout << "NUM PEOPLE: " << two.getNumPeople() << endl;
    int remove_indices[] = {1, 3};
    two.removePeople(remove_indices, 2);
    
    cout << "NUM PEOPLE: " << two.getNumPeople() << endl;
    two.prettyPrintFloorLine1(cout);
    two.prettyPrintFloorLine2(cout);
    
    cout << endl << "three--------------------------";
    cout << endl;
    cout << endl;
    Floor three;
    Person persont1("0f1t4a9");
    Person persont2("0f1t7a7");
    Person persont3("0f1t6a6");
    Person persont4("0f1t5a9");
    Person persont5("0f1t9a0");
   
    three.addPerson(persont1, 2);
    three.addPerson(persont2, 5);
    three.addPerson(persont3, 4);
    three.addPerson(persont4, 3);
    three.addPerson(persont5, 7);
    
    
    
    three.prettyPrintFloorLine1(cout);
    three.prettyPrintFloorLine2(cout);
    
    cout << "NUM PEOPLE: " << three.getNumPeople() << endl;
    int Remove_Indices[] = {0, 2, 4};
    three.removePeople(Remove_Indices, 3);
    
    cout << "NUM PEOPLE: " << three.getNumPeople() << endl;
    three.prettyPrintFloorLine1(cout);
    three.prettyPrintFloorLine2(cout);
    
    cout << endl << "four--------------------------";
    cout << endl;
    cout << endl;
    Floor four;
    Person personG1("0f1t4a9");
    Person personG2("0f1t7a7");
    Person personG3("0f1t6a6");
    Person personG4("0f1t5a9");
    Person personG5("0f1t9a0");
   
    four.addPerson(personG1, 2);
    four.addPerson(personG2, 5);
    four.addPerson(personG3, 4);
    four.addPerson(personG4, 3);
    four.addPerson(personG5, 7);
    
    
    
    four.prettyPrintFloorLine1(cout);
    four.prettyPrintFloorLine2(cout);
    
    cout << "NUM PEOPLE: " << four.getNumPeople() << endl;
    int remove_Indices[] = {0, 1, 2, 3};
    four.removePeople(remove_Indices, 4);
    
    cout << "NUM PEOPLE: " << four.getNumPeople() << endl;
    four.prettyPrintFloorLine1(cout);
    four.prettyPrintFloorLine2(cout);
    cout << endl;
    
}

void test_move(){
    Move move1("");
    Move move2("s");
    Move move3("q");
    Move move4("e1p");
    Move move5("e1f4");
    Move invalid_move1("e4f5");
    Move valid_move1("e2f0");
    Move invalid_move2("e1f2");
    
    Elevator elevators[NUM_ELEVATORS];
    elevators[0] = Elevator();
    elevators[1] = Elevator();
    elevators[2] = Elevator();
    elevators[2].setCurrentFloor(3);
    
    
    cout << "Move """ << endl;
    cout << "Elevator ID: " << move1.getElevatorId() << endl;
    cout << "Target Floor: " << move1.getTargetFloor() << endl;
    cout << "Number to Pick up: " << move1.getNumPeopleToPickup() << endl;
    cout << "Total Satisfaction: " << move1.getTotalSatisfaction() << endl;
    
    cout << "Move 'e1f4'" << endl;
    cout << "Elevator ID: " << move5.getElevatorId() << endl;
    cout << "Target Floor: " << move5.getTargetFloor() << endl;
    cout << "Number to Pick up: " << move5.getNumPeopleToPickup() << endl;
    cout << "Total Satisfaction: " << move5.getTotalSatisfaction() << endl;
    
    cout << "TESTING VALID MOVES" << endl;
    cout << "Expects 0: " << invalid_move1.isValidMove(elevators) << endl;
    cout << "Expects 1: " << move1.isValidMove(elevators) << endl;
    cout << "Expects 1: " << move3.isValidMove(elevators) << endl;
    cout << "Expects 1: " << valid_move1.isValidMove(elevators) << endl;
    cout << "Expects 0: " << invalid_move2.isValidMove(elevators) << endl;

    cout << "TESTING setPeopleToPickup" << endl;
    Floor a;
    Floor b;
    a.addPerson(Person(), 4);
    a.addPerson(Person(), -2);
    a.addPerson(Person(), 3);
    
    int newlist[MAX_PEOPLE_PER_FLOOR];
    
    move5.setPeopleToPickup("23", 0, b);
    cout << "TARGET FLOOR: " << elevators[1].getTargetFloor() << endl;
    cout << "CURRENT FLOOR: " << elevators[1].getCurrentFloor() << endl;
    cout << "num people to pick up" << move5.getNumPeopleToPickup() << endl;
    move5.copyListOfPeopleToPickup(newlist);
    cout << newlist[0] << endl;
    cout << move5.getTotalSatisfaction() << endl;
}

void file_check() {
    // open one of the text files that are part of the starter code
    ifstream ins;
    ins.open("new.in");
    // if the file was not in the correct directory, the stream state is fail
    if (ins.fail()) {
        cout << "Could not open new.in" << endl;
    }
    else {
        cout << "Success! Text files are in the right directory." << endl;
    }
    return;
}

void test_game() {
    Game Newgame;
    bool test = Newgame.isValidPickupList("9876543210", 2);
    cout << test << endl;
    test = Newgame.isValidPickupList("9876543210", 3);
    cout << test << endl;
    test = Newgame.isValidPickupList("0", 9);
    cout << test << endl;
    test = Newgame.isValidPickupList("5", 4);
    cout << test << endl;
    test = Newgame.isValidPickupList("5", 5);
    cout << test << endl;
    test = Newgame.isValidPickupList("5", 6);
    cout << test << endl;
}
