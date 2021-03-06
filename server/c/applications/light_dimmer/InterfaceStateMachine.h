
#ifndef SEQUANTO_INTERFACE_STATE_MACHINE_H_
#define SEQUANTO_INTERFACE_STATE_MACHINE_H_

#include "StateMachine.h"

typedef enum _InterfaceState
{
   INTERFACE_NOT_GRASPED = 0,
   INTERFACE_IGNORING = 1,
   INTERFACE_GRASPED = 2,
   INTERFACE_HOLDING = 3,
} InterfaceState;

typedef enum _InterfaceMessage
{
   INTERFACE_GRASP,
   INTERFACE_RELEASE,
   INTERFACE_TICK,
   INTERFACE_RESET,
} InterfaceMessage;

class InterfaceStateMachine : public StateMachine<InterfaceState, InterfaceMessage>
{
public:
   static const int EPSILON = 20;
   static const int ON_OFF_DELAY = 50;
   static const int DELAY_BEFORE_HOLD = 500;
   static const int LEVEL_DELAY = 1000;
   
private:
   int m_ticksSinceGrasp;
   //int m_ticksSinceHold;

   void setState ( InterfaceState _state );
   
public:
   InterfaceStateMachine ();
   
   void handle ( InterfaceMessage _message );
};

class Interface : public InterfaceStateMachine
{
public:
   static InterfaceStateMachine instance;
};

#endif
