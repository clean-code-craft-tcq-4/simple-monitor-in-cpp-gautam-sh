#include "printMessage.hpp"
#include "base_property.hpp"
#include <vector>
#include <algorithm>

extern std::string printLanguage;

template <class T>
class Property{
  public:
    // enum limit_type {DUAL_INSIDE, DUAL_OUTSIDE, UPPER, LOWER};
    
    // enum state {LOW_LIMIT_BREACH, LOW_LIMIT_WARNING,
    //   NORMAL, HIGH_LIMIT_WARNING, HIGH_LIMIT_BREACH};

    T testVariable;
    BaseProperty<T> baseProperty;
    // limit_type limitType = DUAL_INSIDE;
    // std::string propertyName;

    Property() = delete;

    Property(T ftest_variable, BaseProperty<T> fbase_property)
      : testVariable(ftest_variable), baseProperty(fbase_property){}

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

      
    private:

    // T upperLimit;
    // T lowerLimit;
    // T tolerance;
    // float tolerancePercent;
 
      void printMessage(BaseProperty<float>::state property_state) {

        printPhrase();

        if(property_state == BaseProperty<float>::HIGH_LIMIT_BREACH || property_state == BaseProperty<float>::LOW_LIMIT_BREACH) {
          std::cout << this->baseProperty.propertyName << " = " << this->testVariable << outsideLimitMsg << "!\n";
          return;
        }
        else if(property_state == BaseProperty<float>::HIGH_LIMIT_WARNING) {
          std::cout << this->baseProperty.propertyName << " = " << this->testVariable << upperLimitWarning << this->baseProperty.propertyName << "!\n";
          return;
        }
        else if(property_state == BaseProperty<float>::LOW_LIMIT_WARNING) {
          std::cout << this->baseProperty.propertyName << " = " << this->testVariable  << lowerLimitWarning << this->baseProperty.propertyName << "!\n";
          return;
        }
      }

      BaseProperty<float>::state withinLimits(bool print_message) {
        T conservativeLowerLimit = baseProperty.lowerLimit + baseProperty.tolerance;
        T conservativeUpperLimit = baseProperty.upperLimit - baseProperty.tolerance;
        
        std::vector<T> boundary = {baseProperty.lowerLimit, conservativeLowerLimit, conservativeUpperLimit, baseProperty.upperLimit};
        auto it = std::upper_bound(boundary.cbegin(), boundary.cend(), testVariable);
        if(testVariable == baseProperty.upperLimit) --it;
        
        BaseProperty<float>::state possible_state;
        if(print_message) printMessage(BaseProperty<float>::state(it - boundary.cbegin()));
        return BaseProperty<float>::state(it - boundary.cbegin());
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

      BaseProperty<float>::state outsideUpperLimit(bool print_message) {
        T conservativeUpperLimit = baseProperty.upperLimit - baseProperty.tolerance;

        std::vector<T> boundary = {conservativeUpperLimit, baseProperty.upperLimit};
        auto it = std::upper_bound(boundary.cbegin(), boundary.cend(), testVariable);
        if(testVariable == baseProperty.upperLimit) --it;
        
      BaseProperty<float>::state possible_state;
        if(print_message) printMessage(BaseProperty<float>::state(it - boundary.cbegin()));
        return BaseProperty<float>::state(it - boundary.cbegin());
      }

      BaseProperty<float>::state outsideLowerLimit(bool print_message) {
        T conservativeLowerLimit = baseProperty.lowerLimit + baseProperty.tolerance;

        std::vector<T> boundary = {baseProperty.lowerLimit, conservativeLowerLimit};
        auto it = std::upper_bound(boundary.cbegin(), boundary.cend(), testVariable);
        
        BaseProperty<float>::state possible_state;
        if(print_message) printMessage(BaseProperty<float>::state(it - boundary.cbegin()));
        return BaseProperty<float>::state(it - boundary.cbegin());
      }

      public:
        BaseProperty<float>::state propertyIsOk(bool print_message = false) {
          switch(baseProperty.limitType) {
            case BaseProperty<float>::DUAL_INSIDE:
              return withinLimits(print_message);
            // case DUAL_OUTSIDE:
            //   return outsideLimits(print_message);
            case BaseProperty<float>::UPPER:
              return outsideUpperLimit(print_message);
            case BaseProperty<float>::LOWER:
              return outsideLowerLimit(print_message);
          }
        }
};