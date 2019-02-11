#!/bin/bash
chmod +x test.sh
#Grace Dorgan Jan 2018
#An indexer testing script

#test wrong number of params
./indexer &> /dev/null
if [ $? -ne 0 ]
then
	echo passed test with no params
else
	echo did not pass test with no params
fi

./indexer ~cs50/demo/crawler-output/ test1 test1 &> /dev/null
if [ $? -ne 0 ]
then
        echo Passed test with too many params
else
        echo did not pass test with too many params
fi

#test indexer with non crawler directory

./indexer ~cs50/demo testnoncrawler &> /dev/null
if [ $? -ne 0 ]
then
        echo Passed test with non-crawler directory
else
        echo did not pass test with non-crawler directory
fi

#Test indexer with non-existant directory

./indexer notarealdir testnonexis &> /dev/null
if [ $? -ne 0 ]
then
        echo Passed test with non-existent directory
else
        echo did not pass test with non-existent directory
fi

#run indexer so we can run indextest

./indexer ~cs50/demo/crawler-output/ test1
#run indextest 
./indextest test1 test1cpy
#sort the outputs
gawk -f indexsort.awk test1cpy > test1cpy.sorted
gawk -f indexsort.awk test1 > test1.sorted
#look for differences
diff test1.sorted test1cpy.sorted
if [ $? -ne 0 ]
then
	echo differences between the sorted files were found, test not passed
else
	echo no differences between sorted file, test passed!
fi
echo done with testing!

