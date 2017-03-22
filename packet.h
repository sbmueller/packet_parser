#ifndef PACKET_PARSER_PACKET_H
#define PACKET_PARSER_PACKET_H

#include <vector>
#include <string>
#include <cstdint>

#define POLY 0xEDB88320

class packet {
private:
  static const unsigned int HDR_LEN = 32;
  static const uint32_t MAGIC_NUMBER = 0;

  unsigned int hex2int(std::string hexval);
  char hex2char(std::string hexval);
  bool check_header(std::string data);
  void set_payload(std::string data);
  uint32_t crc32c(uint32_t crc, uint8_t *buf, size_t len);
  bool check_crc32();

public:
  packet(std::string& data);
  std::string raw_packet;
  struct {
    unsigned int hdr1 : 8;
    unsigned int hdr2 : 8;
    unsigned int src: 32;
    unsigned int dst: 32;
    unsigned int crc: 32;
    unsigned int flags: 8;
    unsigned int len: 8;
  } header;
  std::vector<uint8_t> payload;
  bool valid;
  bool urgent();
  bool unknown();
  bool ack();
  bool ack_rqst();
  bool reset();
};

#endif //PACKET_PARSER_PACKET_H
