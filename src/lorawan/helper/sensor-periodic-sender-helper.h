/*
 * Copyright (c) 2024 Enhanced LoRaWAN IoT Simulation
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: IoT Sensor Data Implementation for LoRaWAN NS-3 Simulation
 */

#ifndef SENSOR_PERIODIC_SENDER_HELPER_H
#define SENSOR_PERIODIC_SENDER_HELPER_H

#include "ns3/address.h"
#include "ns3/application-container.h"
#include "ns3/attribute.h"
#include "ns3/net-device.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include "ns3/sensor-periodic-sender.h"

#include <stdint.h>
#include <string>

namespace ns3
{
namespace lorawan
{

/**
 * @ingroup lorawan
 *
 * This class can be used to install SensorPeriodicSender applications on multiple nodes,
 * simulating ESP32-like IoT devices with temperature and humidity sensors.
 */
class SensorPeriodicSenderHelper
{
  public:
    SensorPeriodicSenderHelper();  //!< Default constructor
    ~SensorPeriodicSenderHelper(); //!< Destructor

    /**
     * Helper function used to set the underlying application attributes.
     *
     * @param name The name of the application attribute to set.
     * @param value The value of the application attribute to set.
     */
    void SetAttribute(std::string name, const AttributeValue& value);

    /**
     * Install a SensorPeriodicSender application on each node of the input container
     * configured with all the attributes set with SetAttribute or other functions of this class.
     *
     * @param c NodeContainer of the set of nodes on which a SensorPeriodicSender will be installed.
     * @return Container of Ptr to the applications installed.
     */
    ApplicationContainer Install(NodeContainer c) const;

    /**
     * Install a SensorPeriodicSender application on the input Node configured with all the 
     * attributes set with SetAttribute or other functions of this class.
     *
     * @param node The node on which a SensorPeriodicSender will be installed.
     * @return Container of the Ptr to the application installed.
     */
    ApplicationContainer Install(Ptr<Node> node) const;

    /**
     * Set the period to be used by the sensor applications created by this helper.
     *
     * @param period The period between sensor readings.
     */
    void SetPeriod(Time period);

    /**
     * Set temperature parameters for all sensor devices.
     *
     * @param meanTemp Mean temperature in Celsius.
     * @param variance Temperature variance for realistic simulation.
     */
    void SetTemperatureParams(double meanTemp, double variance);

    /**
     * Set humidity parameters for all sensor devices.
     *
     * @param meanHumidity Mean humidity percentage.
     * @param variance Humidity variance for realistic simulation.
     */
    void SetHumidityParams(double meanHumidity, double variance);

    /**
     * Configure sensors for different environment types.
     *
     * @param envType Environment type: "urban", "rural", "indoor", "greenhouse", "cold", "hot"
     */
    void SetEnvironmentType(std::string envType);

  private:
    /**
     * Install a SensorPeriodicSender application on the input Node configured with all the 
     * attributes set with SetAttribute or other functions of this class.
     *
     * @param node The node on which a SensorPeriodicSender will be installed.
     * @return A pointer to the application installed.
     */
    Ptr<Application> InstallPriv(Ptr<Node> node) const;

    ObjectFactory m_factory;                    //!< The factory to create SensorPeriodicSender applications
    Ptr<UniformRandomVariable> m_initialDelay; //!< Random variable for start delay
    Time m_period;                              //!< The period between sensor readings
    
    // Environmental parameters
    double m_meanTemperature;    //!< Mean temperature for all sensors
    double m_tempVariance;       //!< Temperature variance
    double m_meanHumidity;       //!< Mean humidity for all sensors  
    double m_humidityVariance;   //!< Humidity variance
};

} // namespace lorawan
} // namespace ns3

#endif /* SENSOR_PERIODIC_SENDER_HELPER_H */