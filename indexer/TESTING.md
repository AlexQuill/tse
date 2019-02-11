## CS50 Lab 4
## Grace Dorgan, Jan 2018

### Testing 'indexer'

To test my *indexer* I wrote a test program, [test.sh](test.sh), to explore the
boundaries of the *indexer* to demonstrate that it works on all edge cases

This test program does not take input, but provides it to the indexer program. 
All output from indexer is redirected to /dev/null, and the output that goes to
stdout is just a series of print statements saying whether or not it passes the
mentioned test case.

test.sh can be called using the *make test* command, which will redirect all
output to a file *testing.out*

test.sh can be run with valgrind too, which can be called from make with
*make valgrind*
 
### Test Output

The results of my test.sh script can be found in the *testing.out* file

### Limitations
If differences are found in the files made from *indextest*, you aren't going
to know what they are.
It may be benficial to test ore than one crawler output.
