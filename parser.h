#include <string>
#include <vector>

class parser {
  private:
    std::vector<std::string> d_packets;
    void hex_2_bin();
  public:
    parser();
    void load_packets_from_file(std::string filepath);

    std::vector<std::string> get_packets();
  };
