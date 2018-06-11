import os
import glob
import sys
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from EventHandler import EventHandler

#Set global var. if open var. is hrp, C10 or raw16 delete all other files except that one 
#Compare date and on top of that compare the time if the same type satelites comes after eachother
class DeleteFiles():

	def remove_when_metop(self):
		
		eventhandler.return_globPath()
		pathlist=glob.glob("C:\\Users\\Rickard\\Downloads\\*.HPT")
		print(pathlist)
		length_of_pathlist=len(pathlist)
		print(length_of_pathlist)
		eventhandler.set_globtemp(0)

		if (length_of_pathlist==1):									
			for x in range(0,length_of_pathlist):
				#print('en kvar')
				if(pathlist[0]==eventhandler.return_globPath()):
					#os.remove(pathlist[x])
					print('Success!!!')

				#print (glob.glob("C:\\Users\\Rickard\\Downloads\\*.HRP"))

		'''	
		for BIN in glob.glob("*.BIN"):		#glob.glob creates a list, with the specified file name
		  os.remove(BIN)

		for RAW16 in glob.glob("*.RAW16"):		#glob.glob creates a list, with the specified file name
		  os.remove(RAW16)

		for C10 in glob.glob("C:\\Users\\Rickard\\Downloads\\*.C10"):		#glob.glob creates a list, with the specified file name
		  os.remove(C10)
		
		for RS in glob.glob("*.RS"):		#glob.glob creates a list, with the specified file name
		  os.remove(RS)

		for VCD in glob.glob("*.VCD"):		#glob.glob creates a list, with the specified file name
		  os.remove(VCD)

		for PN in glob.glob("*.PN"):		#glob.glob creates a list, with the specified file name
		  os.remove(PN)

		for PK in glob.glob("*.PKT"):		#glob.glob creates a list, with the specified file name
		  os.remove(PKT)

		for MPD in glob.glob("*.MPD"):		#glob.glob creates a list, with the specified file name
		  os.remove(MPD) 
		'''
	def remove_when_fengyun(self):
		for BIN in glob.glob("*.BIN"):		#glob.glob creates a list, with the specified file name
		  os.remove(BIN)

		for RAW16 in glob.glob("*.RAW16"):		#glob.glob creates a list, with the specified file name
		  os.remove(RAW16)		  

		for C10 in glob.glob("*.HPT"):		#glob.glob creates a list, with the specified file name
		  os.remove(C10)

		for RS in glob.glob("*.RS"):		#glob.glob creates a list, with the specified file name
		  os.remove(RS)

		for VCD in glob.glob("*.VCD"):		#glob.glob creates a list, with the specified file name
		  os.remove(VCD)

		for PN in glob.glob("*.PN"):		#glob.glob creates a list, with the specified file name
		  os.remove(PN)

		for MPD in glob.glob("*.MPD"):		#glob.glob creates a list, with the specified file name
		  os.remove(MPD)

		for FY3 in glob.glob("*.FY3"):		#glob.glob creates a list, with the specified file name
		  os.remove(FY3)  


	def remove_when_noaa(self):
		#Here there is going to be a small problem with taking away the older one maybe 
		#Compare dates then time in the file names
		'''
		if (globvar==1):
			remove_when_metop()
		if (globvar==2):
			remove_when_fengyun()
		if (globvar==3):
			remove_when_noaa()
		if (globvar==4):
			#what to do with the Meteor	
		'''

if __name__ == '__main__':
	
	args = sys.argv[1:] 											#take argument as the second line in the system input
	observer = Observer()											#create an observer object
	observer.schedule(EventHandler(), path=args[0], recursive=False)	#take the first line in the argument as a path
	observer.start()												#Start observing that folder
	eventhandler=EventHandler()
	eventhandler.set_globtemp(0)

	try:
	    while True:
	    	if(eventhandler.return_globtemp()==1):
	    		time.sleep(2)
	    		DF=DeleteFiles()
	    		DF.remove_when_metop()
	    	time.sleep(1)
	except KeyboardInterrupt:
	    observer.stop()

observer.join()



