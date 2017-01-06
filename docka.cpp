#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <vector>

using namespace std;

// help message
static void show_usage(string name){
	cout << "Document Control Kang Anan\t\tGeneral Commmands Manual \n"
		  << " \n"
		  << "Copyight (c) 2016 Ana Nurdiana, S.T. - ananurdiana@gmail.com \n"
			<< " \n"
		  << "This is free software. No warranty from author. \n"
		  << "If you want warranty and support from author, please contact and pay \n"
			<< "him to support you. \n"
			<< " \n"
			<< "NAME \n"
			<< "\t" << name << " - 1.0 A program to generate document control in UID \n"
			<< " \n"
		  << "USAGE \n\t" << name << " <option(s)> VALUE \n"
		  << " \n"
		  << "OPTIONS \n"
		  << "\t-h, --help \t\tShow this help message \n"
		  << "\t-d, --document <DOC>\tSpesify the office (docx, doc, xlsx, xls, ppt,\n"
		  << "\t\t\t\tpptx) file \n"
		  << "\t-s, --stamp <PDF>\tSpesify the stamp (pdf) file \n"
			<< "\t-sfont	<FONT_TYPE>\tSpesify the font type\n"
			<< "\t\t\t\texample: -sfont \"CenturySchL-Roma\" \n"
			<< "\t\t\t\t\t -sfont \"NimbusMono-Regular\" \n"
			<< "\t\t\t\t\t -sfont \"NimbusRomNo9L-Reg\" \n"
			<< "\t\t\t\t\t -sfont \"NimbusSanL-Reg\" \n"
			<< "\t\t\t\t\t -sfont \"URWChanceryL-MediItal\" \n"
			<< "\t-ssize	<FONT_SIZE>\tSpesify the font size of stamp (11, 12, 16...14)\n"
			<< "\t-scolor <FONT_COLOR>\tFont color on CYMK format, min val 0, max val 1 \n"
			<< "\t\t\t\texample: -scolor 0.1x0.2x0.1x0.5 \n"
			<< "\t-sposition <POSITIOn>\tText position for stamp \n"
			<< "\t\t\t\texample: -sposition 25x15 \n"
			<< "\t-stext <TEXT>\t\tText for stamp, text containt space, please \n"
			<< "\t\t\t\tuse \"\\\" before space or text on double quote \n"
		  << "\t-o, --output <PDF>\tSpesify the output (pdf) file \n"
		  << " \n"
		  << "EXAMPLE \n"
		  << "\tSimple usage: \n"
		  << "\t" << name <<" -d dokumen.docx -s stamp.pdf -o hasil.pdf \n"
			<< "\tComplex usage: \n"
		  << "\t" << name <<" -d dokumen.docx -stext \"sedang mencoba\" -o hasil02.pdf -sposition 55x55 -ssize 14 -scolor 0.5x0.5x0.5x0.5 -sfont \"CenturySchL-Roma\" \n"
		  << " \n"
		  << "AUTHOR \n"
		  << "\tAna Nurdiana, S.T. (ananurdiana at gmail dot com) maintains docka. \n"
		  << "\tPlease email to him with question or bug reports. Include in the  \n"
		  << "\tsubject line to ensure successful deliver. Thank you. \n"
		  << " \n"
		  << "\t\t\t\t December, 4 2016 \n"
		  << "";
}

// check file exist
bool file_exists(const string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}

// get current dir
string get_exe_path()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

// split file name
string split(const string& filename, const string& separator){
	string name;
	string ab;
	for (int i = 0; i < filename.length(); i++) {
		ab = filename[i];
		if ( ab == separator ) {
			break;
		}else{
			name = name + filename[i];
		}
	}
	return name;
}

// Change stamp argument
string change_stamp_arg(const string& argument, const string& separator){
	string arg;
	string ab;
	for (int i = 0; i < argument.length(); i++) {
		ab = argument[i];
		if ( ab == separator ) {
			arg = arg + " ";
		}else{
			arg = arg + argument[i];
		}
	}
	return arg;
}

