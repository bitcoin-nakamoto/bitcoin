// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <cstdint>

/** 1 MB */
static const uint64_t ONE_MEGABYTE = 1000000;
static const uint64_t MAX_TX_SIZE = ONE_MEGABYTE;
static const uint64_t LEGACY_MAX_BLOCK_SIZE = ONE_MEGABYTE;
static const uint64_t DEFAULT_MAX_BLOCK_SIZE = 8 * ONE_MEGABYTE;
static const int64_t MAX_BLOCK_SIGOPS_PER_MB = 20000;
static const uint64_t MAX_TX_SIGOPS_COUNT = 20000;
static const int COINBASE_MATURITY = 100;

/** Flags for nSequence and nLockTime locks */
/** Interpret sequence numbers as relative lock-time constraints. */
static constexpr unsigned int LOCKTIME_VERIFY_SEQUENCE = (1 << 0);
/** Use GetMedianTimePast() instead of nTime for end point timestamp. */
static constexpr unsigned int LOCKTIME_MEDIAN_TIME_PAST = (1 << 1);

inline uint64_t GetMaxBlockSigOpsCount(uint64_t blockSize) {
    auto nSize = 1 + ((blockSize - 1) / ONE_MEGABYTE);
    return nSize * MAX_BLOCK_SIGOPS_PER_MB;
}

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
