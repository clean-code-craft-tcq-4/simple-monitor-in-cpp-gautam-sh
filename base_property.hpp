template<class T>
class BaseProperty {
    public:
    enum limit_type {DUAL_INSIDE, DUAL_OUTSIDE, UPPER, LOWER};
    
    enum state {LOW_LIMIT_BREACH, LOW_LIMIT_WARNING,
      NORMAL, HIGH_LIMIT_WARNING, HIGH_LIMIT_BREACH};

    T upperLimit;
    T lowerLimit;
    T tolerance;
    float tolerancePercent;

    limit_type limitType = DUAL_INSIDE;
    std::string propertyName = "test_property";

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


};