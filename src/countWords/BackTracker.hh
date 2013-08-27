/**
 ** Copyright (c) 2011 Illumina, Inc.
 **
 **
 ** This software is covered by the "Illumina Non-Commercial Use Software
 ** and Source Code License Agreement" and any user of this software or
 ** source file is bound by the terms therein (see accompanying file
 ** Illumina_Non-Commercial_Use_Software_and_Source_Code_License_Agreement.pdf)
 **
 ** This file is part of the BEETL software package.
 **
 ** Citation: Markus J. Bauer, Anthony J. Cox and Giovanna Rosone
 ** Lightweight BWT Construction for Very Large String Collections.
 ** Proceedings of CPM 2011, pp.219-231
 **
 **/

#ifndef INCLUDED_BACKTRACKER_HH
#define INCLUDED_BACKTRACKER_HH

#include "BwtReader.hh"
#include "IntervalHandlerBase.hh"
#include "LetterCount.hh"
#include "RangeStore.hh"
#include "Types.hh"
#include "libzoo/util/Logger.hh"

#include <string>

using namespace std;


typedef bool AlphabetFlag[alphabetSize];

// BackTracker class implements the backward search and takes its
// cue from IntervalHandler as to whether to continue down a particular
// branch of the search tree
struct BackTracker
{
    BackTracker( BwtReaderBase *inBwtA, BwtReaderBase *inBwtB,
                 LetterNumber &currentPosA, LetterNumber &currentPosB,
                 RangeStoreExternal &rA, RangeStoreExternal &rB,
                 LetterCount &countsSoFarA, LetterCount &countsSoFarB,
                 int minOcc, const int maxLength, const string &subset, const int cycle,
                 const bool doesPropagateBkptToSeqNumInSetA,
                 const bool doesPropagateBkptToSeqNumInSetB,
                 const bool noComparisonSkip
               );

    void skipIfNecessary( const Range &thisRange,
                          LetterNumber &currentPos,
                          BwtReaderBase &inBwt,
                          LetterCount &countsSoFar );

    void operator() ( int i, string &thisWord, IntervalHandlerBase &intervalHandler );

    BwtReaderBase *inBwtA_;
    BwtReaderBase *inBwtB_;

    LetterNumber &currentPosA_;
    LetterNumber &currentPosB_;

    RangeStoreExternal &rA_;
    RangeStoreExternal &rB_;
    LetterCount &countsSoFarA_;
    LetterCount &countsSoFarB_;

    int minOcc_;
    int maxLength_;
    const string &subset_;
    const int cycle_;

    LetterNumber numRanges_;
    LetterNumber numSingletonRanges_;

    AlphabetFlag propagateIntervalA_;
    AlphabetFlag propagateIntervalB_;

    const bool doesPropagateBkptToSeqNumInSetA_;
    const bool doesPropagateBkptToSeqNumInSetB_;
    const bool noComparisonSkip_;
};

#endif

