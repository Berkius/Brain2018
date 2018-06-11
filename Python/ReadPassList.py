import os 

class ReadPassList():
	
	#Maybe write an init function here
	globvar = 0

	def set_globvar(self,globvar):
	    def trick(arg):							#A small function to set the global variable to the argument
	        global globvar
	        globvar = arg
	    trick(globvar)
	
	def print_globvar(self):   
		print(globvar) 

	def ReadFile(self):					#As arg: self,Path
		i=0
		file = open("C:\\Users\\Rickard\\Desktop\\Brains2018\\PassList.txt", "r") 	#put path as argument 
		lines=file.readlines()

		#for i in range(0,len(lines)):

			#look for file in folder with event handler 
				
		if 'FENG' in lines[0]:
			self.set_globvar(2)
			self.print_globvar()
			print(lines[0])

		'''	
				#do function for proccessing
					#DeleteFiles
					 
				if 'METOP' in lines[i]:
					self.set_globvar(1)
					self.print_globvar()
					print(lines[i])
					#do function for proccessing
				if 'METEOR' in lines[i]:
					self.set_globvar()
					self.print_globvar()
					print('RUS??? Do not want')
					#skipp?
				if 'NOAA' in lines[i]:
					self.set_globvar(3)
					self.print_globvar()
					print('Go go go NOAA')
					#call function for HRPT_Reader	



#for line in file:
#	i=i+1
#	if (i==8):
#		print(line)
#		if(line[4]=='F'):
#			print("success")
#			#Put function for Fengyun here  
#		if(line[7]=='O'):
#			print('success MET')	
#			#put funtion for Metop her 
#		else: 
#			print("sorry")
'''
if __name__ == '__main__':
	rpl=ReadPassList()
	rpl.ReadFile()
	#hämta class och printa imorgon
	

