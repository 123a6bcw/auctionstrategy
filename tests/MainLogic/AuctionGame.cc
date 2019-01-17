#include "../../MainLogic/include/AuctionGame.h"
#include "../../BasicStrategies/StrategyAbstract.h"
#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"
#include "../../BasicStrategies/SellerStrategies/AllSellerStrategies.h"

#include "gtest/gtest.h"

namespace {
class AuctionGameTest : public testing::Test {
protected:
    size_t movesInGame;
    RandomNumberGenerator* randomNumberGenerator;
    StrategiesController* controller;
    std::vector<StrategyAbstract*>* sellerStrategies;
    std::vector<StrategyAbstract*>* buyerStrategies;
    AuctionGame game;
    std::vector<pmove>* moves;


    virtual void SetUp() {
        movesInGame = 5;
        randomNumberGenerator = new RandomNumberGenerator(13);
        controller = new StrategiesController(randomNumberGenerator);
        sellerStrategies = new std::vector<StrategyAbstract*>(0);

        buyerStrategies = new std::vector<StrategyAbstract*>(0);
        moves = new std::vector<pmove>();
    }

    virtual void TearDown() {
    }
};

    TEST_F(AuctionGameTest, SimpleGame) {
        sellerStrategies->push_back(new SBinarySearch(nullptr, 0, movesInGame - 1, 0, 10));
        Seller seller(movesInGame, randomNumberGenerator, controller, sellerStrategies);

        buyerStrategies->push_back(new BSimple(nullptr, 0, movesInGame - 1, 5));
        Buyer buyer(movesInGame, 5, randomNumberGenerator, controller, buyerStrategies);

        AuctionGame game;
        game(&seller, &buyer, movesInGame, moves);
        ASSERT_EQ(movesInGame, moves->size());

        ASSERT_EQ(5, (*moves)[0].getPrice());
        ASSERT_FALSE((*moves)[0].wasSold());

        ASSERT_EQ(3, (*moves)[1].getPrice());
        ASSERT_TRUE((*moves)[1].wasSold());

        ASSERT_EQ(4, (*moves)[2].getPrice());
        ASSERT_TRUE((*moves)[2].wasSold());

        ASSERT_EQ(4, (*moves)[3].getPrice());
        ASSERT_TRUE((*moves)[3].wasSold());

        ASSERT_EQ(4, (*moves)[4].getPrice());
        ASSERT_TRUE((*moves)[4].wasSold());

        ASSERT_EQ(15, seller.getTotalGain());
        ASSERT_EQ(5, buyer.getTotalGain());
    }

    TEST_F(AuctionGameTest, ComplicatedGame) {
        movesInGame = 7;
        sellerStrategies->push_back(new SBinarySearch(nullptr, 0, 2, 1, 8));
        sellerStrategies->push_back(new SBinarySearch(nullptr, 3, 5, 4, 6));
        sellerStrategies->push_back(new SBinarySearch(nullptr, 6, 6, 0, 2));

        int buyerProfit = 2;
        buyerStrategies->push_back(new BSimple(nullptr, 0, 2, buyerProfit));
        buyerStrategies->push_back(new BSimple(nullptr, 3, 4, buyerProfit));
        buyerStrategies->push_back(new BSimple(nullptr, 5, 7, buyerProfit));

        Seller seller(movesInGame, randomNumberGenerator, controller, sellerStrategies);
        Buyer  buyer (movesInGame, buyerProfit, randomNumberGenerator, controller, buyerStrategies);
        game(&seller, &buyer, movesInGame, moves);
        ASSERT_EQ(7, moves->size());

        ASSERT_EQ(4, moves->at(0).getPrice());
        ASSERT_FALSE(moves->at(0).wasSold());

        ASSERT_EQ(2, moves->at(1).getPrice());
        ASSERT_FALSE(moves->at(1).wasSold());

        ASSERT_EQ(1, moves->at(2).getPrice());
        ASSERT_TRUE(moves->at(2).wasSold());

        ASSERT_EQ(5, moves->at(3).getPrice());
        ASSERT_FALSE(moves->at(3).wasSold());

        ASSERT_EQ(5, moves->at(4).getPrice());
        ASSERT_FALSE(moves->at(4).wasSold());

        ASSERT_EQ(5, moves->at(5).getPrice());
        ASSERT_FALSE(moves->at(5).wasSold());

        ASSERT_EQ(1, moves->at(6).getPrice());
        ASSERT_TRUE(moves->at(6).wasSold());

        ASSERT_EQ(2, seller.getTotalGain());
        ASSERT_EQ(2, buyer.getTotalGain());
    }
}