import win32com.client
import os 
import subprocess
import time

shell = win32com.client.Dispatch("WScript.Shell")

path_to_Hrpt_Reader = 'C:\\Tools\\Satsignal\\hrpt-reader.3.0.8\\ReadHRPT'		#Path to the HRPT Reader
path_to_file = 'C:\\Users\\Rickard\\Downloads\\FY3B_2012-05-01_1419.C10'		#Path to the processed file 

p=subprocess.call([path_to_Hrpt_Reader, path_to_file])

#poll=p.poll()

#while poll is None:
#	poll=p.poll()
#	pass
time.sleep(5)

shell.SendKeys("{ENTER}", 0)
