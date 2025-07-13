import tkinter as tk
from tkinter import ttk, messagebox
import numpy as np
from ctypes import CDLL, c_int

# 加载C动态库
try:
    lib = CDLL('./libbanker.so')  # 在Linux/Mac环境下，C动态库为.so文件，而在Windows环境下，则是我们熟悉的.dll

except Exception as e:
    messagebox.showerror("错误", f"无法加载动态库: {str(e)}")
    exit()

# 定义C函数接口
lib.c_is_safe.argtypes = [
    np.ctypeslib.ndpointer(dtype=c_int, ndim=1),  # available
    np.ctypeslib.ndpointer(dtype=c_int, ndim=2),  # max
    np.ctypeslib.ndpointer(dtype=c_int, ndim=2),  # allocation
]
lib.c_is_safe.restype = c_int

lib.c_request_resources.argtypes = [
    np.ctypeslib.ndpointer(dtype=c_int),  # available
    np.ctypeslib.ndpointer(dtype=c_int),  # max
    np.ctypeslib.ndpointer(dtype=c_int),  # allocation
    c_int,                                # pid
    np.ctypeslib.ndpointer(dtype=c_int)   # request
]
lib.c_request_resources.restype = c_int

class BankersGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("银行家算法（Tkinter版） by ZhouYuwei")
        self.root.geometry("800x600")

        # 初始化数据结构
        self.num_processes = 5
        self.num_resources = 3
        self.available = np.zeros(self.num_resources, dtype=c_int)
        self.max = np.zeros((self.num_processes, self.num_resources), dtype=c_int)
        self.allocation = np.zeros((self.num_processes, self.num_resources), dtype=c_int)

        # 创建界面组件
        self.create_widgets()

    def create_widgets(self):
        # 可用资源输入
        ttk.Label(self.root, text="可用资源 (空格分隔):").grid(row=0, column=0, padx=5, pady=5)
        self.available_entry = ttk.Entry(self.root, width=30)
        self.available_entry.grid(row=0, column=1, padx=5, pady=5)
        self.available_entry.insert(0, "3 3 2")

        # 最大需求矩阵表格
        self.max_frame = ttk.LabelFrame(self.root, text="最大需求矩阵")
        self.max_frame.grid(row=1, column=0, columnspan=2, padx=10, pady=10)
        self.create_matrix_table(self.max_frame, "Max", [
            ["7", "5", "3"],
            ["3", "2", "2"],
            ["9", "0", "2"],
            ["2", "2", "2"],
            ["4", "3", "3"]
        ])

        # 已分配矩阵表格
        self.allocation_frame = ttk.LabelFrame(self.root, text="已分配矩阵")
        self.allocation_frame.grid(row=2, column=0, columnspan=2, padx=10, pady=10)
        self.create_matrix_table(self.allocation_frame, "Allocation", [
            ["0", "1", "0"],
            ["2", "0", "0"],
            ["3", "0", "2"],
            ["2", "1", "1"],
            ["0", "0", "2"]
        ])

        # 操作按钮
        self.btn_frame = ttk.Frame(self.root)
        self.btn_frame.grid(row=3, column=0, columnspan=2, pady=10)

        ttk.Button(self.btn_frame, text="安全检查", command=self.check_safety).pack(side=tk.LEFT, padx=5)
        ttk.Button(self.btn_frame, text="资源请求", command=self.request_resources_dialog).pack(side=tk.LEFT, padx=5)

    def create_matrix_table(self, parent, title, default_data):
        # 创建表格
        tree = ttk.Treeview(parent, columns=("R1", "R2", "R3"), show="headings")
        tree.heading("R1", text="R1")
        tree.heading("R2", text="R2")
        tree.heading("R3", text="R3")

        # 添加默认数据
        for i, row in enumerate(default_data):
            tree.insert("", "end", values=row, tags=(f"row{i}",))
            for j, val in enumerate(row):
                tree.set(tree.get_children()[i], f"R{j+1}", val)

        # 添加输入框
        tree.editable = {}
        for i, child in enumerate(tree.get_children()):
            tree.editable[child] = []
            for j, col in enumerate(["R1", "R2", "R3"]):
                entry = ttk.Entry(tree)
                entry.insert(0, tree.set(child, col))
                entry.grid(row=i, column=j, in_=tree)
                tree.editable[child].append(entry)

        tree.pack(padx=10, pady=10)
        return tree

    def get_matrix_data(self, tree):
        # 从表格获取数据
        data = []
        for child in tree.get_children():
            row = [int(entry.get()) for entry in tree.editable[child]]
            data.append(row)
        return np.array(data, dtype=c_int)

    def check_safety(self):
        try:
            # 获取输入数据
            self.available = np.array(
                [int(x) for x in self.available_entry.get().split()],
                dtype=c_int
            )
            self.max = self.get_matrix_data(self.max_frame.winfo_children()[0])
            self.allocation = self.get_matrix_data(self.allocation_frame.winfo_children()[0])

            # 调用C函数
            result = lib.c_is_safe(self.available, self.max, self.allocation)

            # 显示结果
            messagebox.showinfo("安全检查结果",
                                "系统处于安全状态" if result else "系统处于不安全状态！")

        except Exception as e:
            messagebox.showerror("输入错误", f"数据格式错误: {str(e)}")

    def request_resources_dialog(self):
        # 创建资源请求对话框
        dialog = tk.Toplevel(self.root)
        dialog.title("资源请求")

        ttk.Label(dialog, text="进程ID (0-4):").grid(row=0, column=0)
        pid_entry = ttk.Entry(dialog)
        pid_entry.grid(row=0, column=1)

        ttk.Label(dialog, text="请求资源 (空格分隔):").grid(row=1, column=0)
        request_entry = ttk.Entry(dialog)
        request_entry.grid(row=1, column=1)

        def submit():
            try:
                pid = int(pid_entry.get())
                request = np.array(
                    [int(x) for x in request_entry.get().split()],
                    dtype=c_int
                )

                # 调用C函数
                result = lib.c_request_resources(
                    self.available, self.max, self.allocation,
                    pid, request
                )

                # 处理结果
                results = {
                    1: "分配成功，系统保持安全",
                    0: "分配导致系统不安全",
                    -1: "错误：请求超过最大需求",
                    -2: "错误：资源不足"
                }
                messagebox.showinfo("请求结果", results.get(result, "未知错误"))
                dialog.destroy()

            except Exception as e:
                messagebox.showerror("输入错误", f"无效输入: {str(e)}")

        ttk.Button(dialog, text="提交", command=submit).grid(row=2, columnspan=2)

if __name__ == "__main__":
    root = tk.Tk()
    app = BankersGUI(root)
    root.mainloop()