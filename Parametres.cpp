//
//  Parametres.cpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 09/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#include "Parametres.h"

function<Homogene(Homogene)> exempleJulia(unsigned int j){
    function<Homogene(Homogene)> fonction;
    switch (j) {
        case 0:// LAPIN
            fonction = [](Homogene point){
                if (point.carteX() == 0.) {
                    return Homogene(1.,0.);
                }
                complex<double> a = point.carteY();
                return Homogene(a*a + complex<double>(-0.123,0.745));
            };
            break;
        case 1:// COLLIER
            fonction = [](Homogene point){
                if (point.carteX() == 0.) {
                    return Homogene(1.,1.);
                }
                complex<double> a = point.carteY();
                if (a == 0.) {
                    return Homogene(1.,0.);
                }
                return Homogene(1. + complex<double>(-1.)/(a*a));
            };
            break;
        case 2:// GALAXIE
            fonction = [](Homogene point){
                if (point.carteX() == 0.) {
                    return Homogene(1.,0.);
                }
                complex<double> a = point.carteY();
                if (a == 0.) {
                    return Homogene(1.,0.);
                }
                return Homogene(-0.138*a + -0.303 + -0.138/a);
            };
            break;
        case 3:// STRANGE
            fonction = [](Homogene point){
                if (point.carteX() == 0.) {
                    return Homogene(1.,0.);
                }
                complex<double> a = point.carteY();
                return Homogene(a*a + -0.8);
            };
            break;
        case 4:// NEWTON
            fonction = [](Homogene point){
                if (point.carteX() == 0.) {
                    return Homogene(1.,0.);
                }
                complex<double> a = point.carteY();
                return Homogene(2.*a*a*a + -2., 3.*a*a - 2.);
            };
            break;
        case 5:// PENTAGONE
            fonction = [](Homogene point){
                if (point.carteX() == 0.) {
                    return Homogene(0.,1.);
                }
                complex<double> a = point.carteY();
                complex<double> c = a*a*a*a;
                complex<double> b = c*a;
                return Homogene(1. + b*(-435.) + b*b*(-6670.) + b*b*b*b*(-3335.) + b*b*b*b*b*(87.),
                                c*(87.) + c*b*(3335.) + c*b*b*b*(6670.) + c*b*b*b*b*(-435.) + c*b*b*b*b*b*(-1.));
            };
            break;
        default:
            break;
    }
    return fonction;
}
