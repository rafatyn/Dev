#ifndef _CONCOLOR_
#define _CONCOLOR_

#include <iostream>

#ifdef LINUX

char black[] = { 0x1b, '[', '0', ';', '3', '0', 'm', 0 };
char red[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
char blue[] = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
char magenta[] = { 0x1b, '[', '0', ';', '3', '5', 'm', 0 };
char cyan[] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char white[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

char blackb[] = { 0x1b, '[', '1', ';', '3', '0', 'm', 0 };
char redb[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
char greenb[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
char yellowb[] = { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
char blueb[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
char magentab[] = { 0x1b, '[', '1', ';', '3', '5', 'm', 0 };
char cyanb[] = { 0x1b, '[', '1', ';', '3', '6', 'm', 0 };
char whiteb[] = { 0x1b, '[', '1', ';', '3', '7', 'm', 0 };
char normalb[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

#else
#error Falta definir sistema operativo! Definir WIN o LINUX
#endif
#endif
