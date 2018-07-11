#----------------------------------------------------------------#
	
	#SUPERFILE.PY

	#This File contians all the relevant classes and functions
	#used to be able to run the image processing automatically. 
	#The only class used outside this file is the class Tweet()
	#in the file twitter_bot.py. 

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

	#OpenReader class cantains code for opening the program 
	#HRPT Reader if needed and also code to open new files in 
	#this program. 

#----------------------------------------------------------------#		

class OpenReader():
	
	nmbr_tabs=10					#Number of tabs to get to the most recent image when opening a new file
	pyautogui.PAUSE = 0.01			#Wait 0.01 second after each pyautogui function call	
	pyautogui.FAILSAFE = True 		#Move the mouse far up to the left corner will stopp the pyautogui program

	def OpenProgram(self):																	#Function to Open the HRPT Reader 

		path_to_Hrpt_Reader = 'C:\\Ruag_program\\hrpt-reader.3.0.8\\ReadHRPT'				#Path to the HRPT Reader
		path_to_file1 = 'C:\\Ruag_program\\xhrpt_decode\\NOAA-18_HRPT_20180704_080843'		#Path to a processed file, only to put up a picture when the program is started   

		p=subprocess.Popen([path_to_Hrpt_Reader, path_to_file1]) 							#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)																		#Pause the program so the HRPT Reader gets time to pop up 
		pyautogui.press('enter')															#Press Enter 

		time.sleep(2)																		

	def OpenNewFile(self):																	#Opens up a new file in Hrpt Reader, hardcoded button presses 

		try:
			pyautogui.press('enter')															#Presses the by default marked Open button  
			time.sleep(2)																		#Waits two seconds for the open window to pop up

			for x in range(1,self.nmbr_tabs):													#This loop and the lines underneeth tabs its way to the most recently added file  
				pyautogui.press('tab')															#virtual tab

			pyautogui.press('down')																#Move marker down
			pyautogui.press('up')																#Move marker up
			pyautogui.press('enter')															#opens the marked file 
			pyautogui.press('left')																#Southbound or Northbound. When "left" then Southbound is choosen, when "Right" the Northbound is choosen
			pyautogui.press('enter')															#pushes north- or southbound 

		except KeyboardInterrupt:
			print('interrupted!')
				

#---------------------------------------------------------------#

	#DELETEFILES()

	#The DeleteFiles class conatins code for deleting previous 
	#files and also extra files created by MetFy3x. 

#---------------------------------------------------------------#

class DeleteFiles():
	
	def remove_previous(self, path, globpath):												#This function checks if the previous file is of the same type as the new one and if it is it removes the old one
		
		pathlist=glob.glob(path) 															#Creates a list of specific file types decieded by path in a specific folder 
		length_of_pathlist=len(pathlist)													#Check the length of the list

		if (length_of_pathlist>1):															#If there is more then one file of a specific type 											
			for x in range(0,length_of_pathlist):											#loop over these files 
				
				if(pathlist[x]!=globpath):													#If the file checked is not equal to the most recent file 
					os.remove(pathlist[x])													#Remove it 
					
	def remove_when_metop(self):															#Removes all files thats unneccesary after the processing of a metop file is done and olde picture files 

		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):						#glob.glob creates a list, with the specified file name
		  os.remove(BIN)																	#Remove alls files with that specific ending. 

		for RAW16 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"):					#all loop works the same as described above
		  os.remove(RAW16)

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):						#--
		  os.remove(C10)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):						#--
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):						#--
		  os.remove(VCD)																

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):						#--	
		  os.remove(PN)

		for PKT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PKT"):						#--	
		  os.remove(PKT)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):						#--
		  os.remove(MPD) 


	def remove_when_fengyun(self):															#Removes all files thats unneccesary after the processing of a Fengyun file is done and old picture files  
		
		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):						#glob.glob creates a list, with the specified file name
		  os.remove(BIN)																	#Remove all files with that specific ending.

		for RAW16 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"):					#all loop works the same as described above
		  os.remove(RAW16)

		for HPT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):						#--
		  os.remove(HPT)	

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):						#--	
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):						#--
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):						#--
		  os.remove(PN)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):						#--
		  os.remove(MPD)

		for FY3 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.FY3"):						#--
		  os.remove(FY3)  

	def remove_when_noaa(self):																#Removes all files thats unneccesary after the processing of a NOAA file is done and old picture files

		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):						#glob.glob creates a list, with the specified file name
		  os.remove(BIN)																	#Remove all files with that specific ending.

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):						#all loop works the same as described above
		  os.remove(C10)
		
		for HPT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):						#--
		  os.remove(HPT)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):						#--	
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):						#--
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):						#--
		  os.remove(PN)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):						#--
		  os.remove(MPD)

		for FY3 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.FY3"):						#--
		  os.remove(FY3)  


#---------------------------------------------------------------#

	#EVENTHANDLER()

	#The Eventhandler class conatins code for detecting if a
	#specific event occured or if something  changed in a 
	#specific folder

