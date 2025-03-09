## Fish Weight Measurement System with MQTT, NFC, Scale Sensor, and Linear Actuator

This project involves a **digital scale** designed for accurately measuring the weight of fish, integrated with advanced technologies such as **MQTT**, **NFC**, a **scale sensor**, and a **linear actuator**. The system is built to automate the process of weighing fish and trigger an action based on the measured weight.

### Key Features:

1. **Scale Sensor**: The system uses a **high-precision scale sensor** to measure the weight of fish placed on the scale. The sensor provides accurate readings, which are then processed to determine the exact weight of the fish.

2. **MQTT Protocol**: The system employs the **MQTT protocol** for efficient and real-time communication. The weight data is transmitted through MQTT to a central server or monitoring device, allowing for quick updates and interaction with the system.

3. **NFC (Near Field Communication)**: An **NFC reader** is integrated to allow for user identification and interaction. Users can scan an NFC-enabled card or device to authenticate their identity, which helps track the fish weights and manage data securely.

4. **Linear Actuator**: The **linear actuator** is used to automate the opening of a gate based on the weight measurement. For example, when the fish weight exceeds a certain threshold, the actuator can trigger the opening of a gate, allowing the fish to be transferred automatically or placed into a separate area.

### System Overview:

- **MQTT Broker**: The MQTT broker facilitates communication between devices in the system. Weight measurements and actuator commands are sent to the broker and then relayed to connected devices.
  
- **Scale Sensor**: This is the core component for measuring the weight of the fish. The sensor accurately detects the weight, which is transmitted to the central system for further processing.

- **NFC Reader**: NFC is used for user authentication, enabling secure access and interaction with the system. Each NFC card or device is associated with specific user data to personalize the system's behavior.

- **Linear Actuator**: The actuator is used to open a gate or door based on the weight of the fish. For instance, the actuator can be programmed to open the gate if the fish exceeds a certain weight, allowing for seamless automation in environments like fish farming, seafood processing, or commercial fisheries.

### Application Use Cases:

- **Automated Fish Weight Measurement**: This system provides an automated way to weigh fish, eliminating the need for manual weighing and ensuring accurate measurements. It’s perfect for environments where fish weight needs to be monitored regularly.

- **Smart Sorting and Processing**: Based on the weight data, the system can automatically trigger actions like opening a gate to transfer fish, enabling a more efficient and streamlined sorting or processing workflow.

- **User Authentication and Tracking**: The NFC system adds an extra layer of security and personalization, allowing users to log in to track their fish weight measurements and even access historical data.

- **Automation in Fish Farms**: The combination of the scale, actuator, and MQTT allows for automated operations in fish farms or seafood facilities, reducing the need for manual handling and increasing overall efficiency.


