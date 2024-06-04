#ifndef CHECK_STDSORT_H
#define CHECK_STDSORT_H

#include <Qstring>
#include <QtMath>
#include <vector>

#include "timer_common.h"
#include "generator.h"
#include "check.h"

class check_stdsort
{
public:
    check_stdsort();
    QString sort(int size);
};

#endif // CHECK_STDSORT_H