#---------------------------------------------------------------#


class EventHandler(FileSystemEventHandler):
	patterns = ["*.raw16", "*.bin"]			 	#The pattern the observer looks for 

	def set_globtemp(self,globtemp):			#A function to set the global variable globtemp to the argument used in the function call
	    def trick(arg):							
	        global globtemp
	        globtemp = arg
	    trick(globtemp)

	def return_globtemp(self):					#This function returns the value of globtemp
		return globtemp    

	def set_globvar(self,globvar):				#A function to set the global variable globvar to the argument used in the function call	
	    def trick(arg):				
	        global globvar
	        globvar = arg
	    trick(globvar)

	def return_globvar(self):					#This function returns the value of globtemp
		return globvar    

	def set_globPath(self,globPath):			#A function to set the global variable globPath to the argument used in the function call	
	    def trick(arg):
	    	global globPath							
	        globPath = arg
	    trick(globPath)

	def return_globPath(self):					#This function returns the globPath 
		return globPath    	

	def process(self, event):								#This function logs specific events in specific folders. For mor info check the API for the watchdog for more information
	    """
	    event.event_type 
	        'modified' | 'created' | 'moved' | 'deleted'
	    event.is_directory
	        True | False
	    event.src_path
	        path/to/observed/file
	    """
	    #When a file is created the processing starts here
	    if 'Metop' in event.src_path:						#If Metop is in the Path name of the file thats been created 	
	    	if 'bin' in event.src_path:						#If bin is in the Path name of the file thats been created 	
	    		if (event.event_type=='created'):			#And the event type is created
			    	print('METOP')
			    	self.set_globvar(1)						#globvar is set to 1 for the program to know that it is a Metop thats been tracked
			    	#print(globvar)
			    	self.set_globtemp(1)					#globtemp is set to 1 so the observer dosen't detect new file during the time it processing another one
			    	self.set_globPath(event.src_path)		#Sets gloPath to the path of the created file 
			    	while (self.return_globtemp()==1):		#Locks the observer until everything in the main loop and procceising is done 
			    		pass
	    			#self.set_globtemp(0)
	    			print("Nu är vi ute ur whle i watchdog Metop och globtemp Metop=")
	    			print(globtemp)	

	    if 'FY' in event.src_path:							#If FY is in the Path name of the file thats been created 	
	    	if 'bin' in event.src_path:						#If bin is in the Path name of the file thats been created 	
	    		if (event.event_type=='created'):			#And the event type is created
			    	print('FENG')
			    	self.set_globvar(2)						#globvar is set to 2 for the program to know that it is a Fengyun thats been tracked
			    	#print(globvar)
			    	self.set_globtemp(1)					#globtemp is set to 1 so the observer dosen't detect new file during the time it processing another one
			    	self.set_globPath(event.src_path)		#Sets gloPath to the path of the created file 
			    	while (self.return_globtemp()==1):		#Locks the observer until everything in the main loop and procceising is done 
			    		pass
			    	#self.set_globtemp(0)
			    	print("Nu är vi ute ur whle i watchdog Fengyun och globtemp=")
			    	print(globtemp)	
		    
	    if 'NO' in event.src_path and event.event_type=='created':		#If NO is in the Path name of the file thats been created and the event is created	
	    	print('NOAA')
	    	self.set_globvar(3)											#globvar is set to 3 for the program to know that it is a Fengyun thats been tracked
	    	#print(globvar)
	    	self.set_globtemp(1)										#globtemp is set to 1 so the observer dosen't detect new file during the time it processing another one
	    	self.set_globPath(event.src_path)							#Sets gloPath to the path of the created file 
	    	while (self.return_globtemp()==1):							#Locks the observer until everything in the main loop and procceising is done 
	    		pass
	    	#self.set_globtemp(0)
	    	print("Nu är vi ute ur whle i watchdog NOAA och globtemp=")
	    	print(globtemp)	

	    print("end process")	
	    #print(event.src_path, event.event_type)  	# print now only for degug

	def on_modified(self, event):										#If something in the folder is modified this functions sets the event to modified, used it in the beginning but not in this current version
	    self.process(event)

	def on_created(self, event):										#If something in the folder is created this functions sets the event to modified
	    self.process(event)

	#def on_any_event(self,event):										#add if more information about the folder then just pattern files are needed
		#self.process(event)    

#---------------------------------------------------------------#

	#OPENMETFY()

	#The OpenMetFy class conatins code for depending on which
	#satellite is tracked open the extra process program
	#MetFy3x and adjust settings for the specific files 

#---------------------------------------------------------------#


