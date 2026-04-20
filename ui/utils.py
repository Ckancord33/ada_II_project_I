import tkinter as tk

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