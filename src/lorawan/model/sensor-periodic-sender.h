/*
 * Copyright (c) 2024 Enhanced LoRaWAN IoT Simulation
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: IoT Sensor Data Implementation for LoRaWAN NS-3 Simulation
 */

#ifndef SENSOR_PERIODIC_SENDER_H
#define SENSOR_PERIODIC_SENDER_H

#include "ns3/application.h"
#include "ns3/attribute.h"
#include "ns3/nstime.h"
#include "ns3/random-variable-stream.h"
#include "lorawan-mac.h"

namespace ns3
{
namespace lorawan
{

/**
 * @ingroup lorawan
 *
 * Sensor application that periodically sends sensor data (temperature, humidity)
 * over LoRaWAN, simulating ESP32-like IoT devices with DHT22 sensors.
 */
class SensorPeriodicSender : public Application
{
  public:
    SensorPeriodicSender();           //!< Default constructor
    ~SensorPeriodicSender() override; //!< Destructor

    /**
     *  Register this type.
     *  @return The object TypeId.
     */
    static TypeId GetTypeId();

    /**
     * Set the sending interval.
     *
     * @param interval The interval between two sensor readings/packet sends.
     */
    void SetInterval(Time interval);

    /**
     * Get the sending interval.
     *
     * @return The interval between two sensor reads.
     */
    Time GetInterval() const;

    /**
     * Set the initial delay of this application.
     *
     * @param delay The initial delay value.
     */
    void SetInitialDelay(Time delay);

    /**
     * Set device ID for sensor identification.
     *
     * @param deviceId Unique identifier for this sensor device.
     */
    void SetDeviceId(uint32_t deviceId);

    /**
     * Set temperature sensor parameters.
     *
     * @param meanTemp Mean temperature in Celsius.
     * @param tempVariance Temperature variance for realistic simulation.
     */
    void SetTemperatureParams(double meanTemp, double tempVariance);

    /**
     * Set humidity sensor parameters.
     *
     * @param meanHumidity Mean humidity percentage.
     * @param humidityVariance Humidity variance for realistic simulation.
     */
    void SetHumidityParams(double meanHumidity, double humidityVariance);

    /**
     * Send a sensor data packet with temperature and humidity readings.
     */
    void SendSensorPacket();

    /**
     * Start the application by scheduling the first SendSensorPacket event.
     */
    void StartApplication() override;

    /**
     * Stop the application.
     */
    void StopApplication() override;

  private:
    /**
     * Generate sensor data payload with temperature, humidity, device ID and timestamp.
     *
     * @return Packet containing sensor data.
     */
    Ptr<Packet> GenerateSensorData();

    Time m_interval;       //!< The interval between consecutive sensor reads.
    Time m_initialDelay;   //!< The initial delay of this application.
    EventId m_sendEvent;   //!< The sending event scheduled as next.
    Ptr<LorawanMac> m_mac; //!< The MAC layer of this node.

    // Sensor parameters
    uint32_t m_deviceId;                        //!< Device identifier
    Ptr<NormalRandomVariable> m_temperatureRV; //!< Temperature random variable
    Ptr<NormalRandomVariable> m_humidityRV;    //!< Humidity random variable
    
    // Default sensor ranges (realistic for outdoor IoT applications)
    double m_meanTemperature;     //!< Mean temperature (°C)
    double m_tempVariance;        //!< Temperature variance
    double m_meanHumidity;        //!< Mean humidity (%)
    double m_humidityVariance;    //!< Humidity variance

    uint32_t m_sequenceNumber;    //!< Packet sequence number
};

/**
 * Sensor data payload structure for LoRaWAN transmission.
 * Simulates typical IoT sensor data format.
 */
struct SensorDataPayload
{
    uint32_t deviceId;        //!< Device identifier (4 bytes)
    uint32_t sequenceNumber;  //!< Packet sequence number (4 bytes)
    uint32_t timestamp;       //!< Timestamp in seconds (4 bytes)
    int16_t temperature;      //!< Temperature in 0.1°C units (2 bytes)
    uint16_t humidity;        //!< Humidity in 0.1% units (2 bytes)
    uint16_t batteryLevel;    //!< Battery level in 0.1V units (2 bytes)
    uint8_t checksum;         //!< Simple checksum (1 byte)
    uint8_t padding;          //!< Padding for alignment (1 byte)
} __attribute__((packed));   // Total: 20 bytes

} // namespace lorawan
} // namespace ns3

#endif /* SENSOR_PERIODIC_SENDER_H */