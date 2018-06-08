import os
import glob

#Set global var. if open var. is hrp, C10 or raw16 delete all other files except that one 
#Compare date and on top of that compare the time if the same type satelites comes after eachother
class DeleteFiles()
	
	def remove_when_metop():
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
		#Here there is going to be a small problem with taking away the older one maybe 
		#Compare dates then time in the file names

	if (globvar==1):
		remove_when_metop()
	if (globvar==2):
		remove_when_fengyun()
	if (globvar==3):
		remove_when_noaa()
	if (globvar==4):
		#what to do with the Meteor	



