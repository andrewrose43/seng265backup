#IMPORTED LIBRARIES
import argparse
import sys
import re

#ARGUMENT PARSING SETUP
parser = argparse.ArgumentParser()
parser.add_argument("--sort", action = "store_true", help = "Sort word lengths by number of occurrences")
parser.add_argument("--print_words", action = "store_true", help = "Display the unique words found for each word length in alphanumeric order")
parser.add_argument("--infile", action = "store_true", help = "indicates that there is an input file to be processed")
parser.add_argument("filename")
args = parser.parse_args()

# MAIN PROGRAM

if args.infile:

	# Opening the file & handling possible exception
	try:
		the_file = open(args.filename)
	except:
		print("File could not be opened.")
		sys.exit()

	# Now, into the fray...
	longest = 0 # tracks the length of the longest word in the list
	li = [] # list which will contain everything
	for line in the_file:
		line = line.strip() # remove unwanted whitespace
		words = re.split('[\s.,;()]',line) #tokenize by designated delimiters

		for word in words:
			if len(word)>0: # re.split tends to output zero-character nonwords
				word = word.lower() # convert each word to lowercase before processing
				if len(word) > longest: # the list must be expanded if a word is longer than all its predecessors
					for i in range(len(word)-longest): # make empty spaces for words between longest and word in length
						li.append([longest+i+1, 0, []])
					longest = len(word) # update value of longest
				if not word in li[len(word)-1][2]: # add word to the list of distinct words of its length if it is not already there
					li[len(word)-1][2].append(word)
				li[len(word)-1][1]+=1 # increment the tally of words of word's length

	# PRINTING
	if args.sort: # if the sort flag was entered, sort by descending frequency and then by word length in the case of ties
		li = sorted(li, key = lambda x: (-x[1], x[0]))

	for subli in li:

		# Dealing with the print_words flag...
		if args.print_words:
			subli[2].sort() # sort the distinct words of each length alphabetically
			if not subli[1] == 0:
				pwstr = " (words: \"" # this is the beginning of every print_words line segment
				if len(subli[2])>1:
					for word in subli[2][0:-2]: # add a space, with punctuation, for all except the last two distinct words
						pwstr += "{}\", \"".format(word)
					pwstr += "{}\" and \"{}\")".format(subli[2][-2], subli[2][-1]) # but the last two need special formatting
				else:
					pwstr += "{}\")".format(subli[2][0]) # do this instead if there is only one distinct word of this length
				print("Count[{0:02.0f}]={1:02.0f};".format(subli[0], subli[1]) + pwstr) # and, finally, print it!

		# Normal printing...
		else:
			if not subli[1] == 0:
				print("Count[{0:02.0f}]={1:02.0f};".format(subli[0], subli[1]))
	
	
	the_file.close() # close the file

# If the --infile flag was not entered...
else:
	print("You need to enter the --infile flag.")

sys.exit()
