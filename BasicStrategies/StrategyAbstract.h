#pragma once

class StrategyAbstract {
public:
    StrategyAbstract(int _endMove) : startMove(_previousMoves.size()), endMove(_endMove), previousMoves(nullptr), currentMove(_previousMoves.size());
    virtual void randomParametersChange() = delete;
    
    const int startMove;
    const int endMove;
    setPreviousMoves(vector<pmove>& _previousMoves) {
        swap(previousMoves, _previousMoves);
    }
protected:
    vector<pmove>& previousMoves;
    int currentMove;
}
