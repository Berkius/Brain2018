
import os 

#look for file in folder with EventHandler
#if file wait 15 minutes after opening delete everything except 
i=0

file = open("C:\\Users\\Rickard\\Desktop\\Brains2018\\PassList.txt", "r") 
lines=file.readlines()

for i in range(0,len(lines)):

	#look for file in folder with event handler 
	#Maybe write code to skip line to when overlapping
		
		if 'FENG' in lines[i]:
			print(lines[i])
			#do function for proccessing

		if 'METOP' in lines[i]:
			print(lines[i])
			#do function for proccessing
		if 'METEOR' in lines[i]:
			print('RUS??? Do not want')
			#skipp?
		if 'NOAA' in lines[i]:
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


