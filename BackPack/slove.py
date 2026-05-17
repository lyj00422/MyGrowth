import numpy as np
from scipy.optimize import milp,LinearConstraint,Bounds
import random
#枚举法
def Enumeration(item, n, weight):
    max_value = 0
    best_choice = []
    #用二进制记录每个物品选择与否
    for state in range(1 << n):
        total_value = 0
        total_weight = 0
        choice = []
        #遍历每一个物品
        for i in range(n):
            if state & (1 << i):#如果取它
                w, v = item[i]
                total_weight += w
                total_value += v
                choice.append(i)
        #符合条件就更新结果
        if total_weight <= weight and total_value > max_value:
            max_value = total_value
            best_choice = choice

    print("枚举法")
    print(f"枚举法给出的最大价值是{max_value}")
    print(f"枚举法给出的选择是{best_choice}")
#贪心算法
def Greedy(items, n, weight):
    temp = []
    for i in range(n):
        w,v = items[i]
        temp.append((i,w,v))#保留原来的顺序好输出选择
    #根据每单位重量对应的价值
    temp.sort(key = lambda x : x[2]/x[1], reverse = True)
    total_weight = 0
    total_value = 0
    choice = []

    for i,w,v in temp:
        if total_weight+w <= weight:
            total_weight += w
            total_value += v
            choice.append(i)

    print("贪心法")
    print(f"贪心法求得的最大价值是{total_value}")
    print(f"贪心法选择的物品是{choice}")

#动态规划
def DP(items, n, weight):
    dp = [[0]*(weight+1) for _ in range(n+1)]#创建（n+1）*（weight+1)的二维数组，dp[i][j]是考虑在j重量的前提下考虑i个武平的最大价值
    choice = []
    for i in range(1,n+1):
        w,v = items[i-1]

        for j in range(weight+1):
            #情况1；不选这个物品
            dp[i][j] = dp[i-1][j]

            #情况2：选择这个物品
            if j >= w:
                dp[i][j] = max(dp[i][j], dp[i-1][j-w]+v)

    temp = weight
    for i in range(n,0,-1):
        if dp[i][temp] != dp[i-1][temp]:
            choice.append(i-1)

            w,v = items[i-1]
            temp -= w

    print("动态规划")
    print(f"动态规划求得的最佳价值是{dp[n][weight]}")
    print(f"动态规划选择的物品是{choice}")

#线性规划
def Linear(items, n, weight):
    # 处理空物品情况
    if n == 0:
        return 0, []

    # 从 items 中分别取出重量和价值
    weights = np.array([items[i][0] for i in range(n)])
    values = np.array([items[i][1] for i in range(n)])

    # scipy 的 milp 默认是求最小值
    # 01背包要求最大化价值，所以这里取负号
    c = -values

    # 背包重量约束
    A = weights.reshape(1, -1) #变成二维矩阵
    constraints = LinearConstraint(
        A,
        -np.inf,
        weight
    )
    bounds = Bounds(0, 1)

    # 每个变量必须是整数
    integrality = np.ones(n)

    result = milp(
        c=c,
        constraints=constraints,
        bounds=bounds,
        integrality=integrality
    )

    # 求解器返回的结果可能是浮点数，所以四舍五入成整数
    x = np.round(result.x).astype(int)

    # 计算总价值和总重量
    max_value = values @ x

    # 记录选择了哪些物品
    chosen_items = []
    for i in range(n):
        if x[i] == 1:
            chosen_items.append(i)

    print("线性规划")
    print(f"线性规划算出的最大价值是{max_value}")
    print(f"线性规划选择的物品是{chosen_items}")


#随机搜索
#遗传算法(不保证找到全局最优解，但是可以找到近似解）
def Gene(items, n, weight):
    population_size = 50
    generations = 200
    mutation_rate = 0.02

    def total_weight(choice):
        return sum(items[i][0] for i in range(n) if choice[i] == 1)

    def total_value(choice):
        return sum(items[i][1] for i in range(n) if choice[i] == 1)

    def fitness(choice):
        if total_weight(choice) <= weight:
            return total_value(choice)
        return 0

    def random_choice():
        return [random.randint(0, 1) for _ in range(n)]

    def repair(choice):
        choice = choice[:]

        while total_weight(choice) > weight:
            selected = [i for i in range(n) if choice[i] == 1]

            if not selected:
                break

            worst = min(selected, key=lambda i: items[i][1] / items[i][0])
            choice[worst] = 0

        return choice

    def select_parent(population):
        candidates = random.sample(population, 3)
        return max(candidates, key=fitness)

    def crossover(parent1, parent2):
        if n <= 1:
            return parent1[:]

        point = random.randint(1, n - 1)
        return parent1[:point] + parent2[point:]

    def mutate(choice):
        new_choice = choice[:]

        for i in range(n):
            if random.random() < mutation_rate:
                new_choice[i] = 1 - new_choice[i]

        return new_choice

    population = []

    for _ in range(population_size):
        choice = random_choice()
        choice = repair(choice)
        population.append(choice)

    best_choice = population[0]
    best_value = fitness(best_choice)

    for _ in range(generations):
        new_population = []

        current_best = max(population, key=fitness)
        current_best_value = fitness(current_best)

        if current_best_value > best_value:
            best_value = current_best_value
            best_choice = current_best[:]

        new_population.append(current_best[:])

        while len(new_population) < population_size:
            parent1 = select_parent(population)
            parent2 = select_parent(population)

            child = crossover(parent1, parent2)
            child = mutate(child)
            child = repair(child)

            new_population.append(child)

        population = new_population

    # 将二进制列表转换为索引列表，以匹配测试代码格式
    best_indices = [i for i in range(n) if best_choice[i] == 1]

    print("遗传算法")
    print(f"遗传算法算出的最大价值是{best_value}")
    print(f"遗传算法选择的物品是{best_indices}")


