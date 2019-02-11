#!/bin/bash
chmod +x test.sh
#Grace Dorgan Feb 2018
#A querier testing script

#test wrong number of params
./querier &> /dev/null
if [ $? -ne 0 ]
then
	echo passed test with no params
else
	echo did not pass test with no params
fi

./querier ~cs50/demo/crawler-output-small/ test1 test1 &> /dev/null
if [ $? -ne 0 ]
then
        echo Passed test with too many params
else
        echo did not pass test with too many params
fi

#test querier with non crawler directory

./querier ~cs50/demo testnoncrawler &> /dev/null
if [ $? -ne 0 ]
then
        echo Passed test with non-crawler directory
else
        echo did not pass test with non-crawler directory
fi

#Test querier with non-existant directory

./querier notarealdir testnonexis &> /dev/null
if [ $? -ne 0 ]
then
        echo Passed test with non-existent directory
else
        echo did not pass test with non-existent directory
fi

echo done with testing!

