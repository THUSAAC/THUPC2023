import random
import os
import datetime
import numpy as np

TASK_NUM = 1

N_LIMIT = 100
L_LIMIT = 6

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write(f"[{datetime.datetime.now()}] {string}\n")

def gcd(a, b):
	if b == 0:
		return a
	c = a % b
	while c != 0:
		a = b
		b = c
		c = a % b
	return b

def genHack1(n, l, **extra_param):
	assert l == 6
	return ["0.000000"] * (n - 4) + ["0.007812", "0.062500", "0.062500", "0.867188"]

def genHack2(n, l, **extra_param):
	assert l == 6
	return ["0.000000"] * (n - 4) + ["0.023438", "0.144531", "0.144531", "0.687500"]

def genZerosOne(n, l, **extra_param):
	return ["0." + "0" * l] * (n - 1) + ["1." + "0" * l]

def genMaxChecks(n, l, num_ones = 1, **extra_param):
	assert l == 6
	return ["0.000000"] * (n - num_ones - 1) + ["0.000001"] * num_ones + [f"0.{10 ** 6 - num_ones :06d}"]

def genMaxAnswer(n, l, **extra_param):
	assert n == 100 and l == 6
	return list(map(lambda x: f"{x:.{l}f}", [i / 1000000 for i in range(45, 45 + 93)] + [
		0.007162, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5
	]))

def genEqual(n, l, **extra_param):
	assert 10 ** l % n == 0
	return [f"{1 / n:.{l}f}"] * n

def getDivisor(n, l, **extra_param):
	return np.random.default_rng().integers(1, min(10 ** l, 4 * 10 ** (l / 2)))

def genUniform(n, l, divisor = None, **extra_param):
	if divisor is None:
		divisor = 10 ** l
	elif callable(divisor):
		divisor = divisor(n, l, **extra_param)
	else:
		assert isinstance(divisor, int)
	
	rng = np.random.default_rng()
	prob = np.ones(n) / n
	while True:
		d = rng.multinomial(divisor, prob)
		if d[0] > 1:
			g = d[0]
			for i in range(1, n):
				g = gcd(g, d[i])
				if g == 1:
					break
			else:
				continue
		return list(map(lambda x: f"{x:.{l}f}", d / divisor))

def genSilentMajority(n, l, divisor = None, num_speakers = 1, voice = 100, **extra_param):
	if divisor is None:
		divisor = 10 ** l
	elif callable(divisor):
		divisor = divisor(n, l, **extra_param)
	else:
		assert isinstance(divisor, int)
	
	rng = np.random.default_rng()
	prob = np.array([1] * (n - num_speakers) + [voice] * num_speakers)
	prob = prob / prob.sum()
	while True:
		d = rng.multinomial(divisor, prob)
		if d[0] > 1:
			g = d[0]
			for i in range(1, n):
				g = gcd(g, d[i])
				if g == 1:
					break
			else:
				continue
		return list(map(lambda x: f"{x:.{l}f}", d / divisor))

def genArithmetic(n, l, divisor = None, a1 = 1, common_diff = 5, **extra_param):
	if divisor is None:
		divisor = 10 ** l
	elif callable(divisor):
		divisor = divisor(n, l, **extra_param)
	else:
		assert isinstance(divisor, int)
	
	rng = np.random.default_rng()
	prob = np.arange(a1, a1 + n * common_diff, common_diff)
	prob = prob / prob.sum()
	while True:
		d = rng.multinomial(divisor, prob)
		if d[0] > 1:
			g = d[0]
			for i in range(1, n):
				g = gcd(g, d[i])
				if g == 1:
					break
			else:
				continue
		return list(map(lambda x: f"{x:.{l}f}", d / divisor))

def genTestcase(filename, n, l, gen, **extra_param):
	log(f"Generating input for case {filename}, params: {n = }, {l = }, {gen.__name__}, {extra_param = }")
	# assert ..., "Parameters invalid!"
	while True:
		p = gen(n, l, **extra_param)
		if 1 - 1e-9 < sum(map(float, p)) < 1 + 1e-9:
			break
	
	assert n == len(p) and 1 <= n <= N_LIMIT
	assert 1 <= l <= L_LIMIT
	for x in p:
		assert isinstance(x, str) and 0 <= float(x) <= 1 and len(x) == l + 2

	with open(f"{filename}.in", "w") as f:
		print(n, file = f)
		for x in p:
			print(x, file = f)
	log(f"Generating output for case {filename}")
	os.system(f'(time {os.path.join("..", "MirageFlameSword", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, n, l, gen, **extra_param):
		self.cnt += 1
		genTestcase(f"{self.prefix}{self.cnt}", n, l, gen, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
# sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log(f"Generating subtask {i}")
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	
	testcase.gen(100, 6, genUniform)
	testcase.gen(100, 1, genSilentMajority, num_speakers = 3, voice = 40)
	testcase.gen(100, 2, genEqual)
	testcase.gen(20, 3, genUniform, divisor = getDivisor)
	testcase.gen(100, 4, genUniform)
	testcase.gen(14, 5, genArithmetic, divisor = 623)

	testcase.gen(100, 6, genUniform, divisor = getDivisor)
	testcase.gen(100, 6, genSilentMajority, num_speakers = 3)
	testcase.gen(100, 6, genSilentMajority, num_speakers = 3, divisor = getDivisor)
	testcase.gen(100, 6, genArithmetic)

	# Corner cases
	testcase.gen(1, 6, genZerosOne)
	testcase.gen(100, 6, genZerosOne)
	testcase.gen(100, 6, genMaxChecks)
	testcase.gen(100, 6, genMaxChecks, num_ones = 99)
	testcase.gen(100, 6, genMaxAnswer)
	testcase.gen(100, 6, genHack1)
	testcase.gen(100, 6, genHack2)
	
	# add testcases above		
	log(f"Subtask {i} done. ({pre + 1} - {testcase.cnt})")
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
