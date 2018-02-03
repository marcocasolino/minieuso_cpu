#include "OperationMode.h"

/* default constructor */
OperationMode::OperationMode() {
  this->_switch = false;
}



/* notify the object of a mode switch */
void OperationMode::Notify() {

  {
    std::unique_lock<std::mutex> lock(this->_m_switch);   
    this->_switch = true;
  } /* release mutex */
  this->_cv_switch.notify_all();

  /* also notify the analog acquisition */
  this->Analog->Notify();

}

/* reset the object's mode switch */
void OperationMode::Reset() {

  {
    std::unique_lock<std::mutex> lock(this->_m_switch);   
    this->_switch = false;
  } /* release mutex */

  /* also reset the analog switch */
  this->Analog->Reset();

  
}

/* start the operational mode - launch all processes */
void OperationMode::Start() {

}
