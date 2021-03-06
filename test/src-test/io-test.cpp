#include <cmath>
#include <cassert>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

#include "spdlog/spdlog.h"

#include "read_nrg.h"
#include "write_nrg.h"

#include "system.h"


namespace {

static std::vector<bblock::System> systems;

} // namespace

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  if (argc != 2) {
    std::cerr << "usage: energy h2o_ion.nrg"
              << std::endl;
    return 0;
  }

  auto mylg = spdlog::basic_logger_mt("IoTestMain", "CU.log");
  try {
    std::ifstream ifs(argv[1]);

    if (!ifs){
      mylg->error("could not open the NRG file");
      throw std::runtime_error("could not open the NRG file");
    }

    tools::ReadNrg(argv[1], systems);
  } catch (const std::exception& e) {
    std::cerr << " ** Error ** : " << e.what() << std::endl;
    return 1;
  }

  std::string outfile = "output.nrg";
  const char* fname = outfile.c_str();
  tools::WriteNrg(fname,systems);
  
  return 0;
}
