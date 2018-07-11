#----------------------------------------------------------------------------#
	#BRAINS 2018 

	#This is the file that contains the automation program
	#for the decoding programs but it will also save as JPG
	#the picture from HRTP reader and upload it on Twitter.

	#To run the program start it in the terminal. It is located in the Python 
	#folder in the Brains2018 folder
	
	#BEWARE there is alot of quick fixes in this porgram so read the Quick Start 
	#Manual carefully before starting the program 

#----------------------------------------------------------------------------#

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
	args = sys.argv[1:] 																		#takes argument as the second line in the system input
	observer = Observer()												
	observer.schedule(EventHandler(), path='C:\\Ruag_program\\xhrpt_decoder', recursive=False)	#The path to which folder the observer will check for new created files 
	eventhandler=EventHandler()																	#EventHandler Object 
	timepause=TimePause()
	tweet=Tweet()

	path_to_Hrpt_Reader = 'C:\\Ruag_program\\hrpt-reader.3.0.8\\ReadHRPT'						#Path to the program that display the images
	path_metop="C:\\Ruag_program\\xhrpt_decoder\\*.HPT"
	path_fengyun="C:\\Ruag_program\\xhrpt_decoder\\*.C10"
	path_noaa="C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"

	eventhandler.set_globtemp(0)										#The temp variable for the alarming if there is a new file created, if it is globtemp is set to zero

	#Here the constant loop starts
	observer.start()
	app1 = application.Application().start(path_to_Hrpt_Reader)
	try:
		while True:
				
			if (eventhandler.return_globtemp()==1):							#If new file is created in the folder the observer is watching 
				global_path=eventhandler.return_globPath()					#The path of the created file
				checkfiles.check_file_size(eventhandler.return_globPath()) 	#Checks the size of the file and when it changes its done and we keep on going 

				if (eventhandler.return_globvar()==1):						#If it is a Metop satellite thats been tracked	
					openmetfy.OpenForMetop(global_path)						#Opens the extra process program that is needed to be able to display the picture->
					time.sleep(3)											#and chooses the most recently created file.	
					open_reader.OpenNewFile()								#Opens the new file in the HRTP reader
					delete_files.remove_previous(path_metop,global_path)	#If the previous satellite was of the same kind and to not remove the wrong files 
					delete_files.remove_when_metop()						#Delete old files and the extra one created in the process
					time.sleep(2)

				if (eventhandler.return_globvar()==2):						#If it is a Fengyun satelite thats been tracked
					openmetfy.OpenForFengyun(global_path)					#Opens the extra process program that is needed to be able to display the picture->
					time.sleep(3)											#and chooses the most recently created file.	
					open_reader.OpenNewFile()								#Opens the new file in the HRTP reader
					delete_files.remove_previous(path_fengyun,global_path)	#If the previous satellite was of the same kind and to not remove the wrong files 
					delete_files.remove_when_fengyun()						#Delete old files and the extra one created in the process
					time.sleep(2)

				if (eventhandler.return_globvar()==3):						#If it is a NOAA satelite thats been tracked
					open_reader.OpenNewFile()								#Opens the new file in the HRTP reader
					delete_files.remove_previous(path_noaa,global_path)		#If the previous satellite was of the same kind and to not remove the wrong files 
					delete_files.remove_when_noaa()							#Delete old files and the extra one created in the process
					time.sleep(2)

				#Here the program is done with the processing and displaying the image 

				app1.top_window().MenuSelect('File->Save displayed image - JPG')	#Saving the displayed image to the folder Screenshots in Pictures as JPG	
				tweet.tweet_auto()													#Uploading the most recent created JPG to our twitter account
				eventhandler.set_globtemp(0)										#During the entire loop the observer is locked in a loop to not start extra processes in case a new file is created ->
				time.sleep(3)														#By setting global_temp to zero the observer is released and start looking for changes in the specific folder again
				
			time.sleep(3)

	except KeyboardInterrupt:												#Press CTRL + C in cmd to stop the process 
	    observer.stop()

observer.join()


