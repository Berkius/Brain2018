import time
import sys
from Superfile import OpenReader 
from Superfile import DeleteFiles
from Superfile import EventHandler
from Superfile import OpenMetFy
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

if __name__ == '__main__':

		open_reader=OpenReader()
		delete_files=DeleteFiles()
		openmetfy=OpenMetFy()													
		args = sys.argv[1:] 												#take argument as the second line in the system input
		observer = Observer()												
		observer.schedule(EventHandler(), path=args[0], recursive=False)	#take the first line in the argument as a path
		eventhandler=EventHandler()

		eventhandler.set_globtemp(0)										#The temp variable for the alarming if there is a file zero in the beginning
		#Start all the programs write a Init()
		open_reader.OpenProgram()
		#Open more programs here WXTrack?

		#Here the constant loop starts
		observer.start()

		try:
	    	while True:
	    		if (eventhandler.return_globtemp==1):						#If new file 
	    			eventhandler.set_globtemp(0)							#reset temp variable
	    			#Delete old files compare with path to new one? think this through on Monday
	    			#Wait and delete files that comes in during the wait, Think this loop thorough on Monday 
	    			if (eventhandler.return_globvar()==1):					#For Metop	
	    				
	    			if (eventhandler.return_globvar()==2):					#For Fengyun 
	    				

	    			if (eventhandler.return_globvar()==3):					#For Noaa
	    				open_reader.OpenNewFile()


	        	time.sleep(1)
		except KeyboardInterrupt:
	   		observer.stop()



