#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/fileInterface.h"
#include "headers/organization.h"
#include "headers/errorHandling.h"

int countlines(char *filename)
{
    // count the number of lines in the file called filename
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL) {
        return 0;
    }

    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    return lines;
}


seminarArray getSeminars(const char *filename, char type) {
    seminar *seminars = NULL;
    int seminarc = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        dieWithErrno("could not open file");
    }
    char *line = NULL;
    size_t len = 0;
    int linec = 0;
    while (getline(&line, &len, file) != -1) {
        linec++;
        line[strcspn(line, "\n")] = 0;
        seminars = realloc(seminars, sizeof(seminar) * (seminarc + 1));
        failIfNull(seminars, "realloc");
        char *parsed = strtok(line, ";");
        char buf[80];
        snprintf(buf, 80, "seminars incorrectly configured at line %d\n", linec);
        failIfNull(parsed, buf);
        seminar lSeminar;
        lSeminar.name = malloc((strlen(parsed) + 1) * sizeof(char));
        strcpy( lSeminar.name, parsed);
        parsed = strtok(NULL, ";");
        failIfNull(parsed, buf);
        lSeminar.size = strtol(parsed, NULL, 10);
        parsed = strtok(NULL, ";");
        failIfNull(parsed, buf);
        if (strcmp(parsed, "W")==0) {
            lSeminar.seminarType = 'W';
        } else if (strcmp(parsed, "P")==0) {
            lSeminar.seminarType = 'P';
        } else {
            dieWithoutErrno(buf);
        }
        if (parsed[0]==type) {
            seminars[seminarc++] = lSeminar;
        } else {
            free(lSeminar.name);
        }
    }
    fclose(file);

    free(line);
    seminarArray ret = {.size = seminarc, .seminars = seminars};
    return ret;
}

studentArray getStudents(const char *filename, seminarArray wSeminars, seminarArray pSeminars) {
    student *students = NULL;
    int studentc = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        dieWithErrno("could not open file");
    }
    char *line = NULL;
    size_t len = 0;
    int linec = 0;
    while (getline(&line, &len, file) != -1) {
        linec++;
        line[strcspn(line, "\n")] = 0;
        students = realloc(students, sizeof(student) * (studentc + 1));
        failIfNull(students, "realloc");
        char *parsed = strtok(line, ";");
        char buf[80];
        snprintf(buf, 80, "students incorrectly configured at line %d\n", linec);
        failIfNull(parsed, buf);
        student lStudent;
        lStudent.name = malloc((strlen(parsed) + 1) * sizeof(char));
        strcpy(lStudent.name, parsed);
        // W Seminars
        for (int i = 0; i < 3; ++i) {
            parsed = strtok(NULL, ";");
            failIfNull(parsed, buf);
            lStudent.wVotes[i] = wSeminars.seminars[strtol(parsed, NULL, 10)];
        }
        // P Seminars
        for (int i = 0; i < 3; ++i) {
            parsed = strtok(NULL, ";");
            failIfNull(parsed, buf);
            lStudent.pVotes[i] = pSeminars.seminars[strtol(parsed, NULL, 10)];
        }

        students[studentc++] = lStudent;
    }
    fclose(file);

    free(line);
    studentArray ret = {.size = studentc, .students = students};
    return ret;
}