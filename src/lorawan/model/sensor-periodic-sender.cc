/*
 * Copyright (c) 2024 Enhanced LoRaWAN IoT Simulation
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: IoT Sensor Data Implementation for LoRaWAN NS-3 Simulation
 */

#include "sensor-periodic-sender.h"
#include "lora-net-device.h"

#include "ns3/double.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/string.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"

namespace ns3
{
namespace lorawan
{

NS_LOG_COMPONENT_DEFINE("SensorPeriodicSender");

NS_OBJECT_ENSURE_REGISTERED(SensorPeriodicSender);

TypeId
SensorPeriodicSender::GetTypeId()
{
    static TypeId tid = TypeId("ns3::SensorPeriodicSender")
                            .SetParent<Application>()
                            .AddConstructor<SensorPeriodicSender>()
                            .SetGroupName("lorawan")
                            .AddAttribute("Interval",
                                          "The interval between sensor readings",
                                          TimeValue(Time(0)),
                                          MakeTimeAccessor(&SensorPeriodicSender::GetInterval,
                                                           &SensorPeriodicSender::SetInterval),
                                          MakeTimeChecker())
                            .AddAttribute("DeviceId",
                                          "The unique identifier for this sensor device",
                                          UintegerValue(0),
                                          MakeUintegerAccessor(&SensorPeriodicSender::m_deviceId),
                                          MakeUintegerChecker<uint32_t>())
                            .AddAttribute("MeanTemperature",
                                          "Mean temperature in Celsius for sensor simulation",
                                          DoubleValue(22.0),
                                          MakeDoubleAccessor(&SensorPeriodicSender::m_meanTemperature),
                                          MakeDoubleChecker<double>())
                            .AddAttribute("TemperatureVariance",
                                          "Temperature variance for realistic simulation",
                                          DoubleValue(5.0),
                                          MakeDoubleAccessor(&SensorPeriodicSender::m_tempVariance),
                                          MakeDoubleChecker<double>())
                            .AddAttribute("MeanHumidity",
                                          "Mean humidity percentage for sensor simulation",
                                          DoubleValue(60.0),
                                          MakeDoubleAccessor(&SensorPeriodicSender::m_meanHumidity),
                                          MakeDoubleChecker<double>())
                            .AddAttribute("HumidityVariance",
                                          "Humidity variance for realistic simulation",
                                          DoubleValue(15.0),
                                          MakeDoubleAccessor(&SensorPeriodicSender::m_humidityVariance),
                                          MakeDoubleChecker<double>());
    return tid;
}

SensorPeriodicSender::SensorPeriodicSender()
    : m_interval(Seconds(300)),     // Default: 5 minutes (typical for IoT sensors)
      m_initialDelay(Seconds(1)),
      m_deviceId(0),
      m_meanTemperature(22.0),      // 22°C
      m_tempVariance(5.0),          // ±5°C variance
      m_meanHumidity(60.0),         // 60% RH
      m_humidityVariance(15.0),     // ±15% variance
      m_sequenceNumber(0)
{
    NS_LOG_FUNCTION_NOARGS();
}

SensorPeriodicSender::~SensorPeriodicSender()
{
    NS_LOG_FUNCTION_NOARGS();
}

void
SensorPeriodicSender::SetInterval(Time interval)
{
    NS_LOG_FUNCTION(this << interval);
    m_interval = interval;
}

Time
SensorPeriodicSender::GetInterval() const
{
    NS_LOG_FUNCTION(this);
    return m_interval;
}

void
SensorPeriodicSender::SetInitialDelay(Time delay)
{
    NS_LOG_FUNCTION(this << delay);
    m_initialDelay = delay;
}

void
SensorPeriodicSender::SetDeviceId(uint32_t deviceId)
{
    NS_LOG_FUNCTION(this << deviceId);
    m_deviceId = deviceId;
}

void
SensorPeriodicSender::SetTemperatureParams(double meanTemp, double tempVariance)
{
    NS_LOG_FUNCTION(this << meanTemp << tempVariance);
    m_meanTemperature = meanTemp;
    m_tempVariance = tempVariance;
}

void
SensorPeriodicSender::SetHumidityParams(double meanHumidity, double humidityVariance)
{
    NS_LOG_FUNCTION(this << meanHumidity << humidityVariance);
    m_meanHumidity = meanHumidity;
    m_humidityVariance = humidityVariance;
}

Ptr<Packet>
SensorPeriodicSender::GenerateSensorData()
{
    NS_LOG_FUNCTION(this);

    // Initialize random variables if not done yet
    if (!m_temperatureRV)
    {
        m_temperatureRV = CreateObject<NormalRandomVariable>();
        m_temperatureRV->SetAttribute("Mean", DoubleValue(m_meanTemperature));
        m_temperatureRV->SetAttribute("Variance", DoubleValue(m_tempVariance));
    }

    if (!m_humidityRV)
    {
        m_humidityRV = CreateObject<NormalRandomVariable>();
        m_humidityRV->SetAttribute("Mean", DoubleValue(m_meanHumidity));
        m_humidityRV->SetAttribute("Variance", DoubleValue(m_humidityVariance));
    }

    // Generate sensor readings
    double temperature = m_temperatureRV->GetValue();
    double humidity = m_humidityRV->GetValue();

    // Clamp humidity to realistic range (0-100%)
    humidity = std::max(0.0, std::min(100.0, humidity));

    // Simulate battery degradation over time (starts at 3.7V, slowly decreases)
    double batteryVoltage = 3.7 - (Simulator::Now().GetSeconds() / 86400.0) * 0.001; // Decrease 1mV per day
    batteryVoltage = std::max(3.0, batteryVoltage); // Minimum 3.0V

    // Create payload structure
    SensorDataPayload payload;
    payload.deviceId = m_deviceId;
    payload.sequenceNumber = m_sequenceNumber++;
    payload.timestamp = static_cast<uint32_t>(Simulator::Now().GetSeconds());
    payload.temperature = static_cast<int16_t>(temperature * 10); // 0.1°C precision
    payload.humidity = static_cast<uint16_t>(humidity * 10);      // 0.1% precision
    payload.batteryLevel = static_cast<uint16_t>(batteryVoltage * 10); // 0.1V precision
    
    // Simple checksum calculation
    payload.checksum = static_cast<uint8_t>(
        (payload.deviceId ^ payload.sequenceNumber ^ payload.timestamp ^ 
         payload.temperature ^ payload.humidity ^ payload.batteryLevel) & 0xFF);
    payload.padding = 0;

    // Create packet with sensor data
    Ptr<Packet> packet = Create<Packet>(reinterpret_cast<const uint8_t*>(&payload), sizeof(payload));

    NS_LOG_INFO("Sensor " << m_deviceId << " generated data: Temp=" << temperature 
                << "°C, Humidity=" << humidity << "%, Battery=" << batteryVoltage 
                << "V, Seq=" << (payload.sequenceNumber - 1));

    return packet;
}

void
SensorPeriodicSender::SendSensorPacket()
{
    NS_LOG_FUNCTION(this);

    // Generate sensor data packet
    Ptr<Packet> packet = GenerateSensorData();
    
    // Send packet via LoRaWAN MAC
    m_mac->Send(packet);

    // Schedule the next sensor reading
    m_sendEvent = Simulator::Schedule(m_interval, &SensorPeriodicSender::SendSensorPacket, this);

    NS_LOG_DEBUG("Sent sensor packet of size " << packet->GetSize() << " bytes from device " << m_deviceId);
}

void
SensorPeriodicSender::StartApplication()
{
    NS_LOG_FUNCTION(this);

    // Make sure we have a MAC layer
    if (!m_mac)
    {
        // Assumes there's only one device
        Ptr<LoraNetDevice> loraNetDevice = DynamicCast<LoraNetDevice>(m_node->GetDevice(0));
        m_mac = loraNetDevice->GetMac();
        NS_ASSERT(m_mac);
    }

    // Set device ID based on node ID if not explicitly set
    if (m_deviceId == 0)
    {
        m_deviceId = m_node->GetId() + 1000; // Offset to avoid conflicts
    }

    // Schedule the first sensor reading
    Simulator::Cancel(m_sendEvent);
    NS_LOG_DEBUG("Starting sensor application for device " << m_deviceId 
                 << " with " << m_initialDelay.As(Time::S) << " initial delay");
    m_sendEvent = Simulator::Schedule(m_initialDelay, &SensorPeriodicSender::SendSensorPacket, this);
    NS_LOG_DEBUG("Event Id: " << m_sendEvent.GetUid());
}

void
SensorPeriodicSender::StopApplication()
{
    NS_LOG_FUNCTION_NOARGS();
    Simulator::Cancel(m_sendEvent);
}

} // namespace lorawan
} // namespace ns3