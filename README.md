ic22ch-0.99
=============

Calculator for diode vs frequency maps for Icom IC-22S 2M Transceiver.

This application will take a diode map from a file called diodes.txt and 
it will then calculate the frequency represented by this value and print
the channel number and frequency (in KHz) to the output file called freqs.txt.

The diode map should be of the form "1:00000000" where '1:' is the channel 
position and '00000000' is the PLL Divider N value based on the presence or 
absence of diodes on the diode matrix board. 



