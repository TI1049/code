

a = [0] * 500
a[1] = 1
a[2] = 1

for i in range(3, 500):
	a[i] = a[i - 1] + a[i - 2]

while True:
	n = int(input())
	if n == -1:
		break
	print("Hour: %d: %d cow(s) affected" % (n, a[n]))
