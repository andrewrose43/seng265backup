#IMPORTED LIBRARIES
import argparse
import sys
import re

#SORTING KEYS
def byLength(elem):
	return elem[0]

def byOccurrences(elem):
	return elem[1]


#ARGUMENT PARSING SETUP
parser = argparse.ArgumentParser()
parser.add_argument("--sort", action = "store_true", help = "Sort word lengths by number of occurrences")
parser.add_argument("--print_words", action = "store_true", help = "Display the unique words found for each word length in alphanumeric order")
parser.add_argument("--infile", action = "store_true", help = "indicates that there is an input file to be processed")
parser.add_argument("filename")
args = parser.parse_args()

#FLAG PROCESSING & MAIN PROGRAM
if args.infile and args.filename:
	li = [] #create an empty list to append to
	len_present = True
	with open(args.filename) as the_file:
		for line in the_file:
			line = line.strip()
			words = re.split('[\s.,;()]', line)
			for word in words:
				len_present = False #assume this is the first word of its length until proven otherwise
				for subli in li:
					if (len(word) == subli[0]):
						subli[1] += 1 #add to the occurrences of words of that length
						if word not in subli[2]:
							subli[2].append(word) #add this word onto sub-subli of different words if it was not already there 
						len_present = True
						break #word has been placed
				#for word in words: (reminder of which loop the below block is part of)
				if not len_present and not len(word) == 0: #if this word length was not previously in the li
					li.append([len(word), 1, [word]]) #create the relevant entry. count starts at 1
					#word length, total occurrences, words of that length
					#be sure to check the case that this is the first word being processed!
							
	# if the sort flag was supplied, sort the output by number of occurrences, not by word length	
	if args.sort:
		newli = sorted(li, key = byLength)	
		newli = sorted(li, key = byOccurrences, reverse=True)
	else:
		newli = sorted(li, key = byLength, reverse=True)
	#newli = sorted(li, key = byOccurrences)

	#PRINTING
	
	#if --print_words was supplied, this needs to be substituted for something else
	if args.print_words:
		#got to sort those sub-sublis
		for subli in newli:
			subli[2][:] = [word.lower() for word in subli[2]]
			
			subli[2].sort()
			for word in subli[2][0:-1]: # for all items in subli except the last one
				printem = " (words: \""
				printem += "\", ".join(subli[2][0:-1]) #make the first chunk of the string... might cause trouble if there are only two so only one is processed here
				printem += "\" and \"".join(subli[2][-1]) + "\")" #taking care of last word

			print(("Count[{0:02.0f}]={1:02.0f};" + printem).format(subli[0], subli[1]))
	#Perhaps the reason that the above line malfunctioned was that I tried to format on top of printitem?

	else:
		for subli in newli:
			print("Count[{0:02.0f}]={1:02.0f};".format(subli[0], subli[1]))

else:
	print("You need to enter the --infile flag and the name of the file you wish to process.\n")
