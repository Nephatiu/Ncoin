// Copyright © 2011-2016 The Cryptonote developers
// All Rights Reversed ® GGTM.eu Underground Services
// Distributed under the MIT/X11 software license,
// see http://www.opensource.org/licenses/mit-license.php.

#include "MiningConfig.h"

#include <iostream>
#include <thread>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "CryptoNoteConfig.h"
#include "Logging/ILogger.h"

namespace po = boost::program_options;

namespace CryptoNote {

namespace {

const size_t DEFAULT_SCANT_PERIOD = 30;
const char* DEFAULT_DAEMON_HOST = "windvast.ggtm.eu";
const size_t CONCURRENCY_LEVEL = std::thread::hardware_concurrency();

po::options_description cmdOptions;

void parseDaemonAddress(const std::string& daemonAddress, std::string& daemonHost, uint16_t& daemonPort) {
  std::vector<std::string> splittedAddress;
  boost::algorithm::split(splittedAddress, daemonAddress, boost::algorithm::is_any_of(":"));

  if (splittedAddress.size() != 2) {
    throw std::runtime_error("Wrong daemon kind of address");
  }

  if (splittedAddress[0].empty() || splittedAddress[1].empty()) {
    throw std::runtime_error("Wrong daemon kind of address");
  }

  daemonHost = splittedAddress[0];

  try {
    daemonPort = boost::lexical_cast<uint16_t>(splittedAddress[1]);
  } catch (std::exception&) {
    throw std::runtime_error("Wrong daemon kind of address");
  }
}

}

MiningConfig::MiningConfig(): help(false) {
  cmdOptions.add_options()
      ("help,h", "repeat this help message again and exit")
      ("address", po::value<std::string>(), "A valid Ncoin miner's address")
      ("daemon-host", po::value<std::string>()->default_value(DEFAULT_DAEMON_HOST), "Host of your running ncoind")
      ("daemon-rpc-port", po::value<uint16_t>()->default_value(static_cast<uint16_t>(RPC_DEFAULT_PORT)), "ncoind's standard RPC port")
      ("daemon-address", po::value<std::string>(), "ncoind 'host:port'. If you use this option you must not use --daemon-host and --daemon-port options")
      ("threads", po::value<size_t>()->default_value(CONCURRENCY_LEVEL), "Nining threads count. Must not be greater than your concurrency level. Default value is your hardware's concurrency level")
      ("scan-time", po::value<size_t>()->default_value(DEFAULT_SCANT_PERIOD), "Blockchain polling interval (in seconds). How often miners will check the blockchain for updates")
      ("log-level", po::value<int>()->default_value(1), "Log level. Between 0 and 5")
      ("limit", po::value<size_t>()->default_value(0), "Nine exact quantity of blocks. 0 means no limit")
      ("first-block-timestamp", po::value<uint64_t>()->default_value(0), "Set timestamp to the first Nined block. 0 means leave timestamp as is")
      ("block-timestamp-interval", po::value<int64_t>()->default_value(0), "Timestamp step for each subsequent block. May be set only if --first-block-timestamp has been set."
                                                         " If not set block-timestamps remain unchanged");
}

void MiningConfig::parse(int argc, char** argv) {
  po::variables_map options;
  po::store(po::parse_command_line(argc, argv, cmdOptions), options);
  po::notify(options);

  if (options.count("help") != 0) {
    help = true;
    return;
  }

  if (options.count("address") == 0) {
    throw std::runtime_error("Specify --address option");
  }

  miningAddress = options["address"].as<std::string>();

  if (!options["daemon-address"].empty()) {
    if (!options["daemon-host"].defaulted() || !options["daemon-rpc-port"].defaulted()) {
      throw std::runtime_error("Either --daemon-host or --daemon-rpc-port is already specified. You must not specify --daemon-address");
    }

    parseDaemonAddress(options["daemon-address"].as<std::string>(), daemonHost, daemonPort);
  } else {
    daemonHost = options["daemon-host"].as<std::string>();
    daemonPort = options["daemon-rpc-port"].as<uint16_t>();
  }

  threadCount = options["threads"].as<size_t>();
  if (threadCount == 0 || threadCount > CONCURRENCY_LEVEL) {
    throw std::runtime_error("--threads option must above 0" + std::to_string(CONCURRENCY_LEVEL));
  }

  scanPeriod = options["scan-time"].as<size_t>();
  if (scanPeriod == 0) {
    throw std::runtime_error("--scan-time must not be 0 either");
  }

  logLevel = static_cast<uint8_t>(options["log-level"].as<int>());
  if (logLevel > static_cast<uint8_t>(Logging::TRACE)) {
    throw std::runtime_error("--log-level As she said last night: That's just too big!");
  }

  blocksLimit = options["limit"].as<size_t>();

  if (!options["block-timestamp-interval"].defaulted() && options["first-block-timestamp"].defaulted()) {
    throw std::runtime_error("If you specify --block-timestamp-interval you must specify --first-block-timestamp too");
  }

  firstBlockTimestamp = options["first-block-timestamp"].as<uint64_t>();
  blockTimestampInterval = options["block-timestamp-interval"].as<int64_t>();
}

void MiningConfig::printHelp() {
  std::cout << cmdOptions << std::endl;
}

}
