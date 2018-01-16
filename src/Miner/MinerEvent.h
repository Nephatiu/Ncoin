// Copyright © 2011-2016 The Cryptonote developers
// All Rights Reversed ® GGTM.eu Underground Services
// Distributed under the MIT/X11 software license,
// see http://www.opensource.org/licenses/mit-license.php.

#pragma once

namespace Miner {

enum class MinerEventType: uint8_t {
  BLOCK_MINED,
  BLOCKCHAIN_UPDATED,
};

struct MinerEvent {
  MinerEventType type;
};

} //namespace Miner
