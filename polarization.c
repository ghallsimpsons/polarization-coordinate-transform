#include <stddef.h>
#include <math.h>
#include <stdlib.h>

#include <polarization.h>

double
pol_angle_gal_to_eq(double l, double b, double pol_in)
{
	/*
	 * Computes polarization rotation from Galactic to Equatorial (J2000)
	 * coordinates.
	 */

	/* Galactic coordinates of Equatorial pole */
	static const double eq_l = 122.93191813706228*M_PI/180.0;
	static const double eq_theta = M_PI/2.0 - 27.128251257939215*M_PI/180.0;
	return pol_angle_coord_transform(eq_theta, eq_l, M_PI/2.0-b, l, pol_in);
}

double
pol_angle_eq_to_gal(double alpha, double delta, double pol_in)
{
	/*
	 * Computes polarization rotation from Equatorial (J2000) to Galactic
	 * coordinates.
	 */

	/* Equatorial coordinates of Galactic pole */
	static const double gal_alpha = 192.85948098508993*M_PI/180.0;
	static const double gal_theta = M_PI/2.0 - 27.128251257308968*M_PI/180.0;
	return pol_angle_coord_transform(gal_theta, gal_alpha, M_PI/2.0-delta,
	                                 alpha, pol_in);
}

double
pol_angle_coord_transform(double pole_theta, double pole_phi, double pix_theta,
                          double pix_phi, double pol)
{
	/*
	 * Computes polarization rotation from between a reference coordinate system
	 * and a new coordinate system with pole at position (pole_theta, pole_phi)
	 * in the reference system. Phi is the azimuthal position, and Theta is the
	 * angular distance from the reference pole.
	 */

	double side_ref_pixel, side_new_pixel, side_ref_new, angle_new_pixel,
	       cos_side_new_pixel, rot_sin, rot_cos, theta, mod_angle;

	angle_new_pixel = fmod(pix_phi-pole_phi, 2.0*M_PI);
	side_ref_pixel = pix_theta;
	side_ref_new = pole_theta;
	cos_side_new_pixel = cos(side_ref_new)*cos(side_ref_pixel) +
	                    sin(side_ref_new)*sin(side_ref_pixel)*cos(angle_new_pixel);
	if (angle_new_pixel > M_PI)
		side_new_pixel = 2.0*M_PI - acos(cos_side_new_pixel);
	else
		side_new_pixel = acos(cos_side_new_pixel);
	rot_sin = asin(sin(side_ref_new)*sin(angle_new_pixel)/sin(side_new_pixel));
	rot_cos = acos((cos(side_ref_new)-cos(side_ref_pixel)*cos(side_new_pixel))/
	               (sin(side_ref_pixel)*sin(side_new_pixel)));
	if (isnan(rot_cos))
		return pol;

    /* Full angle can be inferred from the arccos and arcsin */
	if (rot_sin<0){
		if (rot_cos>M_PI/2.0)
			theta = -M_PI - rot_sin;
		else
			theta = rot_sin;
	} else {
		theta = rot_cos;
	}

	/* The IAU defines polarization angle to increase counterclockwise. */
	mod_angle = fmod(pol-theta, M_PI);
	if (mod_angle<0)
		return mod_angle + M_PI;
	return mod_angle;
}
