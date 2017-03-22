#include "packet.h"
#include <sstream>
#include <iostream>
#include <cstring>

packet::packet(std::string &data) {
  // check if packet is at least long enough for header
  raw_packet = data;
  if(check_header(data)) {
    header.hdr1 = hex2int(data.substr(0, 2));
    header.hdr2 = hex2int(data.substr(2, 2));
    header.src = hex2int(data.substr(4, 8));
    header.dst = hex2int(data.substr(12, 8));
    header.crc = hex2int(data.substr(20, 8));
    header.flags = hex2int(data.substr(28, 2));
    header.len = hex2int(data.substr(30, 2));
    // checks if payload length is same as in header
    set_payload(data);
    // couldn't produce a valid CRC check here. Which polynomial? Which data is checked? ...
    //valid = check_crc32();
  }
}

unsigned int
packet::hex2int(std::string hexval) {
  // stringstream allows variable length of HEX values
  std::stringstream ss;
  unsigned int result;
  ss << hexval;
  ss >> std::hex >> result;
  return result;
}

char
packet::hex2char(std::string hexval) {
  unsigned int val = hex2int(hexval);
  return static_cast<uint8_t>(val);
}

bool
packet::check_header(std::string data) {
  valid = data.size() >= HDR_LEN; // min length on one packet
  return valid;
}

// this is copied from stack overflow
// http://stackoverflow.com/questions/27939882/fast-crc-algorithm
uint32_t
packet::crc32c(uint32_t crc, uint8_t *buf, size_t len) {
  int k;
  crc = ~crc;
  while (len--) {
    crc ^= *buf++;
    for (k = 0; k < 8; k++)
      crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
  }
  return ~crc;
}

bool
packet::check_crc32() {
  // packet should be valid before crc32 check
  if(payload.size() > 0 && valid) {
    //std::cout << std::hex << crc32c(header.crc, payload.data(), payload.size()) << std::endl;
    return crc32c(header.crc, payload.data(), payload.size()) == MAGIC_NUMBER;
  }
  return false;
}

void
packet::set_payload(std::string data) {
  // packet should be valid to get payload
  if(!valid) {
    return;
  }
  std::string fresh_payload = data.substr(HDR_LEN, data.size()-HDR_LEN);
  // compare desired len in bytes with actual len in 4-bit
  if(header.len*2 != fresh_payload.size() && fresh_payload.size() > 510) {
    valid = false;
  }
  // fill payload vector with data
  if(fresh_payload.size() > 0) {
    payload.reserve(fresh_payload.size());
    for (int i = 0; i < fresh_payload.size() - 1; i += 2) {
      payload.push_back(hex2char(fresh_payload.substr(i, 2)));
    }
  }
}

bool
packet::unknown() {
  return (header.flags & 16) == 16;
}

bool
packet::urgent() {
  return (header.flags & 4) == 4;
}

bool
packet::ack() {
  return (header.flags & 1) == 1;
}

bool
packet::ack_rqst() {
  return (header.flags & 2) == 2;
}
bool
packet::reset() {
  return (header.flags & 8) == 8;
}