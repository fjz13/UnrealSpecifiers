import pandas as pd

# 读取Markdown文件中的表格
df = pd.read_csv("Meta.md", sep="|", skiprows=[0, 1])

# 删除空列（因为Markdown表格的格式有时会导致空列）
df = df.dropna(axis=1, how="all")

# 排序第二列（假设第二列是列名为'Name'）
df = df.sort_values(by='Name')

# 将排序后的表格保存回Markdown文件
df.to_csv("sorted_table.md", sep="|", index=False)