class OpenMetFy():

	nmbr_tabs=8					#Numbers of tabs for the metfy
	X_file=251					#Coordinates for file tab
	Y_file=165					#Coordinates for file tab
	X_proc=730					#Coordinates for the process button	
	Y_proc=210					#Coordinates for the process button	
	X_deRand=570				#Coordinates for DeRandomizer alternativ box
	Y_deRand=192				#Coordinates for DeRandomizer alternativ box
	X_ReedSolomon=569			#Coordinates for ReedSolomon alternativ box
	Y_ReedSolomon=224			#Coordinates for ReedSolomon alternativ box

	pyautogui.PAUSE = 0.5		#Wait 1 second pause after each function call	
	pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

	def OpenForMetop(self,glob_file_path):											#This function puts in the specific settings in MetFy3x for metop files
		
		#This outcommented code only worked on the MetFy3x v0.3.3 unfortunately 

		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'
		path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		path_to_file2 = 'C:\\Ruag_program\\pictures\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 
		print("time to open")
		app = application.Application().start(path_to_MetFy3x)						
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
		try:
			path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader

			p=subprocess.Popen([path_to_MetFy3x]) 									#Opens a subprocess, starts MetFy3x and then goes directly to the next line in the code

			time.sleep(5)															#To give Metfy time to start up 
			pyautogui.click(self.X_file, self.Y_file)								#Click on the file option in the menubar

			time.sleep(1)															#Gives the program time to open dialog window
			#pyautogui.click(Xopen, Yopen)
			pyautogui.press('down')													#Choose the open choise by pushing down and enter
			pyautogui.press('enter')												

			time.sleep(3)															#Give the program time to open the Open option 

			for x in range(1,self.nmbr_tabs):										#This loop tabs it way in the MetFy to a specific spot in the program so the program can access the files
				pyautogui.press('tab')
			
			pyautogui.press('down')													#Push down and then up to mark the most recent added file  
			pyautogui.press('up')
			pyautogui.press('enter')												#Push enter to choose the specific file to process		
				
			time.sleep(3)															 
			#pyautogui.click(Xbin, Ybin)

			pyautogui.press('enter')												#presses enter to Open the file 

			time.sleep(3)															#Gives time for the program to close the Open Window
			pyautogui.click(self.X_proc, self.Y_proc)								#Mouse click on the Process button
			pyautogui.click(self.X_ReedSolomon, self.Y_ReedSolomon)					#Mouse click in the ReedSolomon box
			time.sleep(60)															#Adjust depending on process time could be different long depending on the file size
			
			p.kill() 																#kills the subprocess aka the MetFY program
		except KeyboardInterrupt:
			print('interrupted!')	

	def OpenForFengyun(self,glob_file_path):										#This function puts in the specific settings in MetFy3x for Fengyun files	
		
		#This outcommented code only worked on the MetFy3x v0.3.3 unfortunately 

		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'
		#path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		#path_to_file2 = 'C:\\Ruag_program\\pictures\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 
		app = application.Application().start(path_to_MetFy3x)						
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
		try:
			path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader

			p=subprocess.Popen([path_to_MetFy3x]) 									#Opens a subprocess, starts MetFy3x and then goes directly to the next line in the code

			time.sleep(5)															#To give Metfy time to start up 
			pyautogui.click(self.X_file, self.Y_file)								#Click on the file option in the menubar

			time.sleep(1)															#Gives the program time to open dialog window	
			#pyautogui.click(Xopen, Yopen)
			pyautogui.press('down')													#Choose the open choise by pushing down and enter
			pyautogui.press('enter')													

			time.sleep(3)															#Give the program time to open the Open option 

			for x in range(1,self.nmbr_tabs):										#This loop tabs it way in the MetFy to a specific spot in the program so the program can access the files
				pyautogui.press('tab')
			
			pyautogui.press('down')													#Push down and then up to mark the most recent added file  
			pyautogui.press('up')
			pyautogui.press('enter')												#Push enter to choose the specific file to process		
				
			time.sleep(3)															
			#pyautogui.click(Xbin, Ybin)

			pyautogui.press('enter')												#presses enter to Open the file 

			time.sleep(3)															#Gives time for the program to close the Open Window	
			pyautogui.click(self.X_proc, self.Y_proc)								#Mouse click on the Process button

			time.sleep(60)															#Adjust depending on process time could be different long depending on the file size
			
			p.kill()																#Kills the subprocess aka the MetFY program

		except KeyboardInterrupt:
			print('interrupted!')	


#---------------------------------------------------------------#

	#CHECKFILES()

	#The CheckFiles class contains code to check the file size.
	#When the file size change it means the decoder is finished

#---------------------------------------------------------------#

class CheckFiles():

	def check_file_size(self,filepath):							#This function check the file size and if it changes it lets to of the main program and the imageprocessing starts 

		try:
		#if (filepath!=0)
			print(filepath)
			#if filepath is not the default value...
			while True:
				file_size_1=os.path.getsize(filepath)			#Check file size and wait 5 seconds 
				time.sleep(5)
				file_size_2=os.path.getsize(filepath)			#Check file size again
				if (file_size_1!=file_size_2):					#Compare if they are equal it means the tracker and processing is done and it breaks the loop
					print('file changed size')
					break

		except KeyboardInterrupt:
			print('interrupted!')			
