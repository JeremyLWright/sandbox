#include <complex>
#include <iostream>

#include <boost/typeof/std/complex.hpp>

#include <boost/units/systems/si/energy.hpp>
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/electric_potential.hpp>
#include <boost/units/systems/si/current.hpp>
#include <boost/units/systems/si/resistance.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/cmath.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/base_units/imperial/foot.hpp>

using namespace boost::units;
using namespace boost::units::si;

quantity<energy>
work(const quantity<force>& F, const quantity<length>& dx)
{
    return F * dx; // Defines the relation: work = force * distance.
}

int main()
{
#if 0
    /// Test calculation of work.
    quantity<force>     F(2.0 * newton); // Define a quantity of force.
    quantity<length>    dx(2.0 * meter); // and a distance,
    quantity<energy>    E(work(F,dx));  // and calculate the work done.

    std::cout << "F  = " << F << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E << std::endl
              << std::endl;

    /// Test and check complex quantities.
    typedef std::complex<double> complex_type; // double real and imaginary parts.

    // Define some complex electrical quantities.
    quantity<electric_potential, complex_type> v = complex_type(12.5, 0.0) * volts;
    quantity<current, complex_type>            i = complex_type(3.0, 4.0) * amperes;
    quantity<resistance, complex_type>         z = complex_type(1.5, -2.0) * ohms;

    std::cout << "V   = " << v << std::endl
              << "I   = " << i << std::endl
              << "Z   = " << z << std::endl
              // Calculate from Ohm's law voltage = current * resistance.
              << "I * Z = " << i * z << std::endl
              // Check defined V is equal to calculated.
              << "I * Z == V? " << std::boolalpha << (i * z == v) << std::endl
              << std::endl;
#else
    auto circle = 2.0 * boost::math::constants::pi<double>() * si::radian;
    std::cout << static_cast<quantity<degree::plane_angle>>(circle) << std::endl;

    auto m = 2.0 * si::meter;
    std::cout << quantity<imperial::foot_base_unit::unit_type>(m) << std::endl;

    //auto f = 3 * micron_base_unit::unit_type;
    //auto j = m + f;
    //std::cout << quantity<si::meter>(j) << '\n';

#endif
    return 0;
}
