// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef XSYN_POLICY_FEERATE_H
#define XSYN_POLICY_FEERATE_H

#include "serialize.h"

#include "amount.h"
#include "utilstrencodings.h"

#include <stdlib.h>
#include <string>

extern const std::string CURRENCY_UNIT;

/**
 * Fee rate in satoshis per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nSatoshisPerK; // unit is satoshis-per-1,000-bytes
public:
    /** Fee rate of 0 satoshis per kB */
    CFeeRate() : nSatoshisPerK(0) { }
    explicit CFeeRate(const CAmount& _nSatoshisPerK): nSatoshisPerK(_nSatoshisPerK) { }
    /** Constructor for a fee rate in satoshis per kB. The size in bytes must not exceed (2^63 - 1)*/
    CFeeRate(const CAmount& nFeePaid, size_t nBytes);
    CFeeRate(const CFeeRate& other) { nSatoshisPerK = other.nSatoshisPerK; }
    /**
     * Return the fee in satoshis for the given size in bytes.
     */
    CAmount GetFee(size_t nBytes) const;
    /**
     * Return the fee in satoshis for a size of 1000 bytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK < b.nSatoshisPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK > b.nSatoshisPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK == b.nSatoshisPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK <= b.nSatoshisPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK >= b.nSatoshisPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nSatoshisPerK += a.nSatoshisPerK; return *this; }
    std::string ToString() const;

	IMPLEMENT_SERIALIZE
    (
        READWRITE(nSatoshisPerK);
    )
};

#endif //  XSYN_POLICY_FEERATE_H
