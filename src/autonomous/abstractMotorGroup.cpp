#include <autonomous/abstractMotorGroup.hpp>

int AbstractMotorGroup::count(void) {
    return motors.size();
}

void AbstractMotorGroup::setVelocity(double velocity, vex::velocityUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setVelocity(velocity, units);
    }
}

void AbstractMotorGroup::setVelocity(double velocity, vex::percentUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setVelocity(velocity, units);
    }
}

void AbstractMotorGroup::setStopping(vex::brakeType mode) {
    for (vex::motor* motor : motors) {
        motor -> setStopping(mode);
    }
}

void AbstractMotorGroup::resetPosition(void) {
    for (vex::motor* motor : motors) {
        motor -> resetPosition();
    }
}

void AbstractMotorGroup::setPosition(double value, vex::rotationUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setPosition(value, units);
    }
}

void AbstractMotorGroup::setTimeout(int32_t time, vex::timeUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setTimeout(time, units);
    }
}

void AbstractMotorGroup::spin(vex::directionType dir) {
    for (vex::motor* motor : motors) {
        motor -> spin(dir);
    }
}

void AbstractMotorGroup::spin(vex::directionType dir, double velocity, vex::velocityUnits units) {
    for (vex::motor* motor : motors) {
        motor -> spin(dir, velocity, units);
    }
}

void AbstractMotorGroup::spin(vex::directionType dir, double velocity, vex::percentUnits units) {
    for (vex::motor* motor : motors) {
        motor -> spin(dir, velocity, units);
    }
}

void AbstractMotorGroup::spin(vex::directionType dir, double voltage, vex::voltageUnits units) {
    for (vex::motor* motor : motors) {
        motor -> spin(dir, voltage, units);
    }
}

std::vector<bool> AbstractMotorGroup::spinTo(double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinTo(rotation, units, velocity, units_v, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinToPosition(double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinToPosition(rotation, units, velocity, units_v, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinTo(double rotation, vex::rotationUnits units, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinTo(rotation, units, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinToPosition(double rotation, vex::rotationUnits units, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinToPosition(rotation, units, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinFor(double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinFor(rotation, units, velocity, units_v, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinFor(vex::directionType dir, double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinFor(dir, rotation, units, velocity, units_v, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinFor(double rotation, vex::rotationUnits units, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinFor(rotation, units, waitForCompletion));
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::spinFor(vex::directionType dir, double rotation, vex::rotationUnits units, bool waitForCompletion) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> spinFor(dir, rotation, units, waitForCompletion));
    }
    return v;
}

void AbstractMotorGroup::spinFor(double time, vex::timeUnits units, double velocity, vex::velocityUnits units_v) {
    for (vex::motor* motor : motors) {
        motor -> spinFor(time, units, velocity, units_v);
    }
}

void AbstractMotorGroup::spinFor(vex::directionType dir, double time, vex::timeUnits units, double velocity, vex::velocityUnits units_v) {
    for (vex::motor* motor : motors) {
        motor -> spinFor(dir, time, units, velocity, units_v);
    }
}

void AbstractMotorGroup::spinFor(double time, vex::timeUnits units) {
    for (vex::motor* motor : motors) {
        motor -> spinFor(time, units);
    }
}

void AbstractMotorGroup::spinFor(vex::directionType dir, double time, vex::timeUnits units) {
    for (vex::motor* motor : motors) {
        motor -> spinFor(dir, time, units);
    }
}

std::vector<bool> AbstractMotorGroup::isSpinning(void) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> isSpinning());
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::isDone(void) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> isDone());
    }
    return v;
}

std::vector<bool> AbstractMotorGroup::isSpinningMode(void) {
    std::vector<bool> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> isSpinningMode());
    }
    return v;
}

void AbstractMotorGroup::stop(void) {
    for (vex::motor* motor : motors) {
        motor -> stop();
    }
}

void AbstractMotorGroup::stop(vex::brakeType mode) {
    for (vex::motor* motor : motors) {
        motor -> stop(mode);
    }
}

void AbstractMotorGroup::setMaxTorque(double value, vex::percentUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setMaxTorque(value, units);
    }
}

void AbstractMotorGroup::setMaxTorque(double value, vex::torqueUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setMaxTorque(value, units);
    }
}

void AbstractMotorGroup::setMaxTorque(double value, vex::currentUnits units) {
    for (vex::motor* motor : motors) {
        motor -> setMaxTorque(value, units);
    }
}

std::vector<vex::directionType> AbstractMotorGroup::direction(void) {
    std::vector<vex::directionType> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> direction());
    }
    return v;
}

std::vector<double> AbstractMotorGroup::position(vex::rotationUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> position(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::velocity(vex::velocityUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> velocity(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::velocity(vex::percentUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> velocity(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::current(vex::currentUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> current(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::current(vex::percentUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> current(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::voltage(vex::voltageUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> voltage(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::power(vex::powerUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> power(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::torque(vex::torqueUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> torque(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::efficiency(vex::percentUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> efficiency(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::temperature(vex::percentUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> temperature(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::temperature(vex::temperatureUnits units) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> temperature(units));
    }
    return v;
}

std::vector<double> AbstractMotorGroup::convertVelocity(double velocity, vex::velocityUnits units, vex::velocityUnits unitsout) {
    std::vector<double> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> convertVelocity(velocity, units, unitsout));
    }
    return v;
}

std::vector<vex::gearSetting> AbstractMotorGroup::getMotorCartridge() {
    std::vector<vex::gearSetting> v;
    for (vex::motor* motor : motors) {
        v.push_back(motor -> getMotorCartridge());
    }
    return v;
}