#ifndef GLOBALS_H
#define GLOBALS_H

#include <QTextStream>

static void SPOOKYLOG(std::string log)
{
    QTextStream out(stdout);
    out << log.c_str() << endl;
}




#endif // GLOBALS_H
