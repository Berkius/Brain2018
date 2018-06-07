import os 
import subprocess
import time
import pyautogui

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
path_to_file = 'C:\\Users\\Rickard\\Downloads\\MetopA_2012-09-22_113446.bin'		#Path to the processed file 

p=subprocess.Popen([path_to_MetFy3x]) 			#Opens a subprocess and then goes directly to the next line in the code

time.sleep(5)
pyautogui.click(Xfile, Yfile)

time.sleep(3)
pyautogui.click(Xopen, Yopen)

time.sleep(3)
pyautogui.click(Xbin, Ybin)

pyautogui.press('enter')

time.sleep(3)
pyautogui.click(Xproc, Yproc)

