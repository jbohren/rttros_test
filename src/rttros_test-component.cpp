#include "rttros_test-component.hpp"
#include <rtt/Component.hpp>
#include <rtt/plugin/PluginLoader.hpp>
#include <rtt/internal/GlobalService.hpp>


#include <iostream>

#include <std_msgs/String.h>

Rttros_test::Rttros_test(std::string const& name) : TaskContext(name)
{
  std::cout << "Rttros_test constructed !" <<std::endl;
  this->ports()->addPort("stateInPort",stateInPort);

}

bool Rttros_test::configureHook(){
  RTT::Service::shared_ptr GS = RTT::internal::GlobalService::Instance();
  RTT::OperationCaller<RTT::ConnPolicy(const std::string&)> getTopicConn = GS->provides("ros")->getOperation("topic");
  stateInPort.createStream(getTopicConn("/joint_states"));

  std::cout << "Rttros_test configured !" <<std::endl;
  return true;
}

bool Rttros_test::startHook(){


  std::cout << "Rttros_test started !" <<std::endl;
  return true;
}

void Rttros_test::updateHook() {
  std_msgs::String s;
  stateInPort.read(s);
  std::cout<<s.data<<std::endl;
  std::cout << "Rttros_test executes updateHook !" <<std::endl;
}

void Rttros_test::stopHook() {
  std::cout << "Rttros_test executes stopping !" <<std::endl;
}

void Rttros_test::cleanupHook() {
  std::cout << "Rttros_test cleaning up !" <<std::endl;
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Rttros_test)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Rttros_test)
