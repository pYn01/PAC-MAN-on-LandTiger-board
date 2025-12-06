# 🕹️ PAC-MAN (LandTiger Edition)

## 🎯 Project Description

This project features a faithful and complete implementation of the classic arcade video game **PAC-MAN**, developed entirely for the **LandTiger embedded development board** (based on the **NXP LPC1768** microcontroller).

The project serves as a practical demonstration of embedded programming, covering:

* **Graphics:** Initialization and management of the GLCD display.
* **Input:** Handling input via touchscreen for player control (or other implemented hardware input).
* **Game Logic:** Implementation of movement logic, collision detection, ghost Artificial Intelligence (AI), and score management.

## 🚀 Execution and Functionality

To see the project in action without needing to compile or install it, we invite you to watch the demonstration video.

**📺 Watch the Demo Video:**

The game's functionality is illustrated in the file: **[video.mp4](video.mp4)**.

*(Click the link or download the `video.mp4` file within this repository for the full demonstration.)*

## 🛠️ Hardware and Software Used

| Category | Component | Details |
| :--- | :--- | :--- |
| **Board** | LandTiger Development Board | |
| **MCU** | NXP LPC1768 | ARM Cortex-M3 Microcontroller |
| **IDE** | Keil uVision (or similar) | Embedded development environment |
| **Language** | C/C++ | |
| **Peripherals** | GLCD Display, Touchscreen | |

## ⚙️ Installation and Compilation Instructions

The project is configured for the Keil uVision development environment.

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/pYn01/PAC-MAN-on-LandTiger-board.git](https://github.com/pYn01/PAC-MAN-on-LandTiger-board.git)
    ```
2.  **Open the Project:**
    * Open Keil uVision.
    * Go to `Project` > `Open Project` and select the project file **`sample.uvprojx`** (or equivalent) inside the main folder.
3.  **Compile and Load:**
    * Compile the source code.
    * Load the binary file (`.bin` or `.hex`) onto the LandTiger board using your JTAG/SWD programmer or debugger.
