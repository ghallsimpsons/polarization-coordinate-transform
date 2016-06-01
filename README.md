Coordinate Transform Utilities for Polarization Angles
======================================================

## About

The main function of this library, `pol_angle_coord_transform`, uses simple
spherical trigonometry to translate polarization angles between the current
coordinate system and a new coordinate system with North Pole at location
`(pole_theta, pole_phi)` in the current coordinate system (Using the "Physics"
coordinate convention where theta is inclination from the pole, and phi the
azimuthal coordinate).

Two wrapper functions are provided which translate between Galactic and
Equatorial (J2000) coordinate systems. **Remember that declination and latitude
are defined as &pi;/2 - &theta;.**

