#include "printMessage.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

extern std::string printLanguage;

template <class T>
class Property {
  public:
    enum limit_type {DUAL_INSIDE, DUAL_OUTSIDE, UPPER, LOWER};
    
    enum state {LOW_LIMIT_BREACH, LOW_LIMIT_WARNING,
      NORMAL, HIGH_LIMIT_WARNING, HIGH_LIMIT_BREACH};

    T testVariable;
    T upperLimit;
    T lowerLimit;
    T tolerance = upperLimit * tolerancePercent/100.;
    float tolerancePercent;
    limit_type limitType = DUAL_INSIDE;
    std::string propertyName;

    std::vector<std::string> print_book = {outsideLimitMsg, lowerLimitWarning, normalMsg, upperLimitWarning, outsideLimitMsg};
    Property();

    Property(T ftest_variable) : testVariable(ftest_variable) {};

    void isDualLimit(T flower_limit, T fupper_limit, bool fsafe_inside = true) {
        if(!fsafe_inside) limitType = DUAL_OUTSIDE;
        lowerLimit = flower_limit;
        upperLimit = fupper_limit;
      }

      void isStrictUpperLimit(T fupper_limit) {
        limitType = UPPER;
        upperLimit = fupper_limit;
      }

      void isStrictLowerLimit(T flower_limit) {
        limitType = LOWER;
        lowerLimit = flower_limit;
      }

      void setPropertyName(std::string fproperty_name) {
        propertyName = fproperty_name;
      }

      void setTolerancePercent(float ftolerance_percent) {
        tolerancePercent = ftolerance_percent;
      }

  private:
      void printMessage(state property_state) {

        printPhrase();
        // std::cout << size_t(property_state) << print_book[size_t(property_state)] << std::endl;
        std::cout << this->propertyName << " = " << this->testVariable << print_book[property_state] << this->propertyName <<"!\n";
      }

      state withinLimits(bool print_message) {
        T conservativeLowerLimit = lowerLimit + tolerance;
        T conservativeUpperLimit = upperLimit - tolerance;
        
        std::vector<T> boundary = {lowerLimit, conservativeLowerLimit, conservativeUpperLimit, upperLimit};
        auto it = std::upper_bound(boundary.cbegin(), boundary.cend(), testVariable);
        if(testVariable == upperLimit) --it;
        
        state possible_state;
        if(print_message) printMessage(state(it - boundary.cbegin()));
        return state(it - boundary.cbegin());
      }

      state outsideUpperLimit(bool print_message) {
        T conservativeUpperLimit = upperLimit - tolerance;

        std::vector<T> boundary = {conservativeUpperLimit, upperLimit};
        auto it = std::upper_bound(boundary.cbegin(), boundary.cend(), testVariable);
        if(testVariable == upperLimit) --it;
        
        state possible_state;
        if(print_message) printMessage(state(it - boundary.cbegin()));
        return state(it - boundary.cbegin());
      }

      state outsideLowerLimit(bool print_message) {
        T conservativeLowerLimit = lowerLimit + tolerance;

        std::vector<T> boundary = {lowerLimit, conservativeLowerLimit};
        auto it = std::upper_bound(boundary.cbegin(), boundary.cend(), testVariable);
        
        state possible_state;
        if(print_message) printMessage(state(it - boundary.cbegin()));
        return state(it - boundary.cbegin());
      }

      public:
        state propertyIsOk(bool print_message = false) {
          switch(limitType) {
            case DUAL_INSIDE:
              return withinLimits(print_message);
            // case DUAL_OUTSIDE:
            //   return outsideLimits(print_message);
            case UPPER:
              return outsideUpperLimit(print_message);
            case LOWER:
              return outsideLowerLimit(print_message);
          }
        }
};