#include "headers/algorithm.h"
#include "headers/errorHandling.h"
#include "constants.h"
#include <stdlib.h>
#include <sys/time.h>
#include <glib.h>
#include <stdbool.h>

static void shuffle(int *array, int n) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long usec = tv.tv_usec;
    srand48(usec);

    if (n > 1) {
        int i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48() * (i + 1));
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

static int *getIntRange(int n){
    int *ints = malloc(sizeof(int) * n);
    failIfNull(ints, "could not malloc ints range");
    for (int i = 0; i < n; i++) {
        ints[i] = i;
    }
    return ints;
}

static GArray *copyStudents(const GArray *students) {
    GArray *lStudents = g_array_new(FALSE, FALSE, sizeof(student));
    //g_array_set_clear_func(lStudents, (GDestroyNotify) freeStudent);
    failIfNull(lStudents, "could not create copy of lStudents (malloc)");
    for (int i = 0; i < students->len; i++) {
        student h = g_array_index(students, student, i);
        student t = {.mimiPoints = 0, .name=h.name, .pSeminar=NULL, .wSeminar = NULL, .pVotes = h.pVotes, .wVotes = h.wVotes};
        lStudents = g_array_append_vals(lStudents, &t, 1);
    }
    return lStudents;
}

static int compareStudentsByPoints(const student *s1, const student *s2){
    return s2->mimiPoints-s1->mimiPoints;
}

static gboolean tryAssignment(student *s, seminar sel, GHashTable *assigments, int points, char semType){
    int assignedStudents;
    gboolean success = g_hash_table_lookup_extended(assigments, sel.id, NULL, (gpointer *) &assignedStudents);
    //int *assignedStudentsPointer = g_hash_table_lookup(assigments, sel.id);
    if (!success) {
        dieWithoutErrno("Could not get number of assigned students");
    }
    if (assignedStudents < sel.size) {
        int newCount = assignedStudents + 1;
        g_hash_table_replace(assigments, sel.id, GINT_TO_POINTER(newCount));
        s->mimiPoints += points;
        switch (semType) {
            case 'w':
                s->wSeminar = sel;
                break;
            case 'p':
                s->pSeminar = sel;
                break;
            default:
                dieWithoutErrno("invalid seminar type");
        }
        return TRUE;
    }
    return FALSE;
}

GArray *batchRunAlgorithmn(int times,const GArray *students, const GArray *w_seminars, const GArray *p_seminars){
    GArray *best = NULL;
    int bestPoints = INT_MAX;
    for (int i = 0; i < times; i++) {
        GArray *tmp = runAlgorithm(students, w_seminars, p_seminars);
        int tmpPoints = accumulatePoints(tmp);
        if (tmpPoints < bestPoints) {
            if (best != NULL) {
                g_array_free(best, TRUE);
            }
            best = tmp;
            bestPoints = tmpPoints;
        } else {
            g_array_free(tmp, TRUE);
        }
    }
    return best;
}

GArray *runAlgorithm(const GArray *students, const GArray *w_seminars, const GArray *p_seminars) {
    GHashTable *table = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, NULL);
    for (int i = 0; i < w_seminars->len; i++) {
        seminar s = g_array_index(w_seminars, seminar, i);
        g_hash_table_insert(table, s.id, GINT_TO_POINTER(0));
    }
    for (int i = 0; i < p_seminars->len; i++) {
        seminar s = g_array_index(p_seminars, seminar, i);
        g_hash_table_insert(table, s.id, GINT_TO_POINTER(0));
    }

    GArray *cStudents = copyStudents(students);
    int *intrange = getIntRange(cStudents->len);
    shuffle(intrange, cStudents->len);
    for (int i = 0; i < cStudents->len; i++) {
        student *s = &g_array_index(cStudents, student, intrange[i]);
        if (!tryAssignment(s, s->wVotes[0], table, default_points.first_selection, 'w')) {
            if (!tryAssignment(s, s->wVotes[1], table, default_points.second_selection, 'w')) {
                if (!tryAssignment(s, s->wVotes[2], table, default_points.third_selection, 'w')) {
                    s->mimiPoints += default_points.no_selection;
                }
            }
        }

    }
    free(intrange);
    g_array_sort(cStudents, (GCompareFunc) compareStudentsByPoints);
    for (int i = 0; i < cStudents->len; i++) {
        student *s = &g_array_index(cStudents, student, i);
        if (!tryAssignment(s, s->pVotes[0], table, default_points.first_selection, 'p')) {
            if (!tryAssignment(s, s->pVotes[1], table, default_points.second_selection, 'p')) {
                if (!tryAssignment(s, s->pVotes[2], table, default_points.third_selection, 'p')) {
                    s->mimiPoints += default_points.no_selection;
                }
            }
        }

    }
    g_hash_table_destroy(table);
    return cStudents;
}
