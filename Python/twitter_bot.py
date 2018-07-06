import time
import sys
import pyautogui
from pywinauto.application import Application
from pywinauto import Desktop

path_to_screenshot= "C:\\Users\\Ruag\\Pictures\\Screenshots"
pyautogui.PAUSE = 0.2

class Tweet():
	def tweet_auto(self):

			app=Application().start('explorer.exe "C:\\Users\\Ruag\\Pictures\\Screenshots"')
			# connect to another process spawned by explorer.exe
			t0 = time.time()
			app = Application(backend="uia").connect(path="explorer.exe", title="Screenshots")
			print("first")
			app.Screenshots.set_focus()
			time.sleep(4)
			t1 = time.time()
			total = t1-t0
			print(total)
			#Share_files = app.Screenshots.ItemsView.get_item('-fc')
			#Share_files.right_click_input()
			#app.ContextMenu.Properties.invoke()
			print("up and down")
			pyautogui.press('down')
			pyautogui.press('up')
			#pyautogui.keyDown('shift')  # hold down the shift key
			pyautogui.hotkey('shift', 'F10')
			app.ContextMenu.Share.invoke()
			#app.Screenshots.Wait('enabled')
			#app.DialogScreenshots.Twitter.Click()
			time.sleep(1)
			for x in range(0,2):
				pyautogui.hotkey('Tab')
			pyautogui.hotkey('Enter')
			#app.ScreenshotsDialog.Tweeta.ContextMenulick()
			time.sleep(3)

			for x in range(0,5):
				pyautogui.hotkey('Tab')
			pyautogui.hotkey('Enter')
			time.sleep(15)					

			pyautogui.hotkey('alt','F4')
			app.kill()		
'''
if __name__ == '__main__':
	try:
		tweet_test1()
		
	except KeyboardInterrupt:
		print("stop")	
'''