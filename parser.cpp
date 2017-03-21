#include <iostream>
#include <fstream>
#include "parser.h"

parser::parser() {}

void
parser::load_packets_from_file(std::string filepath) {
  std::string line;
  std::ifstream received(filepath);
  if (received.is_open())
  {
    while ( getline (received,line) )
    {
      d_packets.push_back(line);
    }
    received.close();
    //convert hex data to binary
    hex_2_bin();
  }
  else {
    std::cout << "Problem opening packet file!" << std::endl;
  }
}

void
parser::hex_2_bin() {
  for(unsigned int p = 0; p < d_packets.size(); p++) {
    std::string bits = "";
    for(int h = 0; h < d_packets[p].size(); h++)
    {
        switch(d_packets[p][h])
        {
        case '0': bits.append("0000"); break;
        case '1': bits.append("0001"); break;
        case '2': bits.append("0010"); break;
        case '3': bits.append("0011"); break;
        case '4': bits.append("0100"); break;
        case '5': bits.append("0101"); break;
        case '6': bits.append("0110"); break;
        case '7': bits.append("0111"); break;
        case '8': bits.append("1000"); break;
        case '9': bits.append("1001"); break;
        case 'A': bits.append("1010"); break;
        case 'B': bits.append("1011"); break;
        case 'C': bits.append("1100"); break;
        case 'D': bits.append("1101"); break;
        case 'E': bits.append("1110"); break;
        case 'F': bits.append("1111"); break;
        }
    }
    d_packets[p] = bits;
  }
}

std::vector<std::string>
parser::get_packets() {
  return d_packets;
}
