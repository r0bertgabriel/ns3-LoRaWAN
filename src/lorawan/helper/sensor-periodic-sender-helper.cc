/*
 * Copyright (c) 2024 Enhanced LoRaWAN IoT Simulation
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: IoT Sensor Data Implementation for LoRaWAN NS-3 Simulation
 */

#include "sensor-periodic-sender-helper.h"

#include "ns3/double.h"
#include "ns3/log.h"
#include "ns3/random-variable-stream.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/sensor-periodic-sender.h"

namespace ns3
{
namespace lorawan
{

NS_LOG_COMPONENT_DEFINE("SensorPeriodicSenderHelper");

SensorPeriodicSenderHelper::SensorPeriodicSenderHelper()
    : m_period(Seconds(300)),      // Default: 5 minutes
      m_meanTemperature(22.0),     // 22°C
      m_tempVariance(5.0),         // ±5°C
      m_meanHumidity(60.0),        // 60% RH
      m_humidityVariance(15.0)     // ±15%
{
    m_factory.SetTypeId("ns3::SensorPeriodicSender");

    // Initialize random delay for sensor startup (avoid synchronized transmissions)
    m_initialDelay = CreateObject<UniformRandomVariable>();
    m_initialDelay->SetAttribute("Min", DoubleValue(0));
    m_initialDelay->SetAttribute("Max", DoubleValue(60)); // Up to 1 minute random delay
}

SensorPeriodicSenderHelper::~SensorPeriodicSenderHelper()
{
}

void
SensorPeriodicSenderHelper::SetAttribute(std::string name, const AttributeValue& value)
{
    m_factory.Set(name, value);
}

ApplicationContainer
SensorPeriodicSenderHelper::Install(Ptr<Node> node) const
{
    return ApplicationContainer(InstallPriv(node));
}

ApplicationContainer
SensorPeriodicSenderHelper::Install(NodeContainer c) const
{
    ApplicationContainer apps;
    for (auto i = c.Begin(); i != c.End(); ++i)
    {
        apps.Add(InstallPriv(*i));
    }
    return apps;
}

Ptr<Application>
SensorPeriodicSenderHelper::InstallPriv(Ptr<Node> node) const
{
    NS_LOG_FUNCTION(this << node);

    Ptr<SensorPeriodicSender> app = m_factory.Create<SensorPeriodicSender>();

    // Set sensor reading interval
    app->SetInterval(m_period);
    NS_LOG_DEBUG("Created sensor application with interval = " << m_period.As(Time::S));

    // Set random initial delay to avoid synchronization
    Time delay = Seconds(m_initialDelay->GetValue());
    app->SetInitialDelay(delay);

    // Set device ID based on node ID
    app->SetDeviceId(node->GetId() + 1000); // Offset to distinguish from other IDs

    // Set environmental parameters
    app->SetTemperatureParams(m_meanTemperature, m_tempVariance);
    app->SetHumidityParams(m_meanHumidity, m_humidityVariance);

    app->SetNode(node);
    node->AddApplication(app);

    NS_LOG_INFO("Installed sensor application on node " << node->GetId() 
                << " with device ID " << (node->GetId() + 1000)
                << ", temp: " << m_meanTemperature << "±" << m_tempVariance << "°C"
                << ", humidity: " << m_meanHumidity << "±" << m_humidityVariance << "%");

    return app;
}

void
SensorPeriodicSenderHelper::SetPeriod(Time period)
{
    m_period = period;
}

void
SensorPeriodicSenderHelper::SetTemperatureParams(double meanTemp, double variance)
{
    m_meanTemperature = meanTemp;
    m_tempVariance = variance;
}

void
SensorPeriodicSenderHelper::SetHumidityParams(double meanHumidity, double variance)
{
    m_meanHumidity = meanHumidity;
    m_humidityVariance = variance;
}

void
SensorPeriodicSenderHelper::SetEnvironmentType(std::string envType)
{
    NS_LOG_FUNCTION(this << envType);
    
    if (envType == "urban")
    {
        // Urban environment: higher temperature due to heat islands, moderate humidity
        SetTemperatureParams(25.0, 8.0);  // 25°C ± 8°C
        SetHumidityParams(55.0, 20.0);    // 55% ± 20%
    }
    else if (envType == "rural")
    {
        // Rural environment: more natural temperature variation, higher humidity
        SetTemperatureParams(20.0, 12.0); // 20°C ± 12°C
        SetHumidityParams(70.0, 15.0);    // 70% ± 15%
    }
    else if (envType == "indoor")
    {
        // Indoor environment: controlled temperature, lower humidity
        SetTemperatureParams(22.0, 3.0);  // 22°C ± 3°C
        SetHumidityParams(45.0, 10.0);    // 45% ± 10%
    }
    else if (envType == "greenhouse")
    {
        // Greenhouse: warm and humid
        SetTemperatureParams(28.0, 5.0);  // 28°C ± 5°C
        SetHumidityParams(80.0, 10.0);    // 80% ± 10%
    }
    else if (envType == "cold")
    {
        // Cold climate
        SetTemperatureParams(5.0, 15.0);  // 5°C ± 15°C
        SetHumidityParams(60.0, 25.0);    // 60% ± 25%
    }
    else if (envType == "hot")
    {
        // Hot climate
        SetTemperatureParams(35.0, 10.0); // 35°C ± 10°C
        SetHumidityParams(40.0, 20.0);    // 40% ± 20%
    }
    else
    {
        NS_LOG_WARN("Unknown environment type: " << envType << ". Using default parameters.");
        // Use default parameters already set in constructor
    }

    NS_LOG_INFO("Environment type set to '" << envType 
                << "': Temp=" << m_meanTemperature << "±" << m_tempVariance 
                << "°C, Humidity=" << m_meanHumidity << "±" << m_humidityVariance << "%");
}

} // namespace lorawan
} // namespace ns3