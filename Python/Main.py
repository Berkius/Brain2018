import time
from time import gmtime, strftime
import sys
import pyautogui
from twitter_bot import Tweet
from Superfile import OpenReader 
from Superfile import DeleteFiles
from Superfile import EventHandler
from Superfile import OpenMetFy
from Superfile import CheckFiles
from Superfile import TimePause	
from pywinauto import application
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

if __name__ == '__main__':

	open_reader=OpenReader()
	delete_files=DeleteFiles()
	openmetfy=OpenMetFy()
	checkfiles=CheckFiles()													
	args = sys.argv[1:] 												#take argument as the second line in the system input
	observer = Observer()												
	observer.schedule(EventHandler(), path='C:\\Ruag_program\\xhrpt_decoder', recursive=False)	#take the first line in the argument as a path
	eventhandler=EventHandler()
	timepause=TimePause()
	tweet=Tweet()

	path_to_Hrpt_Reader = 'C:\\Ruag_program\\hrpt-reader.3.0.8\\ReadHRPT'
	path_metop="C:\\Ruag_program\\xhrpt_decoder\\*.HPT"
	path_fengyun="C:\\Ruag_program\\xhrpt_decoder\\*.C10"
	path_noaa="C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"
	path_to_screenshot= "C:\\Users\\Ruag\\Pictures\\Screenshots"
	path_to_FileExplorer="C:\\Users\\Ruag\\Pictures\\Screenshots\\explorer ."

	eventhandler.set_globtemp(0)										#The temp variable for the alarming if there is a file zero in the beginning
	#Start all the programs write a Init()
	#open_reader.OpenProgram()				#Start seperatly instead as initialphase
	#Open more programs here WXTrack?

	#Here the constant loop starts
	observer.start()
	update_time="11:34:00"				# Decided in task manager
	app1 = application.Application().start(path_to_Hrpt_Reader)
	try:
		while True:

			#if(strftime("%H:%M:%S")==update_time):						#Windows task  manager update
				#timepause.pause_file()
				
			if (eventhandler.return_globtemp()==1):						#If new file
				#Wait and delete files that comes in during the wait, can i in someway se when the file is done?
				global_path=eventhandler.return_globPath()
				checkfiles.check_file_size(eventhandler.return_globPath()) 	#checks the size of the file and when it has stopped growing it lets it go 

				if (eventhandler.return_globvar()==1):					#For Metop	
					print('Jag är inne')
					openmetfy.OpenForMetop(global_path)
					time.sleep(3)
					open_reader.OpenNewFile()
					delete_files.remove_previous(path_metop,global_path)
					delete_files.remove_when_metop()					#Delete old files compare with path to new one
					time.sleep(2)

				if (eventhandler.return_globvar()==2):					#For Fengyun
					print('Jag är inne')
					openmetfy.OpenForFengyun(global_path)							#Go to the right folder and choose the right file(idea as comment in method)
					time.sleep(3)
					open_reader.OpenNewFile()
					delete_files.remove_previous(path_fengyun,global_path)
					delete_files.remove_when_fengyun()					#Delete old files compare with path to new one
					time.sleep(2)

				if (eventhandler.return_globvar()==3):					#For Noaa
					print('Jag är inne')
					open_reader.OpenNewFile()
					delete_files.remove_previous(path_noaa,global_path)
					delete_files.remove_when_noaa()					#Delete old files compare with path to new one
					time.sleep(2)

				app1.top_window().MenuSelect('File->Save displayed image - JPEG')
				tweet.tweet_auto()
				eventhandler.set_globtemp(0)	
				time.sleep(3)
				
			time.sleep(3)

	except KeyboardInterrupt:
	    observer.stop()

observer.join()


