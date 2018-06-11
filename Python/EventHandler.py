import os
import re
import sys
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

class EventHandler(FileSystemEventHandler):
	patterns = ["*.raw16", "*.bin"]					#Which files to look for 

	def set_globvar(self,globvar):				#for deciding if it is Metop or feng or noaa
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globvar
	        globvar = arg
	    trick(globvar)

	def return_globvar(self,globvar):
		return globvar    

	def set_globtemp(self,globtemp):			#To know if a new file was added
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globtemp
	        globtemp = arg
	    trick(globtemp)

	def return_globtemp(self):
		return globtemp    

	def set_globPath(self,globPath):
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globPath
	        globPath = arg
	    trick(globPath)

	def return_globPath(self):
		return globPath    	

	def process(self, event):						#Check the API for the watchdog for more information
	    """
	    event.event_type 
	        'modified' | 'created' | 'moved' | 'deleted'
	    event.is_directory
	        True | False
	    event.src_path
	        path/to/observed/file
	    """
	    # the file will be processed there
	    #regex = re.compile(r'\d+')								#For taking out numbers in a string

	    if 'M' in event.src_path and event.event_type=='created':
	    	print('Nu ser det lovande ut')
	    	self.set_globvar(1)
	    	print(globvar)
	    	self.set_globtemp(1)
	    	print(event.src_path)
	    	self.set_globPath(event.src_path)
	    	#numbers=[int(x) for x in regex.findall(event.src_path)]				#find all numbers in the source path
	    	#print(numbers)

	    if 'FY' in event.src_path and event.event_type=='created':
	    	print('Jajamensan')
	    	self.set_globvar(2)
	    	print(globvar)
	    	self.set_globtemp(1)

	    #print(event.src_path, event.event_type)  	# print now only for degug

	def on_modified(self, event):
	    self.process(event)

	def on_created(self, event):
	    self.process(event)

	#def on_any_event(self,event):					#add if more information about the folder then just pattern files are needed
		#self.process(event)    
'''
if __name__ == '__main__':
	args = sys.argv[1:] 											#take argument as the second line in the system input
	observer = Observer()											#create an observer object
	observer.schedule(EventHandler(), path=args[0], recursive=False)	#take the first line in the argument as a path
	observer.start()												#Start observing that folder

	try:
	    while True:
	        time.sleep(1)
	except KeyboardInterrupt:
	    observer.stop()

observer.join()
'''