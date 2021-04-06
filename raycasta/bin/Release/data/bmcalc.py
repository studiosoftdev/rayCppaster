import statistics as s

file = open("ft.txt", "r")
lines = file.readlines()

#avg = 0
#i = 0

#for line in lines:
	#avg += int(line)
	#i += 1

#print(str(round(1/((avg*0.001)/i),2)) + "\n")

data = [float(1/(float(lines[i])*0.001)) for i in range(0,len(lines))]
stdev = s.stdev(data)
mean = s.mean(data)
print("FPS: " + str(round(mean, 2)) + " (stdev: " + str(round(stdev, 2)) + ")\n")
