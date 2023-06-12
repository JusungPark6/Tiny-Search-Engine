#!/bin/bash

make

# Base Test
echo
echo ===== Base Test =====
echo
./querier ../indexer/testDir/letters-10 testIndex.index < test1.txt
echo
echo Expected query [ for and home ]:
echo Score: 6 / docID: 6 
echo Score: 4 / docID: 2 
echo Score: 2 / docID: 1
echo Score: 1 / docID: 3
echo Score: 1 / docID: 4 
echo Score: 1 / docID: 5
echo Score: 1 / docID: 7 
echo Score: 1 / docID: 8 
echo Score: 1 / docID: 9 
echo
echo Expected [ first or playground or coding ]:
echo Score: 8 / docID: 8 
echo Score: 5 / docID: 3 
echo Score: 1 / docID: 6 
echo Score: 1 / docID: 1
echo 
echo Expected [ first or playground and search ]:
echo Score: 8 / docID: 8
echo Score: 5 / docID: 3
echo

# Spaces in input tests
echo ===== Spaces in input tests =====
echo
./querier ../indexer/testDir/letters-10 testIndex.index < test2.txt
echo
echo Query 1: 
echo Spaces before input
echo 
echo Query 2: 
echo Spaces between inputs
echo
echo Query 3: 
echo Spaces after inputs
echo
echo Query 4: 
echo Spaces before, between and after inputs
echo

# Non-char/space in input tests
echo ===== Non-char/space in input tests =====
echo
./querier ../indexer/testDir/letters-10 testIndex.index < test3.txt
echo 
echo Should produce 3 errors
echo

# Adjacent Operator tests
echo ===== Adjacent Operator Tests =====
echo
./querier ../indexer/testDir/letters-10 testIndex.index < test4.1.txt
echo and or test
./querier ../indexer/testDir/letters-10 testIndex.index < test4.2.txt
echo or or test
./querier ../indexer/testDir/letters-10 testIndex.index < test4.3.txt
echo and and test
./querier ../indexer/testDir/letters-10 testIndex.index < test4.4.txt
echo or and test
echo

# Start/end Operator test
echo ===== Start/End Operator Tests =====
echo
echo and before test
./querier ../indexer/testDir/letters-10 testIndex.index < test5.1.txt
echo or before test
./querier ../indexer/testDir/letters-10 testIndex.index < test5.2.txt
echo or after test
./querier ../indexer/testDir/letters-10 testIndex.index < test5.3.txt
echo and after test
./querier ../indexer/testDir/letters-10 testIndex.index < test5.4.txt
echo 

# Invalid Args tests
echo ===== Invalid Args Test =====
echo
echo invalid crawler dir test
./querier ../indexer/testDir/lers-0 testIndex.index
echo invalid index test
./querier ../indexer/testDir/letters-10 tesawefdex.index 
echo

# No Matching Documents test
echo ===== No matching Docs Test =====
echo
./querier ../indexer/testDir/letters-10 testIndex.index < test6.txt