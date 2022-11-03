//
// Created by gbtur on 10/23/2022.
//

#include "NFET.h"

// namespaces
using namespace std;
//have to call filesystem scope directly because
//a few functions have the same name as std functions
using namespace std::filesystem;

//constructors
NFET::NFET(double l, double w, string n, double k, double v, double lm) {
    //initialize name and data_path
    name = n;
    data_path = "../" + name + "_data";

    //initialize members
    length = l;
    width = w;
    k_p = k;
    v_t0 = v;
    lambda = lm;

    //initialize voltage ranges
    vgs.start = 0;
    vgs.end = 5;
    vgs.steps = 5;

    vds.start = 0;
    vds.end = 10;
    vds.steps = 100;
}

NFET::NFET() {
    //initialize name and data_path
    name = "FET";
    data_path = "../" + name + "_data";

    //initialize members
    length = 600e-9;
    width = 3.6e-6;
    k_p = 200e-6;
    v_t0 = 1.0;
    lambda = 0.05;

    //initialize voltage ranges
    vgs.start = 0;
    vgs.end = 5;
    vgs.steps = 5;

    vds.start = 0;
    vds.end = 10;
    vds.steps = 100;
}


//getters and setters

void NFET::set_vt_0(double v) {
    v_t0 = v;
}

double NFET::get_vt_0() const {
    return v_t0;
}

double NFET::get_lambda() const {
    return lambda;
}

void NFET::set_lambda(double l) {
    lambda = l;
}

double NFET::get_length() const {
    return length;
}

void NFET::set_length(double l) {
    length = l;
}

double NFET::get_width() const {
    return width;
}

void NFET::set_width(double w) {
    width = w;
}

double NFET::get_k_p() const {
    return k_p;
}

void NFET::set_k_p(double k) {
    k_p = k;
}

string NFET::get_name() const{
    return name;
}

void NFET::set_name(string n){
    name = n;
    //update data path since we want a systematic
    // correlation between name and data path
    data_path =  "../" + name + "_data";
}

string NFET::get_data_path() const{
    return data_path;
}

range NFET::get_vds() {
    return vds;
}

void NFET::set_vds(double start, double end, int steps) {
    //check for valid start end swap if needed
    if(start > end){
        vds.start = end;
        vds.end = start;
    }
    else{
        vds.start = start;
        vds.end = end;
    }

    //check for steps = 0 this will break the program
    if(steps == 0){
        vds.steps = 1;
    }
    else{
        vds.steps = steps;
    }
}

range NFET::get_vgs() {
    return vgs;
}

void NFET::set_vgs(double start, double end, int steps) {
    //check for valid start end swap if needed
    if(start > end){
        vgs.start = end;
        vgs.end = start;
    }
    else{
        vgs.start = start;
        vgs.end = end;
    }

    //check for steps = 0 this will break the program
    if(steps == 0){
        vgs.steps = 1;  // default steps
    }
    else{
        vgs.steps = steps;
    }
}


//function used to calculate drain current based on a set vgs and vds
double NFET::drain_current(double vgs, double vds) const {
    double id = 0;
    //cut_off region
    if(vgs <= v_t0){
        return id;
    }
    //linear region
    else if(vds <= (vgs-v_t0)){
        id = k_p*width/length * (((vgs-v_t0)*vds) - (pow(vds,2)/2)) * (1+lambda*vds);
        return id;
    }
    //saturation region
    else{
        id = 0.5*k_p*width/length * pow(vgs-v_t0, 2) * (1+lambda*vds);
        return id;
    }
}

bool NFET::generate_curves() {
    //output directory already exists remove it
    if(exists(data_path)){
        remove_all(data_path);
    }

    //create output directory
    create_directory(data_path);
    ofstream out_file;

    for (double i = vgs.start; i <= vgs.end; i += (vgs.end - vgs.start) / vgs.steps) {
        //open a csv for specified vgs
        out_file.open(data_path + "/vgs" + to_string(i) +".csv");

        //add header
        out_file << "V_ds, I_dd, V_gs" << endl;

        //add vgs and vds values
        for(double j = vds.start; j<=vds.end; j += (vds.end - vds.start)/ vds.steps){
            if(j == vds.start){
                out_file << j << "," << drain_current(i,j) << "," << i << endl;
            }
            else{
                out_file << j << "," << drain_current(i,j) << endl;
            }
        }
        //print end line to signify end of csv for python
        out_file << endl;
        //close the file
        out_file.close();
    }

    //return true for successful creation of data directory
    return true;
}






