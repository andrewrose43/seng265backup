# IMPORTED LIBRARIES
import sys
import re

# MAIN PROGRAM

html = sys.stdin.read() # sys.stdin.read() is like input(), but it goes right to the end of the file
if (html):
	csv_out = "" # The final-product-to-be
	tcount = 0 # Tracks the number of input tables
	tlist = re.findall(r"<table[\s*\n*]*(?:\w+[\s*\n*]*=[\s*\n*]*\".*\"\s*)*>\s*(.*?)\s*</table[\s*\n*]*>", html, re.IGNORECASE|re.DOTALL) # list of match objects for instances of "<table>"

	for t in tlist:
		csv_rough = "" # this will be filled with the CSV representation of the HTML table. Rough because its commas have not yet been taken care of properly.
		csv_out = "" # will contain the final version of each table. Needs to be cleared on every iteration
		colcount_max = 0 # this variable tracks the number of columns in each table
		if (tcount):
			print() # prints a blank line between tables
		tcount += 1 # keeps track of which table we are on
		print("TABLE {}:".format(tcount))
		rlist = re.findall(r"<tr[\s*\n*]*(?:\w+[\s*\n*]*=[\s*\n*]*\".*\"\s*)*>\s*(.*?)\s*</tr[\s*\n*]*>", t, re.IGNORECASE|re.DOTALL) # list of rows in the table
		for r in rlist:
			linev1 = "" # this will be filled with CSVs. v1 because it has not been ensured to contain the right number of commas yet
			clist = re.findall(r"<t[hd][\s*\n*]*(?:\w+[\s*\n*]*=[\s*\n*]*\".*\"\s*)*>\s*(.*?)\s*</t[hd][\s*\n*]*>", r, re.IGNORECASE|re.DOTALL) # list of contents of cells in the row
			colcount_tmp = 0 # counts number of columns to ensure trailing commas are present
			for c in clist:
				colcount_tmp += 1
				c = re.sub(r'\s+',' ',c) # puts single spaces where excessive whitespace was
				linev1 = linev1 + c  + "," # adds the cell contents and a comma to the linev1 to be printed
			csv_rough += linev1[0:-1] # removes the extra comma
			csv_rough += "\n" # add a newline
			if (colcount_tmp>colcount_max):
				colcount_max = colcount_tmp # assigns a larger value to colcount_max if needed
	

		# ADDING EXTRA COMMAS TO EOLs AS NEEDED
		commacount = 0 # initializing comma counter variable used to add extra commas to the end of a csv line
		toindex = 0 # tracks position up to which to fetch material from in csv_rough
		fromindex = 0 # tracks position upward from which to fetch material from in csv_rough
		for char in csv_rough: 
			if (char == ','):
				commacount += 1
			if (char=='\n'):
				csv_out = csv_out + csv_rough[fromindex:toindex]
				for i in range(colcount_max-commacount-1): #to end up with a total number of commas equal to the number of columns minus one
					csv_out = csv_out + ',' # this inserts a comma where needed
				commacount = 0 # EOL reached; reset commacount to begin counting the next line's commas
				fromindex = toindex # bring fromindex up to speed
			toindex += 1
		csv_out = csv_out + csv_rough[fromindex:] # append the chunk of csv_out, now that the commas are in order
	
		# PRINTING
		print(csv_out, end="") # the end="" prevents a new line from being printed at the end

# A little bit of error handling
else: # in the case that the input file was empty
	print("You submitted an empty file. Please try again.")


