#!/bin/bash
# Jusung Park
# CS50 Winter 2023
# testing program for crawler 

FILE=crawler.c
if test -f "$FILE"
then
	echo "Crawler was found!"

else
	echo "Crawler was not found."
	exit 1
fi

rm -f pagedir/*
# Testing a normal test
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters-depth-2 2
if [ $? -eq 0 ]
then
  echo "Normal test run passed!"
fi

# Testing an invalid website
./crawler invalidURL pagedir 2
if [ $? -ne 0 ]
then
  echo "Invalid website test passed!"
fi

rm -f pagedir/*
# Testing non-internal website
./crawler https://www.canvas.dartmouth.edu/ pagedir 2
if [ $? -ne 0 ]
then
  echo "Non-internal website test passed!"
fi

rm -f pagedir/*

# Testing non-existing folder (assumption)
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html invalidDir 2
if [ $? -ne 0 ]
then
  echo "Non-existing folder test passed!"
fi

rm -f pagedir/*
# Testing invalid number (assumption)
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html leagueoflegends -2
if [ $? -ne 0 ]
then
  echo "Invalid number test1 passed!"
fi

rm -f pagedir/*
# Testing not a number (assumption)
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html pagedir leagueoflegends
if [ $? -ne 0 ]
then
  echo "Invalid number test2 passed!"
fi

rm -f pagedir/*
# Testing valid seedURL but nonexistent page 
./crawler hhttp://cs50tse.cs.dartmouth.edu/tse/wikipedia/GENGWORLDCHAMPS2021 pagedir 2
if [ $? -ne 0 ]
then
  echo "Non-Existent page test passsed!"
fi

rm -f pagedir/* 
# Run with valgrind with moderate-sized test case
valgrind --leak-check=full --show-leak-kinds=all ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html pagedir 1

rm -f pagedir/*
# Run letters at depth 0, 1, 2, 10
for DEPTH in 0 1 2 10
do
	rm -f letters-depth-$DEPTH/*
  ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html tse-output/letters/letters-depth-$DEPTH $DEPTH
done
if [ $? -eq 0 ]
then
  echo "Letters system passed!"
fi

rm -f pagedir/*
# Run toscrape at depth 0, 1 without 2 and 3(plank connection issues; can't compile for too long)
for DEPTH in 0 1
do
	rm -f toscrape-depth-$DEPTH/*
	./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html tse-output/toscrape/toscrape-depth-$DEPTH $DEPTH
done
if [ $? -eq 0 ]
then
  echo "Toscrape system passed!"
fi

# Run wikipedia at depth 0, 1 without 2 (plank conection issues; can't compile for too long)
for DEPTH in 0 1
do
	rm -f wikipedia-depth-$DEPTH/*
  ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html tse-output/wikipedia/wikipedia-depth-$DEPTH $DEPTH
done
if [ $? -eq 0 ]
then
  echo "Wikipedia system passed!"
fi