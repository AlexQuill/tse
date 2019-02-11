## CS50 Lab 6
## Grace Dorgan, Feb 2018

### Testing 'querier'

To test my *querier* I made a test file, [testing](testing), to provide input
to the *querier* that would prove that it works for all edge cases.

The testing file starts out with several edge cases of my own:
queries with upper case letters, queries with large amounts of whitespace
in them, a blank line, queries with special characters.
After that, I used the *fuzzquery.c* program to generate the rest, with the
hope that it would test any edge cases I didn't think of.

I also wrote a program, [test.sh](test.sh), which tests several different
faulty command line arguments.

test.sh can be called using the *make test* command, which will redirect all
output to a file *testing.out*. 

The output from *querier* when run with *testing* can be found in the file 
*fuzztest.out*

### Test Output

The results of my test.sh script can be found in the *testing.out* file
The results of running querier with the *testing* file can be found in *fuzztest.out*

### Limitations
I don't actually have any known good output from a workng querier, so I just 
had to compare the output to what I got when I did it all by hand.

