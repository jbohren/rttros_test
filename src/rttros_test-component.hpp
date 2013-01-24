#ifndef OROCOS_RTTROS_TEST_COMPONENT_HPP
#define OROCOS_RTTROS_TEST_COMPONENT_HPP

#include <rtt/RTT.hpp>

#include <std_msgs/String.h>

class Rttros_test : public RTT::TaskContext{
  public:
    Rttros_test(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

    RTT::InputPort<std_msgs::String> stateInPort;

};
#endif
