
# Bill of Materials (BOM) for River Monitoring System

## 1. Components for Monitor

| Component                     | Description                                                                                                                    | Quantity | Price (Approx.) | Purchase Link |
|-------------------------------|--------------------------------------------------------------------------------------------------------------------------------|----------|-----------------|---------------|
| **TTGO T-Beam**                | ESP32 module with LoRa (SX1276) and GPS integrated. Ideal for Meshtastic networks.                                             | 1        | $20 - $25       | [AliExpress](https://www.aliexpress.com/) / [Amazon](https://www.amazon.com/) |
| **DS18B20 Temperature Sensor** | Waterproof temperature sensor (compatible with TTGO T-Beam). Used for monitoring water temperature.                            | 1        | $2 - $3         | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **TDS Sensor**                 | Sensor to measure water quality (Total Dissolved Solids).                                                                      | 1        | $8 - $12        | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **LiPo Battery 3.7V 1200mAh**  | 3.7V rechargeable battery. Powers the TTGO T-Beam and sensors.                                                                 | 1        | $5 - $10        | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **Solar Panel 5V 2W**          | 5V 2W solar panel to charge the LiPo battery.                                                                                 | 1        | $10 - $15       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **TP4056 Solar Charge Module**  | Charging module for LiPo batteries, with overcharge and discharge protection. Connects to the solar panel to maintain battery. | 1        | $1 - $3         | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **Waterproof Enclosure**       | Waterproof enclosure to protect the TTGO, battery, and sensors in outdoor environments.                                        | 1        | $5 - $10        | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **LoRa Antenna**               | External antenna to improve LoRa range in remote areas.                                                                        | 1        | $5 - $10        | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |

## 2. Components for LoRaWAN Gateway

| Component                       | Description                                                                                                                  | Quantity | Price (Approx.) | Purchase Link |
|----------------------------------|------------------------------------------------------------------------------------------------------------------------------|----------|-----------------|---------------|
| **LoRaWAN Gateway**              | LoRaWAN gateway with the ability to send and receive data from LoRa devices to the Internet (Wi-Fi/Ethernet/4G).             | 1        | $100 - $300     | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **High Gain LoRa Antenna**       | High gain external antenna to improve the gateway’s range in rural areas.                                                    | 1        | $20 - $40       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **Power Supply**                 | Power supply for the gateway, typically 5V or 12V depending on the model.                                                    | 1        | $10 - $15       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **Waterproof Enclosure for Gateway** | Waterproof enclosure to protect the gateway in outdoor environments.                                                         | 1        | $15 - $30       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **Solar Panel 10W**              | 10W solar panel to power the LoRaWAN Gateway in locations without electrical access, combined with a charge controller.      | 1        | $25 - $40       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **LiPo Battery 7.4V 6000mAh**    | Higher capacity battery to power the LoRaWAN Gateway during both day and night.                                               | 1        | $25 - $40       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |
| **MPPT Solar Charge Controller** | Solar charge controller to optimize battery charging from solar panels in the gateway setup.                                  | 1        | $10 - $20       | [Amazon](https://www.amazon.com/) / [AliExpress](https://www.aliexpress.com/) |

## Notes
1. **Solar Panels**: The size of the solar panel will depend on the consumption of each component and the hours of sun in the specific location.
2. **Antennas**: The choice of antenna is key to maximizing coverage. You can opt for directional antennas if the monitors are aligned along the river.
