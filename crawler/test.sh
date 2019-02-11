#!/bin/bash
chmod +x test.sh
#Grace Dorgan Jan 2018
#A crawler testing script

mkdir data
#MUST MAKE THE DIRECTORY

#test wrong number of params
./crawler &> /dev/null
if [ $? -eq 1 ]
then
	echo Passed test with no params
else
	echo did not pass test with no params
fi

./crawler http://old-www.cs.dartmouth.edu/index.html ./data/ 2 something &> /dev/null
if [ $? -eq 1 ]
then
        echo Passed test with too many params
else
        echo did not pass test with too many params
fi

#test valid server non existant page
#this should just ignore it and print a message to output, but no files should be saved

./crawler http://old-www.cs.dartmouth.edu/notreal ./data/ 2 &> /dev/null 
	if [ $? -eq 0 ]
then
	if [ ! -f data/1 ]
	then
		echo Passed test with non existant seed
	else
		echo did not pass test with non existant seed
		rm data/*
	fi
else
        echo did not pass test with non existant seed
fi



#test with non internal seed 
./crawler https://stackoverflow.com/questions/637827/redirect-stderr-and-stdout-in-bash ./data/ 2 &> /dev/null

if [ $? -eq 5 ]
then
        echo Passed test with non internal seed
else
        echo did not pass test with non internal seed
fi

#test page with small loop - there should be no duplicates
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./data/ 2 &> /dev/null
if [ $? -eq 0 ]
then
	if [ -f data/4 ]
	then
		echo Passed test with small loop
	else
		echo did not pass test in a small loop - wrong number of files made
	fi
else
        echo did not pass test in small loop - error triggered
fi

rm data/*

#test small loop again, but at greater depths
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./data/ 4 &> /dev/null
if [ $? -eq 0 ]
then
        if [ -f data/9 ]
        then
                echo Passed test with small loop at depth 4
        else
                echo did not pass test in small loop at depth 4 - wrong number of files made
        fi
else
        echo did not pass test in small loop of depth 4 - error triggered
fi

rm data/*

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ ./data/ 5 &> /dev/null
if [ $? -eq 0 ]
then
        if [ -f data/10 ]
        then
                echo Passed test with small loop at depth 5
        else
                echo did not pass test in small loop at depth 5 - wrong number of files made
        fi
else
        echo did not pass test in small loop of depth 5 - error triggered
fi

rm data/*

#test with the loop, but with a different starting point
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html ./data/ 3 &> /dev/null
if [ $? -eq 0 ]
then
        if [ -f data/9 ]
        then
                echo Passed test with small loop at depth 3
        else
                echo did not pass test in small loop at depth 3 - wrong number of files made
        fi
else
        echo did not pass test in small loop of depth 3 - error triggered
fi
rm -rf data




#./crawler http://old-www.cs.dartmouth.edu/index.html ./data/ 2

echo done
