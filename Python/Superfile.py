#----------------------------------------------------------------#
	#SUPERFILE.PY

	#This file contains all the relevent classes and functions
	#used to be able to run the image processing automatically.
	#The only class used outside this file is the class Tweet()
	#in the file twitter_bot.py

#----------------------------------------------------------------#
import os 
import subprocess
import time
import pyautogui
import glob
from pywinauto import application
import sys
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

#----------------------------------------------------------------#
	#OPENREADER()

	#OpenReader class contains code for opening the program 
	#HRPT Reader if needed and also code to open new files in 
	#this program.

#----------------------------------------------------------------#

class OpenReader():
	
	nmbr_tabs=10					#Number of tabs to get the most recent image when opening a new file 
	pyautogui.PAUSE = 0.01			#Wait 0.01 second after each pyautogui function call	
	pyautogui.FAILSAFE = True 		#move the mouse far up to the left corner will stop the pyautogui program

	def OpenProgram(self):																	#Function to open the HRPT Reader 

		path_to_Hrpt_Reader = 'C:\\Ruag_program\\hrpt-reader.3.0.8\\ReadHRPT'				#Path to the HRPT Reader 

		p=subprocess.Popen([path_to_Hrpt_Reader, path_to_file1]) 							#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)																		#Pause the program so the HRPT Reader gets time to pop up
		pyautogui.press('enter')															#Push Enter

		time.sleep(2)																		

	def OpenNewFileMetopNOAA(self):															#Opens up a new file in Hrpt Reader, hardcoded button presses 
		try:
			pyautogui.press('enter')														#Presses the by default marked Open button 
			time.sleep(2)																	#Waits two seconds for the open window to pop up 	

			for x in range(1,self.nmbr_tabs):												#This loop and the lines underneeth tabs its way to the most recently added file 				
				pyautogui.press('tab')														#Presses the tab button  

			pyautogui.press('down')															#Move marker down 
			pyautogui.press('up')															#Move marker up				
			pyautogui.press('enter')														#Opens the marked file 
			pyautogui.press('left')															#Southebound or Northbound. When left in this function it will push southbound 
			pyautogui.press('enter')
		except KeyboardInterrupt:
			print('interrupted')     

	def OpenNewFileFENG(self):																#Opens up a new file in Hrpt Reader, hardcoded button presses 		
		pyautogui.press('enter')															#Presses the by default marked Open button 
		time.sleep(2)																		#Waits two seconds for the open window to pop up 

		for x in range(1,self.nmbr_tabs):													#This loop and the lines underneeth tabs its way to the most recently added file 
			pyautogui.press('tab')															#Presses the tab button

		pyautogui.press('down')																#Move marker down
		pyautogui.press('up')																#Move marker up	
		pyautogui.press('enter')															#Opens the marked file 	
		pyautogui.press('enter')															#Southebound or Northbound. When left in this function it will push southbound 
#----------------------------------------------------------------#
	#DELETEFILES()

	#The DeleteFiles class contains code for deleting previous 
	#files and also extra files created by MetFy3x 

