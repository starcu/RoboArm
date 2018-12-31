#define BOOST_TEST_MODULE MuxTests
#include <boost/test/unit_test.hpp>
#include "Multiplexer.h"

BOOST_AUTO_TEST_CASE( begin_state_test )
{
    Multiplexer testMux;

    testMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW, LOW, LOW)
    ->addStateToQueue(HIGH, LOW, LOW)
    ->addStateToQueue(LOW, HIGH, LOW)
    ->addStateToQueue(LOW, LOW, HIGH)
    ->begin();

    State tstate {LOW,LOW,LOW};
    const State currState = testMux.getCurrentState();

    BOOST_CHECK_EQUAL(tstate,currState);

    State tstate2 {LOW,HIGH,LOW};
    BOOST_CHECK_NE(tstate2,currState);
}

BOOST_AUTO_TEST_CASE( next_state_test )
{
    Multiplexer testMux;

    testMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW, LOW, LOW)
    ->addStateToQueue(HIGH, LOW, LOW)
    ->addStateToQueue(LOW, HIGH, LOW)
    ->addStateToQueue(LOW, LOW, HIGH)
    ->begin();

    State tstate {LOW,LOW,LOW};
    State currState = testMux.getCurrentState();

    BOOST_CHECK_EQUAL(tstate,currState); //check if first state is correct

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate2 {HIGH, LOW, LOW};
    BOOST_CHECK_EQUAL(tstate2,currState); // check second state

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate3 {LOW, HIGH, LOW};
    BOOST_CHECK_EQUAL(tstate3,currState); // check third state

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate4 {LOW, LOW, HIGH};
    BOOST_CHECK_EQUAL(tstate4,currState); // check fourth state (the last one)
}

BOOST_AUTO_TEST_CASE( check_return_to_the_front )
{
    Multiplexer testMux;

    testMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW, LOW, LOW)
    ->addStateToQueue(HIGH, LOW, LOW)
    ->addStateToQueue(LOW, HIGH, LOW)
    ->addStateToQueue(LOW, LOW, HIGH)
    ->begin();

    testMux.nextState();
    testMux.nextState();
    testMux.nextState();
    State currState = testMux.getCurrentState();

    State tstate {LOW, LOW, HIGH};
    BOOST_CHECK_EQUAL(tstate,currState); // check fourth state (the last one)

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate2 {LOW, LOW, LOW};
    BOOST_CHECK_EQUAL(tstate2,currState); // check if first state is correct again

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate3 {HIGH, LOW, LOW};
    BOOST_CHECK_EQUAL(tstate3,currState); // check second state
}

BOOST_AUTO_TEST_CASE( check_return_to_the_back )
{
    Multiplexer testMux;

    testMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW, LOW, LOW)
    ->addStateToQueue(HIGH, LOW, LOW)
    ->addStateToQueue(LOW, HIGH, LOW)
    ->addStateToQueue(LOW, LOW, HIGH)
    ->begin();

    State currState = testMux.getCurrentState();
    State tstate {LOW, LOW, LOW};
    BOOST_CHECK_EQUAL(tstate,currState); // check first state

    testMux.prevState();
    currState = testMux.getCurrentState();
    State tstate2 {LOW, LOW, HIGH};
    BOOST_CHECK_EQUAL(tstate2,currState); // check if prevState() jumped to last state (previous was first one)

    testMux.prevState();
    currState = testMux.getCurrentState();
    State tstate3 {LOW, HIGH, LOW};
    BOOST_CHECK_EQUAL(tstate3,currState); // check third state
}

BOOST_AUTO_TEST_CASE( check_mixed_moves )
{
    Multiplexer testMux;

    auto s0 = State(LOW, LOW, LOW);
    auto s1 = State(HIGH, LOW, LOW);
    auto s2 = State(LOW, HIGH, LOW);
    auto s3 = State(LOW, LOW, HIGH);

    testMux
    .setCtrlPins(17, 27, 22)
    ->addStateToQueue(s0)
    ->addStateToQueue(s1)
    ->addStateToQueue(s2)
    ->addStateToQueue(s3)
    ->begin();

    std::vector<State> testsStatesForward = {s0,s1,s2,s3,s0,s1,s2,s3,s0,s1,s2};
    std::vector<State> testsStatesPrev    = {s3,s2,s1,s0,s3,s2,s1,s0,s3,s2,s1};

    for(const auto& stf: testsStatesForward)
    {
        State currState = testMux.getCurrentState();
        BOOST_CHECK_EQUAL(stf, currState); // check status
        testMux.nextState();
    }

    for(const auto& stp: testsStatesPrev)
    {
        State currState = testMux.getCurrentState();
        BOOST_CHECK_EQUAL(stp, currState); // check status
        testMux.prevState();
    }
}

BOOST_AUTO_TEST_CASE( multiple_buses_test )
{
    enum BUSES
    {
        BUS_0,
        BUS_1,
        BUS_2
    };

    Multiplexer testMux;

    testMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW, LOW, LOW, BUSES::BUS_0)
    ->addStateToQueue(HIGH, LOW, LOW, BUSES::BUS_0)
    ->addStateToQueue(LOW, HIGH, LOW, BUSES::BUS_1)
    ->addStateToQueue(LOW, LOW, HIGH, BUSES::BUS_1)
    ->addStateToQueue(LOW, HIGH, HIGH, BUSES::BUS_2)
    ->addStateToQueue(HIGH, LOW, HIGH, BUSES::BUS_2)
    ->begin();

    State tstate {LOW,LOW,LOW,BUSES::BUS_0};
    State currState = testMux.getCurrentState();
    BOOST_CHECK_EQUAL(tstate,currState); //check if first state is correct
    BOOST_CHECK_EQUAL(tstate.getStateBus(), BUSES::BUS_0); //check first state bus

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate2 {HIGH, LOW, LOW,BUSES::BUS_0};
    BOOST_CHECK_EQUAL(tstate2,currState); // check second state
    BOOST_CHECK_EQUAL(tstate2.getStateBus(), BUSES::BUS_0); // check second state bus

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate3 {LOW, HIGH, LOW,BUSES::BUS_1};
    BOOST_CHECK_EQUAL(tstate3,currState); // check third state
    BOOST_CHECK_EQUAL(tstate3.getStateBus(), BUSES::BUS_1); // check third state bus

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate4 {LOW, LOW, HIGH,BUSES::BUS_1};
    BOOST_CHECK_EQUAL(tstate4,currState); // check fourth state
    BOOST_CHECK_EQUAL(tstate4.getStateBus(), BUSES::BUS_1); // check fourth state bus

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate5 {LOW, HIGH, HIGH,BUSES::BUS_2};
    BOOST_CHECK_EQUAL(tstate5,currState); // check fifth state
    BOOST_CHECK_EQUAL(tstate5.getStateBus(), BUSES::BUS_2); // check fifth state bus

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate6 {HIGH, LOW, HIGH,BUSES::BUS_2};
    BOOST_CHECK_EQUAL(tstate6,currState); // check sixth state
    BOOST_CHECK_EQUAL(tstate6.getStateBus(), BUSES::BUS_2); // check sixth state bus

    testMux.nextState();
    currState = testMux.getCurrentState();
    State tstate1_bis {LOW,LOW,LOW,BUSES::BUS_0};
    BOOST_CHECK_EQUAL(tstate1_bis,currState); //check if first state is correct
    BOOST_CHECK_EQUAL(tstate1_bis.getStateBus(), BUSES::BUS_0); //check first state bus after mux overflow
}