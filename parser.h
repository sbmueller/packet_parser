#ifndef PACKET_PARSER_PARSER_H
#define PACKET_PARSER_PARSER_H

#include <string>
#include <vector>
#include "packet.h"

class parser {
  private:
    std::vector<packet> d_packets;
  public:
    parser();
    void load_packets_from_file(std::string filepath);
    void print_urgent_payload();
    void print_lengthy_packets();
    void pretty_print(int packet);
    void pretty_print_all();
  };

#endif //PACKET_PARSER_PARSER_H