// main program
int main(int argc, char* argv[]){
	if (argc < 2){
		show_usage(argv[0]);
		return 1;
	}
	// variable declaration
	string doc;
	string file_name;
	string stamp;
	string stamp_status;
	string stamp_font;
	string stamp_size;
	string stamp_color;
	string stamp_position;
	string stamp_text;
	string output;
	string cmd;

	// default value
	stamp = "stamp.pdf";
	stamp_status = "create";		// create 	- For create from source
														// file 		- For use stamp from pdf file
	stamp_font = "CenturySchL-Roma";
	stamp_size = "20";
	stamp_color = "0.1x0.2x0.1x0.5";
	stamp_position = "25x15";
	stamp_text = "This is a sample text for stamp.";
	output = "";

	/*
	 * OPTIONS
	 * -h, --help 									Show this help message
	 * -d, --document <DOC>					Spesify the office (docx, doc, xlsx, xls, ppt,
   * 		 													pptx) file
	 * -s, --stamp <PDF>						Spesify the stamp (pdf) file
	 * -ssize	<FONT_SIZE>						Spesify the font size of stamp (11, 12, 16 ... 14 )
	 * -scolor <FONT_COLOR>					Font color on CYMK format, min val 0, max val 1
	 * 															example: -scolor 0.1x0.2x0.1x0.5
	 * -sposition <TEXT_POSITIOn>		Text position for stamp
	 * 															example: -sposition 25x15
	 * -stext <TEXT>								Text for stamp, text containt space, please
	 * 															user "\" before space
	 * -o, --output <PDF>						Spesify the output (pdf) file
	 */
	for(int i=1; i<argc; i++){
		string arg = argv[i];	// put argument in variable
		if ( (arg == "-h") || (arg == "--help") ){
			/*
			 * Argument Help
			 */
			show_usage(argv[0]);
			return 0;
		} else if ( (arg == "-d") || (arg == "--document") ){
			/*
			 * Argument Document
			 * Convert Document to PDF
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				doc = argv[i];
				file_name = split(doc, ".");		// get file name
				// checking file exist or not
				if (!file_exists(doc)) {
					cout << "File '" << doc << "' doesn't exist\n";
					return 1;
				} else {
					// convert document to pdf
					cmd = "soffice --headless --convert-to pdf " + doc;
					system(cmd.c_str());
				}
			} else {
				cout << "-d, --document option requires one argument.\n";
				return 1;
			}
			// argument stamp
		} else if ( (arg == "-s") || (arg == "--stamp") ){
			/*
			 * Argument Stamp
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				stamp = argv[i];
				// checking file exist or not
				if (!file_exists(stamp)) {
					cout << "File '" << stamp << "' doesn't exist\n";
					return 1;
				} else {
					stamp_status = "file";
				}
			} else {
				cout << "-s, --stamp option requires one argument.\n";
				return 1;
			}
		} else if ( (arg == "-sfont") ){
			/*
			 * Argument Stamp Font type
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				stamp_font = argv[i];
				stamp_status = "create";
			} else {
				cout << "-sfont option requires one argument.\n";
				return 1;
			}
		} else if ( (arg == "-ssize") ){
			/*
			 * Argument Stamp Size
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				stamp_size = argv[i];
				stamp_status = "create";
			} else {
				cout << "-ssize option requires one argument.\n";
				return 1;
			}
		} else if ( (arg == "-scolor") ){
			/*
			 * Argument Stamp Color
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				stamp_color = argv[i];
				stamp_status = "create";
			} else {
				cout << "-scolor option requires one argument.\n";
				return 1;
			}
		} else if ( (arg == "-sposition") ){
			/*
			 * Argument Stamp Position
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				stamp_position = argv[i];
				stamp_status = "create";
			} else {
				cout << "-sposition option requires one argument.\n";
				return 1;
			}
		} else if ( (arg == "-stext") ){
			/*
			 * Argument Stamp Size
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				stamp_text = argv[i];
				stamp_status = "create";
			} else {
				cout << "-stext option requires one argument.\n";
				return 1;
			}
		} else if ( (arg == "-o") || (arg == "--output") ){
			/*
			 * Argument Output
			 */
			if (i + 1 < argc){ // checking argument value
				i++;
				output = argv[i];
				// checking file exist or not
				if (file_exists(output)) {
					cout << "File '" << output << "' already exist\n";
					return 1;
				}
			} else {
				cout << "-o, --output option requires one argument.\n";
				return 1;
			}
		}
	}

	// check if output is empty, process will stoped
	if (output == "") {
		cout << "-o, --output option requires one argument.\n";
		return 1;
	}

	// generate stamp
	if (stamp_status == "create") {
		// change color format and position format
		stamp_color = change_stamp_arg(stamp_color, "x");
		stamp_position = change_stamp_arg(stamp_position, "x");

		cout << "generate file stamp from script \n";
		cmd = "gs -o stamp.pdf -sDEVICE=pdfwrite -g5950x8420 -c \"/" + stamp_font + " findfont " + stamp_size + " scalefont setfont\" -c \"" + stamp_color + " setcmykcolor\" -c \"" + stamp_position + " moveto\" -c \"(" + stamp_text + ") show\" -c \"showpage\"";
		system(cmd.c_str());
	} else if (stamp_status == "file") {
		cout << "use existing stamp pdf file \n";
	}

	// combile document and stamp
	cmd = "pdftk " + file_name + ".pdf stamp " + stamp + " output " + output;
	system(cmd.c_str());

	cout << "\nDone...\n";

	return 0;
}
