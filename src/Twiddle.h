//
// Created by Fabian on 13.03.18.
//

#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H


#include "PID.h"

class Twiddle {

    bool do_optimize;

    int iteration_run_length;
    double threshold;

    double params [3];
    double delta_params [3];
    int param_to_tweak;
    bool check_improvement;


    PID pid;

    int step;

    double overall_error;
    double best_error;


public:
    Twiddle(bool do_optimize,int iteration_run_length, double threshold, double *params);

    bool updateError(double cte);

    void updateParams(double cte);

    double totalError();
};


#endif //PID_TWIDDLE_H
