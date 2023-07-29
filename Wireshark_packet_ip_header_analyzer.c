/*************************************************************************************************************************/
/*                                                                                                                       */
/*  Name: Wireshark packet Ip header Analyzer                                                                            */
/*                                                                                                                       */
/*  Description: Read Wireshark packet file and check if ip header availabe. Show all Details of ip header contain.      */
/*                                                                                                                       */
/*  Author: Shahriar Siddique                                                                                            */
/*                                                                                                                       */
/*  Date:  26-July-2023                                                                                                  */
/*                                                                                                                       */                                                                                                                      *//*                                                                                                                       *//*                                                                                                                       *//*                                                                                                                       */
/*  Email: shahriar.siddique1x2@gmail.com                                                                                */
/*                                                                                                                       */
/*************************************************************************************************************************/


#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>

#define u_swap_3_5(x) (x<<3 | x>>5)
#define u_swap8(x) ( x<<4 | x>>4)
#define u_swap16(x) (x<<8 | x >> 8)
#define u_swap32(x) (x>>24 | (((x>>16)<<24)>>16) | (((x<<16)>>24)<<16) | x<<24)


struct iphdr
{

    unsigned int version: 4;
    unsigned int ihl: 4;
    unsigned int tos: 8;
    unsigned int tot_len: 16;

    unsigned int id: 16;
    unsigned int Flags: 3;
    unsigned int frag_off: 13;

    unsigned int ttl: 8;
    unsigned int protocol: 8;
    unsigned int check: 16;

    unsigned int saddr : 32;
    unsigned int daddr : 32;


};



bool IsLittleEndian(void)                           //Check current system follow which endian
{
    int number = 1;
    char *p = &number;

    if(*p == 1)
        return true;
    else
        return false;
}


int main(int argc, char *argv[])
{

    struct iphdr ipp;

    FILE *packet_file;
    unsigned char *packet;
    unsigned int len;

    packet_file = fopen("ip_packet.bin", "rb");  // Open the file in binary mode


    if(packet_file == NULL)
    {
        printf("No file found to open\n");
        return -1;
    }

    fseek(packet_file, 0, SEEK_END);                // Jump to the end of the file

    len = ftell(packet_file);                      // Get the current byte offset in the file
    rewind(packet_file);                          // Jump back to the beginning of the file

    packet = (char *)malloc(sizeof(char)*len);   // Create Enough memory for the file

    fread(packet, len, 1, packet_file);         // Read in the entire file
    fclose(packet_file);                        // Close the file

    if(packet[12] != 8)             //Check if this packet contain ip header
    {
        printf("This packet Does not contain any ip header\n");
        return -1;
    }

    char *header_pointer = packet + 14;                 // Pointing to ip header start point

    if(IsLittleEndian)
    {
        printf("This System follow Little Endian\n\n");

        uint16_t *bit16 = header_pointer;
        uint32_t *bit32 = header_pointer;

        // Convert to Little Endian

        *header_pointer = u_swap8(*header_pointer);                             // version and ihl in ip header
        *(bit16 + 1) = u_swap16(*(bit16 + 1));          //total length in ip header

        *(bit16 + 2) = u_swap16(*(bit16 + 2));          //Identification in ip header
        *(header_pointer + 6) = u_swap_3_5(*(header_pointer + 6));                  //Flag and Fragment offset in ip header
        *(bit16 + 3) = u_swap16(*(bit16 + 3));          //Flags and Fragment Offset in ip header

        *(bit16 + 5) = u_swap16(*(bit16 + 5));          //Header Checksum in ip header

        *(bit32 + 3) = u_swap32(*(bit32 + 3));          //Source Address in ip header
        *(bit32 + 4) = u_swap32(*(bit32 + 4));          //Destination Address in ip header

        memcpy(&ipp, header_pointer, 20);                // Copy all ip Header data to Ip header struct with convert little endian

    }
    else
    {
        printf("This System follow Big Endian\n\n");
        memcpy(&ipp, header_pointer, 20);                // Copy all ip Header data to Ip header struct without convert little endian
    }

    printf("version:%u\nihl:%u\ntos:%x\ntot_len:%x\nid:%x\nfrag_off:%u\nttl:%u\nprotocol:%u\ncheck:%x\nsaddr:%x\ndaddr:%x\n\n", ipp.version, ipp.ihl, ipp.tos, ipp.tot_len, ipp.id, ipp.frag_off, ipp.ttl, ipp.protocol, ipp.check, ipp.saddr, ipp.daddr);


    printf("Source Ip Address: %u.%u.%u.%u\n",(ipp.saddr>>24) & 255, (ipp.saddr>>16) & 255, (ipp.saddr>>8) & 255, (ipp.saddr) & 255);
    printf("Destination Ip Address: %u.%u.%u.%u\n",(ipp.daddr>>24) & 255, (ipp.daddr>>16) & 255, (ipp.daddr>>8) & 255, (ipp.daddr) & 255);


    free(packet);
    *packet = NULL;

    return 0;
}

