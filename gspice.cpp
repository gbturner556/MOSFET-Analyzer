#include <iostream>
#include <sstream>
#include "NFET.h"
#include <optional>
#include <process.h>
#include <filesystem>

// this lets CLION not freak out when I add an endless loop
// I don't fully understand it
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

//namespaces
using namespace std;
//have to call filesystem scope directly because
//a few functions have the same name as std functions
namespace fs = std::filesystem;

//TODO comments everywhere!
//TODO write a function to get user input for vgs and vds

//function declarations
void print_title();
void print_menu();
char get_option();
NFET get_fet();
optional<double> get_parameter();

// main
int main(){
    while(true){
        //print menu and title
        print_title();
        print_menu();

        //get option from user
        char option = get_option();

        //decide action based on user input
        //**************** create new FET mode *************
        if(option == 'a'){
            //create an NFET based on user inputs
            NFET nfet = get_fet();

            //generate curve data from users nFET
            nfet.generate_curves();

            //create command for python to plot
            string cmd = "python ../plot.py " + nfet.get_name() + " " + nfet.get_data_path();

            //call command
            system(cmd.c_str());
        }

        //************ Plot existing data mode ********************
        else if(option == 'b'){
            //string to hold name of data directory
            string data_dir;

            //prompt user for name of data_dir
            cout << "Enter the name of the data directory: ";

            //store input in data_dir
            getline(cin, data_dir);

            //if the directory doesn't exist tell the user and loop
            //back to main menu
            if(!fs::exists("../" + data_dir)){
                cout << "Directory " + data_dir + "does not exist." << endl;
            }
            //if the path does exist but it's not a directory tell the
            //user and loop back to main menu
            else if(!fs::is_directory("../" + data_dir)){
                cout << data_dir + "is not a directory." << endl;
            }
            //otherwise the directory exists and is a directory so send the
            //path to python
            //since we don't have a NFET object to call we'll pass the data
            //directory as the name of the FET
            else{
                string cmd = "python ../plot.py ../" + data_dir;
                system(cmd.c_str());
            }
        }

        //****************** exit program *****************
        else{
            exit(0);
        }
    }
    return 0;
}

//Function definitions
void print_title(){
    // had a little fun here
    // copy and pasted ascii art from ascii art generator
    // https://manytools.org/hacker-tools/ascii-banner/
    cout << "_____________________________________________________" << endl;
    cout << "   ______   _____    ____     ____   ______    ______" << endl;
    cout << "  / ____/  / ___/   / __ \\   /  _/  / ____/   / ____/" << endl;
    cout << " / / __    \\__ \\   / /_/ /   / /   / /       / __/   " << endl;
    cout << "/ /_/ /   ___/ /  / ____/  _/ /   / /___    / /___   " << endl;
    cout << "\\____/   /____/  /_/      /___/   \\____/   /_____/  " << endl;
    cout << "_____________________________________________________";
    cout << endl << endl;
}

// print out a nice formatted menu
void print_menu(){
    cout << "Menu:" << endl;
    cout << "(a) Characterize a new MOSFET" << endl;
    cout << "(b) Plot existing MOSFET data" << endl;
    cout << "(c) Exit" << endl << endl;
    cout << "Enter option: ";
}

//this function also has some silliness to it
char get_option(){
    //get line from user
    string input;
    getline(cin, input);

    //keep track of how many times user has failed to enter an option
    int tries = 0;

    while(input.size() != 1 || tolower(input[0]) < 'a' || tolower(input[0] > 'c')){

        //increment tries
        ++tries;

        //we'll print the normal invalid input for the first 10 tries
        if(tries<10){
            //endl for formatting console
            cout << endl;

            //explain invalid option
            cout << "Invalid option! Enter a, b, or c ..." << endl;

            //print menu again and get user input
            print_menu();
            getline(cin, input);
        }

        //after 10 tries the program gets a little sassy
        else{
            if(tries == 11){
                //endl for formatting console
                cout << endl;

                //explain invalid option
                cout << "Seriously? It's not that hard! Enter a, b, or c ..." << endl;

                //print menu again and get user input
                print_menu();
                getline(cin, input);
            }
            else if(tries == 12){
                //endl for formatting console
                cout << endl;

                //explain invalid option
                cout << "Please just enter a, b, or c ..." << endl;

                //print menu again and get user input
                print_menu();
                getline(cin, input);
            }
            else if(tries == 13){
                //endl for formatting console
                cout << endl;

                //explain invalid option
                cout << "*sigh* Invalid input :/ try entering a" << endl;

                //print menu again and get user input
                print_menu();
                getline(cin, input);
            }
            else if(tries == 14){
                //endl for formatting console
                cout << endl;

                //explain invalid option
                cout << "Okay how long are we gonna do this?" << endl;

                //print menu again and get user input
                print_menu();
                getline(cin, input);
            }
            else if(tries == 15){
                //endl for formatting console
                cout << endl;

                //explain invalid option
                cout << "Alright ... I'm done, bye" << endl;

                //exit
                exit(0);
            }
        }
    }

    //return user input
    return input[0];
}

NFET get_fet(){

    //initialize default NFET and name string
    NFET nfet;
    string name;

    //prompt user for MOSFET name
    cout << "Enter a name for your MOSFET: ";

    //get name
    getline(cin, name);

    //change all spaces to underscore
    replace(name.begin(), name.end(), ' ', '_' );

    //set nfet name;
    nfet.set_name(name);

    //used to hold optional from get_parm()
    optional<double> parm;

    //prompt user for width
    cout << "Enter width [nm]: ";
    parm = get_parameter();

    //if the parm has a value set it
    if(parm){
        nfet.set_width(parm.value()*1e-9); //adjusting for nanometers
    }

    //prompt user for length
    cout << "Enter length [nm]: ";
    parm = get_parameter();

    //if the parm has a value set it
    if(parm){
        nfet.set_length(parm.value()*1e-9); // adjusting for nanometers
    }

    //prompt user for kp
    cout << "Enter K_p [uA/V^2]: ";
    parm = get_parameter();

    //if parm has value set it
    if(parm){
        nfet.set_k_p(parm.value()*1e-6);    // adjusting for mircroamps
    }

    //prompt user for Vt0
    cout << "Enter V_t0 [V]: ";
    parm = get_parameter();

    //if parm has value set it
    if(parm){
        nfet.set_vt_0(parm.value());
    }

    //prompt user for lambda
    cout << "Enter lambda [V^-1]: ";
    parm = get_parameter();

    //if parm has value set it
    if(parm){
        nfet.set_lambda(parm.value());
    }

    //return the fet device
    return nfet;
}

optional<double> get_parameter(){
    //used to parse arguments from user
    stringstream parser;

    //used to hold user input
    string input;

    //used to store user input as double
    double temp;

    //get line from user
    getline(cin,input);

    //parse the input and store in temp
    parser << input;
    parser >> temp;

    //if the parser failed return a nullopt
    if(parser.fail()){
        parser.clear();
        return nullopt;
    }
    //else return the value
    else{
        return make_optional<double>(temp);
    }
}

#pragma clang diagnostic pop