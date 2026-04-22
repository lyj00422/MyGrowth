import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
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

lr = LogisticRegression(max_iter=1000)
lr.fit(X_train, y_train)

# 5. 获取特征并将其与重要性配对
num_features = ['age', 'rank', 'finish_time']
cat_encoder = preprocessor.named_transformers_['cat']
cat_feature_names = cat_encoder.get_feature_names_out(['country'])
all_features = num_features + list(cat_feature_names)

coefficients = lr.coef_[0]

feature_importance = sorted(zip(all_features, coefficients), key=lambda x: abs(x[1]), reverse=True)

# 6. 可视化
plt.figure(figsize=(10, 6))
top_n = 10
top_features = feature_importance[:top_n]
names = [f[0] for f in top_features]
values = [f[1] for f in top_features]
colors = ['red' if v < 0 else 'blue' for v in values]
plt.barh(names, values, color=colors)
plt.xlabel('Coefficient Value')
plt.title('Top 10 Feature Importance (Logistic Regression)')
plt.axvline(x=0, color='black', linestyle='--')
plt.grid(axis='x', alpha=0.3)
plt.tight_layout()
plt.show()