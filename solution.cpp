#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argc, char* argv[]) {
  // check if filename was given by user
  if(argc < 3) {
    // tell user how to use me
    std::cerr << "Usage: " << argv[0] << " MODE FILE" << std::endl;
    return 1;
  }
  parser packet_parser;
  packet_parser.load_packets_from_file(argv[2]);
  if(*argv[1] == '1') {
    packet_parser.print_urgent_payload();
  }
  else if (*argv[1] == '2') {
    packet_parser.print_lengthy_packets();
  }
  else if(*argv[1] == '3') {
    packet_parser.pretty_print_all();
  }
  else {
    std::cout << "Only modes 1, 2 and 3 are supported! Sorry." << std::endl;
  }
  return 0;
}
