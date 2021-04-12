#include "types.h"
#include "lock.h"
#include "string.h"
#include "io.h"
#include "print.h"

UByte InByte(UShort port)
{
    UByte result;
    asm volatile("inb %1, %0"
                 : "=a"(result)
                 : "Nd"(port));
    return result;
}

void OutByte(UShort port, UByte data)
{
    asm volatile("outb %0, %1" ::"a"(data), "Nd"(port));
}

// ---------------- SERIAL ---------------- //

#define COM1 0x3f8

Bool InitSerial()
{
    OutByte(COM1 + 1, 0x00); // Disable all interrupts
    OutByte(COM1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
    OutByte(COM1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    OutByte(COM1 + 1, 0x00); //                  (hi byte)
    OutByte(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
    OutByte(COM1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    OutByte(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
    OutByte(COM1 + 4, 0x1E); // Set in loopback mode, test the serial chip
    OutByte(COM1 + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    UByte recv = InByte(COM1 + 0);
    if (recv != 0xAE)
    {
        Char buf[4];
        Println(IntToString((Int)recv, buf, 16));
        return False;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    OutByte(COM1 + 4, 0x0F);
    return True;
}

static Byte _IsTransmitEmpty()
{
    return InByte(COM1 + 5) & 0x20;
}

void SerialChar(char ch)
{
    WAIT_UNTIL(_IsTransmitEmpty() != 0);
    OutByte(COM1, ch);
}

void SerialPrint(Char *str)
{
    WAIT_UNTIL(_IsTransmitEmpty() != 0);
    for (Size i = 0; 1; i++)
    {
        char character = (Char)str[i];

        if (character == '\0')
        {
            return;
        }

        SerialChar(character);
    }
}
void SerialPrintln(Char *str)
{
    WAIT_UNTIL(_IsTransmitEmpty() != 0);
    for (Size i = 0; 1; i++)
    {
        Char character = (Char)str[i];

        if (character == '\0')
        {
            SerialChar('\n');
            return;
        }

        SerialChar(character);
    }
}