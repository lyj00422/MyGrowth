import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.neighbors import KNeighborsClassifier
#拓展思考2：探索k值对knn模型复杂度的影响

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
k_range = range(1,20)
train_acc = []
test_acc = []

for k in k_range:
    knn_temp = KNeighborsClassifier(n_neighbors=k)
    knn_temp.fit(X_train, y_train)
    train_acc.append(knn_temp.score(X_train, y_train))
    test_acc.append(knn_temp.score(X_test, y_test))

best_k = k_range[test_acc.index(max(test_acc))]
print(f"最优k值：{best_k},测试准确率：{max(test_acc):.4f}")

plt.figure(figsize=(10,5))
plt.plot(k_range, train_acc, 'b-o', label='Training accuracy')
plt.plot(k_range, test_acc, 'r-s', label='Test accuracy')
plt.xlabel('Number of neighbors K')
plt.ylabel('Accuracy')
plt.title('KNN Accuracy vs. K Value')
plt.legend()
plt.grid(True)
plt.show()

