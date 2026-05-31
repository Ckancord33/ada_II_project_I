import tkinter as tk
import os
import re


def centrar_ventana(ventana):
    ventana.update_idletasks()
    
    # 1. Obtener tamaño actual (basado en los widgets)
    ancho_ventana = ventana.winfo_reqwidth()
    alto_ventana = ventana.winfo_reqheight()
    
    # 2. Obtener tamaño de pantalla
    ancho_pantalla = ventana.winfo_screenwidth()
    alto_pantalla = ventana.winfo_screenheight()
    
    # 3. Calcular coordenadas
    x = (ancho_pantalla // 2) - (ancho_ventana // 2)
    y = (alto_pantalla // 2) - (alto_ventana // 2)
    
    # 4. FIJAR SOLO LA POSICIÓN (Omitimos el "Ancho x Alto")
    # Nota que el string solo tiene el +X y +Y
    ventana.geometry(f"+{int(x)}+{int(y)}")

def ajustar_alto_segun_contenido(widget):
    contenido = widget.get("1.0", tk.END).split('\n')
    
    num_lineas = len(contenido)
    nuevo_alto = min(max(num_lineas, 5), 30)
    
    widget.config(height=nuevo_alto)

def limpiar_todo(widget):
    widget.config(state="normal")
    widget.delete("1.0", tk.END)
    ajustar_alto_segun_contenido(widget)



# Métodos para la generación de archivos


def _safe_alg_name(alg_name: str) -> str:
    s = alg_name.strip()
    s = s.replace(" ", "_")
    s = re.sub(r"[^A-Za-z0-9_\-]", "", s)
    return s


def _generate_unique_path(dirpath: str, base_name: str, ext: str = ".txt") -> str:
    candidate = os.path.join(dirpath, base_name + ext)
    if not os.path.exists(candidate):
        return candidate

    i = 1
    while True:
        candidate = os.path.join(dirpath, f"{base_name}_{i}{ext}")
        if not os.path.exists(candidate):
            return candidate
        i += 1


def _parse_solution_from_stdout(stdout: str):
    m_cost = re.search(r"El costo es:\s*([-]?\d+)", stdout)
    cost = m_cost.group(1) if m_cost else None

    m_braces = re.search(r"\{([^}]*)\}", stdout)
    if m_braces:
        nums = re.findall(r"-?\d+", m_braces.group(1))
        if nums:
            return cost, nums
        
    m_sol = re.search(r"solucion es[:\-]?\s*(?:\{([^}]*)\}|([-?\d\s]+))", stdout, flags=re.I)
    if m_sol:
        group = m_sol.group(1) or m_sol.group(2)
        if group:
            nums = re.findall(r"-?\d+", group)
            if nums:
                return cost, nums

    all_nums = re.findall(r"-?\d+", stdout)
    if not all_nums:
        return None, None

    if cost is None:
        return all_nums[-1], all_nums[:-1]
    else:
        nums = all_nums[:]
        for i in range(len(nums) - 1, -1, -1):
            if nums[i] == cost:
                pis = nums[:i] + nums[i+1:]
                return cost, pis

        return cost, nums[:-1]


def create_solution_file(stdout: str, input_path: str, algorithm_name: str, out_dir: str = None) -> str:
    if out_dir is None:
        ui_dir = os.path.dirname(os.path.abspath(__file__))
        out_dir = os.path.join(ui_dir, "output")

    os.makedirs(out_dir, exist_ok=True)

    base_input = os.path.splitext(os.path.basename(input_path))[0]
    alg_safe = _safe_alg_name(algorithm_name)
  
    if base_input.lower().endswith(f"_{alg_safe.lower()}"):
        base_name = base_input
    else:
        base_name = f"{base_input}_{alg_safe}"

    target_path = _generate_unique_path(out_dir, base_name, ".txt")

    cost, pis = _parse_solution_from_stdout(stdout)
    with open(target_path, "w", encoding="utf-8") as f:
        if cost is None:
            f.write(stdout)
        else:
            f.write(str(cost) + "\n")
            for p in pis:
                f.write(str(p) + "\n")

    return target_path