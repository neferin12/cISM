#include "organization.h"
#ifndef CISM_FILEINTERFACE_H
#define CISM_FILEINTERFACE_H
int countlines(char *filename);
seminarArray getSeminars(const char *filename, char type);
#endif //CISM_FILEINTERFACE_H