# Assembly Guide

## Introduction
This guide provides step-by-step instructions for assembling the water quality monitoring kit. The kit includes sensors for measuring temperature and Total Dissolved Solids (TDS) in water, a TTGO T-Beam with LoRa communication, a solar-powered battery system, and waterproof enclosures for outdoor use.

## Tools and Materials
### Tools:
- Screwdriver set (small Phillips and flat-head).
- Soldering iron (if necessary for sensor connections).
- Wire cutters and strippers.
- Multimeter (for testing connections).
- Heat shrink tubing or electrical tape.
- Hot glue gun (optional for sealing connections).

### Materials:
- **TTGO T-Beam** (ESP32 + LoRa + GPS module).
- **DS18B20 waterproof temperature sensor**.
- **TDS sensor**.
- **LiPo Battery 3.7V 1200mAh**.
- **Solar Panel 5V 2W**.
- **TP4056 LiPo solar charge module**.
- **Waterproof enclosure** (for TTGO, battery, and sensor connections).
- **LoRa antenna** (optional, but recommended for increased range).

## Steps

### 1. **Connect the Sensors to the TTGO T-Beam**
   - **DS18B20 Temperature Sensor**:
     - Connect the **VCC** (red wire) of the DS18B20 to the **3.3V** pin on the TTGO T-Beam.
     - Connect the **GND** (black wire) to the **GND** pin.
     - Connect the **DATA** (yellow wire) to **GPIO 13 (D13)** on the TTGO T-Beam.
     - Add a **4.7kΩ pull-up resistor** between the **DATA** pin and **3.3V** to ensure stable communication.

   - **TDS Sensor**:
     - Connect the **VCC** (red wire) of the TDS sensor to the **3.3V** pin on the TTGO T-Beam.
     - Connect the **GND** (black wire) to **GND**.
     - Connect the **A (Analog)** pin to **GPIO 34 (A34)** on the TTGO T-Beam.

### 2. **Set Up the Solar Power System**
   - **TP4056 LiPo Charging Module**:
     - Connect the solar panel's **positive (+)** and **negative (-)** wires to the **IN+** and **IN-** terminals on the TP4056 module.
     - Connect the LiPo battery to the **BAT+** and **BAT-** terminals on the TP4056.
     - Verify the charge status of the battery using the onboard indicator LEDs of the TP4056 module.

### 3. **Power the TTGO T-Beam with the LiPo Battery**
   - Connect the **BAT+** and **BAT-** outputs of the TP4056 module to the **3.7V battery input** on the TTGO T-Beam.
   - Ensure the TTGO T-Beam powers up correctly when the battery is connected.

### 4. **Install the LoRa Antenna**
   - Attach the **LoRa antenna** to the TTGO T-Beam using the provided SMA connector.
   - Ensure the antenna is securely fastened for maximum signal strength and range.

### 5. **Enclose Components in the Waterproof Case**
   - Place the TTGO T-Beam, battery, TP4056, and sensor connections inside the **waterproof enclosure**.
   - Drill small holes in the case to route the **sensors** and **antenna** cables outside.
   - Seal the holes with hot glue or silicone to prevent water from entering the enclosure.

### 6. **Position the Solar Panel**
   - Attach the solar panel on the outside of the enclosure or on a nearby pole or structure where it will get optimal sunlight exposure.
   - Secure the panel using brackets or adhesive tape, ensuring it remains at an angle to maximize solar absorption.

### 7. **Test the System**
   - Once the assembly is complete, power on the system and check that the **TTGO T-Beam** is receiving power from the battery and solar panel.
   - Use the serial monitor or connect via **LoRa/Meshtastic** to verify that sensor data (temperature and TDS) is being transmitted correctly.
   - Ensure the battery is charging properly when exposed to sunlight.

## Troubleshooting

### Issue 1: Sensors not reading data correctly.
   - **Solution**: Check the sensor connections, ensuring the **VCC**, **GND**, and **DATA/Analog** pins are connected correctly. Verify the pull-up resistor on the **DS18B20** is properly installed.

### Issue 2: TTGO T-Beam does not power on.
   - **Solution**: Ensure the LiPo battery is charged and properly connected to the **BAT+** and **BAT-** terminals on the TTGO. Check the solar panel's connection to the TP4056 module for proper voltage input.

### Issue 3: LoRa signal is weak or unstable.
   - **Solution**: Verify that the **LoRa antenna** is securely attached to the TTGO T-Beam. Try repositioning the antenna or installing a larger antenna for increased range.

### Issue 4: Battery not charging from the solar panel.
   - **Solution**: Ensure that the solar panel is receiving sufficient sunlight. Check the wiring from the solar panel to the **TP4056** charging module. Use a multimeter to verify voltage output from the solar panel.


