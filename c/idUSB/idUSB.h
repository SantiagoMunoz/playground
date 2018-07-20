/* This function allows you to get device file (/dev/ttyUSBx) associated to the
 * USB with the input serial number. If not found, it returns null.
 * Compile with udev libraries.
 */
char* getTtyFromSerial(char* serial);
