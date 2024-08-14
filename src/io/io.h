#ifndef IO_H
#define IO_H

/**
 * @brief Read a byte from the specified port.
 *
 * @param port The port to read from.
 * @return The byte read from the port.
 */
unsigned char insb(unsigned short port);

/**
 * @brief Read a word from the specified port.
 *
 * @param port The port to read from.
 * @return The word read from the port.
 */
unsigned short insw(unsigned short port);

/**
 * @brief Write a byte to the specified port.
 *
 * @param port The port to write to.
 * @param value The byte to write.
 */
void outb(unsigned short port, unsigned char value);

/**
 * @brief Write a word to the specified port.
 *
 * @param port The port to write to.
 * @param value The word to write.
 */
void outw(unsigned short port, unsigned short value);

#endif