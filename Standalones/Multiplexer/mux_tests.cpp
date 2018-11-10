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