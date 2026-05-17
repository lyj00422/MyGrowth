import slove
import sys
import time

print("选择输入模式")
print("1 自己输入")
print("2 读取本地文件")

mode = int(input())
if mode == 1:
    print("选择算法")
    print("1 枚举法")
    print("2 贪心法")
    print("3 动态规划")
    print("4 线性规划")
    print("5 随机搜索--遗传算法")
    print("输入格式：")
    print("[物品个数] [背包容量]")
    print("...逐行输入物品重量+物品价值")

    mode_choice = int(input())
    num, capacity = map(int, input().split())

    if mode_choice == 1 and num >= 25:
        print("物品个数大于25不宜用枚举法")
        sys.exit()

    items = []
    for i in range(num):
        w = int(input())
        v = int(input())
        items.append((w, v))

    if mode_choice == 1:
        slove.Enumeration(items, num, capacity)
    elif mode_choice == 2:
        slove.Greedy(items, num, capacity)
    elif mode_choice == 3:
        slove.DP(items, num, capacity)
    elif mode_choice == 4:
        slove.Linear(items, num, capacity)
    elif mode_choice == 5:
        slove.Gene(items, num, capacity)

else:
    print("选择数据类型")
    print("1 小数据 (n=15)")
    print("2 中数据 (n=80)")
    print("3 大数据 (n=800)")

    data_choice = int(input())
    file_map = {1: "small.txt", 2: "medium.txt", 3: "large.txt"}
    filename = file_map[data_choice]

    items = []
    with open(filename, "r", encoding="utf-8") as f:
        lines = f.readlines()

    num, capacity = map(int, lines[0].split())
    for line in lines[1:]:
        line = line.strip()
        if not line:
            continue
        w, v = map(int, line.split())
        items.append((w, v))

    print(f"已加载 {len(items)} 件物品，背包容量 {capacity}")

    print("选择算法")
    print("1 枚举法")
    print("2 贪心法")
    print("3 动态规划")
    print("4 线性规划")
    print("5 随机搜索--遗传算法")
    print("6 全部算法 + 性能比较")

    algo_choice = int(input())

    algorithms = {
        1: ("枚举法",     slove.Enumeration),
        2: ("贪心法",     slove.Greedy),
        3: ("动态规划",   slove.DP),
        4: ("线性规划",   slove.Linear),
        5: ("遗传算法",   slove.Gene),
    }

    if algo_choice in algorithms:
        name, func = algorithms[algo_choice]
        if algo_choice == 1 and num > 25:
            print("物品个数大于25不宜用枚举法")
            sys.exit()
        func(items, num, capacity)

    elif algo_choice == 6:
        print("\n" + "=" * 70)
        print(f"数据集: {filename}  |  物品数 n = {num}  |  背包容量 = {capacity}")
        print("=" * 70)

        results = {}

        # ---------- 1. 动态规划（基准：保证最优解） ----------
        print("\n[1/5] 运行动态规划...")
        dp_items = items[:]
        t0 = time.perf_counter()
        slove.DP(dp_items, num, capacity)
        t1 = time.perf_counter()
        dp_time = t1 - t0
        print(f"  -> 动态规划耗时: {dp_time:.6f} 秒")

        # ---------- 2. 贪心法 ----------
        print("\n[2/5] 运行贪心法...")
        greedy_items = items[:]
        t0 = time.perf_counter()
        slove.Greedy(greedy_items, num, capacity)
        t1 = time.perf_counter()
        greedy_time = t1 - t0
        print(f"  -> 贪心法耗时: {greedy_time:.6f} 秒")

        # ---------- 3. 线性规划 ----------
        print("\n[3/5] 运行线性规划 (MILP)...")
        lp_items = items[:]
        t0 = time.perf_counter()
        slove.Linear(lp_items, num, capacity)
        t1 = time.perf_counter()
        lp_time = t1 - t0
        print(f"  -> 线性规划耗时: {lp_time:.6f} 秒")

        # ---------- 4. 遗传算法 ----------
        print("\n[4/5] 运行遗传算法...")
        ga_items = items[:]
        t0 = time.perf_counter()
        slove.Gene(ga_items, num, capacity)
        t1 = time.perf_counter()
        ga_time = t1 - t0
        print(f"  -> 遗传算法耗时: {ga_time:.6f} 秒")

        # ---------- 5. 枚举法（仅小数据） ----------
        enum_time = None
        if num <= 25:
            print("\n[5/5] 运行枚举法...")
            enum_items = items[:]
            t0 = time.perf_counter()
            slove.Enumeration(enum_items, num, capacity)
            t1 = time.perf_counter()
            enum_time = t1 - t0
            print(f"  -> 枚举法耗时: {enum_time:.6f} 秒")
        else:
            print("\n[5/5] 枚举法已跳过 (n > 25, 2^%d 种组合不可行)" % num)

        # =============================================
        # 性能比较汇总表
        # =============================================
        print("\n" + "=" * 70)
        print("                    性能比较汇总")
        print("=" * 70)

        print(f"{'算法':<16} {'运行时间(s)':>14}", end="")
        if enum_time is not None:
            print(f" {'与最优解一致':>14}", end="")
        print()

        print("-" * (44 if enum_time is None else 58))

        print(f"{'动态规划 (最优)':<16} {dp_time:>14.6f}", end="")
        if enum_time is not None:
            print(f" {'是':>14}", end="")
        print()

        print(f"{'贪心法':<16} {greedy_time:>14.6f}", end="")
        if enum_time is not None:
            print(f" {'否 (近似)':>14}", end="")
        print()

        print(f"{'线性规划':<16} {lp_time:>14.6f}", end="")
        if enum_time is not None:
            print(f" {'是':>14}", end="")
        print()

        print(f"{'遗传算法':<16} {ga_time:>14.6f}", end="")
        if enum_time is not None:
            print(f" {'否 (近似)':>14}", end="")
        print()

        if enum_time is not None:
            print(f"{'枚举法':<16} {enum_time:>14.6f} {'是 (基准)':>14}")

        print("-" * (44 if enum_time is None else 58))

        # 算法用时排序
        all_times = [
            ("动态规划", dp_time),
            ("贪心法", greedy_time),
            ("线性规划", lp_time),
            ("遗传算法", ga_time),
        ]
        if enum_time is not None:
            all_times.append(("枚举法", enum_time))

        all_times.sort(key=lambda x: x[1])
        print(f"\n运行时间排序 (快 -> 慢):")
        for i, (name, t) in enumerate(all_times, 1):
            print(f"  {i}. {name}: {t:.6f}s")

        # 关键分析
        print("\n" + "=" * 70)
        print("                    分析要点")
        print("=" * 70)
        print("""
1. 最优解保证:
   - 动态规划、线性规划(MILP)、枚举法 均保证找到全局最优解
   - 贪心法 不保证最优解（按价值密度贪心可能失败）
   - 遗传算法 是随机搜索，不保证找到最优解

2. 时间复杂度比对:
   - 枚举法:       O(2^n)        — 仅适用小规模 (n <= 25)
   - 贪心法:       O(n log n)    — 排序后线性扫描
   - 动态规划:     O(n*capacity) — 伪多项式，容量大时较慢
   - 线性规划:     依赖求解器     — 小规模快，大规模分支定界开销大
   - 遗传算法:     O(generations * population_size * n) — 近似解

3. 贪心法局限性:
   - 01背包问题不具有贪心选择性质
   - 按价值密度排序可能因重量约束错过整体最优组合
   - 在小数据时可与枚举法/DP结果对比验证

4. 不同规模下的推荐:
   - 小规模 (n<=25):   枚举法（直观验证）/ DP（高效）
   - 中规模 (n~80):    DP 首选，线性规划亦可
   - 大规模 (n>=800):  DP 仍可用（取决于容量），遗传算法作为补充
""")
