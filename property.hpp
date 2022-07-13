#include <optional>

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
    limit_type limitType;
    std::string propertyName;

    Property() = delete;

    Property(std::string fproperty_name, T ftest_variable, T fupper_limit, T flower_limit, float ftolerance, bool fsafe_inside)
      : propertyName(fproperty_name), testVariable(ftest_variable), tolerancePercent(ftolerance),
        upperLimit(fupper_limit), lowerLimit(flower_limit) {
          tolerance = upperLimit * tolerancePercent/100.;
          if(fsafe_inside) limitType = DUAL_INSIDE;
          else limitType = DUAL_OUTSIDE;
        }

    Property(std::string fproperty_name, T ftest_variable, T flimit, float ftolerance, bool fis_upper)
      : propertyName(fproperty_name), testVariable(ftest_variable), tolerancePercent(ftolerance) {
          tolerance = flimit * tolerancePercent/100.;
          if(fis_upper) {
            limitType = UPPER;
            upperLimit = flimit;
          }
          else {
            limitType = LOWER;
            lowerLimit = flimit;
          }
        }

    private:
      void printMessage(state property_state) {
        if(property_state == HIGH_LIMIT_BREACH || property_state == LOW_LIMIT_BREACH) {
          std::cout << this->propertyName << " = " << this->testVariable << ": Outside the limits!\n";
          return;
        }
        else if(property_state == HIGH_LIMIT_WARNING) {
          std::cout << this->propertyName << " = " << this->testVariable << ": WARNING: " << this->propertyName << " approaching the upper limit!\n";
          return;
        }
        else if(property_state == LOW_LIMIT_WARNING) {
          std::cout << this->propertyName << " = " << this->testVariable << ": WARNING: " << this->propertyName << " approaching the lower limit!\n";
          return;
        }
      }
      state withinLimits(bool print_message) {
        T conservativeLowerLimit = lowerLimit + tolerance;
        T conservativeUpperLimit = upperLimit - tolerance;
        if(testVariable >= conservativeLowerLimit && testVariable <= conservativeUpperLimit)
          return NORMAL;
        else if(testVariable < conservativeLowerLimit) {
          state fproperty_state = (testVariable < lowerLimit) ? LOW_LIMIT_BREACH : LOW_LIMIT_WARNING;
          if(print_message) printMessage(fproperty_state);
          return fproperty_state;
        }
        else {
          state fproperty_state = (testVariable > upperLimit) ? HIGH_LIMIT_BREACH : HIGH_LIMIT_WARNING;
          if(print_message) printMessage(fproperty_state);
          return fproperty_state;
        }
      }

      state outsideLimits(bool print_message) {
        T conservativeLowerLimit = lowerLimit - tolerance;
        T conservativeUpperLimit = upperLimit + tolerance;
        if(testVariable <= conservativeLowerLimit || testVariable >= conservativeUpperLimit)
          return NORMAL;
        else if(testVariable > conservativeLowerLimit) {
          state fproperty_state = (testVariable <= lowerLimit) ? LOW_LIMIT_WARNING : LOW_LIMIT_BREACH;
          if(print_message) printMessage(fproperty_state);
          return fproperty_state;
        }
        else {
          state fproperty_state = (testVariable >= upperLimit) ? HIGH_LIMIT_WARNING : HIGH_LIMIT_BREACH;
          if(print_message) printMessage(fproperty_state);
          return fproperty_state;
        }
      }

      state outsideUpperLimit(bool print_message) {
        T conservativeUpperLimit = upperLimit - tolerance;
        if(testVariable <= conservativeUpperLimit)
          return NORMAL;
        else {
          state fproperty_state = (testVariable >= upperLimit) ? HIGH_LIMIT_BREACH : HIGH_LIMIT_WARNING;
          if(print_message) printMessage(fproperty_state);
          return fproperty_state;
        }
      }

      state outsideLowerLimit(bool print_message) {
        T conservativeLowerLimit = lowerLimit + tolerance;
        if(testVariable >= conservativeLowerLimit)
          return NORMAL;
        else {
          state fproperty_state = (testVariable <= lowerLimit)  ? LOW_LIMIT_BREACH : LOW_LIMIT_WARNING;
          if(print_message) printMessage(fproperty_state);
          return fproperty_state;
        }
      }

      public:
        state propertyIsOk(bool print_message = false) {
          switch(limitType) {
            case DUAL_INSIDE:
              return withinLimits(print_message);
            case DUAL_OUTSIDE:
              return outsideLimits(print_message);
            case UPPER:
              return outsideUpperLimit(print_message);
            case LOWER:
              return outsideLowerLimit(print_message);
          }
        }
};

// class CheckerFunction {
   
//   private:
//     bool temperatureInRange() {
//     if(temperature < 0 || temperature > 45) {
//       std::cout << "Temperature out of range!\n";
//       return false;
//     }
//     return true;
//   }

//     bool chargeInRange() {
//     if(soc < 20 || soc > 80) {
//       std::cout << "State of Charge out of range!\n";
//       return false;
//     }
//     return true;
//   }

//     bool chargeRateInRange() {
//     if(chargeRate > 0.8) {
//       std::cout << "Charge Rate out of range!\n";
//       return false;
//     }
//     return true;
//   }
  
//   public:
//     float temperature, soc, chargeRate;
//     std::vector<bool(CheckerFunction::*)()> testFunction;

//     CheckerFunction(){
//         testFunction = {&CheckerFunction::temperatureInRange, &CheckerFunction::chargeInRange, &CheckerFunction::chargeRateInRange};
//     };

//     CheckerFunction(float ftemperature, float fsoc, float fchargeRate) : temperature(ftemperature), soc(fsoc), chargeRate(fchargeRate) {
//       testFunction = {&CheckerFunction::temperatureInRange, &CheckerFunction::chargeInRange, &CheckerFunction::chargeRateInRange};
//     };
// };

// bool batteryIsOk(CheckerFunction& test) {
//   bool result = true;
//   auto it = test.testFunction.begin();
//   while(result && it != test.testFunction.end())
//   {
//     result = (test.*(*it))();
//     ++it;
//   }
//   return result;
// }
