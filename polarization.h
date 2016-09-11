#pragma once

#ifndef M_PI
    #define M_PI 3.1415926535897932384626433
#endif

double pol_angle_gal_to_eq(double l, double b, double pol_in);

double pol_angle_eq_to_gal(double alpha, double delta, double pol_in);

double pol_angle_coord_transform(double pole_theta, double pole_phi,
                                 double pix_theta, double pix_phi, double pol_in);
