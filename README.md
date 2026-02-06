# Project README: STM32-based ISO7816 IC Card Reader
## Project Overview
This project implements an ISO7816-compliant IC card reader using STM32F103, enabling communication with contactless IC cards via UART interface. The core logic for card reset, ATR (Answer To Reset) and APDU (Application Protocol Data Unit) interaction has been fully validated through simulation.

---

## Current Progress
✅ **Core Logic Verified**: The reset command and APDU interaction workflows have been thoroughly tested in a simulated environment, with complete and stable logs generated.
✅ **Technical Design Confirmed**: The solution leverages STM32's native UART to handle ISO7816 protocol communication, paired with a TTL-level reader module for physical card interface.

---

## Next Steps
1. **Hardware Integration**: The system requires a TTL IC card reader module (integrating level conversion and card power supply circuits) to connect with the STM32 hardware. A standalone card socket is insufficient for stable card reading.
2. **Physical Testing**: Once the hardware module is available, we will conduct end-to-end testing with real IC cards to validate the full workflow.

---

## Dependencies
- **Required Hardware**: TTL-based ISO7816 IC card reader module (e.g., models supporting 4442 CPU cards)
- **Host Controller**: STM32F103 microcontroller (with UART interface)

---

## Collaboration Notes
As a contractor, I am unable to advance funds for hardware procurement at this stage. To keep the project on track, please either:
1. Provide the TTL reader module directly, or
2. Allocate procurement funds so I can source the necessary hardware promptly.

Once the hardware is in place, I will complete the integration and testing phase within 2–3 business days.

---

