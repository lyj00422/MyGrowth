import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_curve,auc
#扩展思考1：AUC和ROC

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

#6. 逻辑回归分类器
lr = LogisticRegression(max_iter=1000)
lr.fit(X_train, y_train)

#KNN和LR的ROC
knn_proba = knn.predict_proba(X_test)[:, 1]
lr_proba = lr.predict_proba(X_test)[:, 1]

knn_fpr, knn_tpr, _ = roc_curve(y_test, knn_proba, pos_label='M')  # 'M' 为正类
knn_auc = auc(knn_fpr, knn_tpr)

lr_fpr, lr_tpr, _ = roc_curve(y_test, lr_proba, pos_label='M')  # 'M' 为正类
lr_auc = auc(lr_fpr, lr_tpr)

plt.figure(figsize=(8, 6))
plt.plot(knn_fpr, knn_tpr, label=f'KNN (AUC = {knn_auc:.3f})', lw=2)
plt.plot(lr_fpr, lr_tpr, label=f'Logistic Regression (AUC = {lr_auc:.3f})', lw=2)
plt.plot([0, 1], [0, 1], 'k--', label='Random Classifier')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate (FPR)')
plt.ylabel('True Positive Rate (TPR)')
plt.title('ROC Curves on Test Set')
plt.legend(loc='lower right')
plt.grid(alpha=0.3)
plt.show()