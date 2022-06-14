# etm\_zwave
Z-Wave Embedded Trace Module (ETM) debugging example code

The ETM is an invaluable tool for debugging embedded code and measuring code coverage in real-time.
More details on ETM can be found on the [ARM](https://developer.arm.com/documentation/ddi0337/h/embedded-trace-macrocell/about-the-etm) and [Segger](https://www.segger.com/) web sites.

The example code here is provided AS-IS and without warrantee.

# Setup

## Hardware

- Z-Wave Developers Kit - WSTK and a Radio board
    - Or your board assuming it has the JTrace pins
- [Segger J-Trace Pro](https://www.segger.com/products/debug-probes/j-trace/)
    - The Cortex-M model is sufficient for Z-Wave debug (the cheaper one)
    - Cables and power source
- J-Trace 20 pin connector pinout: (./pics/jtrace-pinout.png "J-Trace Pinout")

## Software

- Simplicity Studio (for building the code)
- Segger [Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/]Debugger) (supports ETM trace)
    - SVD files for the respective EFR32 - see the SVD folder

# Step by Step Instructions

1. Clone this repo into your Z-Wave project
2. in SSv5 - right click on the project-\>properties-\>C/C++ Build-\>Settings-\>Tool Settings tab-\>GNU ARM C Compiler-\>Includes
   1. add: "${workspace\_loc:/${ProjName}/etm\_zwave}"
   2. click on Apply and Close
3. Add a call to InitTraceETM() in your code
    1. Need to figure out the best place to do this but for now put it in Main\(\)
    2. Also add the following to the top of that file:
    3. #include "initETM.h"
4. Build the project

# Contacts
- Eric Ryherd - drzwave@silabs.com - Author

