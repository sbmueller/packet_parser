#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argc, char* argv[]) {
  // check if filename was given by user
  if(argc < 2) {
    // tell user how to use me
    std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
    return 1;
  }
  parser packet_parser;
  packet_parser.load_packets_from_file(argv[1]);
  std::vector<std::string> data = packet_parser.get_packets();
  for(int i = 0; i < data.size(); i++) {
    std::cout << data[i] << std::endl;
  }

  return 0;
}
