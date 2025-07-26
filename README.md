# ESP32 Maze Generator on OLED

This project is a **random maze generator and player navigation game** developed using an **ESP32 microcontroller** and an **SSD1306 OLED display**. The maze is generated using the **Hunt and Kill algorithm**, and once generated, the player navigates from one end of the maze to the other using directional buttons.

After successfully reaching the goal, a new maze is automatically generated, creating an endless maze-solving experience.

---

## Features

- Randomly generated mazes on each run
- Maze generation using the **Hunt and Kill** algorithm
- Player block controlled via push buttons
- Goal-based movement from start to end of the maze
- Automatic regeneration of a new maze upon completion
- Manual reset using ESP32 reset button for fresh maze anytime

---

## 🛠 Hardware Used

| Component         | Details                          |
|------------------|----------------------------------|
| Microcontroller   | ESP32 DevKit v1                  |
| Display           | SSD1306 OLED (128x64, I²C)       |
| Input             | 4 Push Buttons (Up, Down, Left, Right) |
| Breadboard        | For prototyping                  |
| Jumper Wires      | For connections                  |


---

## Pin Configuration

### Button Pins
| Button   | ESP32 Pin |
|----------|------------|
| Left     | D13        |
| Right    | D12        |
| Up       | D14        |
| Down     | D27        |

### OLED Pins
| OLED Pin | ESP32 Pin |
|----------|------------|
| GND      | GND        |
| VCC      | 3.3V       |
| SCL      | D22        |
| SDA      | D21        |

---

## Algorithm Used

The maze is generated using the **Hunt and Kill algorithm**, which:
- Randomly walks through the maze path
- Hunts for unvisited neighbors
- Backtracks to generate a complete and solvable maze
- Ensures that every cell is connected and reachable
- For a clear explanation, refer to this (https://youtu.be/uctN47p_KVk?si=2ePoZfVEszk1eyhm).
---

## Libraries Used

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)

---

## Preview

![Maze Generator OLED](images/maze.jpg)

> The maze grid , with the player block visibly navigating from start to finish.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
