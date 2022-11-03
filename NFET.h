//
// Created by gbtur on 10/23/2022.
//

#ifndef M3OEP_GBTURNER_NFET_H
#define M3OEP_GBTURNER_NFET_H

#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <string>

using std::string;

//struct used for voltage ranges
struct range{
    double start;
    double end;
    int steps;
};

class NFET {

private:
    string name;
    string data_path;
    double width;
    double length;
    double k_p;
    double v_t0;
    double lambda;
    range vgs;
    range vds;

public:
    // constructors
    NFET(double l, double w, string n = "FET" , double k = 200e-6, double v = 1, double lm = 0.05);

    NFET();

    // getters and setters
    void set_vgs(double start, double end, int steps);

    range get_vgs();

    void set_vds(double start, double end, int steps);

    range get_vds();

    double get_k_p() const;

    void set_k_p(double k);

    double get_vt_0() const;

    void set_vt_0(double v);

    double get_lambda() const;

    void set_lambda(double lm);

    double get_length() const;

    void set_length(double l);

    double get_width() const;

    void set_width(double w);

    string get_name() const;

    void set_name(string n);

    string get_data_path() const;

    //calculate current
    double drain_current(double vgs, double vds) const;

    //generate data
    bool generate_curves();

};


#endif //M3OEP_GBTURNER_NFET_H