#----------------------------------------------------------------#
class DeleteFiles():														
	
	def remove_previous(self, path, globpath):												#This function checks if the previous file is of the same type as th new one an if it is removes the old one 
		
		pathlist=glob.glob(path) 															#Creates a list of specific file types decieded by path in a specific folder 
		print(pathlist)					
		length_of_pathlist=len(pathlist)													#Check the length of the list 
		print(length_of_pathlist)

		if (length_of_pathlist>1):															#If there is more then one file of a specific type  
			for x in range(0,length_of_pathlist):											#loop over these files	
				
				if(pathlist[x]!=globpath):													#If the file checked is not equal to the most recent file
					os.remove(pathlist[x])													#Remove it 		
					
	def remove_when_metop(self):															#Removes all files thats unneccesary after the processing of the same type as the new on and if it is it removes the old one

		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):						#glob.glob creates a list, with the specified file name

		  os.remove(BIN)																	#Remove all files with that specific ending. 

		for RAW16 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"):					#All loops works the same as described above 
		  os.remove(RAW16)

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):						#---
		  os.remove(C10)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):						#---		
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):						#---		
		  os.remove(VCD)	

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):						#---		
		  os.remove(PN)

		for PKT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PKT"):						#---	
		  os.remove(PKT)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):						#---
		  os.remove(MPD) 


	def remove_when_fengyun(self):															#Removes all files thats unneccesary after the processing of the same type as the new on and if it is it removes the old one
		
		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):						#glob.glob creates a list, with the specified file name
		  os.remove(BIN)																	#Remove all files with that specific ending.

		for RAW16 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"):					#All loops works the same as described above 
		  os.remove(RAW16)

		for HPT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):						#---
		  os.remove(HPT)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):						#---
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):						#---
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):						#---
		  os.remove(PN)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):						#---
		  os.remove(MPD)

		for FY3 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.FY3"):						#---
		  os.remove(FY3)  


	def remove_when_noaa(self):																#Removes all files thats unneccesary after the processing of the same type as the new on and if it is it removes the old one

		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):						#glob.glob creates a list, with the specified file name
		  os.remove(BIN)																	#Remove all files with that specific ending.

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):						#All loops works the same as described above 
		  os.remove(C10)											
		
		for HPT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):						#---
		  os.remove(HPT)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):						#---
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):						#---
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):						#---
		  os.remove(PN)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):						#---
		  os.remove(MPD)

		for FY3 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.FY3"):						#---
		  os.remove(FY3)  


#----------------------------------------------------------------#
	#EVENTHANDLER()

	#The Eventhandler class contains code for detecting if a 
	#soecific event occures or if somthing changed in a specific 
	#folder

#----------------------------------------------------------------#

class EventHandler(FileSystemEventHandler):
	patterns = ["*.raw16", "*.bin"]					#The pattern that the observer looks for 

	def set_globtemp(self,globtemp):				#A function to set the global variable globtemp to the argument used in the function call 
	    def trick(arg):							
	        global globtemp
	        globtemp = arg
	    trick(globtemp)

	def return_globtemp(self):						#This function returns the globtemp
		return globtemp    

	def set_globvar(self,globvar):					#A function to set the global variable globvar to the argument used in the function call 
	    def trick(arg):							
	        global globvar
	        globvar = arg
	    trick(globvar)

	def return_globvar(self):						#This function returns the globvar
		return globvar    


	def set_globPath(self,globPath):				#A function to set the global variable globPath to the argument used in the function call	
	    def trick(arg):
	    	global globPath							
	    	globPath = arg
	    trick(globPath)

	def return_globPath(self):						#This function returns the globPath
		return globPath    	

	def process(self, event):						#This functions logs specific events in specific folders. For more info check API for the watchdog for more information
	    """
	    event.event_type 
	        'modified' | 'created' | 'moved' | 'deleted'
	    event.is_directory
	        True | False
	    event.src_path
	        path/to/observed/file
	    """
	    # When a file is created the processesing starts here
	    if 'Metop' in event.src_path:							#If Metop is in the path name of the file thats been created 
	    	if 'bin' in event.src_path:							#If bin is in the path name of the file thats been created 
	    		if (event.event_type=='created'):				#And the event type is created
			    	print('METOP')
			    	self.set_globvar(1)							#globvar is set to 1 for the program to know that it is a Metop thats been tracked 
			    	#print(globvar)
			    	self.set_globtemp(1)						#globtemp is set to 1 so the observer dosen't detect a new file during the time it processing another one
			    	self.set_globPath(event.src_path)			#Sets globPath to the path of the created file 
			    	while (self.return_globtemp()==1):			#Locks the observer until everthing in the main loop and processing is done 
			    		pass
	    			#self.set_globtemp(0)
	    	print("Nu är vi ute ur whle i watchdog Metop och globtemp Metop=")
	    	print(globtemp)	

	    if 'FY' in event.src_path:								#If FY is in the path name of the file thats been created 
	    	if 'bin' in event.src_path:							#If bin is in the path name of the file thats been created 	
	    		if (event.event_type=='created'):				#And the event type is created
			    	print('FENG')
			    	self.set_globvar(2)							#globvar is set to 2 for the program to know that it is a Fengyun thats been tracked 	
			    	#print(globvar)
			    	self.set_globtemp(1)						#globtemp is set to 1 so the observer dosen't detect a new file during the time it processing another one	
			    	self.set_globPath(event.src_path)			#Sets globPath to the path of the created file 	
			    	while (self.return_globtemp()==1):			#Locks the observer until everthing in the main loop and processing is done
			    		pass
			    	#self.set_globtemp(0)
			    	print("Nu är vi ute ur whle i watchdog Fengyun och globtemp=")
			    	print(globtemp)	
		    
	    if 'NO' in event.src_path and event.event_type=='created':			#If NO is in the path name of the file thats been created and the event type is created
	    	print('NOAA')
	    	self.set_globvar(3)												#globvar is set to 3 for the program to know that it is a NOAA thats been tracked
	    	#print(globvar)
	    	self.set_globtemp(1)											#globtemp is set to 1 so the observer dosen't detect a new file during the time it processing another one
	    	self.set_globPath(event.src_path)								#Sets globPath to the path of the created file 	
	    	while (self.return_globtemp()==1):								#Locks the observer until everthing in the main loop and processing is done
	    		pass
	    	#self.set_globtemp(0)
	    	print("Nu är vi ute ur whle i watchdog NOAA och globtemp=")
	    	print(globtemp)	

	    print("end process")	
	    #print(event.src_path, event.event_type)  	# print now only for degug

	def on_modified(self, event):											#If something in the folder is modified this function sets the event to modified 
	    self.process(event)

	def on_created(self, event):											#If something in the folder is created this function sets the event to modified
	    self.process(event)

	#def on_any_event(self,event):					#add if more information about the folder then just pattern files are needed
		#self.process(event)    

