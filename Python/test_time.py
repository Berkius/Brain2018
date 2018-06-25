from time import gmtime, strftime

try:
	while(1):
		if(strftime("%H:%M:%S")=="12:52:00"):
			print("yes")
except KeyboardInterrupt:
 print('\nDone.')