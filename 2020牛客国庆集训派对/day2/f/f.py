

def mul(a, b):
	res = [
		[0, 0, 0, 0],
		[0, 0, 0, 0],
		[0, 0, 0, 0],
		[0, 0, 0, 0]
	]
	for i in range(0, 4):
		for j in range(0, 4):
#			res[i][j] = 0
			for k in range(0, 4):
				res[i][j] += a[i][k] * b[k][j]
#print(res[i][j])
	return res


def gao(base, res, n):
	while n > 0:
		if (n & 1) == 1:
			res = mul(res, base)
		base = mul(base, base)
		n >>= 1
	return res	


T = int(input())

for i in range(T):
	n = int(input())
	base = [
		[1, 0, 0, 0],
		[1, 1, 0, 0],
		[0, 1, 1, 0],
		[0, 0, 1, 1]
	]
	res = [
		[1, 3, 3, 1],
		[0, 0, 0, 0],
		[0, 0, 0, 0],
		[0, 0, 0, 0]
	]
#	res = mul(res, base)
#	res = mul(res, base)
#	for i in range (4):
#		print(res[0][i], end=" ")
#print("")
#	res = mul(res, base);
	res = gao(base, res, n - 1)
	print(res[0][0] ** 2)
