import os 
import subprocess
import time
import pyautogui
import glob
import sys
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

class OpenReader():
	
	def OpenProgram(self):
		Xpos=806
		Ypos=950
		nmbr_tabs=10

		pyautogui.PAUSE = 1			#Wait 1 second pause after each function call	
		pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

		path_to_Hrpt_Reader = 'C:\\Tools\\Satsignal\\hrpt-reader.3.0.8\\ReadHRPT'		#Path to the HRPT Reader
		path_to_file1 = 'C:\\Users\\Rickard\\Downloads\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		path_to_file2 = 'C:\\Users\\Rickard\\Downloads\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 


		p=subprocess.Popen([path_to_Hrpt_Reader, path_to_file1]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.press('enter')

		time.sleep(5)

	def OpenNewFile(self):													#Hacksolution if time try to solve better 
		
		Xpos=806
		Ypos=950
		nmbr_tabs=10

		pyautogui.press('enter')

		for x in range(1,nmbr_tabs):
			pyautogui.press('tab')

		pyautogui.press('down')
		pyautogui.press('up')
		pyautogui.press('enter')
		#pyautogui.press('enter')

class DeleteFiles()
	
	def remove_when_metop():
		for BIN in glob.glob("*.BIN"):		#glob.glob creates a list, with the specified file name
		  os.remove(bin)

		for RAW16 in glob.glob("*.RAW16"):		#glob.glob creates a list, with the specified file name
		  os.remove(raw16)

		for C10 in glob.glob("*.C10"):		#glob.glob creates a list, with the specified file name
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

	def remove_when_fengyun():
		
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


	def remove_when_noaa():
		#Here there is going to be a small problem with taking away the older one maybe 
		#Compare dates then time in the file names

class MyHandler(FileSystemEventHandler):
	
	patterns = ["*.raw16", "*.bin"]					#Which files to look for 

	def set_globvar(self,globvar):
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globvar
	        globvar = arg
	    trick(globvar)

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
	    if 'Metop' in event.src_path and event.event_type=='created':
	    	print('Nu ser det lovande ut')
	    	self.set_globvar(1)
	    	print(globvar)

	    if 'FY' in event.src_path and event.event_type=='created':
	    	print('Jajamensan')
	    	self.set_globvar(2)
	    	print(globvar)

	    #print(event.src_path, event.event_type)  	# print now only for degug

	def on_modified(self, event):
	    self.process(event)

	def on_created(self, event):
	    self.process(event)

	#def on_any_event(self,event):					#add if more information about the folder then just pattern files are needed
		#self.process(event)    

class OpenMetFy():
	
	def OpenForMetop(self):

		nmbr_tabs=8				#Numbers of tabs for the metfy
		Xfile=326					#Cordinates for file tab
		Yfile=242					#Cordinates for file tab
		Xopen=335					#Cordinates for open folder where the files after
		Yopen=275					#Cordinates for open folder where the files after
		Xbin=1297					#Cordinates for the file at the top in the folder
		Ybin=460					#Cordinates for the file at the top in the folder
		Xproc=1039					#Cordinates for the process button	
		Yproc=280					#Cordinates for the process button	

		pyautogui.PAUSE = 1			#Wait 1 second pause after each function call	
		pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

		path_to_MetFy3x = 'C:\\Users\\Rickard\\Downloads\\MetFy3x'							#Path to the HRPT Reader

		p=subprocess.Popen([path_to_MetFy3x]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.click(Xfile, Yfile)

		time.sleep(3)
		#pyautogui.click(Xopen, Yopen)
		pyautogui.press('down')
		pyautogui.press('enter')

		time.sleep(3)

		for x in range(1,nmbr_tabs):
			pyautogui.press('tab')
		
		pyautogui.press('down')
		pyautogui.press('up')
		pyautogui.press('enter')	
			
		time.sleep(3)
		#pyautogui.click(Xbin, Ybin)

		pyautogui.press('enter')

		time.sleep(3)
		pyautogui.click(Xproc, Yproc)				#Mouse click for 

		time.sleep(20)								#Adjust depending on process time could be different long depending on file
		
		p.kill() 									#kills the MetFY program


