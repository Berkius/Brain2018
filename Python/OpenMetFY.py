import os
import sys 
import subprocess
import time
import pyautogui

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

		time.sleep(30)								#Adjust depending on process time could be different long depending on file
		
		p.kill() 									#kills the MetFY program


if __name__ == '__main__':
	OMF=OpenMetFy()
	OMF.OpenForMetop()

