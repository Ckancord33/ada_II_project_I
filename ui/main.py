import tkinter as tk
from tkinter import messagebox, ttk, filedialog
import subprocess
import os
from utils import centrar_ventana, ajustar_alto_segun_contenido,limpiar_todo
    
def seleccionar_y_leer():
    # Obtener la ruta del archivo
    ruta = filedialog.askopenfilename()

    if ruta:
        try:
            with open(ruta, 'r', encoding='utf-8') as archivo:
                contenido_string = archivo.read()
            
            text_area.insert("1.0", contenido_string)
            ajustar_alto_segun_contenido(text_area)
            
            root.geometry("") 
            centrar_ventana(root)
            
        except Exception as e:
            print(f"Error al leer el archivo: {e}")

def enviar_todo():
    ouput_text_area.config(state="normal")
    
    contenido_txt = text_area.get("1.0", tk.END).strip()
    opcion_seleccionada = combo_opcion.get()

    # 1. Crear el archivo temporal
    ruta_txt = "temp_input.txt"
    with open(ruta_txt, "w") as f:
        f.write(contenido_txt)

    # 2. Ruta del binario
    ruta_exe = os.path.join("..","bin", "main")

    try:
        proceso = subprocess.run(
            [ruta_exe, ruta_txt, opcion_seleccionada],
            capture_output=True,
            text=True
        )

        if proceso.returncode == 0:
            salida_completa = proceso.stdout
            
            ouput_text_area.insert(tk.END,salida_completa)
            ajustar_alto_segun_contenido(ouput_text_area)
            ouput_text_area.config(state="disabled")
            
            root.geometry("") 
            centrar_ventana(root)
            
        else:
            messagebox.showerror("Error C++", proceso.stderr)

    except Exception as e:
        messagebox.showerror("Error de ejecución", str(e))


# --- Interfaz Gráfica ---
root = tk.Tk()
root.title("Consola de Control")

# Sección 1: Boton para subir archivo
tk.Label(root, text="Seleccione el archivo con el problema:").grid(row=2, column=0,padx=10,pady=10)
boton = tk.Button(root, text="Abrir Archivo", command=seleccionar_y_leer)
boton.grid(row=3, column=0, padx=10)

# Sección 2: El archivo en texto 
tk.Label(root, text="Contenido del archivo (.txt):").grid(row=0, column=0,padx=10,pady=30)
text_area = tk.Text(root, height=12, width=60)
text_area.grid(row=1, column=0,padx=10,sticky="nsew")

# Sección 3: Opción 
tk.Label(root, text="Selecciona una algoritmo:").grid(row=0, column=2,padx=10,pady=30)
combo_opcion = ttk.Combobox(root, values=["naive solution", "dynamic solution (bottom up)", "dynamic solution (top down)", "greedy solution"], state="readonly")
combo_opcion.current(0) # Valor por defecto
combo_opcion.grid(row=1, column=2,padx=10)

# Sección 4: Resultados
tk.Label(root, text="Resultados obtenidos:").grid(row=0, column=3,padx=10,pady=30)
ouput_text_area = tk.Text(root, height=12, width=60, state="disabled", bg="#f0f0f0",font=("Consolas", 10))
ouput_text_area.grid(row=1, column=3,padx=10,sticky="nsew")

# Botón de envío
btn_run = tk.Button(root, text="Calcular Resultado", bg="#4CAF50", fg="white", command=enviar_todo)
btn_run.grid(row=2, column=3,padx=10,pady=10)

# Botón de envío
btn_clear = tk.Button(root, text="Limpiar resultados",bg="#808080",fg="white", command=lambda : limpiar_todo(ouput_text_area))
btn_clear.grid(row=3, column=3,padx=10,pady=10)

centrar_ventana(root)
root.mainloop()