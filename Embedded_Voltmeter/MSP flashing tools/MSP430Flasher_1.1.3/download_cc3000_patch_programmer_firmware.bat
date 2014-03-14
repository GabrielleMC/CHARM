CLS
@ECHO off
ECHO Please ensure that your FRAM board is 
ECHO configured correctly and that its USB cable 
ECHO is connected.
PAUSE
@ECHO on

MSP430Flasher.exe -n MSP430FR5739 -w "../../MSP flashing tools/Binary/PatchFlasherFirmware.txt" -z [VCC] -v -g 

@ECHO off
ECHO Please wait arount 10 seconds and look above to ensure all steps were performed successfully. LED5 + LED8 of the FRAM
ECHO board should have turned on if the CC3000 EM Module is mounted.
PAUSE
@ECHO on
