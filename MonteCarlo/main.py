import random

##基础，在边长为一的正方形状内，坐标范围为[0,1]
def MonteCarlo_1(n):
    count = 0
    for _ in range(n):
        x = random.random()
        y = random.random()
        if x ** 2 + y ** 2 <= 1:
            count += 1
    return 4*count/n

##增加正方形的边长2，坐标范围为[-1,1]
def MonteCarlo_2(n):
    count = 0
    for _ in range(n):
        x = random.uniform(-1, 1)
        y = random.uniform(-1, 1)
        if x ** 2 + y ** 2 <= 1:
            count += 1
    return 4*count/n

##增加参数，可以调节正方形的大小,坐标在[-length/2,length/2]之间
def MonteCarlo_3(n,length):
    count = 0
    for _ in range(n):
        x = random.uniform(-length/2,length/2)
        y = random.uniform(-length/2,length/2)
        if x ** 2 + y ** 2 <= (length/2)**2:
            count += 1
    return 4*count/n

##提高精度，我们不采取随机数，而是直接确定分析（强制让点分布得更加均匀）
def MonteCarloHigh(L, k):
    n = k * k
    count = 0
    for i in range(k):
        for j in range(k):
            x = (i + 0.5) * L / k
            y = (j + 0.5) * L / k
            if (x - L/2)**2 + (y - L/2)**2 <= (L/2)**2:
                count += 1
    return 4 * count / n

n_values = [100, 1000, 10000, 100000, 1000000,1000000]
n_values_high = [10,100,1000] ##为了减少调试时间，故就三个数据

print("这是边长为一的正方形")
for n in n_values:
    pi_estimate = MonteCarlo_1(n)
    print(f"投点数量为{n}时，圆周率的估算值为: {pi_estimate}")

print("这是边长为二的正方形")
for n in n_values:
    pi_estimate = MonteCarlo_2(n)
    print(f"投点数量为{n}时，圆周率的估算值为: {pi_estimate}")

print("优化的方法")
print("边长为一")
for k in n_values_high:
    n = k**2
    pi_estimate = MonteCarloHigh(1,k)
    print(f"投点数量为{n}时，圆周率的估算值为: {pi_estimate}")

print("边长为二")
for k in n_values_high:
    n = k**2
    pi_estimate = MonteCarloHigh(2,k)
    print(f"投点数量为{n}时，圆周率的估算值为: {pi_estimate}")





