import os

def generate_links_sorted(root_dir, output_file):
    links = []

    for dirpath, dirnames, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith('.md') and filename != os.path.basename(output_file):
                relative_path = os.path.relpath(os.path.join(dirpath, filename), root_dir)
                link_name = os.path.splitext(filename)[0]
                links.append((link_name, relative_path))

    # 按照链接名称进行排序
    links.sort(key=lambda x: x[0].lower())

    with open(output_file, 'w') as f_out:
        for link_name, relative_path in links:
            f_out.write(f'- [{link_name}]({relative_path})\n')

root_directory = './'  # 设置为你的项目根目录
output_md = 'main.md'  # 生成的目录文件名称
generate_links_sorted(root_directory, output_md)