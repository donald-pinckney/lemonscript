//
//  IteratedFiniteStateMachine.h
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/22/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef IteratedFiniteStateMachine_h
#define IteratedFiniteStateMachine_h

#include "FiniteStateMachine.h"
#include <functional>

// Because this isn't actually templated, could easily move functions to cpp.

class IteratedFiniteStateMachine : public FiniteStateMachine<std::function<FiniteStateMachineVertexID (FiniteStateMachineVertexID)> > {
    
public:
    IteratedFiniteStateMachine(FiniteStateMachineVertexID initialVertex) : FiniteStateMachine(initialVertex) { }

    void update() {
        std::function<FiniteStateMachineVertexID (FiniteStateMachineVertexID)> *currentUpdateFunc = getCurrentVertexData();
        if(currentUpdateFunc == NULL) {
            // TODO: Do something with the case of no given update function.
            return;
        }
        
        FiniteStateMachineVertexID newState = (*currentUpdateFunc)(getCurrentVertex());
        transitionToVertex(newState);
    }
};

#endif /* IteratedFiniteStateMachine_h */
