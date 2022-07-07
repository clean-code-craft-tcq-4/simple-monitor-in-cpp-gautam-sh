#include <assert.h>
#include <iostream>
#include <vector>

class CheckerFunction {
   
  private:
    bool temperatureInRange() {
    if(temperature < 0 || temperature > 45) {
      std::cout << "Temperature out of range!\n";
      return false;
    }
    return true;
  }

    bool chargeInRange() {
    if(soc < 20 || soc > 80) {
      std::cout << "State of Charge out of range!\n";
      return false;
    }
    return true;
  }

    bool chargeRateInRange() {
    if(chargeRate > 0.8) {
      std::cout << "Charge Rate out of range!\n";
      return false;
    }
    return true;
  }
  
  public:
    float temperature, soc, chargeRate;
    std::vector<bool(CheckerFunction::*)()> testFunction;

    CheckerFunction(){
        testFunction = {&CheckerFunction::temperatureInRange, &CheckerFunction::chargeInRange, &CheckerFunction::chargeRateInRange};
    };

    CheckerFunction(float ftemperature, float fsoc, float fchargeRate) : temperature(ftemperature), soc(fsoc), chargeRate(fchargeRate) {
      testFunction = {&CheckerFunction::temperatureInRange, &CheckerFunction::chargeInRange, &CheckerFunction::chargeRateInRange};
    };
};

bool batteryIsOk(CheckerFunction& test) {
  bool result = true;
  auto it = test.testFunction.begin();
  while(result && it != test.testFunction.end())
  {
    result = (test.*(*it))();
    ++it;
  }
  return result;
}
