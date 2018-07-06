#--------------------------------------------------------#
	
	#TWITTER BOT

	#This function shares the most recent JPG file 
	#and uploads it on twitter through GUI automation

#--------------------------------------------------------#

import time
import sys
import pyautogui
from pywinauto.application import Application
from pywinauto import Desktop

pyautogui.PAUSE = 0.2																			#Sets the puase between pyautogui commands in seconds  

class Tweet():
	def tweet_auto(self):

			app=Application().start('explorer.exe "C:\\Users\\Ruag\\Pictures\\Screenshots"')	#Starts the file explorer and opens the Screenshots folders  			
			
			#before line 15 when running the whole program it is a delay of about 90 seconds thats not occuring when running the script seperatly didn't got time to->
			#figur this one out but good to know 

			app = Application(backend="uia").connect(path="explorer.exe", title="Screenshots")	#This command connects the app object to the Window named Screenshots runned by explorer.exe
			app.Screenshots.set_focus()															#Sets the Screenshots window in focus	
			time.sleep(4)																		#Puase so everything is up and in focus 				
			pyautogui.press('down')																#Moves the marker in the folder up and down
			pyautogui.press('up')
			
			pyautogui.hotkey('shift', 'F10')													#Keybord command to right click on the marked file
			app.ContextMenu.Share.invoke()														#Click on the Share alternativ in the dialog window created by the right click
			time.sleep(1)																		#Pause the program one second so the next window has time to pop up
			
			for x in range(0,2):																#This Loop presses tab 3 times to choose the Twitter program 
				pyautogui.hotkey('Tab')
			pyautogui.hotkey('Enter')															#Starts the Twitter program	
			
			time.sleep(3)																		#Pause the prgram so Twitter got time to open up

			for x in range(0,5):																#This Loop presses tab 6 times to mark the Tweet button 
				pyautogui.hotkey('Tab')	
			pyautogui.hotkey('Enter')															#Tweets the image 
			time.sleep(15)																		#Puases the program so it got time to upload the image

			pyautogui.hotkey('alt','F4')														#If for example there is no internet connection the twitter window is closed, if everthing works it closes the file explorer 
			app.kill()																			#If it is something whent wrong and the file explorer is still up this one kills that process otherwise it dosen't do anything 
'''
#To Test the twitter_bot seperatly outcomment main and run the file in cmd 

if __name__ == '__main__':
	try:
		tweet_test1()
		
	except KeyboardInterrupt:
		print("stop")	
'''