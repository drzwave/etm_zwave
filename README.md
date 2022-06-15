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
- J-Trace 20 pin connector pinout: ![J-Trace Pinout](./pics/jtrace-pinout.png)
    - 0.05" (1.27mm) spacing

## Software

- Simplicity Studio (for building the code)
- Segger [Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/]Debugger) (supports ETM trace)
    - SVD files for the respective EFR32 - see the SVD folder

# Step by Step Instructions

1. Clone this repo into your Z-Wave project
    1. SSv5 should automatically add the .c and .h files to the project
2. In SSv5 - right click on the project-\>properties-\>C/C++ Build-\>Settings-\>Tool Settings tab-\>GNU ARM C Compiler-\>Includes
   1. add: "${workspace\_loc:/${ProjName}/etm\_zwave}"
   2. click on Apply and Close
3. Add a call to InitTraceETM() in your code
    1. Need to figure out the best place to do this but for now put it in Main\(\)
        1. Needs to be early in the bootup so the tracing starts before you get to Main otherwise Ozone is confused
        2. Can the GPIOs and routing be setup to be stored even thru SW reset?
        3. In the short term the solution is to press reset on the WSTK board to start the code, then do a Attach and Halt in Ozone then a SW reset.
    2. Also add the following to the top of that file:
    3. #include "initETM.h"
4. Build the project in SSv5
5. Open Ozone
6. Click on the New Project wizard and select the .AXF file for the project. Ozone will find the source code files via the .axf file.
7. Click on File-\>Edit Project file (opens the .jdebug file)
8. Add the following lines in the OnProjectLoad section
    1. Project.AddSvdFile ("$(ProjectDir)/etm\_zwave/svd/EFR32XG13XFULL.svd"); 
        1. Use the .svd file that matches your DUT
        2. For the modules, just use the base-SoC part which has the same internal registers which is what the .SVD defines
    2. Project.SetOSPlugin("FreeRTOSPlugin"); 
9. Enable Tracing
    1. Tools-\>Trace Settings ![Trace Settings](./pics/TraceSettings.png)
10. 

# Scripts

A potentially much better solution is to use a jlinkscript instead of compiling the setup code into your project.
This is just getting underway but will be tested shortly.

# Reference Documents

- [Segger Wiki on xG21](https://wiki.segger.com/Silicon_Labs_EFR32xG21)

# Contacts
- Eric Ryherd - drzwave@silabs.com - Author

