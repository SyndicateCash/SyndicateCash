// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef XSYN_CONSENSUS_CONSENSUS_H
#define XSYN_CONSENSUS_CONSENSUS_H

#include <stdint.h>

/** The maximum allowed size for a serialized block, in bytes (network rule) */
static const unsigned int MAX_BLOCK_SIZE = 20000000;
/** The maximum allowed number of signature check operations in a block (network rule) */
static const unsigned int MAX_BLOCK_SIGOPS = MAX_BLOCK_SIZE/50;



/** The time of  the fork */
static const unsigned int FORK_TIME = 1525827600; // Human time (GMT): Wednesday, May 9, 2018 1:00:00 AM


#endif // XSYN_CONSENSUS_CONSENSUS_H
