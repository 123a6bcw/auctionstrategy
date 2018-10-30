#pragma once

class Strategy {
public:
    SellerStrategyAbstract(int _endMove, vector&<Seller::pmove> _previousMoves) : startMove(_previousMoves.size()), endMove(_endMove), previousMoves(_previousMoves), currentMove(_previousMoves.size());
    virtual void randomParametersChange() = delete;
    
    const int startMove;
    const int endMove;
protected:
    vector& <Seller::pmove> previousMoves;
    int currentMove;
}
