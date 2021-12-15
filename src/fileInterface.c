#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileInterface.h"
#include "organization.h"
#include "errorHandling.h"

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


seminarArray getSeminars(char *filename, char type) {
    seminar *seminars = NULL;
    int seminarc = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        dieWithErrno("could not open file");
    }
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        line[strcspn(line, "\n")] = 0;
        printf("1| %s\n", line);
        seminars = realloc(seminars, sizeof(seminar) * (seminarc + 1));
        failIfNull(seminars, "realloc");
        char *parsed = strtok(line, ";");
        char buf[80];
        snprintf(buf, 80, "seminars incorrectly configured at line %d", seminarc);
        failIfNull(parsed, buf);
        seminar lSeminar;
        printf("2| %d, %s\n", seminarc, parsed);
        lSeminar.name = parsed;
        parsed = strtok(NULL, ";");
        failIfNull(parsed, buf);
        lSeminar.size = strtol(parsed, NULL, 10);
        parsed = strtok(NULL, ";");
        failIfNull(parsed, buf);
        if (strcmp(parsed, "W")) {
            lSeminar.seminarType = 'W';
        } else if (strcmp(parsed, "P")) {
            lSeminar.seminarType = 'P';
        } else {
            dieWithoutErrno(buf);
        }
        if (strcmp(parsed, &type)) {
            seminars[seminarc++] = lSeminar;

        }
    }
    fclose(file);

    free(line);
    seminarArray ret = {.size = seminarc, .seminars = seminars};
    return ret;
}
