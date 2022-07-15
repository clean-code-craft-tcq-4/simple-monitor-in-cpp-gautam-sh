#include "printMessage.hpp"
#include <vector>
#include <algorithm>

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
    T tolerance;
    float tolerancePercent;
    limit_type limitType = DUAL_INSIDE;
    std::string propertyName;

    Property();

    Property(T ftest_variable) : testVariable(ftest_variable) {};

    // Property(std::string fproperty_name, T ftest_variable, T fupper_limit, T flower_limit, float ftolerance, bool fsafe_inside)
    //   : propertyName(fproperty_name), testVariable(ftest_variable), tolerancePercent(ftolerance),
    //     upperLimit(fupper_limit), lowerLimit(flower_limit) {
    //       tolerance = upperLimit * tolerancePercent/100.;
    //       if(fsafe_inside) limitType = DUAL_INSIDE;
    //       else limitType = DUAL_OUTSIDE;
    //     }

    // Property(std::string fproperty_name, T ftest_variable, T flimit, float ftolerance, bool fis_upper)
    //   : propertyName(fproperty_name), testVariable(ftest_variable), tolerancePercent(ftolerance) {
    //       tolerance = flimit * tolerancePercent/100.;
    //       if(fis_upper) {
    //         limitType = UPPER;
    //         upperLimit = flimit;
    //       }
    //       else {
    //         limitType = LOWER;
    //         lowerLimit = flimit;
    //       }
    //     }
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

        if(property_state == HIGH_LIMIT_BREACH || property_state == LOW_LIMIT_BREACH) {
          std::cout << this->propertyName << " = " << this->testVariable << outsideLimitMsg << "!\n";
          return;
        }
        else if(property_state == HIGH_LIMIT_WARNING) {
          std::cout << this->propertyName << " = " << this->testVariable << upperLimitWarning << this->propertyName << "!\n";
          return;
        }
        else if(property_state == LOW_LIMIT_WARNING) {
          std::cout << this->propertyName << " = " << this->testVariable  << lowerLimitWarning << this->propertyName << "!\n";
          return;
        }
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

      // state outsideLimits(bool print_message) {
      //   T conservativeLowerLimit = lowerLimit - tolerance;
      //   T conservativeUpperLimit = upperLimit + tolerance;
      //   if(testVariable <= conservativeLowerLimit || testVariable >= conservativeUpperLimit)
      //     return NORMAL;
      //   else if(testVariable > conservativeLowerLimit) {
      //     state fproperty_state = (testVariable <= lowerLimit) ? LOW_LIMIT_WARNING : LOW_LIMIT_BREACH;
      //     if(print_message) printMessage(fproperty_state);
      //     return fproperty_state;
      //   }
      //   else {
      //     state fproperty_state = (testVariable >= upperLimit) ? HIGH_LIMIT_WARNING : HIGH_LIMIT_BREACH;
      //     if(print_message) printMessage(fproperty_state);
      //     return fproperty_state;
      //   }
      // }

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