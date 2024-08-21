import os
import re

def update_table_with_links(md_file):
    # 读取现有的MD文件内容
    with open(md_file, 'r', encoding='utf-8-sig') as f:
        lines = f.readlines()

    # 搜集第一列的名称
    updated_lines = []
    for line in lines:
        # 使用正则表达式匹配表格行，并提取第一列内容
        match = re.match(r'\| *([^|]+) *\|', line)
        if match:
            name = match.group(1).strip()
            # 在根目录寻找匹配的文件
            for root, dirs, files in os.walk('.'):
                for file in files:
                    if file.lower().startswith(name.lower()) and file.endswith('.md'):
                        # 构建相对路径的超链接
                        relative_path = os.path.relpath(os.path.join(root, file), '.')
                        # 用超链接替换原始名称
                        line = line.replace(name, f'[{name}]({relative_path})')
                        break
        updated_lines.append(line)

    # 将更新后的内容写回文件
    with open(md_file, 'w', encoding='utf-8') as f:
        f.writelines(updated_lines)

md_file = 'Meta.md'  # 替换为你的MD文件名称
update_table_with_links(md_file)