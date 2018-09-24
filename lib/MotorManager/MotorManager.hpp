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
    static constexpr uint motorCount = MotorCountValue;

    //! Maximal ID length of motor
    static constexpr uint maxIDLength = MaxIDLengthValue + 1;

    //! Alias for ID data type
    using ID = Span<char, maxIDLength>;

    //! Initializes next motor
    /*!
        \param id ID of the motor
        \param pinout motor pinout

        \return true if initialized, false if all motors are initialized
    */
    bool initializeMotor(ID const& id,
                         PololuMC33926::Pinout const& pinout) {
        if (m_initializedMotors >= motorCount) return false;

        m_motors[m_initializedMotors].id = id;
        m_motors[m_initializedMotors].motor.initialize(pinout);

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
            if (strcmp(m_motors[i].id.data, id.data) == 0) {
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
            if (strcmp(m_motors[i].id.data, id.data) == 0) {
                return &(m_motors[i].motor);
            }
        }

        return nullptr;
    } 

    //! get count of initialized motors
    /*!
        \return number of initialized motors
    */
    uint initializedMotors() const { 
        return m_initializedMotors;
    }

protected:
    struct MotorIDPair {
        PololuMC33926 motor;
        ID id;
    };

    MotorIDPair m_motors[motorCount];
    uint m_initializedMotors{ 0 };
};

#endif