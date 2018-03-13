//
// Created by Fabian on 13.03.18.
//

#include <iostream>
#include "Twiddle.h"

Twiddle::Twiddle(bool do_optimize, int iteration_run_length, double threshold, double *params) : iteration_run_length(
        iteration_run_length),
                                                                                                 threshold(threshold),
                                                                                                 do_optimize(
                                                                                                         do_optimize) {

    for (int i = 0; i < 3; i++) {
        Twiddle::params[i] = params[i];
    }

    for (double &delta_param : Twiddle::delta_params) {
        delta_param = 1.0;
    }

    param_to_tweak = 0;
    check_improvement = false;

    pid.Init(params[0], params[1], params[2]);

    step = 0;
    overall_error = 0.0;

}

bool Twiddle::updateError(double cte) {
    pid.UpdateError(cte);
    overall_error += cte;

    double delta_param_sum = delta_params[0] + delta_params[1] + delta_params[2];
    if (do_optimize && delta_param_sum > threshold) {
        ++step;
        if (step >= iteration_run_length) {
            step = 0;
            updateParams(cte);
            pid.Init(params[0], params[1], params[2]);
            std::cout << "delta_param_sum: " << delta_param_sum << " Params p: " << params[0] << " i: " << params[1]
                      << " d: " << params[2];
            return true;
        }
    }
    return false;
}

double Twiddle::totalError() {
    return pid.TotalError();
}


void Twiddle::updateParams(double cte) {

    if (!check_improvement) {
        if (cte < best_error) {
            best_error = cte;
            params[param_to_tweak] *= 1.1;
        } else {
            params[param_to_tweak] -= 2 * delta_params[param_to_tweak];
            check_improvement = true;
        }
    } else {
        if (cte < best_error) {
            best_error = cte;
            delta_params[param_to_tweak] *= 1.1;
        } else {
            params[param_to_tweak] += delta_params[param_to_tweak];
            delta_params[param_to_tweak] *= 0.9;
        }
        param_to_tweak = (param_to_tweak + 1) % 3;
        check_improvement = false;
        params[param_to_tweak] += delta_params[param_to_tweak];
    }
}
