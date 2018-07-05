// Copyright (c) 2009-2017 The Bitcoin developers
// Copyright (c) 2017 ION Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "proofs.h"
#include "txdb.h"
#include "main.h"
#include "uint256.h"

static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    bool fEnabled = true;

    typedef std::map<int, uint256> MapCheckpoints;
    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0, Params().HashGenesisBlock())
        (1000, uint256("0x47aebcfdd0b3f23e8cc153ed322e53d1706822784942726adae2c18de4cb1408"))
        (10000, uint256("0x0c56aa36c427c65fc6602e821c0b34495b73590b308a71457718b39e185e31e3"))
        (30000, uint256("0x066d6a599e6b67fbc37ef0cfc16af008633c1c07d522e1ab957a534cf2cbd700"))
        (41050, uint256("0x629f128f0bfac9be34da83b54e74e57095f2f272824f797a4d644d8cd4634c08"))
        (56100, uint256("0x1dbb9a6e879083698cc7b9e90c7f27d69133ba348138e5029d12f87a7349f557"))
        (70000, uint256("0x232118fe6997d31622883b906c938070f754b2c90414e44bc589ec5feab4edda"))
        (1212152, uint256("0x77022783d76d55c49aa3a0b4bdafa4bdd58c1eb54fe98ee08b0d3cd38a691ab7"))
        (1237348, uint256("0x3e6004f85b808c3163ace0655270ff3eafc07e3fac5f84dd1c2434379369f4bb"))
        (1660115, uint256("0x941040ebb584436208ecd233e8349e757e9a8ad870b4f2301a08ba4d51ad71fa"))
        (1812381, uint256("0x22e25a85559e520634fe6e01406b8ad25d51f50cc6809ca316b041e4a7c2b76c"))
        (1826654, uint256("0x736555621b5de69a4050fee0766bf5923b6beb49b63457161b0a54e6e592fe29"))
        (1832632, uint256("0x744d9f4103e653cee3271350eda6b8171321dbc8729075f615cbf9a53f0a25bc"))
        (1836211, uint256("0x6600a48da239588af095540fd2949791e60daa7756df0fd577155160fc686311"));


    static MapCheckpoints mapCheckpointsTestnet;   

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);
        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);
        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);
        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
