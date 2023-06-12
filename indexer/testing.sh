# Jusung Park
# CS50 Winter 2023
# testing file for indexer module

make
# Base Test
./indexer ../indexer/testDir/letters-10 ../indexer/testDir/letters-10/test.index

echo "Unit test"
# 1 Unit Test
./indextest ../indexer/testDir/letters-10/test.index ../indexer/testDir/letters-10/testCopy.index
echo "Check ../indexer/testDir/letters-10/testCopy.index to confirm"
echo ""

# 2. no arguments 
echo "No arguments test"
./indexer
if [ $? -ne 0 ]
then
    echo "2. no arguments test passed"
fi
echo ""

# 3. one argument 
echo "One argument test"
./indexer ../indexer/testDir/letters-10/test.index
if [ $? -ne 0 ]
then
    echo "3. one argument test passed"
fi
echo ""

# 4. three or more arguments 
./indexer ../indexer/testDir/letters-10/ ../indexer/testDir/letters-10/test.index abolubnt
if [ $? -ne 0 ]
then
    echo "4. three argument test passed"
fi
echo ""

# 5. invalid pageDirectory (non-existent path) 
./indexer ../indexer/testDir/letters-1a ../indexer/testDir/letters-10/test.index
if [ $? -ne 0 ]
then
    echo "5. invalid pageDirectory(non existant) passed"
fi
echo ""

# 6. invalid pageDirectory (not a crawler directory) 
./indexer ../indexer/testDir/notCrawler ../indexer/testDir/notCrawler/test.index
if [ $? -ne 0 ]
then
    echo "6. Invalid pageDirectory (non crawler) passed"
fi
echo ""

# 7. invalid indexFile (non-existent path)
./indexer ../indexer/testDir/letters-10 ../indexer/testDir/notaDir/test.index
if [ $? -ne 0 ]
then
    echo "7. invalid indexFIle path test passed"
fi
echo ""

# 8. invalid indexFile (read-only directory) 
./indexer ../indexer/testDir/letters-10 ../indexer/testDir/readOnly/test.index
if [ $? -ne 0 ]
then
    echo "8. invalid indexFile readOnlyDir test passed"
fi
echo ""

# 9. invalid indexFile (existing, read-only file)
./indexer ../indexer/testDir/letters-10 ../indexer/testDir/readOnlyFile/readOnly.index
if [ $? -ne 0 ]
then
    echo "9. invalid indexFIle readOnlyFile test passed"
fi
echo ""

# letters-10 test
echo "Letters-10 test"

valgrind --leak-check=full --show-leak-kinds=all ./indexer ../indexer/testDir/letters-10 ../indexer/testDir/letters-10/test.index
valgrind --leak-check=full --show-leak-kinds=all ./indextest ../indexer/testDir/letters-10/test.index ../indexer/testDir/letters-10/testCopy.index
echo ""
echo ""
echo ""
echo ""

# toscrape-0 test
echo "toscrape-0 test"
valgrind --leak-check=full --show-leak-kinds=all ./indexer ../indexer/testDir/toscrape-0 ../indexer/testDir/toscrape-0/test.index
valgrind --leak-check=full --show-leak-kinds=all ./indextest ../indexer/testDir/toscrape-0/test.index ../indexer/testDir/toscrape-0/testCopy.index
echo ""
echo ""
echo ""
echo ""

# wikipedia-0 test
echo "Wikipedia-0 test"
valgrind --leak-check=full --show-leak-kinds=all ./indexer ../indexer/testDir/wikipedia-0 ../indexer/testDir/wikipedia-0/test.index
valgrind --leak-check=full --show-leak-kinds=all ./indexer ../indexer/testDir/wikipedia-0 ../indexer/testDir/wikipedia-0/test.index