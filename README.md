This is the reference code for the [Ncoin](http://ncoin.ggtm.eu) CryptoCurrency.

**1. Total money supply** (src/CryptoNoteConfig.h)

48.484.848.484,00000000 NCN

**2. Emission curve** (src/CryptoNoteConfig.h)

30

**3. Difficulty target** (src/CryptoNoteConfig.h)

300

**4. Default ports for P2P and RPC networking** (src/CryptoNoteConfig.h)

P2P: 48537
RPC: 48137

**5. Network identifier** (src/P2p/P2pNetworks.h)

0x6c, 0x75, 0x76, 0x73, 0x6f, 0x66, 0x69, 0x65, 0x76, 0x65, 0x72, 0x76, 0x6c, 0x6f, 0x65, 0x74

**6. Seed nodes** (src/CryptoNoteConfig.h)

servacer.ggtm.eu:48537
lenonine.ggtm.eu:48537

**7. Minimum transaction fee** (src/CryptoNoteConfig.h)

100000

**8. Penalty free block size** (src/CryptoNoteConfig.h)

25000

**9 Address prefix** (src/CryptoNoteConfig.h)

0x1481 // "Nc"

---

**#TODO#**

**TD Build the binaries with blank genesis tx hex** (src/CryptoNoteConfig.h)

You should leave `const char GENESIS_COINBASE_TX_HEX[]` blank and compile the binaries without it.

Example:
```
const char GENESIS_COINBASE_TX_HEX[] = "";
```

**TD Start the daemon to print out the genesis block**

Run your daemon with `--print-genesis-tx` argument. It will print out the genesis block coinbase transaction hash.

Example:
```
furiouscoind --print-genesis-tx
```

**TD Copy the printed transaction hash** (src/CryptoNoteConfig.h)

Copy the tx hash that has been printed by the daemon to `GENESIS_COINBASE_TX_HEX` in `src/CryptoNoteConfig.h`

Example:
```
const char GENESIS_COINBASE_TX_HEX[] = "013c01ff0001ffff...785a33d9ebdba68b0";
```

**TD Recompile the binaries**

Recompile everything again. Your coin code is ready now. Make an announcement for the potential users and enjoy!

## Building Ncoin

### On *nix

Dependencies: GCC 4.7.3 or later, CMake 2.8.6 or later, and Boost 1.55.

You may download them from:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternatively, it may be possible to install them using a package manager.

To build, change to a directory where this file is located, and run `make`. The resulting executables can be found in `build/release/src`.

**Advanced options:**

* Parallel build: run `make -j<number of threads>` instead of `make`.
* Debug build: run `make build-debug`.
* Test suite: run `make test-release` to run tests in addition to building. Running `make test-debug` will do the same to the debug version.
* Building with Clang: it may be possible to use Clang instead of GCC, but this may not work everywhere. To build, run `export CC=clang CXX=clang++` before running `make`.

### On Windows
Dependencies: MSVC 2013 or later, CMake 2.8.6 or later, and Boost 1.55. You may download them from:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

To build, change to a directory where this file is located, and run theas commands: 
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
```

And then do Build.
Good luck!
