#ifndef MOTORMANAGER_HPP
#define MOTORMANAGER_HPP
#include <Globals.hpp>
#include <Span.hpp>
#include <PololuMC33926.hpp>
#include <string.h>

//! Class for managing multiple motors by their ID's
template <uint MotorCountValue, uint MaxIDLengthValue>
class MotorManager {
public:
    //! Number of motors managed by object
    static constexpr uint MotorCount = MotorCountValue;

    //! Maximal ID length of motor
    static constexpr uint MaxIDLength = MaxIDLengthValue + 1;

    //! Alias for ID data type
    using ID = Span<char, MaxIDLength>;

    //! Initializes next motor
    /*!
        \param id ID of the motor
        \param pinout motor pinout

        \return true if initialized, false if all motors are initialized or motor initialization has failed
    */
    bool initializeMotor(ID const& id,
                         PololuMC33926::Pinout const& pinout) {
        if (m_initializedMotors >= MotorCount) return false;

        m_motors[m_initializedMotors].id = id;
        if (!m_motors[m_initializedMotors].motor.initialize(pinout)) {
            return false;
        }

        m_initializedMotors++;
        return true;
    } 

    //! map-like access to motor by it's ID
    /*!
        note: this will perform linear search, this is not a map!

        \param id motor id
        \return a pointer to motor, or nullptr if no motor was found
    */
    PololuMC33926* operator[](ID const& id) {
        for(uint i = 0; i < m_initializedMotors; i++) {
            if (strcmp(m_motors[i].id, id) == 0) {
                return &(m_motors[i].motor);
            }
        }

        return nullptr;
    } 

    //! map-like constant access to motor by it's ID
    /*!
        note: this will perform linear search, this is not a map!

        \param id motor id
        \return a pointer to motor, or nullptr if no motor was found
    */
    PololuMC33926 const* operator[](ID const& id) const {
        for(uint i = 0; i < m_initializedMotors; i++) {
            if (strcmp(m_motors[i].id, id) == 0) {
                return &(m_motors[i].motor);
            }
        }

        return nullptr;
    } 

protected:
    struct MotorIDPair {
        PololuMC33926 motor;
        ID id;
    };

    MotorIDPair m_motors[MotorCount];
    uint m_initializedMotors{ 0 };
};

#endif