import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression

# 1. 数据加载与清洗
data = pd.read_csv(
    './bm_results2012.txt',
    quotechar='"',
    delimiter=',',
    header=None,
    names=['name', 'gender', 'age', 'rank', 'country', 'finish_time']
)
data_clean = data.dropna()

# 2. 特征与标签
X = data_clean[['age', 'rank', 'country', 'finish_time']]
y = data_clean['gender']

# 3. 特征预处理
preprocessor = ColumnTransformer(
    transformers=[
        ('num', StandardScaler(), ['age', 'rank', 'finish_time']),
        ('cat', OneHotEncoder(handle_unknown='ignore'), ['country'])
    ]
)
X_processed = preprocessor.fit_transform(X)

# 4. 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(
    X_processed, y, test_size=0.2, random_state=42, stratify=y
)

# 5. KNN分类器
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
knn_acc = knn.score(X_test, y_test)
print(f"KNN测试集准确率: {knn_acc:.4f}")

#6. 逻辑回归分类器
lr = LogisticRegression(max_iter=1000)
lr.fit(X_train, y_train)
lr_acc = lr.score(X_test, y_test)
print(f"逻辑回归测试集准确率: {lr_acc:.4f}")

# 7. 可视化
plt.figure(figsize=(12, 5))
mask_m = data_clean['gender'] == 'M'
mask_f = data_clean['gender'] == 'F'
plt.scatter(data_clean[mask_m]['age'], data_clean[mask_m]['finish_time'], c='blue', alpha=0.5, label='Male')
plt.scatter(data_clean[mask_f]['age'], data_clean[mask_f]['finish_time'], c='red', alpha=0.5, label='Female')
plt.xlabel('Age')
plt.ylabel('Finish Time (minutes)')
plt.title('Age vs. Finish Time by Gender')
plt.legend()
plt.show()