The provided input file tests several cases at once. It contains multiple instances of various words, a 34-character word, a series of special characters, and punctuation immediately before line breaks (a necessary test case to ensure that \n has been included in strtok as a delimiter, which I had not initially included when I was writing the program).

It also contains a few features which would have become useful if I had managed to finish Part C, which I did not. Some words are repeated with their first letters capitalized; this is meant to test whether the program knows to treat versions of words with different capitalization as identical. I also included a "l33tspeak" version of a phrase to test the program's handling of number characters.

It is pig-themed because there's this song by Meat Loaf that I heard on the radio once in which the chorus went: "In the land of the pigs, the butcher is king!" a zillion times. For some reason, that song popped into my head when I was writing the test file. Don't ask me why.


