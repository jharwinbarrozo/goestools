#include <signal.h>

#include <iostream>

#include "config.h"
#include "decoder.h"
#include "demodulator.h"
#include "monitor.h"
#include "options.h"
#include "publisher.h"

static bool sigint = false;

static void signalHandler(int signum) {
  fprintf(stderr, "Signal caught, exiting!\n");
  sigint = true;
}

int main(int argc, char** argv) {
  auto opts = parseOptions(argc, argv);
  auto config = Config::load(opts.config);

  // Convert satellite option string option to enum
  Demodulator::Satellite satellite;
  if (config.demodulator.satellite == "GK-2A") {
    satellite = Demodulator::GK2A;
  } else {
    std::cerr
      << "Invalid satellite name: "
      << config.demodulator.satellite
      << std::endl;
    exit(1);
  }

  // Convert downlink option string option to enum
  Demodulator::Downlink downlink;
  if (config.demodulator.downlink == "lrit") {
    downlink = Demodulator::LRIT;
  } else if (config.demodulator.downlink == "hrit") {
    downlink = Demodulator::HRIT;
  } else {
    std::cerr
      << "Invalid downlink type: "
      << config.demodulator.downlink
      << std::endl;
    exit(1);
  }

  Demodulator demod(satellite, downlink);
  demod.initialize(config);

  Decoder decode(demod.getSoftBitsQueue());
  decode.initialize(config);

  Monitor monitor(opts.verbose, opts.interval);
  monitor.initialize(config);

  // Install signal handler
  #ifndef _WIN32
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
  #endif

  #ifdef _WIN32
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
  #else
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
  #endif

  demod.start();
  decode.start();
  monitor.start();

  while (!sigint) {
    pause();
  }

  demod.stop();
  decode.stop();
  monitor.stop();

  return 0;
}
