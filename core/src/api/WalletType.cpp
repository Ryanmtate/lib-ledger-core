// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from currency.djinni

#include "WalletType.hpp"  // my header
#include "enum_from_string.hpp"

namespace ledger { namespace core { namespace api {

std::string to_string(const WalletType& walletType) {
    switch (walletType) {
        case WalletType::BITCOIN: return "BITCOIN";
        case WalletType::ETHEREUM: return "ETHEREUM";
        case WalletType::RIPPLE: return "RIPPLE";
        case WalletType::MONERO: return "MONERO";
        case WalletType::TEZOS: return "TEZOS";
        case WalletType::STELLAR: return "STELLAR";
    };
};
template <>
WalletType from_string(const std::string& walletType) {
    if (walletType == "BITCOIN") return WalletType::BITCOIN;
    else if (walletType == "ETHEREUM") return WalletType::ETHEREUM;
    else if (walletType == "RIPPLE") return WalletType::RIPPLE;
    else if (walletType == "MONERO") return WalletType::MONERO;
    else if (walletType == "TEZOS") return WalletType::TEZOS;
    else return WalletType::STELLAR;
};

std::ostream &operator<<(std::ostream &os, const WalletType &o)
{
    switch (o) {
        case WalletType::BITCOIN:  return os << "BITCOIN";
        case WalletType::ETHEREUM:  return os << "ETHEREUM";
        case WalletType::RIPPLE:  return os << "RIPPLE";
        case WalletType::MONERO:  return os << "MONERO";
        case WalletType::TEZOS:  return os << "TEZOS";
        case WalletType::STELLAR:  return os << "STELLAR";
    }
}

} } }  // namespace ledger::core::api