class OpenMetFy():

	nmbr_tabs=8					#Numbers of tabs for the metfy
	X_file=256					#Coordinates for file tab
	Y_file=167					#Coordinates for file tab
	X_proc=718					#Coordinates for the process button	
	Y_proc=214					#Coordinates for the process button	
	X_deRand=571				#Coordinates for DeRandomizer alternativ box
	Y_deRand=192				#Coordinates for DeRandomizer alternativ box
	X_ReedSolomon=571			#Coordinates for ReedSolomon alternativ box
	Y_ReedSolomon=225			#Coordinates for ReedSolomon alternativ box
	pyautogui.PAUSE = 0.5		#Wait 1 second pause after each function call	
	pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

	def OpenForMetop(self,glob_file_path):											#This function puts in the specific settings in MetFy3x for metop files 
		#TEST NYA LÖSNINGEN
		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'
		path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		path_to_file2 = 'C:\\Ruag_program\\pictures\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 
		print("time to open")
		app = application.Application().start(path_to_MetFy3x)						#Måste startas med denna
		app.MetFY3x_Processor_.MenuSelect('File->Open')
		app.Open.Edit.SetText("C:\\Ruag_program\\xhrpt_decoder")
		app.Open.Open.Click()
		app.Open.Edit.SetText(glob_file_path)
		app.Open.Open.Click()
		app.MetFY3x_Processor_v.derandomize.Click()
		app.MetFY3x_Processor_v.ReedSalomon.Click()
		app.MetFY3x_Processor_v.Process.Click()
		time.sleep(20)
		app.kill()
		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader

		p=subprocess.Popen([path_to_MetFy3x]) 									#Opens a subprocess, starts MetFy3x and then goes directly to the next line in the code

		time.sleep(5)															#To give Metfy time to start up			
		pyautogui.click(self.X_file, self.Y_file)								#Click on the file option in the menubar 

		time.sleep(1)															#Gives the program time to open dialog window 
		#pyautogui.click(Xopen, Yopen)
		pyautogui.press('down')													#Choose the open choise by pushing down and enter 		
		pyautogui.press('enter')

		time.sleep(3)															#Give the program time to open the Open option 

		for x in range(1,self.nmbr_tabs):										#This loop tabs it way in the Metfy to a specific spot in the program so the program can access the files  
			pyautogui.press('tab')
		
		pyautogui.press('down')													#Push down and then up to mark the most recent added file 	
		pyautogui.press('up')
		pyautogui.press('enter')												#Push Enter to choose the specific file to process 
			
		time.sleep(3)														
		#pyautogui.click(Xbin, Ybin)

		pyautogui.press('enter')												#Presses enter to open the file 

		time.sleep(3)															#Gives time for the program to close the Open Window
		pyautogui.click(self.X_proc, self.Y_proc)								#Mouse click on the process button 
		pyautogui.click(self.X_ReedSolomon, self.Y_ReedSolomon)					#Mouse click in ReedSolomon box 
		time.sleep(30)															#Adjust depending on process time could be different long depending on file
		
		p.kill() 																#kills the process aka the MetFY program
		
	def OpenForFengyun(self,glob_file_path):
		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'
		#path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		#path_to_file2 = 'C:\\Ruag_program\\pictures\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 
		app = application.Application().start(path_to_MetFy3x)						#Måste startas med denna
		app.MetFY3x_Processor_v.MenuSelect('File->Open')
		app.Open.Edit.SetText("C:\\Ruag_program\\xhrpt_decoder")
		app.Open.Open.Click()
		app.Open.Edit.SetText(glob_file_path)
		app.Open.Open.Click()
		app.MetFY3x_Processor_v.derandomize.Click()
		app.MetFY3x_Processor_v.Process.Click()
		time.sleep(20)
		app.kill()
		'''
		
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader

		p=subprocess.Popen([path_to_MetFy3x]) 									#Opens a subprocess, starts MetFy3x and then goes directly to the next line in the code

		time.sleep(5)															#To give Metfy time to start up
		pyautogui.click(self.X_file, self.Y_file)								#Click on the file option in the menubar

		time.sleep(1)															#Gives the program time to open dialog window
		#pyautogui.click(Xopen, Yopen)
		pyautogui.press('down')													#Choose the open choise by pushing down and enter
		pyautogui.press('enter')

		time.sleep(3)															#Give the program time to open the Open option

		for x in range(1,self.nmbr_tabs):										#This loop tabs it way in the Metfy to a specific spot in the program so the program can access the files
			pyautogui.press('tab')
		
		pyautogui.press('down')													#Push down and then up to mark the most recent added file 
		pyautogui.press('up')
		pyautogui.press('enter')												#Push Enter to choose the specific file to process 
			
		time.sleep(3)
		#pyautogui.click(Xbin, Ybin)

		pyautogui.press('enter')												#Presses enter to open the file

		time.sleep(3)															#Gives time for the program to close the Open Window
		#pyautogui.click(self.X_deRand,self.Y_deRand)
		pyautogui.click(self.X_proc, self.Y_proc)								#Mouse click on the process button

		time.sleep(60)															#Adjust depending on process time could be different long depending on file
		
		p.kill()																#kills the process aka the MetFY program
		
#----------------------------------------------------------------#
	#CHECKFILES()

	#The CheckFiles class conatins code to lock the Main function
	#for 16.5 min so the tracker can finish, if needed this could
	#be adjust. 

#----------------------------------------------------------------#

class CheckFiles():

	def check_file_size(self,filepath):
		a=0
		try:
			print(filepath)
			while (a==0):
				file_size_1=os.path.getsize(filepath)			#Check files size and wait 16.5 min   
				print('wait for 16.5 min')
				time.sleep(20)
				file_size_2=os.path.getsize(filepath)			#Check the file size again 	
				if (file_size_1!=file_size_2):					#Compare if they are equal it means the tracker processing is done and it breaks the loop
					print('Inside the if loop')
					a=1

		except KeyboardInterrupt:
			print('interrupted!')			
class TimePause():

	def pause_file(self):
		time.sleep(120)
		print("waiting 17")