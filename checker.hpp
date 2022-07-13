#include <assert.h>
#include <iostream>
#include <vector>
#include "property.hpp"

class BatteryChecker {
    public:

        std::vector<Property<float>> battery_properties;

        BatteryChecker();

        BatteryChecker(std::vector<Property<float>> &properties)
            : battery_properties(properties) {
            };

        bool batteryIsOk(bool printMessage = false) {
            for(auto it : battery_properties) {
                Property<float>::state property_state = it.propertyIsOk(printMessage);
                if(property_state == it.HIGH_LIMIT_BREACH || property_state == it.LOW_LIMIT_BREACH)
                    return false;
            }
            return true;
        }

};