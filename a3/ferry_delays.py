#IMPORTED LIBRARIES
import argparse
import sys
import csv

#ARGUMENT PARSING SETUP
parser = argparse.ArgumentParser()
parser.add_argument('filename', nargs = '*', help = 'file to be processed')
args = parser.parse_args()

# MAIN PROGRAM

if args.filename:
	for arg in args.filename:
		print(arg)
		# Opening each file...
		try:
			the_file = open(arg)
	#		print("{} was opened".format(arg)) # debugging print statement
		except:
			print("File could not be opened.")
			sys.exit()
		
		# Into the fray...		

		# Determining terminal of interest
		terminal = input("Would you like delay statistics for Tsawwassen or for Swartz Bay?\nEnter 't' for Tsawwassen or 's' for Swartz Bay.\n")
		while not (terminal == 't' or terminal == 's'):
			terminal = input("Sorry, your input was invalid.\nEnter 't' for Tsawwassen or 's' for Swartz Bay.\n")
		
		# Determining month of interest
		month = "Unassigned" # declaring it here for scope
		try:
			month = int(input("Which month would you like delay statistics for?\nEnter the number between 1 and 12 which corresponds to the desired month.\n"))
		except:
			pass
		while not (month in (1,2,3,4,5,6,7,8,9,10,11,12)):
			try:
				month = int(input("Invalid input. Please try again.\nEnter the number between 1 and 12 which corresponds to the desired month.\n"))
			except:
				pass
		# Turning the month number into a month name
		monthnames = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
		mon = monthnames[month-1]

		# Cracking open a csv one with the boys
		reader = csv.reader(the_file)
		sumdels = 0 # sum of delays
		rowcount = 0 # keeps track of how many rows (i.e. departures) there are in the month of interest
		delaydata = False # tracks whether any data exists for the desired month
		rowmon = -1 # tracks which month the current row pertains to
		for row in reader:
			#print(month) # debugging print statements
			#print(int(row[-14]))
			try:
				rowmon = int(row[-14])
			except:
				rowmon = -1
			if (rowmon==month):
				if (terminal=='t'):
					if (row[0]=='Tsawwassen'):
						delaydata = True
						rowcount += 1
						# Adding to sumdels
						sumdels += int(row[-6]) # adding real departure minutes
						sumdels += 60*int(row[-7]) # adding real departure hours, converted into minutes
						sumdels -= int(row[-11]) # subtracting scheduled departure minutes
						sumdels -= 60*int(row[-12]) # subtracting scheduled departure hours, converted into minutes
				elif (terminal=='s'):
					if (row[0]=='Swartz Bay'):
						delaydata = True
						rowcount += 1
                	                        # Adding to sumdels
						sumdels += int(row[-6]) # adding real departure minutes
						sumdels += 60*int(row[-7]) # adding real departure hours, converted into minutes
						sumdels -= int(row[-11]) # subtracting scheduled departure minutes
						sumdels -= 60*int(row[-12]) # subtracting scheduled departure hours, converted into minutes
			
		# Printing output...
		print(":RESULTS")
		if (terminal=='t'):
			print("Tsawwassen:")
		elif (terminal=='s'):
			print("Swartz Bay:")
		if (delaydata):
			print("    Average delay for {0}: {1:.2f}\nEND".format(mon, float(sumdels/rowcount)))
		else:
			print("    No delay data for {0}\nEND".format(mon))
else:
	print("You did not provide any files for processing. Please try again.")

sys.exit()
