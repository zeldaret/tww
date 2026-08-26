#ifndef OSSTOPWATCH_H
#define OSSTOPWATCH_H

struct OSStopwatch {
    char * name;
    long long total;
    unsigned long hits;
    long long min;
    long long max;
    long long last;
    int running;
};

void OSInitStopwatch(struct OSStopwatch * sw, char * name);
void OSStartStopwatch(struct OSStopwatch * sw);
void OSStopStopwatch(struct OSStopwatch * sw);
long long OSCheckStopwatch(struct OSStopwatch * sw);
void OSResetStopwatch(struct OSStopwatch * sw);
void OSDumpStopwatch(struct OSStopwatch * sw);

#endif /* OSSTOPWATCH_H */
