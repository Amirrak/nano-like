#ifndef NANOLIKE_H
#define NANOLIKE_H

void crash(const char *message);

void disableRawMode();

void enableRawMode();

char readKey();

void executeKey();
#endif
