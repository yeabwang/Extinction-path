import os

def print_tree(start_path=".", indent=""):
    """Recursively prints the directory tree"""
    items = sorted(os.listdir(start_path))
    for index, item in enumerate(items):
        path = os.path.join(start_path, item)
        is_last = index == len(items) - 1
        connector = "└── " if is_last else "├── "
        print(indent + connector + item)
        if os.path.isdir(path):
            new_indent = indent + ("    " if is_last else "│   ")
            print_tree(path, new_indent)

if __name__ == "__main__":
    print_tree(".")
