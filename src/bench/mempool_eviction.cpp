// Copyright (c) 2011-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bench/bench.h>
#include <policy/policy.h>
#include <txmempool.h>

#include <list>
#include <vector>

// TODO
/*
static void AddTx(const CTransaction& tx, const CAmount& nFee, CTxMemPool& pool)
{
    int64_t nTime = 0;
    unsigned int nHeight = 1;
    bool spendsCoinbase = false;
    unsigned int sigOpCost = 4;
    LockPoints lp;
    pool.addUnchecked(tx.GetHash(), CTxMemPoolEntry(
                                        MakeTransactionRef(tx), nFee, nTime, nHeight,
                                        spendsCoinbase, sigOpCost, lp));
}
*/

// Right now this is only testing eviction performance in an extremely small
// mempool. Code needs to be written to generate a much wider variety of
// unique transactions for a more meaningful performance measurement.
static void MempoolEviction(benchmark::State& state)
{
    // TODO
}

BENCHMARK(MempoolEviction, 41000);
