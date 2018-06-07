import os 
import subprocess
import time
import pyautogui

Xpos=806
Ypos=950
nmbr_tabs=10

pyautogui.PAUSE = 1			#Wait 1 second pause after each function call	
pyautogui.FAILSAFE = True 	#move the mouse far up to the left corner will crash the program

path_to_Hrpt_Reader = 'C:\\Tools\\Satsignal\\hrpt-reader.3.0.8\\ReadHRPT'		#Path to the HRPT Reader
path_to_file1 = 'C:\\Users\\Rickard\\Downloads\\2012-09-22_1134_M02.hpt'		#Path to the processed file 
path_to_file2 = 'C:\\Users\\Rickard\\Downloads\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 


subprocess.Popen([path_to_Hrpt_Reader, path_to_file1]) 			#Opens a subprocess and then goes directly to the next line in the code

time.sleep(5)
pyautogui.press('enter')

time.sleep(5)

pyautogui.press('enter')

for x in range(1,nmbr_tabs):
	pyautogui.press('tab')

pyautogui.press('down')
pyautogui.press('up')
pyautogui.press('enter')
pyautogui.press('enter')

