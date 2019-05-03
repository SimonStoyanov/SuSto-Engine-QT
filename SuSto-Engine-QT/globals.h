#ifndef GLOBALS_H
#define GLOBALS_H

#include <QTextStream>

static float DEGTORAD(float deg) {
    return deg*(3.1415/180);
}

static float RADTODEG(float rad) {
    return rad*(180/3.1415);
}

static void SPOOKYLOG(std::string log)
{
    QTextStream out(stdout);
    out << log.c_str() << endl;
}




#endif // GLOBALS_H
