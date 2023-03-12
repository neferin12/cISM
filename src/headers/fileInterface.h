#include "organization.h"
#ifndef CISM_FILEINTERFACE_H
#define CISM_FILEINTERFACE_H
GArray *getSeminars(const char *filename, char type);
GArray *getStudents(const char *filename, GArray *wSeminars, GArray *pSeminars);
#endif //CISM_FILEINTERFACE_H
