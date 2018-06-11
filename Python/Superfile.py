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

		pyautogui.PAUSE = 0.5			#Wait 1 second pause after each function call	
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

class DeleteFiles():
	
	def remove_when_metop():
		
		eventhandler.return_globPath()
		pathlist=glob.glob("C:\\Users\\Rickard\\Downloads\\*.HPT")				#Byt ut den här pathen
		print(pathlist)
		length_of_pathlist=len(pathlist)
		print(length_of_pathlist)
		eventhandler.set_globtemp(0)

		if (length_of_pathlist>1):									
			for x in range(0,length_of_pathlist):
				#print('en kvar')
				if(pathlist[0]!=eventhandler.return_globPath()):
					os.remove(pathlist[x])
					#print('Success!!!')


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

		eventhandler.return_globPath()
		pathlist=glob.glob("C:\\Users\\Rickard\\Downloads\\*.C10")				#Byt ut den här pathen
		print(pathlist)
		length_of_pathlist=len(pathlist)
		print(length_of_pathlist)
		eventhandler.set_globtemp(0)

		if (length_of_pathlist>1):									
			for x in range(0,length_of_pathlist):
				#print('en kvar')
				if(pathlist[0]!=eventhandler.return_globPath()):
					os.remove(pathlist[x])
					#print('Success!!!')
		
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

		eventhandler.return_globPath()
		pathlist=glob.glob("C:\\Users\\Rickard\\Downloads\\*.RAW16")				#Byt ut den här pathen
		print(pathlist)
		length_of_pathlist=len(pathlist)
		print(length_of_pathlist)
		eventhandler.set_globtemp(0)

		if (length_of_pathlist>1):									
			for x in range(0,length_of_pathlist):
				#print('en kvar')
				if(pathlist[0]!=eventhandler.return_globPath()):
					os.remove(pathlist[x])
					#print('Success!!!')

class EventHandler(FileSystemEventHandler):
	patterns = ["*.raw16", "*.bin"]					#Which files to look for 

	def set_globtemp(self,globtemp):
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globtemp
	        globtemp = arg
	    trick(globtemp)

	def return_globtemp(self):
		return globtemp    

	def set_globvar(self,globvar):
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globvar
	        globvar = arg
	    trick(globvar)

	def return_globvar(self):
		return globvar    

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
	    if 'Metop' in event.src_path and event.event_type=='created':
	    	print('Nu ser det lovande ut')
	    	self.set_globvar(1)
	    	print(globvar)
	    	self.set_globtemp(1)
	    	while (self.return_globtemp()==1):
	    		pass

	    if 'FY' in event.src_path and event.event_type=='created':
	    	print('Jajamensan')
	    	self.set_globvar(2)
	    	print(globvar)
	    	self.set_globtemp(1)
	    	while (self.return_globtemp()==1):
	    		pass
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
		X_file=326					#Coordinates for file tab
		Y_file=242					#Coordinates for file tab
		X_open=335					#Coordinates for open folder where the files after
		Y_open=275					#Coordinates for open folder where the files after
		X_bin=1297					#Coordinates for the file at the top in the folder
		Y_bin=460					#Coordinates for the file at the top in the folder
		X_proc=1039					#Coordinates for the process button	
		Y_proc=280					#Coordinates for the process button	

		pyautogui.PAUSE = 0.5			#Wait 1 second pause after each function call	
		pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

		path_to_MetFy3x = 'C:\\Users\\Rickard\\Downloads\\MetFy3x'							#Path to the HRPT Reader

		p=subprocess.Popen([path_to_MetFy3x]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.click(X_file, Y_file)

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
		pyautogui.click(X_proc, Y_proc)				#Mouse click for 

		time.sleep(30)								#Adjust depending on process time could be different long depending on file
		
		p.kill() 									#kills the MetFY program

	def OpenForFengyun(self):

		nmbr_tabs=8					#Numbers of tabs for the metfy
		X_file=326					#Coordinates for file tab
		Y_file=242					#Coordinates for file tab
		X_open=335					#Coordinates for open folder where the files after
		Y_open=275					#Coordinates for open folder where the files after
		X_bin=1297					#Coordinates for the file at the top in the folder
		Y_bin=460					#Coordinates for the file at the top in the folder
		X_deRand=792				#Coordinates for DeRandomizer alternativ box
		Y_deRand=279				#Coordinates for DeRandomizer alternativ box
		X_proc=1039					#Coordinates for the process button	
		Y_proc=280					#Coordinates for the process button	

		pyautogui.PAUSE = 0.5		#Wait 1 second pause after each function call	
		pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

		path_to_MetFy3x = 'C:\\Users\\Rickard\\Downloads\\MetFy3x'							#Path to the HRPT Reader

		p=subprocess.Popen([path_to_MetFy3x]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.click(X_file, Y_file)

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
		pyautogui.click(X_deRand,Y_deRand)
		pyautogui.click(X_proc, Y_proc)				#Mouse click for 

		time.sleep(30)								#Adjust depending on process time could be different long depending on file
		
		p.kill()	

