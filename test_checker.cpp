#include "checker.hpp"

std::string printLanguage = "ENGLISH";

int main() {
    size_t testSize = 7;


    std::vector<float> test_temperature(0, testSize);
    std::vector<float> test_soc(0, testSize);
    std::vector<float> test_charge_rate(0, testSize);

    test_temperature = {-2, 0, 2.25, 25, 42.75, 45, 60};
    test_soc = {-5, 20, 24, 70, 76, 80, 100};
    test_charge_rate = {-3, 0.35, 0.8, 0.84, 0.945, 1.0, 20.3};

    std::vector<bool> expected_result = {false, false, true, true, true, true, false};

    BaseProperty<float> temperatureObj;
    temperatureObj.isDualLimit(0, 45);
    temperatureObj.setTolerancePercent(5);

    BaseProperty<float> socObj;
    socObj.isDualLimit(20, 80);
    socObj.setTolerancePercent(5);

    BaseProperty<float> chargeRateObj;
    chargeRateObj.isStrictLowerLimit(0.8);
    chargeRateObj.setTolerancePercent(5);

    for(size_t i = 0; i < testSize; ++i) {
        Property<float> temperature(test_temperature[i], temperatureObj);
        Property<float> soc(test_soc[i], socObj);
        Property<float> chargeRate(test_charge_rate[i], chargeRateObj);
        
        std::vector<Property<float>> test_properties = {temperature, soc, chargeRate};
        BatteryChecker test_battery(test_properties);
        // std::cout << i << test_battery.batteryIsOk() << expected_result[i] << std::endl;
        assert(test_battery.batteryIsOk(true) == expected_result[i]);
    }

    return 0;
}