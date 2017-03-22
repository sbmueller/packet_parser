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
      d_packets.push_back(packet(line));
    }
    received.close();
  }
  else {
    throw std::runtime_error("Problem opening packet file!");
  }
}

void
parser::print_urgent_payload() {
  std::cout <<  "*************************************************" << std::endl <<
                "**** Printing valid packets with Urgent flag ****" << std::endl <<
                "*************************************************" << std::endl;
  for (int p = 0; p < d_packets.size(); ++p) {
    // packet is urgent and valid and has payload
    if(d_packets[p].valid && d_packets[p].payload.size() > 0 && d_packets[p].urgent()) { // pick 3rd LSB
      std::cout << std::dec << "----------------------------- Packet " << p+1 << " ---------------------------" << std::endl;
      for (int h = 0; h < d_packets[p].payload.size(); ++h) {
        std::cout << std::uppercase << std::hex << static_cast<unsigned int>(d_packets[p].payload[h]);
      }
      std::cout << std::endl << std::endl;
    }
  }
}

void
parser::print_lengthy_packets() {
  std::cout <<  "********************************************************************" << std::endl <<
            "**** Printing packets with payload length >= 10 && Unknown flag ****" << std::endl <<
            "********************************************************************" << std::endl;
  for (int p = 0; p < d_packets.size(); ++p) {
    // packet has payload of length >= 10 and has Unknown flag set
    if(d_packets[p].payload.size() >= 10 && d_packets[p].unknown()) { // pick 5th LSB
      pretty_print(p);
    }
  }
}

void
parser::pretty_print(int packet) {
  if(d_packets.size() <= packet) {
    std::cout << "Packet " << packet << " does not exist!" << std::endl;
    return;
  }
  std::cout << "********************************** Packet " << std::dec << packet+1 << " *****************************" << std::endl;
  if(!d_packets[packet].valid) {
    std::cout << "******************************* PACKET NOT VALID **************************" << std::endl;
  }
  std::string props = "";
  if((d_packets[packet].header.flags & 16) == 16) {props += "unknown, ";}
  if((d_packets[packet].header.flags & 8) == 8) {props += "reset, ";}
  if((d_packets[packet].header.flags & 4) == 4) {props += "urgent, ";}
  if((d_packets[packet].header.flags & 2) == 2) {props += "ack rqst, ";}
  if((d_packets[packet].header.flags & 1) == 1) {props += "ack, ";}
  if(props.size() > 0) { props = props.substr(0, props.size()-2);}
  std::cout << "Props  -| " << props << std::endl;
  std::cout << "        |----------------------------------------------------------------" << std::endl;
  std::cout << "Header -| [hdr1]  " << std::uppercase << std::hex << d_packets[packet].header.hdr1 << std::endl;
  std::cout << "        | [hdr2]  " << std::uppercase << std::hex << d_packets[packet].header.hdr2 << std::endl;
  std::cout << "        | [src]   " << std::uppercase << std::hex << d_packets[packet].header.src << std::endl;
  std::cout << "        | [dst]   " << std::uppercase << std::hex << d_packets[packet].header.dst << std::endl;
  std::cout << "        | [crc]   " << std::uppercase << std::hex << d_packets[packet].header.crc << std::endl;
  std::cout << "        | [flags] " << std::uppercase << std::hex << d_packets[packet].header.flags << std::endl;
  std::cout << "        | [len]   " << std::uppercase << std::hex << d_packets[packet].header.len << std::endl;
  std::cout << "        |----------------------------------------------------------------" << std::endl;
  std::cout << "Payload-| ";
  for (int h = 0; h < d_packets[packet].payload.size(); ++h) {
    std::cout << std::uppercase << std::hex << static_cast<unsigned int>(d_packets[packet].payload[h]);
  }
  std::cout << std::endl << std::endl;
}

void
parser::pretty_print_all() {
  for (int i = 0; i < d_packets.size(); ++i) {
    pretty_print(i);
  }
}
