#ifndef BITCOIN_DSTENCODE_H
#define BITCOIN_DSTENCODE_H

// key.h and pubkey.h are not used here, but gcc doesn't want to instantiate
// CTxBCHDestination if types are unknown
#include "key.h"
#include "pubkey.h"
#include "script/standard.h"
#include <string>

class CChainParams;

std::string EncodeBCHDestination(const CTxBCHDestination &dest, bool fUseLegacy = false);

CTxBCHDestination DecodeBCHDestination(const std::string &addr, const CChainParams& params);

bool IsValidBCHDestinationString(const std::string &addr,
                              const CChainParams &params);

// Temporary workaround. Don't rely on global state, pass all parameters in new
// code.
//std::string EncodeBCHDestination(const CTxBCHDestination &, bool fUseLegacy);
//bool IsValidBCHDestinationString(const std::string &addr);

// TODO remove
CTxBCHDestination DecodeLegacyAddr(const std::string& str, const CChainParams& params);

std::string EncodeLegacyAddr(const CTxBCHDestination &dest, const CChainParams& params);

#endif // BITCOIN_DSTENCODE_H
