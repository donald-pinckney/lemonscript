//
//  main.cpp
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/20/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#include <iostream>
#include "FiniteStateMachine.h"
#include "IteratedFiniteStateMachine.h"

using namespace std;

typedef enum : unsigned int {
    Zero,
    One,
    Two
} States;

int main(int argc, const char * argv[]) {
    
    auto addOneCallback = [] (FiniteStateMachineEdge edge) {
        cout << "Adding 1!" << endl;
    };
    
    auto subtractTwoCallack = [] (FiniteStateMachineEdge edge) {
        cout <<  "Subtract 2!" << endl;
    };
    
    
    
    // Test the "manual", not "iterated" state machine.
    FiniteStateMachine<double> sm(Zero);
    
    sm.addEdge(Zero, One, addOneCallback);
    sm.addEdge(One, Two, addOneCallback);
    sm.addEdge(Two, Zero, subtractTwoCallack);
    
    bool b = sm.transitionToVertex(Two); // Won't do anything
    b = sm.transitionToVertex(One); // Works
    b = sm.transitionToVertex(Two); // Works
    b = sm.transitionToVertex(One); // Won't do anything
    b = sm.transitionToVertex(Zero); // Works
    
    
    
    cout << endl << endl;
    
    // Now test iterated state machine
    int i;
    
    IteratedFiniteStateMachine ism(Zero);
    ism.addEdge(Zero, One, addOneCallback);
    ism.addEdge(One, Two, addOneCallback);
    ism.addEdge(Two, Zero, [] (FiniteStateMachineEdge edge) {
        cout <<  "Subtract 2!" << endl;
    });
    
    ism.setVertexData(Zero, [&i] (FiniteStateMachineVertexID vertex) {
        return i > 2 ? One : Zero;
    });
    
    ism.setVertexData(One, [&i] (FiniteStateMachineVertexID vertex) {
        return i > 4 ? Two : One;
    });
    
    ism.setVertexData(Two, [&i] (FiniteStateMachineVertexID vertex) {
        return i > 10 ? Zero : Two;
    });
    
    for (i = 0; i < 100; i++) {
        cout << ism.getCurrentVertex() << endl;
        ism.update();
    }
    
    
    
    
    return 0;
}
