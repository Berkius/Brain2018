import os 
import subprocess
import time
import pyautogui
import glob
import sys
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

class OpenReader():
	
	nmbr_tabs=10
	pyautogui.PAUSE = 0.01			#Wait 1 second pause after each function call	
	pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

	def OpenProgram(self):
		#Xpos=806
		#Ypos=950
		#nmbr_tabs=10

		#pyautogui.PAUSE = 0.5			#Wait 1 second pause after each function call	
		#pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

		path_to_Hrpt_Reader = 'C:\\Ruag_program\\hrpt-reader.3.0.8\\ReadHRPT'		#Path to the HRPT Reader
		path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		#path_to_file2 = 'C:\\Users\\Rickard\\Downloads\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 


		p=subprocess.Popen([path_to_Hrpt_Reader, path_to_file1]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.press('enter')

		time.sleep(5)

	def OpenNewFile(self):													#Hacksolution if time try to solve better 

		pyautogui.press('enter')
		time.sleep(2)

		for x in range(1,self.nmbr_tabs):
			pyautogui.press('tab')

		pyautogui.press('down')
		pyautogui.press('up')
		pyautogui.press('enter')
		pyautogui.press('enter')

class DeleteFiles():
	
	def remove_previous(self, path, globpath):
		
		pathlist=glob.glob(path) 				
		print(pathlist)
		length_of_pathlist=len(pathlist)
		print(length_of_pathlist)

		if (length_of_pathlist>1):									
			for x in range(0,length_of_pathlist):
				
				if(pathlist[x]!=globpath):
					os.remove(pathlist[x])
					
	def remove_when_metop(self):

		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):		#glob.glob creates a list, with the specified file name
		  os.remove(BIN)

		for RAW16 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"):		
		  os.remove(RAW16)

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):		
		  os.remove(C10)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):		
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):		
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):		
		  os.remove(PN)

		for PK in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PKT"):		
		  os.remove(PKT)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):		
		  os.remove(MPD) 

	def remove_when_fengyun(self):
		
		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):		#glob.glob creates a list, with the specified file name
		  os.remove(BIN)

		for RAW16 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RAW16"):		
		  os.remove(RAW16)

		for HPT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):		
		  os.remove(HPT)

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):		
		  os.remove(C10)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):		
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):		
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):		
		  os.remove(PN)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):		
		  os.remove(MPD)

		for FY3 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.FY3"):		
		  os.remove(FY3)  


	def remove_when_noaa(self):

		for BIN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.BIN"):		#glob.glob creates a list, with the specified file name
		  os.remove(BIN)

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):		
		  os.remove(C10)

		for RS in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.RS"):		
		  os.remove(RS)

		for VCD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.VCD"):		
		  os.remove(VCD)

		for PN in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PN"):		
		  os.remove(PN)

		for MPD in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.MPD"):		
		  os.remove(MPD)

		for FY3 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.FY3"):		
		  os.remove(FY3)  

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
	    	print('METOP')
	    	self.set_globvar(1)
	    	print(globvar)
	    	self.set_globtemp(1)
	    	self.set_globPath(event.src_path)
	    	while (self.return_globtemp()==1):
	    		pass

	    if 'FY' in event.src_path and event.event_type=='created':
	    	print('FENG')
	    	self.set_globvar(2)
	    	print(globvar)
	    	self.set_globtemp(1)
	    	self.set_globPath(event.src_path)
	    	while (self.return_globtemp()==1):
	    		pass
	    
	    if 'NO' in event.src_path and event.event_type=='created':
	    	print('NOAA')
	    	self.set_globvar(3)
	    	print(globvar)
	    	self.set_globtemp(1)
	    	self.set_globPath(event.src_path)
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

	nmbr_tabs=8				#Numbers of tabs for the metfy
	X_file=214					#Coordinates for file tab
	Y_file=159					#Coordinates for file tab
	X_proc=692					#Coordinates for the process button	
	Y_proc=186					#Coordinates for the process button	
	X_deRand=527				#Coordinates for DeRandomizer alternativ box
	Y_deRand=185				#Coordinates for DeRandomizer alternativ box

	pyautogui.PAUSE = 0.5		#Wait 1 second pause after each function call	
	pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

	def OpenForMetop(self):
		path_to_MetFy3x = 'C:\\Users\\Rickard\\Downloads\\MetFy3x'
		path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		path_to_file2 = 'C:\\Ruag_program\\pictures\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 
		app = application.Application().start(path_to_MetFy3x)						#Måste startas med denna
		app.MetFY3x_Processor_v.MenuSelect('File->Open')
		app.Öppna.Edit.SetText('MetopA_2012-09-22_113446')
		app.Öppna.Öppna.Click()
		app.MetFY3x_Processor_v.Process.Click()
		time.sleep(30)
		app.kill()
		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader CHANGE THIS

		p=subprocess.Popen([path_to_MetFy3x]) 			#Opens a subprocess and then goes directly to the next line in the code

		#This part underneeth needs to be more developed and fitted to the final computer when we get real files in  
		
		time.sleep(5)
		pyautogui.click(self.X_file, self.Y_file)

		time.sleep(3)
		#pyautogui.click(Xopen, Yopen)
		pyautogui.press('down')
		pyautogui.press('enter')

		time.sleep(3)

		for x in range(1,self.nmbr_tabs):
			pyautogui.press('tab')
		
		pyautogui.press('down')
		pyautogui.press('up')
		pyautogui.press('enter')	
			
		time.sleep(3)
		#pyautogui.click(Xbin, Ybin)

		pyautogui.press('enter')

		time.sleep(3)
		pyautogui.click(self.X_proc, self.Y_proc)				#Mouse click for 

		time.sleep(30)								#Adjust depending on process time could be different long depending on file
		
		p.kill() 									#kills the MetFY program
		'''
	def OpenForFengyun(self):
		path_to_MetFy3x = 'C:\\Users\\Rickard\\Downloads\\MetFy3x'
		path_to_file1 = 'C:\\Ruag_program\\pictures\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
		path_to_file2 = 'C:\\Ruag_program\\pictures\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 
		app = application.Application().start(path_to_MetFy3x)						#Måste startas med denna
		app.MetFY3x_Processor_v.MenuSelect('File->Open')
		app.Öppna.Edit.SetText('MetopA_2012-09-22_113446')
		app.Öppna.Öppna.Click()
		app.MetFY3x_Processor_v.derandomize.Click()
		app.MetFY3x_Processor_v.Process.Click()
		time.sleep(30)
		app.kill()
		
		'''
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader

		p=subprocess.Popen([path_to_MetFy3x]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.click(self.X_file, self.Y_file)

		time.sleep(3)
		#pyautogui.click(Xopen, Yopen)
		pyautogui.press('down')
		pyautogui.press('enter')

		time.sleep(3)

		for x in range(1,self.nmbr_tabs):
			pyautogui.press('tab')
		
		pyautogui.press('down')
		pyautogui.press('up')
		pyautogui.press('enter')	
			
		time.sleep(3)
		#pyautogui.click(Xbin, Ybin)

		pyautogui.press('enter')

		time.sleep(3)
		pyautogui.click(self.X_deRand,self.Y_deRand)
		pyautogui.click(self.X_proc, self.Y_proc)				#Mouse click for 

		time.sleep(30)								#Adjust depending on process time could be different long depending on file
		
		p.kill()	
		'''
class CheckFiles():

	def check_file_size(self,filepath):

		while True:
			file_size_1=os.path.getsize(filepath)
			time.sleep(5)
			file_size_2=os.path.getsize(filepath)
			if (file_size_1==file_size_2):
				break

class TimePause():

	def pause_file(self):
		time.sleep(4)
		print("testing")