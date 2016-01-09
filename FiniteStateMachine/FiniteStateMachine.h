//
//  FiniteStateMachine.h
//  FiniteStateMachine
//
//  Created by Donald Pinckney on 12/20/15.
//  Copyright © 2015 Donald Pinckney. All rights reserved.
//

#ifndef FiniteStateMachine_h
#define FiniteStateMachine_h

#include <map>
#include <vector>
#include <functional>

typedef int FiniteStateMachineVertexID;
typedef int FiniteStateMachineEdgeID;

struct FiniteStateMachineEdge {
    FiniteStateMachineVertexID fromVertexID;
    FiniteStateMachineVertexID toVertexID;
    FiniteStateMachineEdgeID edgeID;
};


template <typename VertexData>
class FiniteStateMachine {
    
    FiniteStateMachineVertexID currentVertex;
    FiniteStateMachineEdgeID automaticUniqueEdgeID = -1;
    std::map<FiniteStateMachineVertexID, std::vector<FiniteStateMachineEdge> > directedAdjacencyListByVertexID;
    std::map<FiniteStateMachineEdgeID, FiniteStateMachineEdge> directedAdjacencyListByEdgeID;
    std::map<FiniteStateMachineVertexID, VertexData> vertexData;
    
    std::map<FiniteStateMachineEdgeID, std::function<void (FiniteStateMachineEdge)> > callbackFunctions;
    
    void completeEdgeTransition(FiniteStateMachineEdge edge) {
        // TODO: Run call back functions, etc.
        std::map<FiniteStateMachineEdgeID, std::function<void (FiniteStateMachineEdge)> >::const_iterator it = callbackFunctions.find(edge.edgeID);
        if(it != callbackFunctions.end()) {
            (it->second)(edge);
        }
        
        currentVertex = edge.toVertexID;
    }
    
public:
    FiniteStateMachine(FiniteStateMachineVertexID initialVertex) : currentVertex(initialVertex) { }
    
    void setVertexData(FiniteStateMachineVertexID i, VertexData d) {
        vertexData[i] = d;
    }
    
    FiniteStateMachineVertexID getCurrentVertex() const {
        return currentVertex;
    }
    
    VertexData *getCurrentVertexData() {
        typename std::map<FiniteStateMachineVertexID, VertexData>::iterator it = vertexData.find(currentVertex);
        if(it == vertexData.end()) {
            return NULL;
        }
        
        return &(it->second);
    }
    
    
    void fullyConnect(const std::vector<FiniteStateMachineVertexID> &vertices) {
        fullyConnect(vertices, NULL);
    }
    
    void fullyConnect(const std::vector<FiniteStateMachineVertexID> &vertices, std::function<void (FiniteStateMachineEdge)> callback) {
        for (std::vector<FiniteStateMachineVertexID>::const_iterator it = vertices.begin(); it != vertices.end(); it++) {
            FiniteStateMachineVertexID vertex1 = *it;
            for (std::vector<FiniteStateMachineVertexID>::const_iterator it2 = it + 1; it2 != vertices.end(); it2++) {
                addEdge(vertex1, *it2, callback);
                addEdge(*it2, vertex1, callback);
            }
        }
    }
    
    void addEdge(FiniteStateMachineVertexID from, FiniteStateMachineVertexID to) {
        addEdge(from, to, automaticUniqueEdgeID, NULL);
        automaticUniqueEdgeID--;
    }
    

    // The edge ID must be 0 or positive.
    void addEdge(FiniteStateMachineVertexID from, FiniteStateMachineVertexID to, FiniteStateMachineEdgeID edgeID) {
        addEdge(from, to, edgeID, NULL);
    }
    

    void addEdge(FiniteStateMachineVertexID from, FiniteStateMachineVertexID to, std::function<void (FiniteStateMachineEdge)> callback) {
        addEdge(from, to, automaticUniqueEdgeID, callback);
        automaticUniqueEdgeID--;
    }
    
    // The edge ID must be 0 or positive.
    void addEdge(FiniteStateMachineVertexID from, FiniteStateMachineVertexID to, FiniteStateMachineEdgeID edgeID, std::function<void (FiniteStateMachineEdge)> callback) {
        FiniteStateMachineEdge edge;
        edge.fromVertexID = from;
        edge.toVertexID = to;
        edge.edgeID = edgeID;
        
        directedAdjacencyListByVertexID[from].push_back(edge);
        directedAdjacencyListByEdgeID[edgeID] = edge;
        callbackFunctions[edgeID] = callback;
    }
    
    bool edgeWhichTransitionsToVertex(FiniteStateMachineVertexID destinationVertexID, FiniteStateMachineEdge *maybeEdge) const {
        std::map<FiniteStateMachineVertexID, std::vector<FiniteStateMachineEdge> >::const_iterator it = directedAdjacencyListByVertexID.find(currentVertex);
        if(it == directedAdjacencyListByVertexID.end()) {
            return false;
        }
        
        const std::vector<FiniteStateMachineEdge> &edges = it->second;
        
        // Search for an edge that leads to our destination
        for (std::vector<FiniteStateMachineEdge>::const_iterator it = edges.begin(); it != edges.end(); it++) {
            if(it->toVertexID == destinationVertexID) {
                *maybeEdge = *it;
                return true;
            }
        }
        
        return false;
    }
    
    bool transitionToVertex(FiniteStateMachineVertexID destinationVertexID) {
        if(destinationVertexID == currentVertex) {
            return false;
        }
        
        FiniteStateMachineEdge edge;
        if(edgeWhichTransitionsToVertex(destinationVertexID, &edge)) {
            completeEdgeTransition(edge);
            return true;
        }
        return false;
    }
    
    bool canTransitionUsingEdge(FiniteStateMachineEdgeID edgeID) const {
        
        std::map<FiniteStateMachineEdgeID, FiniteStateMachineEdge>::const_iterator it = directedAdjacencyListByEdgeID.find(edgeID);
        if(it == directedAdjacencyListByEdgeID.end()) {
            return false;
        }
        
        FiniteStateMachineEdge possibleEdge = it->second;
        if(possibleEdge.fromVertexID == currentVertex) {
            return true;
        }
        return false;
    }
    
    bool transitionUsingEdge(FiniteStateMachineEdgeID edgeID) {
        FiniteStateMachineEdge possibleEdge = directedAdjacencyListByEdgeID[edgeID];
        if(possibleEdge.fromVertexID == currentVertex) {
            completeEdgeTransition(possibleEdge);
            return true;
        }
        return false;
    }
};

#endif /* FiniteStateMachine_h */
