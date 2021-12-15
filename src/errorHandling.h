//
// Created by julian on 15.12.21.
//

#ifndef CISM_ERRORHANDLING_H
#define CISM_ERRORHANDLING_H
void dieWithErrno(char *msg);
void dieWithoutErrno(char *msg);
void failIfNull(void *anyPointer, char *msg);
#endif //CISM_ERRORHANDLING_H
