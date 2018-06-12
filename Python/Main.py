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
	path_metop="C:\\Ruag_program\\xhrpt_decoder\\*.HPT"
	path_fengyun="C:\\Ruag_program\\xhrpt_decoder\\*.C10"
	path_noaa="C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"

	eventhandler.set_globtemp(0)										#The temp variable for the alarming if there is a file zero in the beginning
	#Start all the programs write a Init()
	#open_reader.OpenProgram()				#Start seperatly instead as initialphase
	#Open more programs here WXTrack?

	#Here the constant loop starts
	observer.start()

	try:
		while True:
			if (eventhandler.return_globtemp()==1):						#If new file
				print(eventhandler.return_globtemp())
				#Wait and delete files that comes in during the wait, can i in someway se when the file is done?
				time.sleep(30) 	#change to 20 min in real application 
				if (eventhandler.return_globvar()==1):					#For Metop	
					print('Jag är inne på riktigt')
					openmetfy.OpenForMetop()
					time.sleep(10)
					delete_files.remove_previous(path_metop,eventhandler.return_globPath())
					delete_files.remove_when_metop()					#Delete old files compare with path to new one
					open_reader.OpenNewFile()

				if (eventhandler.return_globvar()==2):					#For Fengyun
					print('Jag är inne')
					openmetfy.OpenForFengyun()							#Go to the right folder and choose the right file(idea as comment in method)
					time.sleep(10)
					delete_files.remove_previous(path_fengyun,eventhandler.return_globPath())
					delete_files.remove_when_fengyun()					#Delete old files compare with path to new one
					open_reader.OpenNewFile()

				if (eventhandler.return_globvar()==3):					#For Noaa
					print('Jag är inne')
					delete_files.remove_previous(path_noaa,eventhandler.return_globPath())
					delete_files.remove_when_noaa()					#Delete old files compare with path to new one
					time.sleep(10)
					open_reader.OpenNewFile()

			eventhandler.set_globtemp(0)								#unlock the eventhandler 
			time.sleep(1)		
	except KeyboardInterrupt:
	    observer.stop()

observer.join()


