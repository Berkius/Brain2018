import os 
import subprocess
import time
import pyautogui

pyautogui.PAUSE = 1			#Wait 1 second pause after each function call	
pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

path_to_Hrpt_Reader = 'C:\\Tools\\Satsignal\\hrpt-reader.3.0.8\\ReadHRPT'		#Path to the HRPT Reader
path_to_file = 'C:\\Users\\Rickard\\Downloads\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 

p=subprocess.Popen([path_to_Hrpt_Reader, path_to_file]) 			#Opens a subprocess and then goes directly to the next line in the code

pyautogui.PAUSE = 1			#Wait 1 second to start the gui function	
pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

time.sleep(5)
pyautogui.click(806, 950)	