# Smart Cold Storage System (IoT-Based)

## 📌 Overview
The **Smart Cold Storage System** is an Internet of Things (IoT)–based solution designed to monitor, regulate, and maintain optimal temperature and humidity conditions for perishable goods. The system automates cooling using sensor feedback and provides real-time local and remote monitoring through a cloud-based dashboard.

This project is implemented using an **ESP32 microcontroller**, **DHT11 temperature and humidity sensor**, and a **Peltier thermoelectric cooling module**, with IoT connectivity enabled via the **Blynk platform**.

---

## 🎯 Objectives
- Continuous monitoring of temperature and humidity
- Automatic activation of cooling when temperature exceeds a threshold
- Local alerts using buzzer and LED
- On-site display of readings using an LCD
- Remote monitoring and control through IoT
- Role-based access with Admin and Client dashboards

---

## 🧠 System Architecture
The system follows a layered architecture:

1. **Sensing Layer**
   - DHT11 sensor collects temperature and humidity data

2. **Processing Layer**
   - ESP32 processes sensor data and controls actuators

3. **Cloud & User Interface Layer**
   - Blynk IoT dashboard for real-time monitoring and control

**Data Flow:**  
DHT11 → ESP32 → Cooling & Alerts → LCD → Blynk Cloud → User Dashboards

---

## 🛠️ Hardware Components
- ESP32 Microcontroller  
- DHT11 Temperature & Humidity Sensor  
- Peltier Module (TEC1-12706)  
- DC Cooling Fan  
- Motor Driver (L298N / L293D)  
- 16×2 I2C LCD Display  
- Buzzer  
- LED  
- Breadboard and Jumper Wires  
- Dual Power Supply (5V for logic, 12V for cooling)  
- Cardboard Box (Prototype Enclosure)

---

## 💻 Software & Tools
- **Arduino IDE**
- **Blynk IoT Platform**

### Libraries Used
- `WiFi.h`
- `BlynkSimpleEsp32.h`
- `DHT.h`
- `LiquidCrystal_I2C.h`
- `Wire.h`

---

## ⚙️ Working Principle
1. The DHT11 sensor continuously measures temperature and humidity.
2. ESP32 compares the temperature with a predefined threshold.
3. If the temperature exceeds the threshold:
   - Peltier module and cooling fan turn ON
   - Buzzer and LED alert are activated
   - Alert message displayed on LCD and Blynk dashboard
4. When temperature returns to the safe range:
   - Cooling and alerts turn OFF automatically

This forms a **closed-loop automated control system**.

---

## 📱 Blynk Dashboard
### Admin Dashboard
- View live temperature and humidity
- Adjust temperature threshold
- Monitor cooling and alert status

### Client Dashboard
- Read-only access
- Live monitoring of environmental data

---

## 📊 Results
- Stable temperature regulation achieved
- Real-time cloud monitoring enabled
- Automatic alerts reduced risk of spoilage
- System proved reliable for small-scale cold storage applications

---

## 🚀 Applications
- Food and cold-chain storage
- Pharmaceutical storage
- Agricultural produce preservation
- Laboratory environments
- Educational IoT demonstrations

---

## 🔮 Future Enhancements
- Use higher-accuracy sensors (DHT22, SHT series)
- Add data logging and analytics
- Integrate AI-based predictive temperature control
- Scale for commercial cold storage
- Improve insulation and energy efficiency

---

## 👥 Team
- **M. Muralikrishnan** (22MIS1177)  
- **Sonaa Rajagopal** (22MIS1028)  

**Course:** ECE3501 – IoT Fundamentals  
**Institution:** Vellore Institute of Technology, Chennai  

---

