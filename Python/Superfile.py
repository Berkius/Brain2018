import os 
import subprocess
import time
import pyautogui
import glob
from pywinauto import application
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
		path_to_file1 = 'C:\\Ruag_program\\xhrpt_decode\\NOAA-18_HRPT_20180704_080843'		#Path to the processed file 
		#path_to_file2 = 'C:\\Users\\Rickard\\Downloads\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 


		p=subprocess.Popen([path_to_Hrpt_Reader, path_to_file1]) 			#Opens a subprocess and then goes directly to the next line in the code

		time.sleep(5)
		pyautogui.press('enter')

		time.sleep(2)

	def OpenNewFile(self):													#Opens up a new file in Hrpt Reader, hardcoded button presses 

		pyautogui.press('enter')
		time.sleep(2)

		for x in range(1,self.nmbr_tabs):
			pyautogui.press('tab')

		pyautogui.press('down')
		pyautogui.press('up')
		pyautogui.press('enter')
		pyautogui.press('left')
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

		for PKT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.PKT"):	
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

		for C10 in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.C10"):		
		  os.remove(C10)
		
		for HPT in glob.glob("C:\\Ruag_program\\xhrpt_decoder\\*.HPT"):		
		  os.remove(HPT)

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


	def set_globPath(self,globPath):			#A function to set the global variable globPath to the argument used in the function call	
	    def trick(arg):
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
	    if 'Metop' in event.src_path:
	    	if 'bin' in event.src_path:	
	    		if (event.event_type=='created'):
			    	print('METOP')
			    	self.set_globvar(1)
			    	#print(globvar)
			    	self.set_globtemp(1)
			    	self.set_globPath(event.src_path)
			    	while (self.return_globtemp()==1):
			    		pass
	    			#self.set_globtemp(0)
	    	print("Nu är vi ute ur whle i watchdog Metop och globtemp Metop=")
	    	print(globtemp)	

	    if 'FY' in event.src_path:
	    	if 'bin' in event.src_path:	
	    		if (event.event_type=='created'):
			    	print('FENG')
			    	self.set_globvar(2)
			    	#print(globvar)
			    	self.set_globtemp(1)
			    	self.set_globPath(event.src_path)
			    	while (self.return_globtemp()==1):
			    		pass
			    	#self.set_globtemp(0)
			    	print("Nu är vi ute ur whle i watchdog Fengyun och globtemp=")
			    	print(globtemp)	
		    
	    if 'NO' in event.src_path and event.event_type=='created':
	    	print('NOAA')
	    	self.set_globvar(3)
	    	#print(globvar)
	    	self.set_globtemp(1)
	    	self.set_globPath(event.src_path)
	    	while (self.return_globtemp()==1):
	    		pass
	    	#self.set_globtemp(0)
	    	print("Nu är vi ute ur whle i watchdog NOAA och globtemp=")
	    	print(globtemp)	

	    print("end process")	
	    #print(event.src_path, event.event_type)  	# print now only for degug

	def on_modified(self, event):
	    self.process(event)

	def on_created(self, event):
	    self.process(event)

	#def on_any_event(self,event):					#add if more information about the folder then just pattern files are needed
		#self.process(event)    

class OpenMetFy():

	nmbr_tabs=8				#Numbers of tabs for the metfy
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

	def OpenForMetop(self,glob_file_path):
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
		path_to_MetFy3x = 'C:\\Ruag_program\\MetFy3x'							#Path to the HRPT Reader CHANGE THIS

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
		pyautogui.click(self.X_proc, self.Y_proc)				#Mouse click for 
		pyautogui.click(self.X_ReedSolomon, self.Y_ReedSolomon)
		time.sleep(30)								#Adjust depending on process time could be different long depending on file
		
		p.kill() 									#kills the MetFY program
		
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
		#pyautogui.click(self.X_deRand,self.Y_deRand)
		pyautogui.click(self.X_proc, self.Y_proc)				#Mouse click for 

		time.sleep(60)								#Adjust depending on process time could be different long depending on file
		
		p.kill()	
		
class CheckFiles():

	def check_file_size(self,filepath):
		a=0
		try:
			print(filepath)
			while (a==0):
				file_size_1=os.path.getsize(filepath)			#check files size, when they are equal keep on checking 
				print('wait for 16.5 min')
				time.sleep(990)
				file_size_2=os.path.getsize(filepath)
				if (file_size_1!=file_size_2):					#when they are not break Change to not equal before live!!!
					print('Inside the if loop')
					a=1

		except KeyboardInterrupt:
			print('interrupted!')			
class TimePause():

	def pause_file(self):
		time.sleep(120)
		print("waiting 17")