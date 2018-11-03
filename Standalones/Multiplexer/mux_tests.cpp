#define BOOST_TEST_MODULE MuxTests
#include <boost/test/unit_test.hpp>
#include "Multiplexer.h"

BOOST_AUTO_TEST_CASE( begin_state_test )
{
    //my_class test_object( "qwerty" );
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
