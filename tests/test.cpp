#include <iostream>
#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>



struct MockAcc : public Account{
    MockAcc(int id, int balance) : Account(id, balance){}
    MOCK_METHOD1(ChangeBalance, void(int diff));
    MOCK_METHOD0(GetBalance, int());
    MOCK_METHOD0(id, int());
    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
};

struct MockTrans : public Transaction{
    MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum));
    MOCK_METHOD1(set_fee, void(int fee));
    MOCK_METHOD0(fee, int());
};


TEST(Transaction, TransMockTest1){
    MockTrans Acc_Trans1;
    MockAcc Human1(1, 10000);
    MockAcc Human2(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans1, set_fee(testing::_)).Times(1);
    EXPECT_CALL(Acc_Trans1, Make(testing::_, testing::_, testing::_)).Times(2);
    EXPECT_CALL(Acc_Trans1, fee()).Times(1);
    EXPECT_CALL(Human1, GetBalance()).Times(1);
    EXPECT_CALL(Human2, GetBalance()).Times(1);
    Acc_Trans1.set_fee(500);
    Acc_Trans1.Make(Human1, Human2, 2000);
    Acc_Trans1.fee();
    Human1.GetBalance();
    Human2.GetBalance();
    Acc_Trans1.Make(Organisation, Human2, 20000);
}

TEST(Transaction, TransMockTest2){
    MockTrans Acc_Trans2;
    MockAcc Human1(1, 10000);
    MockAcc Human2(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans2, Make(testing::_, testing::_, testing::_)).Times(3);
    Acc_Trans2.Make(Car_Shop, Car_Shop, 100000);
    Acc_Trans2.Make(Car_Shop, Organisation, -5600);
    Acc_Trans2.Make(Human2, Car_Shop, 55);
}

TEST(Transaction, Make){
    Transaction Acc_Trans;

    Account Human1(1, 10000);
    Account Human2(2, 230000);
    Account Car_Shop(3, 8000000);
    Account Organisation(4, 5500);

    Acc_Trans.set_fee(500);
    Acc_Trans.Make(Human1, Human2, 2000);

    EXPECT_NE(Acc_Trans.fee(), 350);
    EXPECT_EQ(Human1.GetBalance(), 7500);
    EXPECT_EQ(Human2.GetBalance(), 232000);
    ASSERT_EQ(Acc_Trans.Make(Organisation, Human2, 20000), false);
}

TEST(Transaction, MakeExceptions){
    Transaction Acc_Trans;

    Account Human1(1, 10000);
    Account Human2(2, 230000);
    Account Car_Shop(3, 8000000);
    Account Organisation(4, 5500);

    ASSERT_ANY_THROW(Acc_Trans.Make(Car_Shop, Car_Shop, 100000));
    ASSERT_ANY_THROW(Acc_Trans.Make(Car_Shop, Organisation, -5600));
    ASSERT_ANY_THROW(Acc_Trans.Make(Human2, Car_Shop, 55));
}

