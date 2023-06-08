# J-Trace 19 pin to 10-pin MiniSimplicity Adapter PCB

This folder contains the KiCAD database for a small PCB that
provides a solid connection from the 19 pin 0.05" header on the
Segger J-Trace to the Silicon Labs MiniSimplicity header.

The board is plugged directly into the J-Trace without a cable.
The DUT is then typically connected with a Tag-Connect or a Minisimplcity ribbon cable.
The cable should be short - less than 1 foot. There is only a single ground pin. The data rate of the pins is 20MHz so a short cable is necessary to ensure signal integrity.

This board assumes the PTI pins are NOT wired to the MiniSimplicity header and the D1 and D2 trace pins are wired in their place.

Ordering the PCB from a proto PCB house like [OSH-Park](https://oshpark.com/) is cheap (less than $10 for 3!) and fast.

The PCB is easily hand-soldered as there are no active components. The connectors are a bit small so you do need decent soldering skills and perhaps a magnifying glass. 

# Gerbers

The JT2Mini-Gerbers.zip file contains the files for ordering the PCB from any prototype PCB manufacturer.
Some PCB houses (like OSHPark) accept the KiCAD files directly.

# Bill Of Materials (BOM)

1. J1 - 20 pin header - [CBEC224-1079B001C1AF](https://www.digikey.com/en/products/detail/greenconn/CBEC224-1079B001C1AF/16529509) - $2.34
2. J2 - 10 pin header - [3220-10-0300-00](https://www.digikey.com/en/products/detail/cnc-tech/3220-10-0300-00/3883266) - $0.78

Plus the PCB of course.

# Schematic 

See the JT2MiniSchematic.pdf for the schematic if you don't have KiCAD installed.

