**Description:**

The "Wireshark Packet IP Header Analyzer" is a C program that reads a binary file containing network packets captured using Wireshark. It analyzes the packets to check if they contain an IP header and displays the details of the IP header contents. The program determines the endianness of the system and converts the IP header fields to little endian if necessary.

**Author:** Shahriar Siddique

**Date:** 26-July-2023

**Email:** shahriar.siddique1x2@gmail.com


**How to Use:**
1. Compile the program using a C compiler.
2. Run the compiled executable with the file name of the binary packet capture (e.g., "ip_packet.bin") as a command-line argument.
3. The program will read the binary packet file, analyze it, and display the IP header details.


**Endianess Conversion:**

The program checks the endianness of the system and converts the IP header fields to little endian if the system follows little endian byte order. This ensures consistent interpretation of multi-byte data in the IP header.


**Output:**


The program displays the following IP header details:

* IP version
* Internet Header Length (IHL)
* Type of Service (TOS)
* Total Length
* Identification
* Flags
* Fragment Offset
* Time To Live (TTL)
* Protocol
* Header Checksum
* Source IP Address
* Destination IP Address



**Endianess Information:**

The program determines whether the system follows little endian or big endian byte order and prints the appropriate message.

**Note:**

Ensure you have the required permissions to read the binary packet file. The program is designed to work with binary files generated using Wireshark packet capture.

**Cleanup:**

The program frees the memory allocated for reading the binary file.

**Important:**

* This program is provided as-is and may not be suitable for all use cases. It is intended for educational purposes only.
* Use this program responsibly and only on files you have permission to access.
* The author is not responsible for any misuse or damages caused by using this program.
