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
- Connect the DUT to the J-Trace and ensure the Target Power is green
    - Note that the 20 pin debug cable should be as short as possible - ideally just 2-3"
    - If you get LTRACE invalid frame errors on the trace, the signal quality across the ribbon cable is probably not good.
    - Try lowering the clock speed, adjusting the timing in JTrace and that all ground pins are connected.

## JT2Mini Adapter

- See the [Adapter](./adapter/ReadMe.md) folder for the J-Trace to MiniSimplicity adapter.

## Software

- Simplicity Studio (for building the code)
- Segger [Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/]Debugger) (supports ETM trace)
    - SVD files for the respective EFR32 - see the SVD folder
- This repo contains JLink scripts and other files needed for tracing

# Step by Step Instructions

1. Clone this repo into your Z-Wave project
2. Build the project in SSv5
3. Open Ozone
4. Click on the New Project wizard and select the .AXF file for the project. Ozone will find the source code files via the .axf file.
5. Click on File-\>Edit Project file (opens the .jdebug file)
6. Add the following lines to the end of the OnProjectLoad section
    1. Project.SetOSPlugin("FreeRTOSPlugin\_ARM"); 
    1. For xG13 projects:
        1. Project.AddSvdFile ("$(ProjectDir)/etm\_zwave/svd/EFR32XG13XFULL.svd"); 
    1. For xG14 projects:
        1. Project.AddSvdFile ("$(ProjectDir)/etm\_zwave/svd/EFR32XG14XFULL.svd"); 
    1. For xG23 projects:
        1. Project.AddSvdFile ("$(ProjectDir)/etm\_zwave/svd/EFR32XG23A000F512GM40\_SEQ\_M33.svd"); 
    2. For modules (ZGM130,ZGM230), just use the base-SoC part which has the same internal registers which is what the .SVD defines
7. Scroll down to the BeforeTargetConnect section
    1. uncomment the call and the }
    2. Add ONE of the following lines that matches your Z-Wave chip :
        1. Project.SetJLinkScript("$(ProjectDir)/etm_zwave/ZGM130S_Traceconfig.JLinkScript"); 
        1. Project.SetJLinkScript("$(ProjectDir)/etm_zwave/ZG23_Traceconfig.JLinkScript"); 
8. Enable Tracing
    1. Tools-\>Trace Settings ![Trace Settings](./pics/TraceSettings.png)
    2. Trace Source is Trace Pins
    3. CPU Frequency is 39MHz
    4. Trace Port Width is ideally 4 but if you have limited pinout, 2 or even 1 will work but will stall the CPU potentially altering the program flow
    5. Increase the Maximum Instruction Count to at least 100M
    6. Trace Timing should be default - the script alters the slew rate of the GPIOs which should be sufficient with a short cable
9. Click on View -\> Instruction Trace, Code Profile, Timeline and any other windows desired
10. Click on Download and Reset Program  
11. Review the console window and look for any errors
12. The DUT should stop at the beginning of Main() and there is data in the Timeline

# Software Project Recommendations

- Do not use -flto optimization when debugging. Link Time Optimization (LTO) mashes the code making Ozone unable to match the PC with the C source code.
- Recommend installing Z-Wave DEBUG in the SLC - This will set the -Og optimzation option which will make the code much easier to trace and debug but requires more FLASH.
    - In Simplicity Studio, click on the .slcp file for your project, then Software Components, then scroll down (or search) for Z-Wave Debug and click on it, then install it. Do NOT ship production code with Z-Wave Debug installed! Uninstall it for the final production release.
    - May also want to install Z-Wave Debug Print and uncomment the #define DEBUGPRINT in app.c. This also requires IO Stream and a UART. This enables print statements to help with debugging. The print statements are sent out the uart and are visible on the SSv5 console window.

# TroubleShooting

- Ozone will give all sorts of different errors that most often are caused by Signal Integrity issues
    - LTRACE (Time since start: 0.139 656, Thread=ETM1): Unknown trace data packet detected
    - No trace clock present, trace may not work correctly.
    - LTRACE (Time since start: 0.074 546, Thread=ETM1): Trace overflow detected. Trace packets may have been lost.
    - General flakeyness where restarting Ozone yields different errors or works sometimes but not all the time
- Signal Integrity of TRACECLK and TRACEDATA
    - Use short cables (less than 6")
    - Connect EVERY ground pin on the 20-pin header to the DUT if possible or add additional GND wires
    - View the TRACECLK and TRACEDATA pins on a good scope with good grounds
        - Adjust the slew rate of the EFR GPIO port to try to make the signals cleaner or sharper (See the .JLinkScript file for an example)
    - Adjust the timing in the J-Trace - Ozone - Trace Settings - Trace Timing
        - If the cable is short, the trace timing timing should not need to be adjusted as the EFR provides good setup/hold

# Reference Documents

- [Segger Wiki on xG21](https://wiki.segger.com/Silicon_Labs_EFR32xG21)
- [Segger Wiki on xG23](https://wiki.segger.com/Silicon_Labs_EFR32xG23)

# Contacts - Eric Ryherd - Author

- File an Issue to report a problem or make a suggestion.

