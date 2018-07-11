// Copyright (c) 2017 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "dstencode.h"
#include "base58.h"
#include "cashaddrenc.h"
#include "chainparams.h"
#include "script/standard.h"

#include <iostream>

std::string EncodeBCHDestination(const CTxBCHDestination &dest, bool fUseLegacy) {
    const CChainParams &params = Params();
    if (fUseLegacy)
        return EncodeLegacyAddr(dest, params);
    else
        return EncodeCashAddr(dest, params);
}

CTxBCHDestination DecodeBCHDestination(const std::string &addr,
                                 const CChainParams &params) {

    std::cout << "dstencode DecodeBCHDestination 0\n";

    CTxBCHDestination dst = DecodeCashAddr(addr, params);
    if (IsValidBCHDestination(dst)) {
    std::cout << "dstencode DecodeBCHDestination 1\n";
        return dst;
    }
    std::cout << "dstencode DecodeBCHDestination 2\n";
    return DecodeLegacyAddr(addr, params);
}

bool IsValidBCHDestinationString(const std::string &addr,
                              const CChainParams &params) {
    return IsValidBCHDestination(DecodeBCHDestination(addr, params));
}

CTxBCHDestination DecodeLegacyAddr(const std::string& str, const CChainParams& params) {
    std::vector<uint8_t> data;
    uint160 hash;
    if (!DecodeBase58Check(str, data)) {
        return CNoDestination();
    }
    // Base58Check decoding
    const std::vector<uint8_t> &pubkey_prefix =
        params.Base58Prefix(CChainParams::PUBKEY_ADDRESS);
    if (data.size() == 20 + pubkey_prefix.size() &&
        std::equal(pubkey_prefix.begin(), pubkey_prefix.end(), data.begin())) {
        memcpy(hash.begin(), &data[pubkey_prefix.size()], 20);
        return CKeyID(hash);
    }
    const std::vector<uint8_t> &script_prefix =
        params.Base58Prefix(CChainParams::SCRIPT_ADDRESS);
    if (data.size() == 20 + script_prefix.size() &&
        std::equal(script_prefix.begin(), script_prefix.end(), data.begin())) {
        memcpy(hash.begin(), &data[script_prefix.size()], 20);
        return CScriptID(hash);
    }
    return CNoDestination();
}

namespace {
class DestinationEncoder : public boost::static_visitor<std::string> {
private:
    const CChainParams &m_params;

public:
    DestinationEncoder(const CChainParams &params) : m_params(params) {}

    std::string operator()(const CKeyID &id) const {
        std::vector<uint8_t> data =
            m_params.Base58Prefix(CChainParams::PUBKEY_ADDRESS);
        data.insert(data.end(), id.begin(), id.end());
        return EncodeBase58Check(data);
    }

    std::string operator()(const CScriptID &id) const {
        std::vector<uint8_t> data =
            m_params.Base58Prefix(CChainParams::SCRIPT_ADDRESS);
        data.insert(data.end(), id.begin(), id.end());
        return EncodeBase58Check(data);
    }

    std::string operator()(const CNoDestination &no) const { return ""; }
};
}

std::string EncodeLegacyAddr(const CTxBCHDestination &dest,
                             const CChainParams &params) {
    return boost::apply_visitor(DestinationEncoder(params), dest);
}

