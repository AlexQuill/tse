## CS50 Lab 4
## Grace Dorgan, Jan 2018

### Testing 'crawler'

To test my *crawler* I wrote a test program, [test.sh](test.sh), to explore the
boundaries of the *crawler* to demonstrate that it works on all edge cases

This test program does not take input, but provides it to the crawler program. 
All output from Crawler is redirected to /dev/null, and the output that goes to
stdout is just a series of print statements saying whether or not it passes the
mentioned test case.

### Test Output

I ran the program and got the following output:  
>[dorgan@flume ~/tse/crawler]$ bash test.sh
>Passed test with no params
>Passed test with too many params
>Passed test with non existant seed
>Passed test with non internal seed
>Passed test with small loop
>Passed test with small loop at depth 4
>Passed test with small loop at depth 5
>Passed test with small loop at depth 3
>done  
One can see I have thouroughly tested edge cases and duplicity.


### Limitations
The user has to look at the webpages themselves to make sure that my predicted
number of files created for each case is the right number.
